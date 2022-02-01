#include "jlCompoundObjects.h"


jlCompoundObject::jlCompoundObject()
{
}

jlCompoundObject::~jlCompoundObject()
{
}

void 
jlCompoundObject::setMaterial(WeakSptr<jlMaterial> material) {
  for (uint32 i = 0; i < m_numObjects; ++i) {
    m_objects[i]->m_pMaterial = material.lock();

  }
}

bool 
jlCompoundObject::hit(const jlRay& ray, double& tmin, jlShadeRec& sr) {
  double t;
  jlNormal normal;
  jlVector3 local_hit_point;
  bool hit = false;
  tmin = HUGE_VAL;

  for (uint32 i = 0; i < m_numObjects; ++i)
  {
    if (m_objects[i]->hit(ray, t, sr) && (t < tmin)) {
      hit = true;
      tmin = t;
      m_pMaterial = m_objects[i]->m_pMaterial;
      normal = sr.m_normal;
      local_hit_point = sr.m_localHitPoint;
    }
  }
  if (hit) {
    sr.m_t = tmin;
    sr.m_normal = normal;
    sr.m_localHitPoint = local_hit_point;
  }
  return hit;
}

bool 
jlCompoundObject::shadowHit(const jlRay& ray, float& tmin) {
  float t;
  jlNormal normal;
  jlVector3 local_hit_point;
  bool hit = false;
  tmin = HUGE_VAL;

  for (uint32 i = 0; i < m_numObjects; ++i)
  {
    if (m_objects[i]->shadowHit(ray, t) && (t < tmin)) {
      hit = true;
    }
  }
  return hit;
}
