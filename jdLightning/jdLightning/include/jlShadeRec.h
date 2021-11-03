/**
 * @file    shadeRec.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   A basic class for shadeRec
 *
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include <jlPoint3.h>
#include <jlVector3.h>
#include <jlColor.h>
#include <jlRay.h>
#include <jlNormal.h>

class jlWorld;
class jlMaterial;

class jlShadeRec {
public:
  /**
   * @brief constructo with world
   * @param world is a pointer to the world to use
   */
  jlShadeRec(jlWorld* world);

  /**
   * @brief copy constructor
   * @param sr is the other ShadeRec to copy
   */
  jlShadeRec(const jlShadeRec& sr);

   /**
    * @brief defaul destructor
    */
  ~jlShadeRec() {};

  /**
   * @brief assignment operator
   * @param rhs is the other ShadeRec to copy
   */
  jlShadeRec&
  operator= (const jlShadeRec& rhs);

  /**
   * @brief to check if the ray hitted and objetc
   */
  bool m_hitAnObject;

  /**
   * @brief world coordinates of hit point
   */
  jlVector3 m_HitPoint;

  /**
   * @brief world coordinates of hit point, for attaching textures to objects
   */
  jlVector3 m_localHitPoint;

  /**
   * @brief normal at hit point
   */
  jlNormal m_normal;

  /**
   * @brief use for debug
   */
  jlColor m_color;

  /**
   * @brief neareat object's material
   */
  SPtr<jlMaterial> m_pMaterial = nullptr;

  /**
   * @brief for specular highlights
   */
  jlRay m_ray;

  /**
   * @brief recursion depth
   */
  int32 m_depth = 0;

  /**
   * @brief current near point distance
   */
  float m_t = 0;

  /**
   * @brief for area lights
   */
  jlVector3 m_dir;

  /**
   * @brief world reference for shading
   */
  jlWorld* m_world = nullptr;


};

inline 
jlShadeRec::jlShadeRec(jlWorld* wr)
  : m_hitAnObject(false),
    m_HitPoint({ 0, 0, 0 }),
    m_localHitPoint({0, 0, 0}),
    m_normal(),
    m_color({ 0,}),
    m_ray(),
    m_dir({0, 0, 0}),
    m_world(wr) {}

//inline 
//ShadeRec::ShadeRec(const ShadeRec& sr) {
//  *this = sr;
//}

inline 
jlShadeRec::jlShadeRec(const jlShadeRec& sr) {
  m_hitAnObject = sr.m_hitAnObject;
  m_HitPoint = sr.m_HitPoint;
  m_localHitPoint = sr.m_localHitPoint;
  m_normal = sr.m_normal;
  m_color = sr.m_color;
  m_pMaterial = sr.m_pMaterial;
  m_ray = sr.m_ray;
  m_depth = sr.m_depth;
  m_dir = sr.m_dir;
  m_world = sr.m_world;
}

inline jlShadeRec&
jlShadeRec::operator=(const jlShadeRec& rhs) {
  m_hitAnObject = rhs.m_hitAnObject;
  m_HitPoint = rhs.m_HitPoint;
  m_localHitPoint = rhs.m_localHitPoint;
  m_normal = rhs.m_normal;
  m_color = rhs.m_color;
  m_pMaterial = rhs.m_pMaterial;
  m_ray = rhs.m_ray;
  m_depth = rhs.m_depth;
  m_dir = rhs.m_dir;
  m_world = rhs.m_world;
}
