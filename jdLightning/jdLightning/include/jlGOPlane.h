/*****************************************************************************/
/**
	* @file    jlGOPlane.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    26/10/2021
	* @brief   A class for a plane heredated by jlGeometriObject
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include <jlVector3.h>

class jlPlane : public jlGeometricObject
{
 public:
  /**
   * @brief defaul constructor
   */
   jlPlane() {
     m_type = GEOMETRITYPE::PLANE;
   };

  /**
   * @brief constructor with point and normal
   * @param point is the plane's point
   * @param normal is the plane's normal
   */
   jlPlane(const jlVector3 point, const jlNormal& normal);
  
  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest 
   * @pram sr is the shade rec
   */
  virtual bool
  hit(const jlRay& ray, double& tmin, jlShadeRec& sr) override;

  /**
   * @brief defaul destructor
   */
  ~jlPlane() {};

private:
  /**
   * @brief point through which
   */
  jlVector3 m_point;

  /**
   * @brief normal to the plane
   */
  jlNormal m_normal;

  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};
