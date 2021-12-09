/*****************************************************************************/
/**
	* @file    jlMPlastic.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    3/11/2021
	* @brief   A class for a Plastic material, you can set whatever brdf you want for each brdf in material
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlMaterial.h"
#include "jlBRDF.h"

class jlMPlastic : public jlMaterial {
 public:
		/**
			* @brief default constructor
			*/
		jlMPlastic() {
				m_type = MATERIALTYPE::PLASTIC;
		};
		
		/**
			* @brief default destructor
			*/
		~jlMPlastic() {};
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
			* @brief set ambient brdf 
			* @param ambient is the brdf to set
			*/
  void
  setAmbientBRDF(WeakSptr<jlBRDF> ambient) {
				m_ambientBRDF = ambient.lock();
  }

		/**
			* @brief set Diffuse brdf 
			* @param diffuse is the brdf to set
			*/
  void
  setDiffuseBRDF(WeakSptr<jlBRDF> diffuse) {
				m_diffuseBRDF = diffuse.lock();
  }

		/**
			* @brief set specular brdf 
			* @param specular is the brdf to set
			*/
  void
  setSpecularBRDF(WeakSptr<jlBRDF> specular) {
				m_specularBRDF = specular.lock();
  }

		/**
			* @brief BRDF for ambient
			*/
  SPtr<jlBRDF> m_ambientBRDF = nullptr;

		/**
			* @brief BRDF for difuse
			*/
		SPtr<jlBRDF> m_diffuseBRDF = nullptr;

		/**
			* @brief BRDF for difuse
			*/
		SPtr<jlBRDF> m_specularBRDF = nullptr;
};
