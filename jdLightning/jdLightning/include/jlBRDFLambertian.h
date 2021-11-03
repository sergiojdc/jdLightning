/*****************************************************************************/
/**
	* @file    jlBRDFLambertian.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A class for BRDF lambertian
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlBRDF.h"

class jlBRDFLambertian : public jlBRDF {
 public:
		/**
			* @brief default constructor
			*/
  jlBRDFLambertian() {};
  
		/**
			* @brief default destructor
			*/
  ~jlBRDFLambertian() {};

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
  sampleF(const jlShadeRec& sr, jlVector3& wi, const jlVector3& wo) override;

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
  rho(const jlShadeRec& sr, const jlVector3& wo) override;

  /**
   * @brief set the Diffuse Reflection Coefficient (kd)
   * @param kd is the value to set
   */
  void
  setDiffuseReflectionCoefficient(const float& kd) {
    m_kd = kd;
  };

  /**
   * @brief set the Diffuse Color
   * @param color is the color to set
   */
  void
  setDiffuseColor(const jlColor& color) {
    m_cd = color;
  }

  /**
   * @brief get the Diffuse Reflection Coefficient (kd)
   * @return a float with the value
   */
  float
  getDiffuseReflectionCoefficient() const {
    return m_kd;
  }

  /**
   * @brief get the Diffuse Color
   * @return a color 
   */
  jlColor
  getDiffuseColor() const {
    return m_cd;
  }

 private:
  /**
   * @brief the diffuse reflection coefficient
   */
  float m_kd = 1.0f;

  /**
   * @brief the diffuse color
   */
		jlColor m_cd = {0, 0, 0};

};