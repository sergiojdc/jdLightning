/*****************************************************************************/
/**
	* @file    jlBRDFGlossySpecular.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    03/11/2021
	* @brief   A class for BRDF Glossy specular
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlBRDF.h"

class jlBRDFGlossySpecular : public jlBRDF{
 public:
		/**
			* @brief default constructor
			*/
		jlBRDFGlossySpecular() {};

  /**
   * @brief default constructor with params
   * @param c is the color of brdf
   * @param ks is specular Reflection Coefficient
   */
  jlBRDFGlossySpecular(const jlColor& c, const float& ks, int32 exp = 1) : m_cd(c), 
                                                                           m_ks(ks), 
                                                                           m_exp(exp) {};

		/**
			* @brief default destructor
			*/
		~jlBRDFGlossySpecular() {};

  /**
   * @brief returns the BRDF itself
   * @param Sr is the shadeRec to use
   * @param wi is incoming direction
   * @param wo is relfected direction
   * @return jlColor with the result color
   */
  virtual jlColor
  f(const jlShadeRec& sr, const jlVector3& wi, const jlVector3& wo) override;

  /**
   * @brief used to compute the direction of reflected rays for simulating reflective materials
   *        and diff use-diff use light transport.
   * @param Sr is the shadeRec to use
   * @param wi is incoming direction
   * @param wo is relfected direction
   * @return jlColor with the result color
   * @note the wi parameter is not constant, as this is used to return the direction wi.
   *       As the name implies, the directions are computed by sampling the BRDF.
   *       That’s why the base class BRDF contains a pointer to a sampler object.
   */
  virtual jlColor
  sampleF(const jlShadeRec& sr, jlVector3& wi, const jlVector3& wo) override {
    UNREFERENCED_PARAMETER(sr);
    UNREFERENCED_PARAMETER(wi);
    UNREFERENCED_PARAMETER(wo);
    return { 0, 0, 0 };
  };

  /**
   * @brief returns the bihemispherical reflectance phh.
   * @param Sr is the shadeRec to use
   * @param wi is incoming direction
   * @return jlColor with the result color
   * @note phh or bihemispherical reflectance is the fraction of the total incident flux from
   *       the full hemisphere that’s reflected into the full hemisphere when the incident
   *       radiance is isotropic and spatially invariant.
   */
  virtual jlColor
  rho(const jlShadeRec& sr, const jlVector3& wo) override {
    UNREFERENCED_PARAMETER(sr);
    UNREFERENCED_PARAMETER(wo);
    return { 0, 0, 0 };
  };

  /**
   * @brief set the specular Reflection Coefficient (ks)
   * @param kd is the value to set
   */
  void
  setSpecularReflectionCoefficient(const float& ks) {
    m_ks = ks;
  };

  /**
   * @brief set the Diffuse Color
   * @param color is the color to set
   */
  void
  setColor(const jlColor& color) {
    m_cd = color;
  }

  /**
   * @brief set the specular exponent
   * @param exp is the value to set
   */
  void
  setSpecularReflectionExponent(int32 exp) {
    m_exp = exp;
  };

  /**
   * @brief get the specular Reflection Coefficient (kd)
   * @return a float with the value
   */
  float
  getSpecularReflectionCoefficient() const {
    return m_ks;
  }

  /**
   * @brief get the Diffuse Color
   * @return a color 
   */
  jlColor
  getColor() const {
    return m_cd;
  }

 private:
  friend class jlWorld;
  /**
   * @brief the specular reflection coefficient
   */
  float m_ks = 1.0f;

  /**
   * @brief the diffuse color
   */
		jlColor m_cd = {0, 0, 0};
  
  /**
   * @brief the specular exponent
   */
  int32 m_exp = 1;

};
