#include "jlGeometriObject.h"
#include "jlBoundingBox.h"

void 
jlGeometricObject::updateBoundigBox() {
		if (nullptr != m_bbox)	{
				m_bbox->calculateRealMinMax();
		}
}
