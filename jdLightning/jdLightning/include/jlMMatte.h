/*****************************************************************************/
/**
	* @file    jlMMatte.h
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

class jlMMatte : public jlMaterial {
 public:
		/**
			* @brief default constructor
			*/
		jlMMatte() {
				m_ambientBRDF.reset(new jlBRDFLambertian);
				m_diffuseBRDF.reset(new jlBRDFLambertian);
				m_type = MATERIALTYPE::MATTE;
		};

		/**
			* @brief copy constructor
			*/
		jlMMatte(jlMMatte& mat) {
				m_ambientBRDF.reset(new jlBRDFLambertian(*mat.m_ambientBRDF.get()));
				m_diffuseBRDF.reset(new jlBRDFLambertian(*mat.m_diffuseBRDF.get()));
				m_type = MATERIALTYPE::MATTE;
		};
		
		/**
			* @brief default destructor
			*/
		~jlMMatte() {};
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
  normalShade(jlShadeRec& sr) override;

		/**
			* @brief calculate shade with shadows
			* @param sr is the sahde rec with the data to use 
			* @reutrn the result color
			*/
  virtual jlColor
  shadowShade(jlShadeRec& sr) override;

		/**
			* @brief set ambient reflection coefficient
			* @param k is value of coefficient
			*/
  void
  setKa(const float& k) {
    m_ambientBRDF->setDiffuseReflectionCoefficient(k);
  }

		/**
			* @brief set diffuse reflection coefficient
			* @param k is value of coefficient
			*/
  void
  setKd(const float& k) {
				m_diffuseBRDF->setDiffuseReflectionCoefficient(k);
  }

		/**
			* @brief set the material's color
			* @param c is color to set
			*/
  void
  setCd(const jlColor& c) {
    m_ambientBRDF->setDiffuseColor(c);
				m_diffuseBRDF->setDiffuseColor(c);
				m_color = c;
  }

		/**
			* @brief BRDF for ambient
			*/
  SPtr<jlBRDFLambertian> m_ambientBRDF;

		/**
			* @brief BRDF for difuse
			*/
		SPtr<jlBRDFLambertian> m_diffuseBRDF;
};
