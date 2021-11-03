/*****************************************************************************/
/**
	* @file    jlPointLight.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A class for a point light
	*
	*
	* @bug	    No known bugs.
	*/
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlLight.h"

class jlPointLight : public jlLight {
 public:
		/**
			* @brief default constructor
			*/
		jlPointLight() = default;

		/**
			* @brief default destructor
			*/
		~jlPointLight() {};

		/**
			* @brief returns the direction of the incoming light at a hit point
			* @return a vector3 with the direction
			*/
		virtual jlVector3
		getDirection(jlShadeRec& sr) override;

		/**
			* @brief returns the incident radiance at a hit point
			* @return a color with the incident radiance
			*/
		virtual jlColor
		L(jlShadeRec& sr) override;

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
			* @brief set the light's Postions
			* @param pos is the position to set
			*/
		void
		setPosition(const jlVector3& pos) {
				m_position = pos;
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

		/**
			* @brief get the light's Postions
			* @return a vector3 with the position
			*/
		jlVector3
		getPosition() {
				return m_position;
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
		
		/**
			* @brief the position of light
			*/
		jlVector3 m_position = { 0, 0, 0 };

};