#include "jlMPlastic.h"
#include "jlShadeRec.h"
#include "jlWorld.h"

jlColor 
jlMPlastic::shade(jlShadeRec& sr) {
  if (!m_ambientBRDF || !m_diffuseBRDF || !m_specularBRDF)
    return { 0, 0 ,0 };
  
  jlVector3 wo = -sr.m_ray.m_direction;
  jlColor L = m_ambientBRDF->rho(sr, wo) * sr.m_world->m_pAmbientLight->L(sr);
  uint32 numLights = (uint32)sr.m_world->m_sceneLights.size();

  for (uint32 i = 0; i < numLights; i++) {
    jlVector3 wi = sr.m_world->m_sceneLights[i]->getDirection(sr);
    float ndotwi = sr.m_normal.dot(wi);
    if (ndotwi > 0.0f) {
      L += (m_diffuseBRDF->f(sr, wi, wo) + m_specularBRDF->f(sr, wi, wo)) * //change wi for wo and viceversa
        sr.m_world->m_sceneLights[i]->L(sr) *
        ndotwi;
    }
  }
  return  L;
}
