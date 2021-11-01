/*****************************************************************************/
/**
	* @file    jlSample.h
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
   * @brief get next sample on unit square
   */
  jlVector2
  sampleUnitSquare() {
    if (m_count % m_numSamples == 0) // start of a new pixel
      m_jump = (jlRandom::randomInt0_255() % m_numSets) * m_numSamples;
    //uint32 idx = uint32(m_jump + m_count++ % m_numSamples);
    uint32 idxS = uint32(m_jump + m_count++ % m_numSamples);
    uint32 idx = uint32(m_jump + m_shuffledIndices[idxS]);
    return (m_samples[idx]);
    //return (m_samples[m_jump + m_shuffledIndices[m_jump+ m_count++ % m_numSamples]]);
    //simple
    //int index = m_count++ % (m_numSamples * m_numSets);
    //if (index >= m_samples.size())
    //  index = m_samples.size() - 1;
    //return (m_samples[index]);
  };

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
   * @brief shuffled samples array indices
   */
		Vector<int32> m_shuffledIndices;

		/**
			* @brief random index jump
			*/
		unsigned long m_count = 0;

		/**
			* @brief random index jump
			*/
		int32 m_jump = 0;

};
