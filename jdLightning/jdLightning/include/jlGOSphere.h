/*****************************************************************************/
/**
 * @file    jlGOSphere.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    27/10/2021
 * @brief   A class for a Sphere heredated by jlGeometriObject
 *
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include "jlVector3.h"

class jlSphere : public jlGeometricObject {
 public:
  /**
   * @brief defaul constructor
   */
  jlSphere() {
    m_type = GEOMETRITYPE::SPHERE;
  };

  /**
   * @brief constructor with point and normal
   * @param point is the plane's point
   * @param normal is the plane's normal
   */
  jlSphere(const jlVector3 pos, const float& ratio);

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
  ~jlSphere() {};

  /**
   * @brief point through which
   */
  jlVector3 m_position;

  /**
   * @brief normal to the plane
   */
  float m_radius = 1;

 private:
  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};
