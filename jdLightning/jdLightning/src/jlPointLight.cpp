#include "jlPointLight.h"
#include "jlShadeRec.h"

jlVector3 
jlPointLight::getDirection(jlShadeRec& sr) {
  return (m_position - sr.m_HitPoint).getnormalize();
}

jlColor 
jlPointLight::L(jlShadeRec& sr) {
  UNREFERENCED_PARAMETER(sr);
  return m_ls * m_color;
}
