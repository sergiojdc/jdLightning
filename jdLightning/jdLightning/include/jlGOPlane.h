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
   * @brief defaul destructor
   */
  ~jlPlane() {};

  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @pram sr is the shade rec
   * @return true if tha ray hit with it
   */
  virtual bool
  hit(const jlRay& ray, double& tmin, jlShadeRec& sr) override;

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
   * @brief normal to the plane
   */
  jlNormal m_normal;

  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};
