/*****************************************************************************/
/**
 * @file    jlGODisk.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    01/FEB/2022
 * @brief   A class for a disk
 *
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include "jlVector3.h"
#include "jlNormal.h"

class jlDisk : public jlGeometricObject {
public:
  /**
   * @brief defaul constructor
   */
  jlDisk() {
    m_type = GEOMETRITYPE::DISK;
  };

  /**
   * @brief constructor with point and normal
   * @param pos is the sphere's position
   */
  jlDisk(const float& ratio, const jlNormal& normal, const jlVector3& position) {
    m_type = GEOMETRITYPE::DISK;
    m_ratio = ratio;
    m_normal = normal;
    m_position = position;
    m_squareRatio = m_ratio * m_ratio;
  };

  /**
   * @brief defaul destructor
   */
  ~jlDisk() {};

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
   * @brief vertices
   */
  float m_ratio = 10;
  float m_squareRatio = 100;

  /**
   * @brief normal
   */
  jlNormal m_normal = { 0,1,0 };

  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};