/*****************************************************************************/
/**
	* @file    ray.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    26/10/2021
	* @brief   A basic class for a ray
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once

#include "jlPlatformDefines.h"
#include "jlVector3.h"
#include "jlPoint3.h"

namespace jlUtilitiesSDK
{
		class jlRay
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
				jlRay() : m_direction(0, 0, 0), m_origin(0, 0, 0) {};

				/**
					* @brief constructor with origini and direction of ray
					* @param origin is the postion of the origin of the ray
					* @param direction is the direction of the ray
					*/
				jlRay(const jlVector3 origin, const jlVector3 direction) :
						m_origin(origin), m_direction(direction) {};

				/**
					* @brief copy constructor
					* @param ray is the other ray to copy
					*/
				jlRay(const jlRay& ray) {
						m_origin = ray.m_origin;
						m_direction = ray.m_direction;
				};

				/**
					* @brief defaul destructor
					*/
				~jlRay() {};

/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/
				/**
					* @brief assignment operator
					* @param ray is the other ray to copy
					*/
				jlRay&
				operator=(const jlRay& ray) {
						m_origin = ray.m_origin;
						m_direction = ray.m_direction;
						return *this;
				};

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
				/**
					* @brief ray's origin
					*/
				jlPoint3 m_origin;

				/**
					* @brief ray's direction
					*/
				jlVector3 m_direction;
		};
}
