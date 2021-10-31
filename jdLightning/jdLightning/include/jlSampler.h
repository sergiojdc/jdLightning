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
#include <jlPoint2.h>
#include <algorithm>

class jlSample
{
 public:
		/**
			* @brief default constructor
			*/
		jlSample() = default;

		/**
			* @brief default destructor
			*/
		virtual ~jlSample() {};

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
    m_shuffledIndices.reserve(m_numSamples * m_numSets);
    std::vector<int> indices;
    for (int j = 0; j < m_numSamples; j++)
      indices.push_back(j);
    for (int p = 0; p < m_numSets; p++) {
      //RandomShuffle
      std::random_device rd;
      std::mt19937 g(rd());
      std::shuffle(indices.begin(), indices.end(), g);
      for (int j = 0; j < m_numSamples; j++)
        m_shuffledIndices.push_back(indices[j]);
    }
  };

  /**
   * @brief randomly shuffle the samples in each pattern
   */
  void
  shuffleSamples(); 

  /**
   * @brief get next sample on unit square
   */
  jlPoint2
  sampleUnitSquare(){
    if (m_count % m_numSamples == 0) // start of a new pixel
      m_jump = (randomInt() % m_numSets) * m_numSamples;
    return (m_samples[m_jump + m_count++ % m_numSamples]);
    //return (m_samples[m_jump + m_shuffledIndices[m_jump+ m_count++ % m_numSamples]]);
    //simple
    //int index = m_count++ % (m_numSamples * m_numSets);
    //if (index >= m_samples.size())
    //  index = m_samples.size() - 1;
    //return (m_samples[index]);
  };

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
  Vector<jlPoint2> m_samples;
		
		/**
   * @brief shuffled samples array indices
   */
		Vector<int32> m_shuffledIndices;

		/**
			* @brief random index jump
			*/
		unsigned long m_count;

		/**
			* @brief random index jump
			*/
		int32 m_jump;

};
