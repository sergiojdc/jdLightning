/*****************************************************************************/
/**
	* @file    jlLAmbient.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A class for a ambient light
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlLight.h"

class jlLAmbient : public jlLight {
 public:
		/**
			* @brief default constructor
			*/
		jlLAmbient() {
				m_type = LIGHTTYPES::AMBIENT;
		};

		/**
			* @brief constructor with params
			*/
		jlLAmbient(const float& ls, const jlColor& color) : m_ls(ls), m_color(color) {
				m_type = LIGHTTYPES::AMBIENT;
		};
		
		/**
			* @brief default destructor
			*/
		~jlLAmbient() {};

		/**
			* @brief returns the direction of the incoming light at a hit point
			* @return a vector3 with the direction
			*/
  virtual jlVector3
		getDirection(jlShadeRec& sr) override {
				UNREFERENCED_PARAMETER(sr);
				return { 0, 0, 0 };
		};

		/**
			* @brief returns the incident radiance at a hit point
			* @return a color with the incident radiance
			*/
  virtual jlColor
  L(jlShadeRec& sr) override {
				UNREFERENCED_PARAMETER(sr);
				return m_color * m_ls;
		};

 /**
   * @brief set the Radiance Scaling Factor (ls)
   * @param ls is the value to set
   */
  void
  setRadianceScalingFactor(const float& ls) {
    m_ls = ls;
  };

  /**
   * @brief set the light's Color
   * @param color is the color to set
   */
  void
  setColor(const jlColor& color) {
				m_color = color;
  }

  /**
   * @brief get the Radiance Scaling Factor (ls)
   * @return a float with the value
   */
  float
  getRadianceScalingFactor() const {
    return m_ls;
  }

  /**
   * @brief get the light's Color
   * @return a color 
   */
  jlColor
  getColor() const {
    return m_color;
  }

 private:
		/**
		 * @brief radiance scaling factor 
		 */
		float m_ls = 1.0f;

		/**
			* @brief the color of light
			*/
		jlColor m_color = { 1, 1, 1 };

};
