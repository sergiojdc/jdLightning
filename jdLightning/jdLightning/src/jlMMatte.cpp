#include "jlMMatte.h"
#include "jlShadeRec.h"
#include "jlWorld.h"
#include "jlLight.h"

jlColor 
jlMMatte::normalShade(jlShadeRec& sr, uint32 sampleIndex) {
  UNREFERENCED_PARAMETER(sampleIndex);
  jlVector3 wo = -sr.m_ray.m_direction;
  jlColor L = m_ambientBRDF->rho(sr, wo) * sr.m_world->m_pAmbientLight->L(sr);
  uint32 numLights = (uint32)sr.m_world->m_sceneLights.size();
  jlVector3 wi;
  float ndotwi;

  for (uint32 i = 0; i < numLights; i++) {
    wi = sr.m_world->m_sceneLights[i]->getDirection(sr);
    ndotwi = sr.m_normal.dot(wi);
    if (ndotwi > 0.0f) {
      L += m_diffuseBRDF->f(sr, wo, wi) * sr.m_world->m_sceneLights[i]->L(sr) * ndotwi;
    }
  }
  return  L;
}

jlColor 
jlMMatte::shadowShade(jlShadeRec& sr, uint32 sampleIndex) {
  jlVector3 wo = -sr.m_ray.m_direction;
  jlColor L = m_ambientBRDF->rho(sr, wo) * sr.m_world->m_pAmbientLight->L(sr, sampleIndex);
  uint32 numLights = (uint32)sr.m_world->m_sceneLights.size();
  jlVector3 wi;
  float ndotwi;
  bool inShadow = false;

  for (uint32 i = 0; i < numLights; i++) {
    wi = sr.m_world->m_sceneLights[i]->getDirection(sr);
    ndotwi = sr.m_normal.dot(wi);

    if (ndotwi > 0.0f) {
      inShadow = false;
      if (sr.m_world->m_sceneLights[i]->m_bCastShadows) {
        jlRay shadowRay(sr.m_HitPoint, wi);
        inShadow = sr.m_world->m_sceneLights[i]->inShadow(shadowRay, sr);
      }
      if (!inShadow) {
        L += m_diffuseBRDF->f(sr, wo, wi) * sr.m_world->m_sceneLights[i]->L(sr) * ndotwi;
      }
    }
  }
  return  L;
}
