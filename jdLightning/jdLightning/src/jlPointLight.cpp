#include "jlPointLight.h"
#include "jlShadeRec.h"
#include "jlWorld.h"

jlVector3 
jlPointLight::getDirection(jlShadeRec& sr) {
  return (m_position - sr.m_HitPoint).getnormalize();
}

jlColor 
jlPointLight::L(jlShadeRec& sr) {
  UNREFERENCED_PARAMETER(sr);
  return m_ls * m_color;
}

bool 
jlPointLight::inShadow(const jlRay& ray, jlShadeRec& sr) {
  float t;
  uint32 numObjects = (uint32)sr.m_world->m_sceneObjects.size();
  float d = m_position.distance(ray.m_origin);
  for (uint32 i = 0; i < numObjects; ++i) {
    if (sr.m_world->m_sceneObjects[i]->shadowHit(ray, t) && t < d)
      return true;
  }
  return false;
}
