/*****************************************************************************/
/**
	* @file    jlGOBox.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    03/11/2021
	* @brief   A class for a box heredated by jlGeometriObject
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "jlGeometriObject.h"
#include "jlVector3.h"
#include "jlNormal.h"

class jlBox : public jlGeometricObject {
 public:
  /**
   * @brief defaul constructor
   */
   jlBox() {
     m_type = GEOMETRITYPE::BOX;
   };

  jlBox (const jlVector3& min, 
         const jlVector3& max, 
         const jlVector3& pos, 
         const jlVector3& offset = { 0, 0, 0 }) {
    m_type = GEOMETRITYPE::BOX;
    m_min = min;
    m_max = max;
    m_position = pos;
    m_offset = offset;
    calculateRealMinMax();
  }

		/**
			* @brief defaul destructor
			*/
  ~jlBox() {};


  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @pram sr is the shade rec
   * @return true if tha ray hit with it
   */
  virtual bool
  hit(const jlRay& ray, double& t, jlShadeRec& s) override;

  /**
   * @brief function to detected if the object is in shadow
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @return true if tha ray hit with it
   */
  virtual bool
  shadowHit(const jlRay& ray, float& tmin) override;

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
   * @brief epislon const
   */
  static const double kEpsilon;

  jlNormal
  getNormalFace(uint32 faceHit);

  void
  calculateRealMinMax() {
    m_realMax = m_position + m_offset + m_max;
    m_realMin = m_position + m_offset + m_min;
  };
};
