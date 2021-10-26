#include "jlDegree.h"
#include "jlRadian.h"

namespace jlUtilitiesSDK {

  jlDegree::jlDegree(const jlRadian& r) : m_degree(r.valueDegrees()) {}

  jlDegree&
  jlDegree::operator=(const jlRadian& r) {
    m_degree = r.valueDegrees();
    return *this;
  }

  jlDegree
  jlDegree::operator+(const jlRadian& r) const {
    return jlDegree(m_degree + r.valueDegrees());
  }

  jlDegree&
  jlDegree::operator+=(const jlRadian& r) {
    m_degree += r.valueDegrees();
    return *this;
  }

  jlDegree
  jlDegree::operator-(const jlRadian& r) const {
    return jlDegree(m_degree - r.valueDegrees());
  }

  jlDegree&
  jlDegree::operator-=(const jlRadian& r) {
    m_degree -= r.valueDegrees();
    return *this;
  }

  float
    jlDegree::valueRadians() const {
    return m_degree * Math::DEG2RAD;
  }

  void
  jlDegree::unwindDegrees() {
    m_degree = Math::unwindDegrees(m_degree);
  }
}
