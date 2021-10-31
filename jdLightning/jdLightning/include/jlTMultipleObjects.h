/*****************************************************************************/
/**
 * @file    jlTMultipleObjects.h
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

class jlTMultipleObjects : public jlTracer {
 public:
   /**
    * @brief defaul constructor
    */
   jlTMultipleObjects() {};

  /**
   * @brief constructor with world
   * @param world is a pointer to the world
   */
   jlTMultipleObjects(jlWorld* world) { m_world = world; };
		
  /**
   * @brief defaul destructor
   */
  ~jlTMultipleObjects() {};

  /**
   * @brief check if the ray hit with geometri
   * @param ray is the ray with check the hits
   * @return a color
   */
  virtual jlColor
  traceRay(const jlRay& ray) const {
    jlShadeRec sr(m_world->hitBareBonesObjects(ray));
    //double t;
    jlColor col = m_world->m_backgroundColor;
    if (sr.m_hitAnObject)
      col = sr.m_color;
    return col;
  }
};
