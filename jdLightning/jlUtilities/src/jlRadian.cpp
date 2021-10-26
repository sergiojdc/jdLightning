#include "jlRadian.h"
#include "jlDegree.h"

namespace jlUtilitiesSDK {
  jlRadian::jlRadian(const jlDegree & d) : m_radian(d.valueRadians()) {}

  jlRadian &
  jlRadian::operator=(const jlDegree & d) {
    m_radian = d.valueRadians();
    return *this;
  }

  jlRadian
  jlRadian::operator+(const jlDegree & d) const {
    return jlRadian(m_radian + d.valueRadians());
  }

  jlRadian &
  jlRadian::operator+=(const jlDegree & d) {
    m_radian += d.valueRadians();
    return *this;
  }

  jlRadian
  jlRadian::operator-(const jlDegree & d) const {
    return jlRadian(m_radian - d.valueRadians());
  }

  jlRadian &
  jlRadian::operator-=(const jlDegree & d) {
    m_radian -= d.valueRadians();
    return *this;
  }

  float
  jlRadian::valueDegrees() const {
    return m_radian * Math::RAD2DEG;
  }

  void
  jlRadian::unwindRadians() {
    m_radian = Math::unwindRadians(m_radian);
  }
}