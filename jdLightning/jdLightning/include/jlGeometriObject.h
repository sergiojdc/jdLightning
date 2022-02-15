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
class jlBBox;

namespace GEOMETRITYPE {
		enum E {
				PLANE = 0,
				SPHERE,
				BOX,
				CYLINDER,
				TRIANGLE,
				DISK,
				COMPOUND,
			 NUMOFTYPES,
				UNKNOW
		};
}

class jlGeometricObject {
 public:
  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest 
   * @pram sr is the shade rec
   * @return true if tha ray hit with it
   */
  virtual bool
  hit(const jlRay& ray, double& tmin, jlShadeRec& sr) { 
				UNREFERENCED_PARAMETER(ray);
				UNREFERENCED_PARAMETER(tmin);
				UNREFERENCED_PARAMETER(sr);
				return false; 
		};

		/**
			* @brief function to detected if the object is in shadow
			* @param ray is the ray whit check the hit
			* @pram tmin is to check the nearest
			* @return true if tha ray hit with it
			*/
		virtual bool
		shadowHit(const jlRay& ray, float& tmin) {
				UNREFERENCED_PARAMETER(ray);
				UNREFERENCED_PARAMETER(tmin); 
				return false; 
		};

		/**
			* @brief function to update the object's bounding box 
			*/
		virtual void
		updateBoundigBox();

  /**
   * @brief function to add object to Compound
   * @param material is a weakSptr with the material to set
   */
		void 
		addObject(WeakSptr<jlGeometricObject> object) {
				UNREFERENCED_PARAMETER(object);
		}


		/**
			* @brief color use for debug
			*/
  jlColor m_color; // only used in first step

	 /**
	 	* @brief object Material
	 	*/
		SPtr<jlMaterial> m_pMaterial;
		
		/**
			* @brief the type of the geometri object
			*/
		GEOMETRITYPE::E m_type = GEOMETRITYPE::UNKNOW;

		/**
   * @brief point through which
   */
  jlVector3 m_position;
		
		/**
			* @brief teh bounding box of object
			*/
		SPtr<jlBBox> m_bbox;
};
