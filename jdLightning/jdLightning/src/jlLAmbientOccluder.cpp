#include "jlLAmbientOccluder.h"
#include "jlSampler.h"
#include "jlShadeRec.h"
#include "jlWorld.h"

jlVector3 
jlLAmbientOccluder::getDirection(jlShadeRec& sr,
                                 const jlVector3& u,
                                 const jlVector3& v,
                                 const jlVector3& w,
                                 uint32 sampleIndex) {
  UNREFERENCED_PARAMETER(sr);
		jlVector3 sp = m_pSampler->sampleHemisphere(sampleIndex);
		return (sp.x * u + sp.y * v + sp.z * w);
}

jlColor 
jlLAmbientOccluder::L(jlShadeRec& sr, uint32 sampleIndex) {
  jlVector3 w = sr.m_normal;
  // jitter up vector in case normal is vertical
  jlVector3 v;
  jlVector3 u;
  v = w.cross(jlVector3(0.0072f, 1.0f, 0.0034f));
  //v = jlVector3(0.0072f, 1.0f, 0.0034f).cross(w);
  v.normalize();
  u = v.cross(w);
  //u = w.cross(v);
  jlRay shadow_ray;
  shadow_ray.m_origin.x = sr.m_HitPoint.x;
  shadow_ray.m_origin.y = sr.m_HitPoint.y;
  shadow_ray.m_origin.z = sr.m_HitPoint.z;
  shadow_ray.m_direction = getDirection(sr, u, v, w, sampleIndex);
    //return (m_ls * m_color);
    //return (m_minAmount * m_ls * m_color);
  if (inShadow(shadow_ray, sr))
    return (m_minAmount * m_ls * m_color);
  else
    return (m_ls * m_color);
}

bool 
jlLAmbientOccluder::inShadow(const jlRay& ray, jlShadeRec& sr) {
		float t;
		uint32 num_objects = (uint32)sr.m_world->m_sceneObjects.size();
		for (uint32 j = 0; j < num_objects; ++j)
				if (sr.m_world->m_sceneObjects[j]->shadowHit(ray, t))
      if (t < 100.0f)
  						return true;
		return false;
}

void jlLAmbientOccluder::setSampler(WeakSptr<jlSampler> sampler) {
		m_pSampler = sampler.lock();
		m_pSampler->mapSamplesToHemisphere(1000.0f);
}
