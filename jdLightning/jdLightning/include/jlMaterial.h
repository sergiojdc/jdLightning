/*****************************************************************************/
/**
	* @file    jlMaterial.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A virtual class for any type of material
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include <jlColor.h>

class jlShadeRec;

class jlMaterial {
 public:
		/**
			* @brief default constructor
			*/
		jlMaterial() = default;
		
		/**
			* @brief default destructor
			*/
		virtual ~jlMaterial() {};

		/**
			* @brief calculate shade
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  shade(jlShadeRec& sr) {
    return { 0, 0, 0};
  };

		/**
			* @brief calculate a area light shade
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  areaLightShade(jlShadeRec& sr) {
    return { 0, 0, 0 };
  };

		/**
			* @brief calculate a path shade
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  pathShade(jlShadeRec& sr) {
    return { 0, 0, 0 };
  };
};