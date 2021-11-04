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
jlWorld::imguiShowObjectPropierties() {
  if (!m_selectedObject) {
    return;
  }
  ImGui::Begin("object propierties");
  switch (m_selectedObject->m_type) {
   case GEOMETRITYPE::PLANE:
    imguiShowPlanePropierties();
    break;
   case GEOMETRITYPE::SPHERE:
    imguiShowSpherePropierties();
    break;
   case GEOMETRITYPE::BOX:
    imguiShowBoxPropierties();
    break;
   case GEOMETRITYPE::CYLINDER:
    imguiShowCylindrePropierties();
    break;
   default:
    break;
  }

  imguiShowMaterialPropierties();
  ImGui::End();
}

void
jlWorld::imguiShowSpherePropierties() {
  auto sphere = std::static_pointer_cast<jlSphere>(m_selectedObject);
  ImGui::DragFloat3("Position", &sphere->m_position.x);
  ImGui::DragFloat("Ratio", &sphere->m_radius, 0.5f, 0.0f);
}

void
jlWorld::imguiShowBoxPropierties() {

}

void
jlWorld::imguiShowPlanePropierties() {

}

void
jlWorld::imguiShowCylindrePropierties() {

}

void
jlWorld::imguiShowMaterialPropierties() {
  switch (m_selectedObject->m_pMaterial->m_type) {
   case MATERIALTYPE::MATTE:
    imguiShowMatteMaterialPropierties();
    break;
   case MATERIALTYPE::PHONG:
    imguiShowPhongMaterialPropierties();
    break;
   case MATERIALTYPE::PLASTIC:
    imguiShowPlasticMaterialPropierties();
    break;
   default:
    break;
  }
}

void
jlWorld::imguiShowMatteMaterialPropierties() {
  auto matte = std::static_pointer_cast<jlMMatte>(m_selectedObject->m_pMaterial);
  auto color = matte->m_diffuseBRDF->m_cd;
  ImGui::ColorEdit3("Color", &color.r);
  ImGui::DragFloat("Ambient reflection coefficient",
                   &matte->m_ambientBRDF->m_kd,
                   0.05f);
  ImGui::DragFloat("Diffuse reflection coefficient",
                   &matte->m_diffuseBRDF->m_kd,
                   0.05f);
  matte->setCd(color);
}

void
jlWorld::imguiShowPhongMaterialPropierties() {
  auto phong = std::static_pointer_cast<jlMPhong>(m_selectedObject->m_pMaterial);
  auto color = phong->m_diffuseBRDF->m_cd;
  ImGui::ColorEdit3("Color", &color.r);
  ImGui::DragFloat("Ambient reflection coefficient",
                   &phong->m_ambientBRDF->m_kd,
                   0.05f,
                   0.00f,
                   1.00f);
  ImGui::DragFloat("Diffuse reflection coefficient",
                   &phong->m_diffuseBRDF->m_kd,
                   0.05f,
                   0.00f,
                   1.00f);
  ImGui::DragFloat("Specular reflection coefficient",
                   &phong->m_specularBRDF->m_ks,
                   0.05f,
                   0.00f,
                   1.00f);
  ImGui::DragInt("Specular reflection exponent", 
                 &phong->m_specularBRDF->m_exp, 
                 1.0f, 
                 0,
                 50);
  phong->setCd(color);
}

void
jlWorld::imguiShowPlasticMaterialPropierties() {

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
jlWorld::imguiShowLightPropierties() {
  if (!m_selectedLight) {
    return;
  }
  ImGui::Begin("Light propierties");
  switch (m_selectedLight->m_type) {
   case LIGHTTYPES::AMBIENT:
    break;
   case LIGHTTYPES::POINT:
    imguiShowPointLightPropierties();
    break;
   default:
    break;
  }
  ImGui::End();
}

void
jlWorld::imguiShowPointLightPropierties() {
  auto point = std::static_pointer_cast<jlPointLight>(m_selectedLight);
  auto pos = point->getPosition();
  ImGui::DragFloat3("Position", &pos.x);
  point->setPosition(pos);

  auto col = point->getColor();
  ImGui::ColorEdit3("Position", &col.x);
  point->setColor(col);
}
