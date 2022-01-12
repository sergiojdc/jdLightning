/*****************************************************************************/
/**
	* @file    jlGOTriangle.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    12/ENE/2022
	* @brief   A class for a triangle heredated by geometry object
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include "jlVector3.h"
#include "jlNormal.h"

class jlTriangle : public jlGeometricObject {
 public:
  /**
   * @brief defaul constructor
   */
  jlTriangle() {
    m_type = GEOMETRITYPE::TRIANGLE;
  };

  /**
   * @brief constructor with point and normal
   * @param pos is the sphere's position
   */
  jlTriangle(const jlVector3& a, const jlVector3& b, const jlVector3& c) {
    m_type = GEOMETRITYPE::TRIANGLE;
    m_v0 = a;
    m_v1 = b;
    m_v2 = c;
    m_normal = jlNormal((m_v1-m_v0).cross(m_v2-m_v0));
  };

  /**
   * @brief defaul destructor
   */
  ~jlTriangle() {};

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

  void
  updateNormal() {
    m_normal = jlNormal((m_v1 - m_v0).cross(m_v2 - m_v0));
  };

  /**
   * @brief vertices
   */
  jlVector3 m_v0 = { 0,0,0 };
  jlVector3 m_v1 = { 0,0,1 };
  jlVector3 m_v2 = { 1,0,0 };

  /**
   * @brief normal
   */
  jlNormal m_normal = { 0,1,0 };

  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};