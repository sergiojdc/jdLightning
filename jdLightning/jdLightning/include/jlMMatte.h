/*****************************************************************************/
/**
	* @file    jlMMatte.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A virtual class for a Matte material
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
				m_difuseBRDF.reset(new jlBRDFLambertian);
		};
		
		/**
			* @brief default destructor
			*/
		~jlMMatte() {};

		/**
			* @brief calculate shade
			* @param sr is the sahde rec with the data to use
			* @reutrn the result color
			*/
  virtual jlColor
  shade(jlShadeRec& sr) override;

  void
  setKa(const float& k) {
    m_ambientBRDF->setDiffuseReflectionCoefficient(k);
  }
  void
  setKd(const float& k) {
    m_difuseBRDF->setDiffuseReflectionCoefficient(k);
  }

  void
  setCd(const jlColor& c) {
    m_ambientBRDF->setDiffuseColor(c);
    m_difuseBRDF->setDiffuseColor(c);
  }

  SPtr<jlBRDFLambertian> m_ambientBRDF;
		SPtr<jlBRDFLambertian> m_difuseBRDF;
};