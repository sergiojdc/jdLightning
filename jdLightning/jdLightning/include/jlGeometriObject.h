/*****************************************************************************/
/**
	* @file    jlgeometriObject.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    26/10/2021
	* @brief   A virtual class any kind of geometri
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include <Prerequisites.h>
#include <jlRay.h>
#include <jlColor.h>
#include "jlShadeRec.h"

class jlGeometricObject {
 public:
		/**
			* @brief function to detected a hit
			* @param ray is the ray whit check the hit
			* @pram tmin is the theta minimun
			* @pram sr is the shade rec
			*/
  virtual bool
  hit(const jlRay& ray, double& tmin, jlShadeRec& sr) { 
				UNREFERENCED_PARAMETER(ray);
				UNREFERENCED_PARAMETER(tmin);
				UNREFERENCED_PARAMETER(sr);
				return false; 
		};

		virtual bool
		shadowHit(const jlRay& ray, float& tmin) {
				UNREFERENCED_PARAMETER(ray);
				UNREFERENCED_PARAMETER(tmin); 
				return false; 
		};


		/**
			* @brief color use for debug
			*/
  jlColor m_color; // only used in first step

	 /**
	 	* @brief object Material
	 	*/
		SPtr<jlMaterial> m_pMaterial;
		//Material* m_pMaterial;
};
