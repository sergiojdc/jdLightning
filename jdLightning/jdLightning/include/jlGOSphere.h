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

		/**
			* @brief function to update the object's bounding box 
			*/
		virtual void
		updateBoundigBox() override;

  /**
   * @brief defaul destructor
   */
  ~jlSphere() {};

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
