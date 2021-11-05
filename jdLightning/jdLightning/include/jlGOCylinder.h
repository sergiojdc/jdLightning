/*****************************************************************************/
/**
	* @file    jlGOCylinder.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    05/11/2021
	* @brief   A class for a cylinder heredated by jlGeometriObject
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include "jlVector3.h"
#include "jlNormal.h"

class jlCylinder : public jlGeometricObject {
 public:
  /**
   * @brief defaul constructor
   */
  jlCylinder() {
    m_type = GEOMETRITYPE::CYLINDER;
  };

  /**
   * @brief constructor with point and normal
   * @param pos is the sphere's position
   */
  jlCylinder(const float& radio, const float& height, const jlVector3 & pos) {
    m_radius = radio;
    m_height = height;
    m_position = pos;
    m_type = GEOMETRITYPE::CYLINDER;
  }

  /**
   * @brief defaul destructor
   */
  ~jlCylinder() {};

  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @pram sr is the shade rec
   * @return true if tha ray hit with it
   */
  virtual bool
  hit(const jlRay & ray, double& t, jlShadeRec & s) override;

  /**
   * @brief function to detected if the object is in shadow
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @return true if tha ray hit with it
   */
  virtual bool
  shadowHit(const jlRay& ray, float& tmin) override;
 
 private:
  friend class jlWorld;
  /**
   * @brief Cylinder´s radius
   */
  float m_radius;

  /**
   * @brief Cylinder´s radius
   */
  float m_height;

  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};
