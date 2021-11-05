#include "jlWorld.h"
#include <jlColor.h>
#include <jlVector4.h>
#include <jlTimer.h>
#include <jlRandom.h>
//Tracers
#include "jlTSingleSphere.h"
#include "jlTMultipleObjects.h"
#include "jlTRayCast.h"
//Geometri objects
#include "jlGOPlane.h"
//Samplers
#include "jlSJittered.h"
//Cameras
#include "jlCPinhole.h"
//Lights
#include "jlLAmbient.h"
#include "jlPointLight.h"
//Materials
#include "jlMMatte.h"
#include "jlMPhong.h"

void
jlWorld::modifyPointlight() {
  ImGui::Begin("pointLight");
  auto point = std::static_pointer_cast<jlPointLight>(m_pPointLight);
  auto pos = point->getPosition();
  ImGui::DragFloat3("Position", &pos.x);
  point->setPosition(pos);

  auto col = point->getColor();
  ImGui::ColorEdit3("Position", &col.x);
  point->setColor(col);

  ImGui::End();
}

void
jlWorld::imguiAmbientLight() {
  ImGui::Begin("Ambient Light");
  auto al = std::static_pointer_cast<jlLAmbient>(m_pAmbientLight);
  auto ls = al->getRadianceScalingFactor();
  auto col = al->getColor();

  ImGui::DragFloat("radiance scaling factor ", &ls, 0.05f);
  ImGui::ColorEdit3("Position", &col.x);

  al->setRadianceScalingFactor(ls);
  al->setColor(col);

  ImGui::End();
}

void
jlWorld::imguiShowObjects() {
  ImGui::Begin("SceneGraph");
  ImGui::CloseCurrentPopup();

  uint32 objects = (uint32)m_sceneObjects.size();
  for (uint32 i = 0; i < objects; i++) {
    String name = "object " + std::to_string(i);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth |
                               ImGuiTreeNodeFlags_OpenOnArrow |
                               ImGuiTreeNodeFlags_OpenOnDoubleClick |
                               ImGuiTreeNodeFlags_Leaf |
                               ImGuiTreeNodeFlags_Bullet;
    if (m_selectedObject == m_sceneObjects[i]) {
      flags |= ImGuiTreeNodeFlags_Selected;
    }
    ImGui::TreeNodeEx(name.c_str(), flags);
    if (ImGui::IsItemClicked()) {
      m_selectedObject = m_sceneObjects[i];
    }
    ImGui::TreePop();
  }
  ImGui::End();
  //if (nullptr == object->getParent()) {
  //  flags |= ImGuiTreeNodeFlags_DefaultOpen;
  //  ImGui::SetNextTreeNodeOpen(true);
  //}
}

void
jlWorld::imguiShowObjectProperties() {
  if (!m_selectedObject) {
    return;
  }
  ImGui::Begin("object Properties");
  switch (m_selectedObject->m_type) {
   case GEOMETRITYPE::PLANE:
    imguiShowPlaneProperties();
    break;
   case GEOMETRITYPE::SPHERE:
    imguiShowSphereProperties();
    break;
   case GEOMETRITYPE::BOX:
    imguiShowBoxProperties();
    break;
   case GEOMETRITYPE::CYLINDER:
    imguiShowCylindreProperties();
    break;
   default:
    break;
  }

  imguiShowMaterialProperties(m_selectedObject->m_pMaterial);
  ImGui::End();
}

void
jlWorld::imguiShowSphereProperties() {
  auto sphere = std::static_pointer_cast<jlSphere>(m_selectedObject);
  ImGui::DragFloat3("Position", &sphere->m_position.x);
  ImGui::DragFloat("Ratio", &sphere->m_radius, 0.5f, 0.0f);
}

void
jlWorld::imguiShowBoxProperties() {

}

void
jlWorld::imguiShowPlaneProperties() {
  auto plane = std::static_pointer_cast<jlPlane>(m_selectedObject);
  ImGui::DragFloat3("Position", &plane->m_point.x);
  ImGui::DragFloat3("Normal", &plane->m_normal.x, 0.05f, 0.0f,1.0f);
}

void
jlWorld::imguiShowCylindreProperties() {

}

void
jlWorld::imguiShowMaterialProperties(SPtr<jlMaterial> material) {
  switch (material->m_type) {
   case MATERIALTYPE::MATTE:
    imguiShowMatteMaterialProperties(material);
    break;
   case MATERIALTYPE::PHONG:
    imguiShowPhongMaterialProperties(material);
    break;
   case MATERIALTYPE::PLASTIC:
    imguiShowPlasticMaterialProperties(material);
    break;
   default:
    break;
  }
}

void
jlWorld::imguiShowMatteMaterialProperties(SPtr<jlMaterial> material) {
  auto matte = std::static_pointer_cast<jlMMatte>(material);
  auto color = matte->m_diffuseBRDF->m_cd;
  ImGui::ColorEdit3("Color", &color.r);
  ImGui::DragFloat("Ambient reflection coefficient",
                   &matte->m_ambientBRDF->m_kd,
                   0.05f,
                   0.00f,
                   5.00f);
  ImGui::DragFloat("Diffuse reflection coefficient",
                   &matte->m_diffuseBRDF->m_kd,
                   0.05f,
                   0.00f,
                   5.00f);
  matte->setCd(color);
}

void
jlWorld::imguiShowPhongMaterialProperties(SPtr<jlMaterial> material) {
  auto phong = std::static_pointer_cast<jlMPhong>(material);
  auto color = phong->m_diffuseBRDF->m_cd;
  ImGui::ColorEdit3("Color", &color.r);
  ImGui::DragFloat("Ambient reflection coefficient",
                   &phong->m_ambientBRDF->m_kd,
                   0.05f,
                   0.00f,
                   5.00f);
  ImGui::DragFloat("Diffuse reflection coefficient",
                   &phong->m_diffuseBRDF->m_kd,
                   0.05f,
                   0.00f,
                   5.00f);
  ImGui::DragFloat("Specular reflection coefficient",
                   &phong->m_specularBRDF->m_ks,
                   0.05f,
                   0.00f,
                   5.00f);
  ImGui::DragInt("Specular reflection exponent", 
                 &phong->m_specularBRDF->m_exp, 
                 1.0f, 
                 0,
                 50);
  phong->setCd(color);
}

void
jlWorld::imguiShowPlasticMaterialProperties(SPtr<jlMaterial> material) {

}

void
jlWorld::imguiShowLights() {
  ImGui::Begin("SceneLights");
  ImGui::CloseCurrentPopup();
  uint32 lights = (uint32)m_sceneLights.size();
  for (uint32 i = 0; i < lights; i++) {
    String name = "Light " + std::to_string(i);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth |
      ImGuiTreeNodeFlags_OpenOnArrow |
      ImGuiTreeNodeFlags_OpenOnDoubleClick |
      ImGuiTreeNodeFlags_Leaf |
      ImGuiTreeNodeFlags_Bullet;
    if (m_selectedLight == m_sceneLights[i]) {
      flags |= ImGuiTreeNodeFlags_Selected;
    }
    ImGui::TreeNodeEx(name.c_str(), flags);
    if (ImGui::IsItemClicked()) {
      m_selectedLight = m_sceneLights[i];
    }
    ImGui::TreePop();
  }
  ImGui::End();
}

void
jlWorld::imguiShowLightProperties() {
  if (!m_selectedLight) {
    return;
  }
  ImGui::Begin("Light Properties");
  switch (m_selectedLight->m_type) {
   case LIGHTTYPES::AMBIENT:
    break;
   case LIGHTTYPES::POINT:
    imguiShowPointLightProperties();
    break;
   default:
    break;
  }
  ImGui::End();
}

void
jlWorld::imguiShowPointLightProperties() {
  auto point = std::static_pointer_cast<jlPointLight>(m_selectedLight);
  auto pos = point->getPosition();
  auto col = point->getColor();
  auto ls = point->getRadianceScalingFactor();
  ImGui::DragFloat3("Position", &pos.x);
  ImGui::DragFloat("Radiance Scaling Factor", &ls, 0.05f, -1.0f, 5.0f);
  ImGui::ColorEdit3("Position", &col.x);

  point->setPosition(pos);
  point->setRadianceScalingFactor(ls);
  point->setColor(col);
}

void
jlWorld::imguiShowCameraProperties() {
  ImGui::Begin("Camera Properties");
  String campos = "Eye " + m_pCamera->m_eye.getString();
  String camf = "Front " + m_pCamera->m_w.getString();
  String camr = "Right " + m_pCamera->m_u.getString();
  String camu = "Up " + m_pCamera->m_v.getString();
  ImGui::Text(campos.c_str());
  ImGui::Text(camf.c_str());
  ImGui::Text(camr.c_str());
  ImGui::Text(camu.c_str());
  ImGui::DragFloat("Speed", &m_pCamera->m_moveSpeed, 0.5f, 0.1f, 200.0f);
  ImGui::DragFloat("Rotation Speed", &m_pCamera->m_rotationPercen, 0.05f, 0.01f, 1.0f);
  ImGui::DragFloat("ExposureTime", &m_pCamera->m_exposureTime, 0.05f, 0.05f, 200.0f);
  ImGui::End();
}
