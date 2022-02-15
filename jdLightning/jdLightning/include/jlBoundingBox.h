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
   * @return true if the ray hit with it
   */
  virtual bool
  hit(const jlRay& ray, double& t, jlShadeRec& s);

  /**
   * @brief function to detected if a point is inside of bbox
   * @point ray is the point position on world
   * @return true if the point is inside 
   */
  virtual bool
  inside(const jlVector3& point);

  virtual void
  setPosition(const jlVector3& pos) {
    m_position = pos;
    calculateRealMinMax();
  };

  virtual void
  setOffset(const jlVector3& offset) {
    m_offset = offset;
    calculateRealMinMax();
  };

  virtual void
  setMin(const jlVector3& min) {
    m_min = min;
    calculateRealMinMax();
  };

  virtual void
  setMax(const jlVector3& max) {
    m_max = max;
    calculateRealMinMax();
  };

  virtual void
  setMinAndMax(const jlVector3& min, const jlVector3& max) {
    setMin(min);
    setMax(max);
  };

  virtual void
  updateRealMinAndMax(){
    calculateRealMinMax();
  };

 private:
friend class jlWorld;
friend class jlGrid;
friend class jlGeometricObject;
		/**
   * @brief min box position 
   */
  jlVector3 m_min = { 0,0,0 };
  
  /**
   * @brief real min box position, calculate with the min range, box's position and offset
   */
  jlVector3 m_realMin = { 0,0,0 };

  /**
   * @brief max box position 
   */
  jlVector3 m_max = { 0,0,0 };

  /**
   * @brief real max box position, calculate with the min range, box's position and offset
   */
  jlVector3 m_realMax = { 0,0,0 };

  /**
   * @brief box position offset
   */
  jlVector3 m_offset = { 0,0,0 };

  /**
   * @brief box position
   */
  jlVector3 m_position = { 0,0,0 };

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