/*****************************************************************************/
/**
	* @file    jlBRDF.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A virtual class for any BRDF (Bidirectional Reflectate Distribution Function)
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include <jlVector3.h>
#include <jlColor.h>

class jlShadeRec;
class jlSampler;

class jlBRDF {
 public:
		/**
			* @brief default constructor
			*/
		jlBRDF() = default;
		
	 /**
   * @brief default destructor
   */
		~jlBRDF() {} ;

  /**
   * @brief returns the BRDF itself
   * @param Sr is the shadeRec to use
   * @param wi is incoming direction
   * @param wo is relfected direction
   * @return jlColor with the result color
   */
  virtual jlColor
  f(const jlShadeRec& sr, const jlVector3& wi, const jlVector3& wo) {
    UNREFERENCED_PARAMETER(sr);
    UNREFERENCED_PARAMETER(wi);
    UNREFERENCED_PARAMETER(wo);
    return { 0, 0, 0 };
  };

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
  sampleF(const jlShadeRec& sr, jlVector3& wi, const jlVector3& wo) {
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
  rho(const jlShadeRec& sr, const jlVector3& wo) {
    UNREFERENCED_PARAMETER(sr);
    UNREFERENCED_PARAMETER(wo);
    return { 0, 0, 0 };
  };

  /**
   * @brief pointer to a sampler object
   */
  SPtr<jlSampler> m_pSampler = nullptr;

};
