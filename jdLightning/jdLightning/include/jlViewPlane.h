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
#include "jlSampler.h"
#include "jlSJittered.h"
#include "jlSRegular.h"

class jlViewPlane {
 public:
  /**
   * @brief defaul constructor
   */
  jlViewPlane() {
    m_wRes = 400;
    m_hRes = 400;
    m_pixelSize = 1;
    m_gamma = 1;
    m_invGamma = 1 / m_gamma;
    m_numSamples = 1;
    m_pSampler = nullptr;
  };

  /**
   * @brief constructor with params
   * @param hres is the width resolution for the view plane
   * @param hres is the height resolution for the view plane
   * @param psize is the size for pixels
   * @param gamma is the gamma of the view plane
   * @note if psampler isn't null, the numsamplers change to the num in the psampler, 
   *       in this case the function of jlSampler "generateSamples" isn't called in view port
   *       and not set the numsets
   *       if psampler is null, is going to create a jittleredsample with the numSamplers.
   *       in this case the function of jlSampler "generateSamples" is called in view port and
   *       set de numsets
   */
  jlViewPlane(uint32 wres, 
              uint32 hres, 
              const float& psize, 
              const float& gamma, 
              uint32 numSamplers = 0,
              SPtr<jlSampler> psampler = nullptr) {
    m_wRes = wres;
    m_hRes = hres;
    m_pixelSize = psize;
    m_gamma = gamma;
    m_invGamma = 1/gamma;
    m_numSamples = numSamplers;
    m_pSampler = psampler;
    if (m_pSampler) {
      m_numSamples = m_pSampler->getNumSamples();
    }
    else {
      if (numSamplers > 1) {
        m_pSampler.reset(new jlSJittered(m_numSamples));
      }
      else {
        m_pSampler.reset(new jlSRegular(m_numSamples));
      }
      m_pSampler->setNumSets(m_wRes * m_hRes);
      m_pSampler->generateSamples();
      m_pSampler->setupShuffledIndices();
      m_pSampler->mapSamplerToUnitDisk();
    }
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

  /**
   * @brief sampler to use
   */
  SPtr<jlSampler> m_pSampler;

  /**
   * @brief to show color out of gamma
   */
  bool m_bShowOutOfGamut = true;
};