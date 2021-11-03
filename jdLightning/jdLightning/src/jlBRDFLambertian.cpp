#include "jlBRDFLambertian.h"
#include "jlShadeRec.h"

jlColor 
jlBRDFLambertian::f(const jlShadeRec& sr, const jlVector3& wi, const jlVector3& wo) {
  UNREFERENCED_PARAMETER(sr);
  UNREFERENCED_PARAMETER(wi);
  UNREFERENCED_PARAMETER(wo);
  return m_kd * m_cd * Math::INV_PI;
}

jlColor 
jlBRDFLambertian::sampleF(const jlShadeRec& sr, jlVector3& wi, const jlVector3& wo) {
  UNREFERENCED_PARAMETER(sr);
  UNREFERENCED_PARAMETER(wi);
  UNREFERENCED_PARAMETER(wo);
  return { 0, 0, 0 };
}

jlColor 
jlBRDFLambertian::rho(const jlShadeRec& sr, const jlVector3& wo) {
  UNREFERENCED_PARAMETER(sr);
  UNREFERENCED_PARAMETER(wo);
  return m_kd * m_cd;
}
