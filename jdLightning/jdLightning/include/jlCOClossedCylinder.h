/*****************************************************************************/
/**
 * @file    jlCOClossedCylinder.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    01/FEB/2022
 * @brief   A class for a ClossedCylinder (A compound object)
 *
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once
#include "jlCompoundObjects.h"
#include "jlVector3.h"
#include "jlNormal.h"

class jlClossedCylinder : public jlCompoundObject
{
 public:
		jlClossedCylinder();

  /**
   * @brief constructor with point and normal
   * @param pos is the sphere's position
   */
  jlClossedCylinder(const float& radio, const float& height, const jlVector3& pos) {
    m_ratio = radio;
    m_height = height;
    m_position = pos;
    m_type = GEOMETRITYPE::CYLINDER;
    createCylindre();
  }

		~jlClossedCylinder();

  private:
   friend class jlWorld;

   float m_ratio = 10;

   float m_height = 50;

   void createCylindre();
};
