#include "jlBRDFGlossySpecular.h"
#include "jlShadeRec.h"

jlColor 
jlBRDFGlossySpecular::f(const jlShadeRec& sr, const jlVector3& wi, const jlVector3& wo) {
  jlColor L={ 0, 0, 0 };
  float ndotwi = sr.m_normal.dot(wi);
  jlVector3 r(-wi + 2.0 * sr.m_normal * ndotwi);
  float rdotwo = r.dot(wo);

  if (rdotwo > 0.0) {
    auto col = m_ks * Math::pow(rdotwo, m_exp);
    L = { col ,col ,col };
  }
  return L;
}
