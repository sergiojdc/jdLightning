/*****************************************************************************/
/**
 * @file    jlGrid.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    03/FEB/2022
 * @brief   A class for a Grid (A compound object)
 *
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once
#include "jlCompoundObjects.h"
//#include "jlBoundingBox.h"

class jlGrid : public jlCompoundObject
{
public:
  /**
   * @brief defaul constructor
   */
		jlGrid();

  /**
   * @brief defaul constructor
   */
		~jlGrid();

  /**
   * @brief function to get the boundig box of grid
   * @return a jlBBox with the grid's jlBBox data
   */
  //virtual jlBBox
  //getBoundingBox();

  /**
   * @brief function to setup cells on in grid
   */
  void
  setupCells();

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
  /**
   * @brief vector to store the pointer
   */
  Vector<SPtr<jlGeometricObject>> m_cells;

  /**
   * @brief bounding box for grid
   */
  //jlBBox m_bbox;

  /**
   * @brief number of cells in x y z coordinates
   */
  uint32 nx, ny, nz;

  /**
   * @brief compute minimun grid cordinates
   */
  jlVector3
  min_coord();

  /**
   * @brief compute maximun grid cordinates
   */
  jlVector3
  max_coord();


  /**
   * @brief epislon const
   */
  static const double kEpsilon;
};