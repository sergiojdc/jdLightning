/*****************************************************************************/
/**
 * @file    jlQuaternion.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   A basic quaternion
 *
 * The quaternion had component x, y, z, w
 *
 *
 * @bug	    No known bugs.
 */
/*****************************************************************************/
#pragma once

#include "jlPrerequisitesUtil.h"
#include "jlVector3.h"
#include "jlMatrix4.h"
#include "jlRadian.h"

namespace jlUtilitiesSDK {
  class JL_UTILITY_EXPORT jlQuaternion {
/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/
   public:
    /**
     * @brief Default constructor (no initialization).
     */
    FORCEINLINE jlQuaternion() = default;
    
    /**
     * @brief Constructor.
     * @param x is the x component of the quaternion
     * @param y is the y component of the quaternion
     * @param z is the z component of the quaternion
     * @param w is the w component of the quaternion
     */
    jlQuaternion(const float& x, const float& y, const float& z);
    jlQuaternion(const float& x, const float& y, const float& z, const float& w);
    jlQuaternion(const jlRadian& x, const jlRadian& y, const jlRadian& z);
    jlQuaternion(const jlDegree& x, const jlDegree& y, const jlDegree& z);
    
    /**
     * @brief Constructor.
     * @param x, y, z is for x, y, z components of the quaternion
     * @param w is the w component of the quaternion
     */
    jlQuaternion(jlVector3 xyz, const float& w);
    
    /**
     * @brief Copy Constructor 
     * @param quaternion is the quaternion to copy
     */
    jlQuaternion(const jlQuaternion& quaternion);

/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/
   public:
    /** 
     * @brief equals a quaternion 
     * @param quaternion is a quaternion what this with which is equaled
     * @return this quaternio equalize.
     */
    jlQuaternion& 
    operator=(const jlQuaternion& quaternion);
    
    /** 
     * @brief add two quaternions
     * @param quaternion is another quaternion.
     * @return the addition in this quaternion.
     */
    jlQuaternion&
    operator+=(const jlQuaternion& quaternion);
    
    /**
     * @brief add two quaternions
     * @param quaternion is another quaternion.
     * @return a quiaternion with the addition.
     */
    jlQuaternion 
    operator+(const jlQuaternion& quaternion) const;
    
    /**
     * @brief subtract two quaternions.
     * @param quaternion is another quaternion.
     * @return a quiaternion with the subtraction in this quaternion.
     */
    jlQuaternion&
    operator-=(const jlQuaternion& quaternion);
    
    /**
     * @brief subtract two quaternions
     * @param quaternion is another quaternion.
     * @return a quiaternion with the subtraction.
     */
    jlQuaternion 
    operator-(const jlQuaternion& quaternion) const;
    
    /** 
     * @brief Multiply two quaternion.
     * @param quaternion Another quaternion.
     * @return the multiplication in this quaternion
     */
    jlQuaternion&
    operator*=(const jlQuaternion& quaternion);
    
    /**
     * @brief Multiply two quaternion.
     * @param quaternion Another quaternion.
     * @return a quaternion with the multiplication
     */
    jlQuaternion 
    operator*(const jlQuaternion& quaternion) const;
    
    /**
     * @brief Multiply this quaternion with a scale
     * @param scale is the value to multiply the quaternion.
     * @return the multiplication in this quaternion
     */
    jlQuaternion&
    operator*=(const float& scale);
    
    /**
     * @brief Multiply this quaternion with a scale
     * @param scale is the value to multiply the quaternion.
     * @return a quaternion with the multiplication
     */
    jlQuaternion 
    operator*(const float& scale) const;
    
    /**
     * @brief Compare two quaternions
     * @param quaternion is the quaternion with which it will be compared
     * @return true if this quaternion is identical to the other  
     */
    bool
    operator==(const jlQuaternion& quaternion) const;
    
    /**
     * @brief Compare two quaternions
     * @param quaternion is the quaternion with which it will be compared
     * @return true if this quaternion is diferent to the other  
     */
    bool
    operator!=(const jlQuaternion& quaternion) const;
    
    /**
     * @brief Compare two quaternions
     * @param quaternion is the quaternion with which it will be compared
     * @return true if this quaternion is less than the other  
     */
    bool
    operator<(const jlQuaternion& quaternion) const;
    
    /**
     * @brief Compare two quaternions
     * @param quaternion is the quaternion with which it will be compared
     * @return true if this quaternion is greater than the other  
     */
    bool 
    operator>(const jlQuaternion& quaternion) const;

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/
    /** 
     * @brief get the magnitud of this quaternion
     * @return the magnitude of this quaternion.
     */
    float
    magnitude() const;
    
    /**
     * @brief get the sauqre magnitud of this quaternion
     * @return the magnitude of this quaternion.
     */
    float
    squareMagnitude() const;
    
    /** 
     * @brief tranform this quaternion to it's normalized form.
     * @return this quaternion normalized.
     */
    jlQuaternion&
    normalize();
    
    /** 
     * @brief tranform this quaternion to it's normalized form.
     * @return None.
     */
    jlQuaternion
    getNormalize() const;
    
    /** 
     * @brief conjugate this quaternion.
     * @return this quaternion conjugated.
     */
    jlQuaternion&
    conjugate();
    
    /**
     * @brief get the conjugate of this quaternion.
     * @return A quaternion with the conjugate of this quaternion.
     */
    jlQuaternion
    getConjugate() const;
    
    /**
     * @brief invert this quaternion.
     * @return this quaternion inverted.
     */
    jlQuaternion& 
    inverse();
    
    /**
     * @brief get the inverse form of this quaternion.
     * @return A quaternion with the inverse form of this quaternion.
     */
    jlQuaternion 
    getInverse() const;

    /**
     * @brief get to rotate this quaternion.
     * @return this quaternion rotated
     */
    jlQuaternion&
    rotate(const float& _x, const float& _y, const float& _z, bool degree);

    /**
     * @brief get to rotate this quaternion.
     * @return this quaternion rotated
     */
    jlQuaternion&
    rotate(jlDegree _x, jlDegree _y, jlDegree _z);

    /**
     * @brief get to rotate this quaternion.
     * @return this quaternion rotated
     */
    jlVector3
    getEuler();

    jlVector3
    getRadians();

    jlMatrix4
    getMatrix() const;
/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
   public:
    /**
     * @brief The quaternion's X-component.
     */
    float x;

    /**
     * @brief The quaternion's Y-component.
     */
    float y;

    /**
     * @brief The quaternion's Z-component.
     */
    float z;

    /**
     * @brief The quaternion's W-component.
     */
    float w;
		};
}
