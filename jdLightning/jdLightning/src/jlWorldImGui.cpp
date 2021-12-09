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
#include "jlGOBox.h"
#include "jlGOCylinder.h"
//Samplers
#include "jlSJittered.h"
//Cameras
#include "jlCPinhole.h"
//Lights
#include "jlLAmbient.h"
#include "jlPointLight.h"
#include "jlLAmbientOccluder.h"
//Materials
#include "jlMMatte.h"
#include "jlMPhong.h"
#include "jlMPlastic.h"

void
jlWorld::imguiAmbientLight() {
  ImGui::Begin("Ambient Light");
  int32 alightType = m_pAmbientLight->m_type;
  int32 alightindex = 0;
  int32 alightcurrentIndex = 0;
  switch (m_pAmbientLight->m_type)
  {
  case LIGHTTYPES::AMBIENT:
    alightType = LIGHTTYPES::AMBIENT;
    alightcurrentIndex = 0;
    break;
  case LIGHTTYPES::AMBIENTOCCLUDER:
    alightType = LIGHTTYPES::AMBIENTOCCLUDER;
    alightcurrentIndex = 1;
    break;
  }
  alightindex = alightcurrentIndex;
  ImGui::Separator();
  String OptionPreviw = m_ambientLightsListString[alightcurrentIndex];
  if (ImGui::BeginCombo("Ambient Lights", OptionPreviw.c_str())) {
    OptionPreviw = "";
    ImGui::ListBox("Alight",
      &alightindex,
      &m_ambientLightsListString[0],
      (int32)m_ambientLightsListString.size());
    ImGui::EndCombo();
  }
  if (alightindex != alightcurrentIndex) {
    
    if (alightindex == 0) {
      m_pAmbientLight = m_pDefaultLAmbient;
    }
    if (alightindex == 1) {
      m_pAmbientLight = m_pDefaultLAmbientOccluder;
    }
  }

  auto al = std::static_pointer_cast<jlLAmbient>(m_pAmbientLight);
  auto ls = al->getRadianceScalingFactor();
  auto col = al->getColor();

  ImGui::DragFloat("radiance scaling factor ", &ls, 0.05f);
  ImGui::ColorEdit3("Color", &col.x);
  if (m_pAmbientLight->m_type == LIGHTTYPES::AMBIENTOCCLUDER) {
    auto occluder = std::static_pointer_cast<jlLAmbientOccluder>(m_pAmbientLight);
    ImGui::ColorEdit3("minAmount", &occluder->m_minAmount.x);
  }
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
      m_selectedObjectIdx = i;
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
  
  int32 objType = (int32)m_selectedObject->m_type;
  ImGui::Separator();
  String OptionPreviw = m_geometriObjectsListString[objType];
  if (ImGui::BeginCombo("Objects", OptionPreviw.c_str())) {
    OptionPreviw = "";
    ImGui::ListBox("object", 
                   &objType,
                   &m_geometriObjectsListString[0],
                   (int32)m_geometriObjectsListString.size());
    ImGui::EndCombo();
  }
  if (objType != (int32)m_selectedObject->m_type) {
    auto material = m_selectedObject->m_pMaterial;
    auto position = m_selectedObject->m_position;
    if (objType == GEOMETRITYPE::PLANE) {
      m_sceneObjects[m_selectedObjectIdx].reset(new jlPlane(*m_pDefaultPlane));
    }
    if (objType == GEOMETRITYPE::SPHERE) {
      m_sceneObjects[m_selectedObjectIdx].reset(new jlSphere(*m_pDefaultSphere));
    }
    if (objType == GEOMETRITYPE::BOX) {
      SPtr<jlBox> box(new jlBox(*m_pDefaultBox));
      box->m_position = position;
      box->calculateRealMinMax();
      m_sceneObjects[m_selectedObjectIdx] = box;
    }
    if (objType == GEOMETRITYPE::CYLINDER) {
      m_sceneObjects[m_selectedObjectIdx].reset(new jlCylinder(*m_pDefaultCylinder));
    }
    m_selectedObject = m_sceneObjects[m_selectedObjectIdx];
    m_selectedObject->m_pMaterial = material;
    m_selectedObject->m_position = position;
  }
  
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
  int32 matType = (int32)m_selectedObject->m_pMaterial->m_type;
  ImGui::Separator();
  OptionPreviw = m_MaterialsListString[matType];
  if (ImGui::BeginCombo("Matterials", OptionPreviw.c_str())) {
    OptionPreviw = "";
    ImGui::ListBox("Matterial", 
                   &matType,
                   &m_MaterialsListString[0],
                   (int32)m_MaterialsListString.size());
    ImGui::EndCombo();
  }
  if (matType != (int32)m_selectedObject->m_pMaterial->m_type) {
    auto color = m_selectedObject->m_pMaterial->m_color;
    if (matType == MATERIALTYPE::MATTE) {
      SPtr<jlMMatte> matte(new jlMMatte(*m_pDefaultMMatte));
      matte->setCd(color);
      m_selectedObject->m_pMaterial = matte;
    }
    if (matType == MATERIALTYPE::PHONG) {
      SPtr<jlMPhong> phong(new jlMPhong(*m_pDefaultMPhong));
      phong->setCd(color);
      m_selectedObject->m_pMaterial = phong;
    }
    if (matType == MATERIALTYPE::PLASTIC) {
      SPtr<jlMPlastic> plastic(new jlMPlastic(*m_pDefaultMPlastic));
      plastic->m_color = color;
      m_selectedObject->m_pMaterial = plastic;
    }
  }

  imguiShowMaterialProperties(m_selectedObject->m_pMaterial);
  ImGui::End();
}

void
jlWorld::imguiShowSphereProperties() {
  ImGui::Text("SPHERE");
  auto sphere = std::static_pointer_cast<jlSphere>(m_selectedObject);
  ImGui::DragFloat3("Position", &sphere->m_position.x);
  ImGui::DragFloat("Ratio", &sphere->m_radius, 0.5f, 0.0f);
}

void
jlWorld::imguiShowBoxProperties() {
  ImGui::Text("BOX");
  auto box = std::static_pointer_cast<jlBox>(m_selectedObject);
  ImGui::DragFloat3("Position", &box->m_position.x);
  ImGui::DragFloat3("offset", &box->m_offset.x);
  ImGui::Text("MinX");
  ImGui::SameLine();
  ImGui::DragFloat("MinX", &box->m_min.x, 0.5f, -10000000, box->m_max.x - 1);
  ImGui::Text("MinY");
  ImGui::SameLine();
  ImGui::DragFloat("MinY", &box->m_min.y, 0.5f, -10000000, box->m_max.y - 1);
  ImGui::Text("MinZ");
  ImGui::SameLine();
  ImGui::DragFloat("MinZ", &box->m_min.z, 0.5f, -10000000, box->m_max.z - 1);

  ImGui::Text("MaxX");
  ImGui::SameLine();
  ImGui::DragFloat("MaxX", &box->m_max.x, 0.5f, box->m_min.x + 1, 10000000);
  ImGui::Text("MaxY");
  ImGui::SameLine();
  ImGui::DragFloat("MaxY", &box->m_max.y, 0.5f, box->m_min.y + 1, 10000000);
  ImGui::Text("MaxZ");
  ImGui::SameLine();
  ImGui::DragFloat("MaxZ", &box->m_max.z, 0.5f, box->m_min.z + 1, 10000000);
  box->calculateRealMinMax();
}

void
jlWorld::imguiShowPlaneProperties() {
  ImGui::Text("PLANE");
  auto plane = std::static_pointer_cast<jlPlane>(m_selectedObject);
  ImGui::DragFloat3("Position", &plane->m_position.x);
  ImGui::DragFloat3("Normal", &plane->m_normal.x, 0.05f, 0.0f,1.0f);
}

void
jlWorld::imguiShowCylindreProperties() {
  ImGui::Text("CYLINDER");
  auto cylinder = std::static_pointer_cast<jlCylinder>(m_selectedObject);
  ImGui::DragFloat3("Position", &cylinder->m_position.x);
  ImGui::DragFloat("Height", &cylinder->m_height, 0.5f, 0.0f);
  ImGui::DragFloat("Ratio", &cylinder->m_radius, 0.5f, 0.0f);
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
  ImGui::Text("MATTE");
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
  ImGui::Text("PHONG");
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
  ImGui::Text("PLASTIC");
}

void
jlWorld::imguiShowLights() {
  ImGui::Begin("SceneLights");
  ImGui::CloseCurrentPopup();
  uint32 lights = (uint32)m_sceneLights.size();
  for (uint32 i = 0; i < lights; ++i) {
    String name = "Light " + std::to_string(i);
    ImGuiTreeNodeFlags flags = ImGuiTreeNodeFlags_SpanFullWidth |
                               ImGuiTreeNodeFlags_OpenOnArrow |
                               ImGuiTreeNodeFlags_OpenOnDoubleClick |
                               ImGuiTreeNodeFlags_Leaf |
                               ImGuiTreeNodeFlags_Bullet;
    if (m_selectedLight == m_sceneLights[i]) {
      flags |= ImGuiTreeNodeFlags_Selected;
    }
    if (ImGui::TreeNodeEx(name.c_str(), flags))
    {
      if (ImGui::IsItemClicked()) {
        m_selectedLight = m_sceneLights[i];
        m_selectedLightIdx = i;
      }
      ImGui::TreePop();
    }
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
  ImGui::Text("POINT LIGHT");
  auto point = std::static_pointer_cast<jlPointLight>(m_selectedLight);
  auto pos = point->getPosition();
  auto col = point->getColor();
  auto ls = point->getRadianceScalingFactor();
  ImGui::DragFloat3("Position", &pos.x);
  ImGui::DragFloat("Radiance Scaling Factor", &ls, 0.05f, -1.0f, 5.0f);
  ImGui::ColorEdit3("Color", &col.x);
  ImGui::Checkbox("Cast Shadows", &point->m_bCastShadows);

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
