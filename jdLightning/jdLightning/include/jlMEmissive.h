/*****************************************************************************/
/**
	* @file    jlMEmissive.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A class for a Matte material
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlMaterial.h"
#include "jlBRDFLambertian.h"


class jlMEmissive : public jlMaterial {
public:
		/**
			* @brief default constructor
			*/
		jlMEmissive() {
				m_ls = 1.0f;
				m_ce = { 1,1,1,1 };
				m_type = MATERIALTYPE::EMISSIVE;
		};

		/**
			* @brief copy constructor
			*/
		jlMEmissive(jlMEmissive& mat) {
			 m_ls = mat.m_ls;
			 m_ce = mat.m_ce;
				m_type = MATERIALTYPE::EMISSIVE;
		};

		/**
			* @brief default destructor
			*/
		~jlMEmissive() {};
		//This is the first version of shade, was changed to normal shade
		///**
		//	* @brief calculate shade
		//	* @param sr is the sahde rec with the data to use
		//	* @reutrn the result color
		//	*/
		//virtual jlColor
		//shade(jlShadeRec& sr) override;

		/**
			* @brief calculate shade without shadows
			* @param sr is the sahde rec with the data to use
			* @reutrn the result color
			*/
		virtual jlColor
		normalShade(jlShadeRec& sr, uint32 sampleIndex = 0) override;

		/**
			* @brief calculate shade with shadows
			* @param sr is the sahde rec with the data to use
			* @reutrn the result color
			*/
		virtual jlColor
		shadowShade(jlShadeRec& sr, uint32 sampleIndex = 0) override;
		
		/**
			* @brief calculate a area light shade
			* @param sr is the sahde rec with the data to use
			* @reutrn the result color
			*/
  virtual jlColor
  areaLightShade(jlShadeRec& sr, uint32 sampleIndex = 0) override;

  virtual jlColor
  getLe(jlShadeRec& sr) const;

		/**
			* @brief radiance scaling factor
			*/
		float m_ls;
		
		/**
			* @brief color
			*/
		jlColor m_ce;
};
