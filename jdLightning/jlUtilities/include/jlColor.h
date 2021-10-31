/*****************************************************************************/
/**
 * @file    jlColor.h
 * @author  Sergio Diaz (sergio_jdc@hotmail.com)
 * @date    26/10/2021
 * @brief   Structure for a color in rgba, tha values are in unit
 *
 * Structure for color rgba.
 *
 * @bug     No known bugs.
 */
#pragma once

#include "jlPlatformDefines.h"
#include "jlVector3.h"
#include "jlVector4.h"

namespace jlUtilitiesSDK {

  class jlColor {
  /*****************************************************************************/
  /**
   * Constructors
   */
  /*****************************************************************************/	
   public:
    /**
     * @brief constructor with floats params with default 0, except alpha with 1.
     * @param _r for r value
     * @param _g for g value
     * @param _b for b value
     * @param _a for a value
     */
    jlColor(const float& _r = 0.0f,
            const float& _g = 0.0f,
    		      const float& _b = 0.0f, 
            const float& _a = 1.0f,
            bool inUnit = true,
            bool limited = true) : r(_r), 
                                   g(_g),
                                   b(_b), 
                                   a(_a),
                                   m_isUnit(inUnit), 
                                   m_limitedMax(limited) { 
      makeNegativeTo0();
      makeLimited();
    };

    /**
     * @brief constructor with floats params with default 0, except alpha with 1.
     * @param _rgb is a 3dvector for rgb value
     * @param _a for a value
     */
    jlColor(const jlVector3& _rgb, 
            const float& _a = 1.0f,
            bool inUnit = true,
            bool limited = true) : r(_rgb.x), 
                                   g(_rgb.y), 
                                   b(_rgb.z), 
                                   a(_a), 
                                   m_isUnit(inUnit), 
                                   m_limitedMax(limited) { 
      makeNegativeTo0();
      makeLimited();
    };

    /**
     * @brief constructor with floats params with default 0, except alpha with 1.
     * @param _rgb is a 3dvector for rgb value
     * @param _a for a value
     */
    jlColor(const jlVector4& _rgba, bool inUnit = true, bool limited = true) : 
              r(_rgba.x), 
              g(_rgba.y), 
              b(_rgba.z), 
              a(_rgba.w),
              m_isUnit(inUnit), 
              m_limitedMax(limited) { 
      makeNegativeTo0(); 
      makeLimited();
    };

    ~jlColor() {};

/*****************************************************************************/
/**
 * Operators
 */
/*****************************************************************************/

   public:
    /**
     * @brief Negative operator
     * @return A new point negative of this vector
     */
    jlColor
    operator-() const;
    
    /**
     * @brief Positive operator
     * @return A new point Positive of this vector
     */
    jlColor
    operator+() const;
    
    /**
     * @brief add two vectors
     * @param color is the othe vector to add
     * @return the addition of this vector with other
     */
    jlColor
    operator+(const jlColor& color) const;
    
    /**
     * @brief substraction of two vectors
     * @param color is the othe vector to subtrac
     * @return the substraction of this vector with other
     */
    jlColor
    operator-(const jlColor& color) const;
    
    /**
     * @brief modificque this vector adding other vector
     * @param color is the othe vector to add
     * @return the addition of this vector with other in this vector
     */
    jlColor&
    operator+=(const jlColor& color);
    
    /**
     * @brief modificque this vector subtacting other vector
     * @param color is the othe vector to subtrac
     * @return the substraction of this vector with other in this vector
     */
    jlColor&
    operator-=(const jlColor& color);
    
    /**
     * @brief Get the result of scaling on this vector.
     * @param scale What to multiply the vector by.
     * @return A new scaled vector.
     */
    jlColor
    operator*(const float& scale) const;
    
    /**
     * @brief Get the result of multiply this vector with other vector.
     * @param color What to multiply the vector by.
     * @return the result of the multiply this vector with other.
     */
    jlColor
    operator*(const jlColor& color) const;
    
    /**
     * @brief Scale this vector
     * @param Scale What to multiply this vector by.
     * @return the result of the multiply in this vector.
     */
    jlColor&
    operator*=(const float& scale);
    
    /**
     * @brief multiply this vector with other vector.
     * @param color What to multiply this vector by.
     * @return the result of the multiply this vector with other in this vector.
     */
    jlColor&
    operator*=(const jlColor& color);
    
    /**
     * @brief divition of vector with a scale.
     * @param scale What to divide the vector by.
     * @return the result of the dividetion.
     */
    jlColor
    operator/(const float& scale) const;
    
    /**
     * @brief divition of vector with an other vector.
     * @param color is a vector What to divide the vector by.
     * @return a vector with the result of the dividetion.
     */
    jlColor
    operator/(const jlColor& color) const;
    
    /**
     * @brief divition of this vector with a scale.
     * @param scale What to divide this vector by.
     * @return the result of the dividetion in this vector.
     */
    jlColor&
    operator/=(const float& scale);
    
    /**
     * @brief divition of this vector with an other vector.
     * @param color is vector What to divide this vector by.
     * @return the result of the dividetion in this vector.
     */
    jlColor&
    operator/=(const jlColor& color);
    
    /**
     * @brief compare a vector with an other vector.
     * @param color is vector What to compare vector by.
     * @return true if all components are equal
     */
    bool
    operator==(const jlColor& color) const;
    
    /**
     * @brief compare a vector with an other vector.
     * @param color is vector What to compare vector by.
     * @return true if one component is diferent
     */
    bool
    operator!=(const jlColor& color) const;
    
    /**
     * @brief compare a vector with an other vector.
     * @param color is vector What to compare vector by.
     * @return true if one component is less
     */
    bool
    operator<(const jlColor& color) const;
    
    /**
     * @brief compare a vector with an other vector.
     * @param color is vector What to compare vector by.
     * @return true if one component is major
     */
    bool
    operator>(const jlColor& color) const;
    
    /**
     * @brief get the component in a index
     * @param index is index of component in the vector.
     * @return a const of the component in the index
     */
    float
    operator[](uint32 index) const;
    
    /**
     * @brief get the component in a index
     * @param index is index of component in the vector.
     * @return a reference of the component in the index
     */
    float&
    operator[](uint32 index);
    
    /**
     * @brief queal this vector to other vector.
     * @param color is vector What to equal vector by.
     * @return this vector equaled
     */
    jlColor&
    operator=(const jlColor& color);

/*****************************************************************************/
/**
 * Friends
 */
/*****************************************************************************/

    /**
     * @brief multiplicate the components of a vector for a constant
     * @param scale multply the components
     * @return the result of multiplication.
     */
    friend jlColor
    operator*(const float& a, const jlColor& color);
    
    /**
     * @brief out stream the vector
     * @return the values of the vector.
     */
    friend std::ostream&
    operator<<(std::ostream& os, const jlColor& color);

/*****************************************************************************/
/**
 * Functions
 */
/*****************************************************************************/
   public:

    /**
     * @brief function to check if the color is in unit or not
     * @return true if the color is in unit
     */
    bool
    isInUnits(){
      return m_isUnit;
    }

    /**
     * @brief function to check if the color is limited to max (1 or 255)
     * @return true if the color is limited
     */
    bool
    isLimited(){
      return m_limitedMax;
    }

    /**
     * @brief function to set colo in unit or not
     * @note for default, units are active when the color is created
     */
    void
    setInUnits(bool active = true) {
      m_isUnit = active;
      if (m_isUnit)
        makeUnit();
      else
        make255();

      makeLimited();
    };

    /**
     * @brief function to set colo in limted to 1, 255 or not
     * @note for default, limit are active when the color is created
     */
    void
    setLimited(bool active = true) {
      m_limitedMax = active;
      makeLimited();
    };

    /**
     * @brief function to make the values between 0-1
     * @return this color with values in unit
     */
    jlColor&
    makeUnit();

    /**
     * @brief function to make the values between 0-255
     * @return this color with values in unit
     */
    jlColor&
    make255();

    /**
     * @brief function to make the values between 0 to max value
     * @return this color limited
     */
    jlColor&
    makeLimited();

    /**
     * @brief function get the color in units for 4dvector
     * @return jdvector with values rgba in unit
     */
    jlVector4
    getInUnit() const;

    /**
     * @brief function get the color in 255 value for 4dvector
     * @return jdvector4 with values rgba in 255 value
     */
    jlVector4
    getIn255() const;

   private:
    /**
     * @brief function to make the values between 0 to max value
     * @return this color limited
     */
    void
    makeNegativeTo0();

/*****************************************************************************/
/**
 * Static Functions
 */
/*****************************************************************************/
   public:
    /**
     * @brief static function to get a red color in units
     * @return color red in units
     */
    static jlColor
    Red() { return {1.0f, 0.0f, 0.0f, 1.0}; }

    /**
     * @brief static function to get a blue color in units
     * @return color blue in units
     */
    static jlColor
    Blue() { return {0.0f, 0.0f, 1.0f, 1.0f}; }

    /**
     * @brief static function to get a green color in units
     * @return green blue in units
     */
    static jlColor
    Green() { return {0.0f, 1.0f, 0.0f, 1.0f}; }

    /**
     * @brief static function to get a black color in units
     * @return color black in units
     */
    static jlColor
    Black() { return {0.0f, 0.0f, 0.0f, 1.0f}; }

    /**
     * @brief static function to get a white color in units
     * @return color white in units
     */
    static jlColor
    White() { return {1.0f, 1.0f, 1.0f, 1.0f}; }

/*****************************************************************************/
/**
 * Members
 */
/*****************************************************************************/
   public:
    /**
     * @brief Vector's components.
     */
    union {
      /**
       * @brief struc in xyzw format.
       */
      struct {
        /**
         * @brief Color's x component.
         */
        float x;
        /**
         * @brief Color's y component.
         */
        float y;
        /**
         * @brief Color's z component.
         */
        float z;
        /**
         * @brief Color's w component.
         */
        float w;
						};
      /**
       * @brief struc in rgba format.
       */
      struct {
        /**
         * @brief Color's r component.
         */
        float r;
        /**
         * @brief Color's g component.
         */
        float g;
        /**
         * @brief Color's b component.
         */
        float b;
        /**
         * @brief Color's a component.
         */
        float a;
      };
      /**
       * @brief Vector's components as array.
       */
      float C[4];
    };

   private:
    bool m_isUnit = true;
    bool m_limitedMax = true;
  };

  FORCEINLINE jlColor
  jlColor::operator-() const {
   return jlColor(-x, -y, -z, -w);
  }
  
  FORCEINLINE jlColor
  jlColor::operator+() const {
    return *this;
  }
  
  FORCEINLINE jlColor
  jlColor::operator+(const jlColor& color) const {
    return jlColor(x + color.x, y + color.y, z + color.z, w + color.w);
  }
  
  FORCEINLINE jlColor
  jlColor::operator-(const jlColor& color) const {
    return jlColor(x - color.x, y - color.y, z - color.z, w - color.w);
  }
  
  FORCEINLINE jlColor&
  jlColor::operator+=(const jlColor& color) {
    x += color.x; y += color.y; z += color.z; w += color.w;
    return *this;
  }
  
  FORCEINLINE jlColor&
  jlColor::operator-=(const jlColor& color) {
    x -= color.x; y -= color.y; z -= color.z; w -= color.w;
    return *this;
  }
  
  FORCEINLINE jlColor
  jlColor::operator*(const float& scale) const {
    return jlColor(x * scale, y * scale, z * scale, w * scale);
  }
  
  FORCEINLINE jlColor
  jlColor::operator*(const jlColor& color) const {
    return jlColor(x * color.x, y * color.y, z * color.z, w * color.w);
  }
  
  FORCEINLINE jlColor&
  jlColor::operator*=(const float& scale) {
    x *= scale; y *= scale; z *= scale; w *= scale;
    return *this;
  }
  
  FORCEINLINE jlColor&
  jlColor::operator*=(const jlColor& color) {
    x *= color.x; y *= color.y; z *= color.z; w *= color.w;
    return *this;
  }

  FORCEINLINE jlColor
  jlColor::operator/(const float& scale) const {
    return jlColor(x / scale, y / scale, z / scale, w / scale);
  }
  
  FORCEINLINE jlColor
  jlColor::operator/(const jlColor& color) const {
    return jlColor(x / color.x, y / color.y, z / color.z, w / color.w);
  }

  FORCEINLINE jlColor& 
  jlColor::operator/=(const float& scale)	{
    x /= scale; y /= scale; z /= scale; w /= scale;
    return *this;
  }
  
  FORCEINLINE jlColor& 
  jlColor::operator/=(const jlColor& color) {
    x /= color.x; y /= color.y; z /= color.z; w /= color.w;
    return *this;
  }
  
  FORCEINLINE bool
  jlColor::operator==(const jlColor& color) const {
    return (x == color.x) && (y == color.y) && (z == color.z) && (w == color.w);
  }
  
  FORCEINLINE bool
  jlColor::operator!=(const jlColor& color) const {
    return (x != color.x) || (y != color.y) || (z != color.z) || (w != color.w);
  }

  FORCEINLINE bool
  jlColor::operator<(const jlColor& color) const {
    if (x < color.x || y < color.y || z < color.z || w < color.w) {
      return true;
    }
    return false;
  }
  
  FORCEINLINE bool
  jlColor::operator>(const jlColor& color) const {
    if (x > color.x || y > color.y || z > color.z || w > color.w) {
      return true;
    }
    return false;
  }

  FORCEINLINE float
  jlColor::operator[](uint32 index) const {
    JL_ASSERT(index < 4);
    return (&x)[index];
  }

  FORCEINLINE float&
  jlColor::operator[](uint32 index) {
    JL_ASSERT(index < 4);
    return (&x)[index];
  }
  
  FORCEINLINE jlColor&
  jlColor::operator=(const jlColor& color) {
    x = color.x; y = color.y; z = color.z; w = color.w;
    m_isUnit = color.m_isUnit;
    m_limitedMax = color.m_limitedMax;
    return *this;
  }
  
  FORCEINLINE jlColor
  operator*(const float& a, const jlColor& color) {
    return jlColor(a * color.x, a * color.y, a * color.z, a * color.w);
  }

  FORCEINLINE std::ostream&
  operator<<(std::ostream& os, const jlColor& color) {
    os << "(" << color.x << ", " << color.y << ", " << color.z << ", " << color.w << ")";
    return os;
  }

  FORCEINLINE jlColor&
  jlColor::makeUnit() {
    if (!m_isUnit) {
      m_isUnit = true;
      *this /= 255;
      makeLimited();
    }
    return *this;
  }

  FORCEINLINE jlColor&
  jlColor::make255() {
    if (m_isUnit) {
      *this *= 255;
      m_isUnit = false;
      makeLimited();
    }
    return *this;
  }

  FORCEINLINE jlColor&
  jlColor::makeLimited() {
    if (m_isUnit) {
      if (r > 1) {
        r = 1;
      }
      if (g > 1) {
        g = 1;
      }
      if (b > 1) {
        b = 1;
      }
      if (a > 1) {
        a = 1;
      }
    }
    else {
      if (r > 255) {
        r = 255;
      }
      if (g > 255) {
        g = 255;
      }
      if (b > 255) {
        b = 255;
      }
      if (a > 255) {
        a = 255;
      }
    }
    return *this;
  }

  FORCEINLINE jlVector4
  jlColor::getInUnit() const {
    jlVector4 temp;
    if (m_isUnit) {
      temp = { r, g, b, a };
    }
    else {
      auto col = *this;
      col.makeUnit();
      temp = col.C;
    }
    return temp;
  }

  FORCEINLINE jlVector4
  jlColor::getIn255() const {
    jlVector4 temp;
    if (m_isUnit) {
      auto col = *this;
      col.make255();
      temp = col.C;
    }
    else {
      temp = { r, g, b, a };
    }
    return temp;
  }
  
  FORCEINLINE void
  jlColor::makeNegativeTo0() {
    if (r < 0) {
      r = 0;
    }
    if (g < 0) {
      g = 1;
    }
    if (b < 0) {
      b = 0;
    }
    if (a < 0) {
      a = 0;
    }
  }
}