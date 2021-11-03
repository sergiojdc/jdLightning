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

 protected:

		//to check its uses
		bool m_bShadows = false;

};
