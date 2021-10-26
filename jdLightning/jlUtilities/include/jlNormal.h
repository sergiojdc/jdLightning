/*****************************************************************************/
/**
 * @file    jlNormal.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for a normal
 *
 * Structure for color rgba.
 *
 * @bug     No known bugs.
 */
#pragma once

#include "jlPlatformDefines.h"
#include "jlVector3.h"

namespace jlUtilitiesSDK {
		class jlNormal : public jlVector3
		{
/*****************************************************************************/
/**
 * Constructor
 */
/*****************************************************************************/
		 public:
    /**
     * @brief defaul constructor
     */
    jlNormal() { x = 0; y = 0; z = 0; };

    /**
     * @brief constructor with float params with default 0.
     * @param _x for x cordinate
     * @param _y for y cordinate
     * @param _z for z cordinate
     */
    jlNormal(const float& _x, const float& _y = 0.0f, const float& _z = 0.0f) {
      x = _x; y = _y; z = _z;
      normalize();
    };

    /**
     * @brief constructor with a array float 4 params.
     * @param _xyz for x, y ,z cordinate
     */
    jlNormal(const float _xyz[3]) {
      x = _xyz[0]; y = _xyz[1]; z = _xyz[2];
      normalize();
    };

    /**
     * @brief constructor with a jlVector2 and float params.
     * @param _xy for x, y cordinate
     * @param _z for z cordinate
     */
    jlNormal(const jlVector2& _xy, const float& _z = 0.0f) {
      x = _xy.x; y = _xy.y; z = _z;
      normalize();
    };

    /**
     * @brief constructor with a jlVector3 and float params.
     * @param vec for x, y, z cordinate
     */
    jlNormal(const jlVector3& vec) {
      x = vec.x; y = vec.y; z = vec.z;
      normalize();
    };

    /**
     * @brief defaul destructor
     */
    ~jlNormal() {};
/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/
    /**
					* @brief assignment operator
					* @param ray is the other ray to copy
					*/
    jlNormal&
				operator=(const jlNormal& normal) {
						x = normal.x;
						y = normal.y;
						z = normal.z;
						return *this;
				};

		};
}