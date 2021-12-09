/*****************************************************************************/
/**
	* @file    jlLight.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A virtual class for any kind of Light
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlVector3.h"
#include "jlColor.h"
#include "jlRay.h"

namespace LIGHTTYPES {
		enum E {
				AMBIENT = 0,
				POINT,
				AMBIENTOCCLUDER,
				NUMLIGHTS,
				UNKNOW
		};
};

class jlShadeRec;

class jlLight {
 public:
		/**
			* @brief default constructor
			*/
		jlLight() = default;
		
		/**
			* @brief default destructor
			*/
		virtual ~jlLight() {};

		/**
			* @brief returns the direction of the incoming light at a hit point
			* @return a vector3 with the direction
			*/
  virtual jlVector3
  getDirection(jlShadeRec& sr, uint32 sampleIndex = 0) {
				UNREFERENCED_PARAMETER(sr);
				UNREFERENCED_PARAMETER(sampleIndex);
				return { 0,0,0 };
		};

		/**
			* @brief returns the direction of the incoming light at a hit point
			* @param sr is the shadeRec with data
			* @param u is right vector for hemisphere
			* @param v is up vector for hemisphere
			* @param w is front vector for hemisphere
			* @param sampleIndex iuf for optimized sampler only, is the index of sampler
			* @return a vector3 with the direction
			*/
		virtual jlVector3
		getDirection(jlShadeRec& sr, 
               const jlVector3& u, 
               const jlVector3& v, 
               const jlVector3& w, 
               uint32 sampleIndex = 0) {
				UNREFERENCED_PARAMETER(sr);
				UNREFERENCED_PARAMETER(u);
				UNREFERENCED_PARAMETER(v);
				UNREFERENCED_PARAMETER(w);
				UNREFERENCED_PARAMETER(sampleIndex);
				return { 0,0,0 };
		};

		/**
			* @brief returns the incident radiance at a hit point
			* @return a color with the incident radiance
			*/
  virtual jlColor
  L(jlShadeRec& sr, uint32 sampleIndex = 0) = 0;

		/**
		 * @brief returns if ray hit with another 
			* @param ray is the ray to cast
			* @param sr is the shadeRec with data
		 * @return true if is hit and that means there is a shadow
		 */
		virtual bool
		inShadow(const jlRay& ray, jlShadeRec& sr) { 
				UNREFERENCED_PARAMETER(ray);
				UNREFERENCED_PARAMETER(sr);
				return false; 
		};

		/**
			* @brief the type of the light
			*/
		LIGHTTYPES::E m_type = LIGHTTYPES::UNKNOW;

		//to check its uses
		/**
			* @brief to cast or not shadows
			*/
		bool m_bCastShadows = true;
 protected:


};
