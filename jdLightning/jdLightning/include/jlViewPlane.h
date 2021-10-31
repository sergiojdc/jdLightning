/**
 * @file    jlViewPlane.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    27/10/2021
 * @brief   A basic class for a view plane
 *
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once
#include "Prerequisites.h"

class jlViewPlane {
 public:
  /**
   * @brief defaul constructor
   */
  jlViewPlane() = default;

  /**
   * @brief constructor with params
   * @param hres is the width resolution for the view plane
   * @param hres is the height resolution for the view plane
   * @param psize is the size for pixels
   * @param gamma is the gamma of the view plane
   */
  jlViewPlane(uint32 wres, uint32 hres, const float& psize, const float& gamma ) {
    m_wRes = wres;
    m_hRes = hres;
    m_pixelSize = psize;
    m_gamma = gamma;
    m_invGamma = 1/gamma;
  };
  
  /**
   * @brief defaul destructor
   */
  ~jlViewPlane() {};

  /**
   * @brief width resolution
   */
  uint32 m_wRes;

  /**
   * @brief height resolution
   */
  uint32 m_hRes;

  /**
   * @brief pixel size
   */
  float m_pixelSize;

  /**
   * @brief gamma value
   */
  float m_gamma;

  /**
   * @brief one over gamma
   */
  float m_invGamma;

  /**
   * @brief num of samples
   */
  uint32 m_numSamples = 1;
};