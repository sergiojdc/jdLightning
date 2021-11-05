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

namespace MATERIALTYPE {
		enum E {
				MATTE = 0,
				PHONG,
				PLASTIC,
				NUMOFMATERIALS,
				UKNOW
		};
};

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
#ifdef CASTSHADOWS
    return shadowShade(sr);
#else
    return normalShade(sr);
#endif // CASTSHADOWS
  };

		/**
			* @brief calculate shade without shadows
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  normalShade(jlShadeRec& sr) {
				UNREFERENCED_PARAMETER(sr);
    return { 0, 0, 0};
  };

		/**
			* @brief calculate shade with shadows
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  shadowShade(jlShadeRec& sr) {
				UNREFERENCED_PARAMETER(sr);
    return { 0, 0, 0};
  };

		/**
			* @brief calculate a area light shade
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  areaLightShade(jlShadeRec& sr) {
				UNREFERENCED_PARAMETER(sr);
    return { 0, 0, 0 };
  };

		/**
			* @brief calculate a path shade
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  pathShade(jlShadeRec& sr) {
				UNREFERENCED_PARAMETER(sr);
    return { 0, 0, 0 };
  };

		/**
			* @brief the type of the material
			*/
		MATERIALTYPE::E m_type = MATERIALTYPE::UKNOW;

		/**
			* @brief color for copy when change the material
			*/
		jlColor m_color;
};