#include "jlMMatte.h"
#include "jlShadeRec.h"
#include "jlWorld.h"
#include "jlLight.h"

jlColor 
jlMMatte::shade(jlShadeRec& sr) {
  jlVector3 wo = -sr.m_ray.m_direction;
  jlColor L = m_ambientBRDF->rho(sr, wo) * sr.m_world->m_pAmbientLight->L(sr);
  uint32 numLights = (uint32)sr.m_world->m_sceneLights.size();

  for (uint32 i = 0; i < numLights; i++) {
    jlVector3 wi = sr.m_world->m_sceneLights[i]->getDirection(sr);
    float ndotwi = sr.m_normal.dot(wi);
    if (ndotwi > 0.0f) {
      L += m_difuseBRDF->f(sr, wo, wi) * sr.m_world->m_sceneLights[i]->L(sr) * ndotwi;
    }
  }
  return  L;
}
