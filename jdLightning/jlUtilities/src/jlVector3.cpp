#include "jlVector3.h"
#include "jlPoint3.h"

namespace jlUtilitiesSDK {
  jlVector3::jlVector3(const jlPoint3& point) {
    x = (float)point.x;
    y = (float)point.y;
    z = (float)point.z;
  }

}