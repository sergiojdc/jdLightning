/*****************************************************************************/
/**
 * @file    jlTracer.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    27/10/2021
 * @brief   A virtual class for a Tracer
 *
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include <jlColor.h>
#include <jlRay.h>

class jlWorld;

class jlTracer {
 public:
  /**
   * @brief defaul constructor
   */
  jlTracer() = default;

  /**
   * @brief constructor with world
   * @param world is a pointer to the world
   */
  jlTracer(jlWorld* world) : m_world(world) {};

  /**
   * @brief defaul destructor
   */
  virtual ~jlTracer() {};

  /**
   * @brief virtual method for check if the ray hit with geometri
   * @param ray is the ray with check the hits
   * @return a color
   */
  virtual jlColor
  traceRay(const jlRay& ray) const {
    UNREFERENCED_PARAMETER(ray);
    return { 0, 0, 0 };
  }

  /**
   * @brief virtual method for check if the ray hit with geometri with depth
   * @param ray is the ray with check the hits
   * @param depth is the depth with check it
   * @return a color
   */
  virtual jlColor
  traceRay(const jlRay& ray, uint32 depth) const {
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(depth);
    return { 0, 0, 0 };
  };

  /**
   * @brief virtual method for check if the ray hit with geometri with depth
   * @param ray is the ray with check the hits
   * @param tmin is the current nearlers 
   * @param depth is the depth with check it
   * @return a color
   */
  virtual jlColor
  traceRay(const jlRay& ray, const float& tmin, uint32 depth) const {
    UNREFERENCED_PARAMETER(ray);
    UNREFERENCED_PARAMETER(tmin);
    UNREFERENCED_PARAMETER(depth);
    return { 0, 0, 0 };
  };
 protected:
 
  /**
   * @brief pointer to the world
   */
  jlWorld* m_world;
  
};