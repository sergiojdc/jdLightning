/*****************************************************************************/
/**
 * @file    jlRadian.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Wrapper class which indicates a given angle value is in Radians.
 *
 * jlRadian values are interchangeable with jlDegree values, and conversions will
 * be done automatically between them.
 *
 * @bug	    No known bugs.
 */
 /*****************************************************************************/
#pragma once

#include "jlPrerequisitesUtil.h"

namespace jlUtilitiesSDK
{
  class jlDegree;

  class JL_UTILITY_EXPORT jlRadian
  {
/*****************************************************************************/
/**
 * Constructors
 */
/*****************************************************************************/
   public:
    /**
     * @brief Default constructor radian.
     */
    jlRadian() = default;

    /**
     * @brief constructor with other radian.
     * @param radian is the radian with which is equaled
     */
    jlRadian(const jlRadian& radian) = default;

    /**
     * @brief constructor with float.
     * @param radian is the float value
     */
    jlRadian(const float& radian) : m_radian(radian) {}

    /**
     * @brief constructor with a degree.
     * @param degree is the degree to cast
     */
    jlRadian(const jlDegree& degree);
   
/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/
   public:
    /**
     * @brief equals to float
     * @param f is the float with which is equaled
     */
    constexpr jlRadian&
    operator=(const float& f) {
      m_radian = f;
      return *this;
    }

    /**
     * @brief equals to radian
     * @param radian is the radian with which is equaled
     */
    constexpr jlRadian&
    operator=(const jlRadian& radian) = default;

    /**
     * @brief equals to degree
     * @param degree is the degree to cast with which is equaled
     */
    jlRadian&
    operator=(const jlDegree& degree);

    /**
     * @brief Get this radian on positive
     * @return the value of this radian on positive
     */
    const jlRadian&
    operator+() const {
      return *this;
    }

    /**
     * @brief add two radian
     * @param radian is the othe radian to add
     * @return the addition of this radian with other
     */
    jlRadian
    operator+(const jlRadian& radian) const {
      return jlRadian(m_radian + radian.m_radian);
    }

    /**
     * @brief add a degree with this radian
     * @param degree is the degree to add
     * @return the addition of this radian with the degree
     */
    jlRadian
    operator+(const jlDegree& degree) const;

    /**
     * @brief add two radian
     * @param radian is the othe radian to add
     * @return the addition of this radian with other in this radian
     */
    jlRadian&
    operator+=(const jlRadian& radian) {
      m_radian += radian.m_radian;
      return *this;
    }

    /**
     * @brief add a degree with this radian
     * @param degree is the degree to add
     * @return the addition of this radian with the degree in this radian
     */
    jlRadian&
    operator+=(const jlDegree& degree);

    /**
     * @brief Get this radian on negative
     * @return the value of this radian on negative
     */
    jlRadian
    operator-() const {
      return jlRadian(-m_radian);
    }

    /**
     * @brief subtrac two radian
     * @param radian is the other radian to subtrac
     * @return the subtraction of this radian with other
     */
    jlRadian
    operator-(const jlRadian& radian) const {
      return jlRadian(m_radian - radian.m_radian);
    }

    /**
     * @brief subtrac this radian with a degree
     * @param degree is the degree to subtrac
     * @return the subtraction of this radian with degree
     */
    jlRadian
    operator-(const jlDegree& degree) const;

    /**
     * @brief subtrac two radian
     * @param radian is the radian to subtrac
     * @return the subtraction of this radian with other in this radian
     */
    jlRadian&
    operator-=(const jlRadian& radian) {
      m_radian -= radian.m_radian;
      return *this;
    }

    /**
     * @brief subtrac this radian with a degree
     * @param radian is the othe radian to subtrac
     * @return the subtraction of this radian with degree in this radian
     */
    jlRadian&
    operator-=(const jlDegree& degree);

    /**
     * @brief multiplicate this radian with a float
     * @param f is the float to multply the radian
     * @return the result of multiplication
     */
    jlRadian
    operator*(float f) const {
      return jlRadian(m_radian * f);
    }

    /**
     * @brief multiplicate this radian with a radian
     * @param radian is the radian to multply this radian
     * @return the result of multiplication
     */
    jlRadian
    operator*(const jlRadian& radian) const {
      return jlRadian(m_radian * radian.m_radian);
    }
    
    /**
     * @brief multiplicate this radian with a float
     * @param f is the float to multply the radian
     * @return the result of multiplication in this radian
     */
    jlRadian&
    operator*=(float f) {
      m_radian *= f;
      return *this;
    }

    /**
     * @brief multiplicate this radian with a radian
     * @param radian is the radian to multply this radian
     * @return the result of multiplication in this radian
     */
    jlRadian&
    operator*=(const jlRadian& radian) {
      m_radian *= radian.m_radian;
      return *this;
    }

    /**
     * @brief divide this radian with a float
     * @param f is the float to divide the radian
     * @return the result of division
     */
    jlRadian
    operator/(float f) const {
      return jlRadian(m_radian / f);
    }

    /**
     * @brief divide this radian with a float
     * @param f is the float to divide the radian
     * @return the result of division in this radian
     */
    jlRadian&
    operator/=(float f) {
      m_radian /= f;
      return *this;
    }

    /**
     * @brief divide two radians
     * @param radian is the radian to divide this radian
     * @return the result of division
     */
    jlRadian
    operator/(const jlRadian& radian) const {
      return jlRadian(m_radian / radian.m_radian);
    }

    /**
     * @brief divide two radians
     * @param radian is the radian to divide this radian
     * @return the result of division in this radian
     */
    jlRadian&
    operator/=(const jlRadian& radian) {
      m_radian /= radian.m_radian;
      return *this;
    }

    /**
     * @brief compare two radians
     * @param radian is the radian to compare
     * @return true if this randian is less
     */
    bool
    operator<(const jlRadian& radian) const {
      return m_radian < radian.m_radian;
    }

    /**
     * @brief compare two radians
     * @param radian is the radian to compare
     * @return true if this randian is less or equal
     */
    bool
    operator<=(const jlRadian& radian) const {
      return m_radian <= radian.m_radian;
    }

    /**
     * @brief compare two radians
     * @param radian is the radian to compare
     * @return true if the randians are identical
     */
    bool
    operator==(const jlRadian& radian) const {
      return m_radian == radian.m_radian;
    }

    /**
     * @brief compare two radians
     * @param radian is the radian to compare
     * @return true if the randians are diferent
     */
    bool
    operator!=(const jlRadian& radian) const {
      return m_radian != radian.m_radian;
    }

    /**
     * @brief compare two radians
     * @param radian is the radian to compare
     * @return true if this randian is greater or equal
     */
    bool
    operator>=(const jlRadian& radian) const {
      return m_radian >= radian.m_radian;
    }

    /**
     * @brief compare two radians
     * @param radian is the radian to compare
     * @return true if this randian is greater
     */
    bool
    operator>(const jlRadian& radian) const {
      return m_radian > radian.m_radian;
    }

    /**
     * @brief compare this radian with a float
     * @param f is the float to compare
     * @return true if this randian's value is less than the float
     */
    bool
    operator<(const float& f) const {
      return m_radian < f;
    }

    /**
     * @brief compare this radian with a float
     * @param f is the float to compare
     * @return true if this randian's value is less or equal than the float
     */
    bool
    operator<=(const float& f) const {
      return m_radian <= f;
    }

    /**
     * @brief compare this radian with a float
     * @param f is the float to compare
     * @return true if this randian's value is identical to the float
     */
    bool
    operator==(const float& f) const {
      return m_radian == f;
    }

    /**
     * @brief compare this radian with a float
     * @param f is the float to compare
     * @return true if this randian's value is diferent to the float
     */
    bool
    operator!=(const float& f) const {
      return m_radian != f;
    }

    /**
     * @brief compare this radian with a float
     * @param f is the float to compare
     * @return true if this randian's value is greater or equal than the float
     */
    bool
    operator>=(const float& f) const {
      return m_radian >= f;
    }

    /**
     * @brief compare this radian with a float
     * @param f is the float to compare
     * @return true if this randian's value is greater than the float
     */
    bool 
    operator>(const float& f) const {
      return m_radian > f;
    }

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/
    /**
     * @brief multiplicate a float with a radian
     * @param lhs is the float to multply the radian
     * @param rhs is the radian that will be multiplied 
     * @return the result of multiplication
     */
    friend jlRadian
    operator*(float lhs, const jlRadian& rhs) {
      return jlRadian(lhs * rhs.m_radian);
    }

    /**
     * @brief divide a float with a radian
     * @param lhs is the float to divide the radian
     * @param rhs is the radian that will be dvided
     * @return the result of divition
     */
    friend jlRadian
    operator/(float lhs, const jlRadian& rhs) {
      return jlRadian(lhs / rhs.m_radian);
    }

    /**
     * @brief add a radian with a float
     * @param lhs is the radian to will add the float
     * @param rhs is the float that will be added
     * @return the result of addition
     */
    friend jlRadian
    operator+(jlRadian& lhs, float rhs) {
      return jlRadian(lhs.m_radian + rhs);
    }

    /**
     * @brief add a float with a radian
     * @param lhs is the float to will add the radian
     * @param rhs is the radian that will be added
     * @return the result of addition
     */
    friend jlRadian
    operator+(float lhs, const jlRadian& rhs) {
      return jlRadian(lhs + rhs.m_radian);
    }

    /**
     * @brief subtract a radian with a float
     * @param lhs is the radian to will subtract the float
     * @param rhs is the float that will be subtracted
     * @return the result of subtraction
     */
    friend jlRadian
    operator-(const jlRadian& lhs, float rhs) {
      return jlRadian(lhs.m_radian - rhs);
    }

    /**
     * @brief subtract a float with a radian
     * @param lhs is the float to will subtract the radian
     * @param rhs is the radian that will be subtracted
     * @return the result of subtraction
     */
    friend jlRadian
    operator-(const float lhs, const jlRadian& rhs) {
      return jlRadian(lhs - rhs.m_radian);
    }

    /**
     * @brief compare a float with a radian
     * @param lhs is the float to will compare the radian
     * @param rhs is the radian that will be compared
     * @return true if the float is less 
     */
    friend bool
    operator<(float lhs, const jlRadian& rhs) {
      return lhs < rhs.m_radian;
    }

    /**
     * @brief compare a float with a radian
     * @param lhs is the float to will compare the radian
     * @param rhs is the radian that will be compared
     * @return true if the float is less or equal
     */
    friend bool
    operator<=(float lhs, const jlRadian& rhs) {
      return lhs <= rhs.m_radian;
    }

    /**
     * @brief compare a float with a radian
     * @param lhs is the float to will compare the radian
     * @param rhs is the radian that will be compared
     * @return true if the float is identical to the radian
     */
    friend bool
    operator==(float lhs, const jlRadian& rhs) {
      return lhs == rhs.m_radian;
    }

    /**
     * @brief compare a float with a radian
     * @param lhs is the float to will compare the radian
     * @param rhs is the radian that will be compared
     * @return true if the float is diferent to the radian
     */
    friend bool
    operator!=(float lhs, const jlRadian& rhs) {
      return lhs != rhs.m_radian;
    }

    /**
     * @brief compare a float with a radian
     * @param lhs is the float to will compare the radian
     * @param rhs is the radian that will be compared
     * @return true if the float is greater or equal
     */
    friend bool
    operator>=(float lhs, const jlRadian& rhs) {
      return lhs >= rhs.m_radian;
    }

    /**
     * @brief compare a float with a radian
     * @param lhs is the float to will compare the radian
     * @param rhs is the radian that will be compared
     * @return true if the float is greater
     */
    friend bool
    operator>(float lhs, const jlRadian& rhs) {
      return lhs > rhs.m_radian;
    }

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/
   public:
     /**
      * @brief get the value of this radian on degree
      * @return the value of this radian on degree
      */
    float
    valueDegrees() const;

    /**
      * @brief get the value of this radian on radian
      * @return the value of this radian on radian
      */
    FORCEINLINE float
    valueRadians() const {
      return m_radian;
    }

    /**
     * @brief Utility to ensure angle is between +/- PI range by unwinding.
     */
    void
    unwindRadians();

/*****************************************************************************/
/**
 * Mmebers
 */
/*****************************************************************************/
  private:
    /**
     * @brief Randian value
     */
    float m_radian = 0.0f;
  };
}
