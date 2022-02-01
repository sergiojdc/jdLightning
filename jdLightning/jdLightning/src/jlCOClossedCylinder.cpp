#include "jlCOClossedCylinder.h"
#include "jlGODisk.h"
#include "jlGOCylinder.h"

jlClossedCylinder::jlClossedCylinder() {
  m_type = GEOMETRITYPE::CYLINDER;
  createCylindre();
}

jlClossedCylinder::~jlClossedCylinder() {}

void jlClossedCylinder::createCylindre() {
  SPtr<jlDisk> newDisk(new jlDisk(m_ratio, {0,-1,0}, m_position));
  m_objects.push_back(newDisk);
  SPtr<jlCylinder> newCylinder(new jlCylinder(m_ratio, m_height, m_position));
  m_objects.push_back(newCylinder);
  jlVector3 topPos = m_position;
  topPos.y += m_height;
  newDisk.reset(new jlDisk(m_ratio, { 0,1,0 }, topPos));
  m_objects.push_back(newDisk);
  m_numObjects = m_objects.size();
}
