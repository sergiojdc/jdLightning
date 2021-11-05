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
  getDirection(jlShadeRec& sr) = 0;

		/**
			* @brief returns the incident radiance at a hit point
			* @return a color with the incident radiance
			*/
  virtual jlColor
  L(jlShadeRec& sr) = 0;

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
