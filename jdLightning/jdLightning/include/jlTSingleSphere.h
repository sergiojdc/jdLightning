/*****************************************************************************/
/**
 * @file    jlTSingleSphere.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    27/10/2021
 * @brief   A class for a single sphere Tracer
 *
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlTracer.h"
#include "jlShadeRec.h"
#include "jlWorld.h"

class jlTSingleSphere : public jlTracer {
 public:
   /**
    * @brief defaul constructor
    */
  jlTSingleSphere() {};

  /**
   * @brief constructor with world
   * @param world is a pointer to the world
   */
  jlTSingleSphere(jlWorld* world) { m_world = world; };
		
  /**
   * @brief defaul destructor
   */
  ~jlTSingleSphere() {};

  /**
   * @brief check if the ray hit with geometri
   * @param ray is the ray with check the hits
   * @return a color
   */
  virtual jlColor
  traceRay(const jlRay& ray) const {
    jlShadeRec sr(m_world);
    double t;
    jlColor col;
    if (m_world->m_sphere.hit(ray, t, sr))
      col = jlColor::Red();
    else
      col =  jlColor::Black();
    return col;
  }
};
