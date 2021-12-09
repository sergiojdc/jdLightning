/*****************************************************************************/
/**
	* @file    jlSampler.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    31/10/2021
	* @brief   A virtual class for any kind of sample
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include <jlVector2.h>
#include <jlVector3.h>
#include <jlRandom.h>

class jlSampler
{
 public:
		/**
			* @brief default constructor
			*/
  jlSampler() = default;

		/**
			* @brief default destructor
			*/
		virtual ~jlSampler() {};

  /**
   * @brief generate sample patterns in a unit square
   */
  virtual void
  generateSamples() {};

  /**
   * @brief set up the randomly shuffled indices
   */
  void
  setupShuffledIndices() {
    auto mult = m_numSamples * m_numSets;
    m_shuffledIndices.reserve(mult);
    Vector<uint32> indices;
    for (uint32 j = 0; j < m_numSamples; j++)
      indices.push_back(j);
    for (uint32 p = 0; p < m_numSets; p++) {
      //RandomShuffle
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(indices.begin(), indices.end(), g);
      for (uint32 j = 0; j < m_numSamples; j++)
        m_shuffledIndices.push_back(indices[j]);
    }
  };

  /**
   * @brief randomly shuffle the samples in each pattern
   */
  void
  shuffleSamples() {}; 

  /**
   * @brief map samplers to unit disk
   */
  void
  mapSamplerToUnitDisk();

  /**
   * @brief map samplers to hemisphere
   */
  void
  mapSamplesToHemisphere(const float& e);

  /**
   * @brief get next sample on unit square
   */
  jlVector2
  sampleUnitSquare() {
    if (m_count % m_numSamples == 0) // start of a new pixel
      m_jump = (jlRandom::randomInt() % m_numSets) * m_numSamples;
    //uint32 idx = uint32(m_jump + m_count++ % m_numSamples);
    uint32 idxS = uint32(m_jump + m_count++ % m_numSamples);
    uint32 idx = uint32(m_jump + m_shuffledIndices[idxS]);
    return (m_samples[idx]);
  };

  /**
   * @brief get next sample on unit square
   */
  jlVector2
  sampleUnitSquare(uint32 index) {
    if (!omtimized) {
      return sampleUnitSquare();
    }
    uint32 idx = index;
    if (index >= m_samples.size()) {
      idx = index - m_samples.size();
    }
    //suint32 idxS = uint32(m_jump + m_count++ % m_numSamples);
    //suint32 idx = uint32(m_jump + m_shuffledIndices[idxS]);
    return (m_samples[idx]);
  };

  /**
   * @brief get next sample on unit disk
   */
  jlVector2
  sampleUnitDisk() {
    if (m_countDisk % m_numSamples == 0) // start of a new pixel
      m_jump = (jlRandom::randomInt() % m_numSets) * m_numSamples;
    uint32 indx = uint32(m_jump + m_countDisk++ % m_numSamples);
    return (m_diskSamples[indx]);
  }

  /**
   * @brief get next sample on hemisphere
   */
  jlVector3
  sampleHemisphere() {
    if (m_countHemisphere % m_numSamples == 0) // start of a new pixel
      m_jumpHemisphere = (jlRandom::randomInt() % m_numSets) * m_numSamples;
    uint32 indx = uint32(m_jumpHemisphere + m_countHemisphere++ % m_numSamples);
    return (m_hemisphereSamples[indx]);
  }

  jlVector3
  sampleHemisphere(uint32 index) {
    if (!omtimized) {
      return sampleHemisphere();
    }
    uint32 idx = index;
    if (index >= m_hemisphereSamples.size()) {
      idx = index - m_samples.size();
    }
    return (m_hemisphereSamples[idx]);
  }

  /**
   * @brief function to get the number of samples
   * @return the number of samples
   */
  uint32
  getNumSamples() {
    return m_numSamples;
  }

  /**
   * @brief function to set the number of sets
   * @param numsets is the number of sets
   * @note the num of sets are the number of pixels
   */
  void
  setNumSets(uint32 numsets) {
    m_numSets = numsets;
  }

 protected:
  /**
   * @brief the number of sample points in a pattern
   */
  uint32 m_numSamples;

  /**
   * @brief the number of sample sets (patterns) stored
   */
		uint32 m_numSets;

  /**
   * @brief sample points on a unit square
   */
  Vector<jlVector2> m_samples;

  /**
   * @brief sample points on a unit disk
   */
  Vector<jlVector2> m_diskSamples;

  /**
   * @brief sample points on a hemisphere
   */
  Vector<jlVector3> m_hemisphereSamples;
		
		/**
   * @brief shuffled samples array indices
   */
		Vector<int32> m_shuffledIndices;

		/**
			* @brief random index jump
			*/
		unsigned long m_count = 0;
		unsigned long m_countDisk = 0;
  unsigned long m_countHemisphere = 0;

		/**
			* @brief random index jump
			*/
		int32 m_jump = 0;
		int32 m_jumpHemisphere = 0;


  bool omtimized = true;
};
