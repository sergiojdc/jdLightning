/*****************************************************************************/
/**
	* @file    jlBoundingBox.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    03/11/2021
	* @brief   A class for a boundig box
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include "jlVector3.h"
#include "jlNormal.h"

class jlBBox {
 public:
  /**
   * @brief defaul constructor
   */
  jlBBox() {};

  jlBBox(const jlVector3& min,
         const jlVector3& max, 
         const jlVector3& pos, 
         const jlVector3& offset = { 0, 0, 0 }) {
   m_min = min;
   m_max = max;
   m_position = pos;
   m_offset = offset;
   calculateRealMinMax();
  }

		/**
			* @brief defaul destructor
			*/
  ~jlBBox() {};

  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @pram sr is the shade rec
   * @return true if tha ray hit with it
   */
  virtual bool
  hit(const jlRay& ray, double& t, jlShadeRec& s);

 private:
friend class jlWorld;
		/**
   * @brief min box position 
   */
  jlVector3 m_min;
  
  /**
   * @brief real min box position, calculate with the min range, box's position and offset
   */
  jlVector3 m_realMin;

  /**
   * @brief max box position 
   */
  jlVector3 m_max;

  /**
   * @brief real max box position, calculate with the min range, box's position and offset
   */
  jlVector3 m_realMax;

  /**
   * @brief box position offset
   */
  jlVector3 m_offset;

  /**
   * @brief box position
   */
  jlVector3 m_position;

  /**
   * @brief epislon const
   */
  static const double kEpsilon;

  void
  calculateRealMinMax() {
    m_realMax = m_position + m_offset + m_max;
    m_realMin = m_position + m_offset + m_min;
  };
};