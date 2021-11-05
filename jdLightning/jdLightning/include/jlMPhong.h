/*****************************************************************************/
/**
	* @file    jlMPhong.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    3/11/2021
	* @brief   A class for a phong material 
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlMaterial.h"
#include "jlBRDFLambertian.h"
#include "jlBRDFGlossySpecular.h"

class jlMPhong : public jlMaterial {
 public:
		/**
			* @brief default constructor
			*/
		jlMPhong() {
				m_ambientBRDF.reset(new jlBRDFLambertian);
				m_diffuseBRDF.reset(new jlBRDFLambertian);
				m_specularBRDF.reset(new jlBRDFGlossySpecular);
				m_type = MATERIALTYPE::PHONG;
		};

		/**
			* @brief default destructor
			*/
		~jlMPhong() {};
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
			* @brief set specular reflection coefficient
			* @param k is value of coefficient
			*/
  void
  setKs(const float& k) {
				m_specularBRDF->setSpecularReflectionCoefficient(k);
  }

		/**
			* @brief set the material's color
			* @param c is color to set
			*/
  void
  setCd(const jlColor& c) {
    m_ambientBRDF->setDiffuseColor(c);
				m_diffuseBRDF->setDiffuseColor(c);
				m_specularBRDF->setColor(c);
  }

		void
		setSpecularExponent(int32 exp) {
				m_specularBRDF->setSpecularReflectionExponent(exp);
		}

		/**
			* @brief BRDF for ambient
			*/
  SPtr<jlBRDFLambertian> m_ambientBRDF;

		/**
			* @brief BRDF for diffuse
			*/
		SPtr<jlBRDFLambertian> m_diffuseBRDF;

		/**
			* @brief BRDF for specular
			*/
		SPtr<jlBRDFGlossySpecular> m_specularBRDF;
};
