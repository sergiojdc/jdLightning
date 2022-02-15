#include "jlGrid.h"
#include "jlBoundingBox.h"

const double jlGrid::kEpsilon = 0.00001;

jlGrid::jlGrid()
{
  m_bbox.reset(new jlBBox);
}

jlGrid::~jlGrid()
{
}

void 
jlGrid::setupCells() {
  //find the minimun and maximun coordinates of the grid
  jlVector3 p0 = min_coord();
  jlVector3 p1 = max_coord();

  //store in the grid's bounding box
  m_bbox->m_realMin = p0;
  m_bbox->m_realMax = p1;

  // compute the number of cells in the x y z direction
  jlVector3 w = p1 - p0;
  float multiplier = 2; //about 8 times more cells than objects
  float wMult = w.x * w.y * w.z / float(m_numObjects);
  float s = Math::pow(wMult, 0.3333333f);

  nx = multiplier * w.x / s + 1;
  ny = multiplier * w.y / s + 1;
  nz = multiplier * w.z / s + 1;

  // compute the number of cells in the x-, y-, and z-direction
  uint32 numCells = nx * ny * nz;
  m_cells.reserve(numCells);

  for (uint32 i = 0; i < numCells; ++i) {
    m_cells.push_back(nullptr);
  }

  // compute the number of cells in the x-, y-, and z-direction
  Vector<uint32> counts;
  counts.reserve(numCells);
  for (uint32 j = 0; j < numCells; ++j)
    counts.push_back(0);
  // put objects into the cells
  jlBBox objBbox; // object’s bounding box
  uint32 index; // cells array index

  for (uint32 i = 0; i < m_numObjects; ++i) {
    objBbox = *m_objects[i]->m_bbox.get();
    // compute the cell indices for the corners of the bounding box of the object
    uint32 ixmin = (uint32)Math::clamp((objBbox.m_realMin.x - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
    uint32 iymin = (uint32)Math::clamp((objBbox.m_realMin.y - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
    uint32 izmin = (uint32)Math::clamp((objBbox.m_realMin.z - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
    uint32 ixmax = (uint32)Math::clamp((objBbox.m_realMax.x - p0.x) * nx / (p1.x - p0.x), 0, nx - 1);
    uint32 iymax = (uint32)Math::clamp((objBbox.m_realMax.y - p0.y) * ny / (p1.y - p0.y), 0, ny - 1);
    uint32 izmax = (uint32)Math::clamp((objBbox.m_realMax.z - p0.z) * nz / (p1.z - p0.z), 0, nz - 1);
    // add the object to the cells
    for (uint32 iz = izmin; iz <= izmax; ++iz) { // cells in z direction
      for (uint32 iy = iymin; iy <= iymax; ++iy) { // cells in y direction
        for (uint32 ix = ixmin; ix <= ixmax; ++ix) { // cells in x direction
          index = ix + nx * iy + nx * ny * iz;
          if (counts[index] == 0) {
            m_cells[index] = m_objects[i];
            counts[index] += 1; 
            index = 1;
          }
          else {
            if (counts[index] == 1) {
              // construct a compound object
              SPtr<jlCompoundObject> compound_ptr(new jlCompoundObject);
              // add the object already in cell
              compound_ptr->addObject(m_cells[index]);
              // add the new object
              compound_ptr->addObject(m_objects[i]);
              // store compound in current cell
              m_cells[index] = compound_ptr;
              // index = 2
              counts[index] += 1;
            }
            else {
              // counts[index] > 1
              // just add current object
              m_cells[index]->addObject(m_objects[i]);
              // for statistics only
              counts[index] += 1;
            }
          }
        }
      }
    }
  }
  // erase Compound::Objects, but don’t delete the objects
  m_objects.erase(m_objects.begin(), m_objects.end());
  // code for statistics on cell objects counts can go in here
  // erase the temporary counts vector
  counts.erase(counts.begin(), counts.end());
}

bool 
jlGrid::hit(const jlRay& ray, double& t, jlShadeRec& s){
  //code based on https://github.com/libingzeng/RayTraceGroundUp/blob/master/src/object/Grid.cpp
  jlVector3 rO = ray.m_origin; //ray origin
  jlVector3 bb0 = m_bbox->m_realMin; //bounding box min
  jlVector3 bb1 = m_bbox->m_realMax; //bounding box max
  double ox = ray.m_origin.x;
  double oy = ray.m_origin.y;
  double oz = ray.m_origin.z;

  double dx = ray.m_direction.x;
  double dy = ray.m_direction.y;
  double dz = ray.m_direction.z;

  double tx_min, ty_min, tz_min;
  double tx_max, ty_max, tz_max;

  double a = 1.0 / dx;
  if (a >= 0) {
    tx_min = (bb0.x - ox) * a;
    tx_max = (bb1.x - ox) * a;
  }
  else {
    tx_min = (bb1.x - ox) * a;
    tx_max = (bb0.x - ox) * a;
  }
  double b = 1.0 / dy;
  if (b >= 0) {
    ty_min = (bb0.y - oy) * b;
    ty_max = (bb1.y - oy) * b;
  }
  else {
    ty_min = (bb1.y - oy) * b;
    ty_max = (bb0.y - oy) * b;
  }
  double c = 1.0 / dz;
  if (c >= 0) {
    tz_min = (bb0.z - oz) * c;
    tz_max = (bb1.z - oz) * c;
  }
  else {
    tz_min = (bb1.z - oz) * c;
    tz_max = (bb0.z - oz) * c;
  }

  //if (a >= 0) {
  //  tx_min = (bb0.x - ox) * a;
  //  tx_max = (bb1.x - ox) * a;
  //}
  //else {
  //  tx_min = (bb1.x - ox) * a;
  //  tx_max = (bb0.x - ox) * a;
  //}

  //double b = 1.0 / dy;
  //if (b >= 0) {
  //  ty_min = (bb0.y - oy) * b;
  //  ty_max = (bb1.y - oy) * b;
  //}
  //else {
  //  ty_min = (bb1.y - oy) * b;
  //  ty_max = (bb0.y - oy) * b;
  //}

  //double c = 1.0 / dz;
  //if (c >= 0) {
  //  tz_min = (bb0.z - oz) * c;
  //  tz_max = (bb1.z - oz) * c;
  //}
  //else {
  //  tz_min = (bb1.z - oz) * c;
  //  tz_max = (bb0.z - oz) * c;
  //}

  double t0, t1;
  // find largest entering t value
  if (tx_min > ty_min) {
    t0 = tx_min;
  }
  else {
    t0 = ty_min;
  }
  if (tz_min > t0) {
    t0 = tz_min;
  }
  // find smallest exiting t value
  if (tx_max < ty_max) {
    t1 = tx_max;
  }
  else {
    t1 = ty_max;
  }
  if (tz_max < t1) {
    t1 = tz_max;
  }

  if (!(t0 < t1 && t1 > kEpsilon)) { // condition for a hit
    if (!(t0 > kEpsilon)) {
      return false;
    }
  }

  int32 ix, iy, iz;
  if (m_bbox->inside(ray.m_origin)) {
    ix = Math::clamp((rO.x - bb0.x) * nx / (bb1.x - bb0.x), 0, nx - 1);
    iy = Math::clamp((rO.y - bb0.y) * ny / (bb1.y - bb0.y), 0, ny - 1);
    iz = Math::clamp((rO.z - bb0.z) * nz / (bb1.z - bb0.z), 0, nz - 1);
  }
  else {
    jlVector3 p = ray.m_origin + t0 * ray.m_direction;
    float ixx = Math::clamp((p.x - bb0.x) * nx / (bb1.x - bb0.x), 0, nx - 1);
    float iyy = Math::clamp((p.y - bb0.y) * ny / (bb1.y - bb0.y), 0, ny - 1);
    float izz = Math::clamp((p.z - bb0.z) * nz / (bb1.z - bb0.z), 0, nz - 1);
    ix = Math::clamp((p.x - bb0.x) * nx / (bb1.x - bb0.x), 0, nx - 1);
    iy = Math::clamp((p.y - bb0.y) * ny / (bb1.y - bb0.y), 0, ny - 1);
    iz = Math::clamp((p.z - bb0.z) * nz / (bb1.z - bb0.z), 0, nz - 1);
  }
  // ray parameter increments per cell in the x, y, and z directions
  //Compute txnext, tynext and tznext for nitial cell
  float dtx = (bb1.x - bb0.x) / nx;
  float dty = (bb1.y - bb0.y) / ny;
  float dtz = (bb1.z - bb0.z) / nz;

  float tx_next, ty_next, tz_next;
  int ix_step, iy_step, iz_step;
  int ix_stop, iy_stop, iz_stop;

  if (dx > 0) {
    tx_next = tx_min + (ix + 1) * dtx;
    ix_step = +1;
    ix_stop = nx;
  }
  else {
    tx_next = tx_min + (nx - ix) * dtx;
    ix_step = -1;
    ix_stop = -1;
  }

  if (dx == 0.0) {
    tx_next = HUGE_VAL;
    ix_step = -1;
    ix_stop = -1;
  }


  if (dy > 0) {
    ty_next = ty_min + (iy + 1) * dty;
    iy_step = +1;
    iy_stop = ny;
  }
  else {
    ty_next = ty_min + (ny - iy) * dty;
    iy_step = -1;
    iy_stop = -1;
  }

  if (dy == 0.0) {
    ty_next = HUGE_VAL;
    iy_step = -1;
    iy_stop = -1;
  }

  if (dz > 0) {
    tz_next = tz_min + (iz + 1) * dtz;
    iz_step = +1;
    iz_stop = nz;
  }
  else {
    tz_next = tz_min + (nz - iz) * dtz;
    iz_step = -1;
    iz_stop = -1;
  }

  if (dz == 0.0) {
    tz_next = HUGE_VAL;
    iz_step = -1;
    iz_stop = -1;
  }

  /*tx_next = tx_min + (ix + 1) * dtx;
  ix_step = +1;
  ix_stop = nx;
  ty_next = ty_min + (iy + 1) * dty;
  iy_step = +1;
  iy_stop = ny;
  tz_next = tz_min + (iz + 1) * dtz;
  iz_step = +1;
  iz_stop = nz;*/

  if (iy == 1 && ix == 1 )
  {
    bool aver = true;
  }

  // traverse the grid

  while (true) {
    jlGeometricObject* object_ptr = m_cells[ix + nx * iy + nx * ny * iz].get();

    if (tx_next < ty_next && tx_next < tz_next) {
      //if (object_ptr && object_ptr->hit(ray, t, s) && t < tx_next) {
      if (object_ptr && object_ptr->hit(ray, t, s)) {
        m_pMaterial = object_ptr->m_pMaterial;
        return (true);
      }

      tx_next += dtx;
      ix += ix_step;

      if (ix == ix_stop)
        return (false);
    }
    else {
      if (ty_next < tz_next) {
        //if (object_ptr && object_ptr->hit(ray, t, s) && t < ty_next) {
        if (object_ptr && object_ptr->hit(ray, t, s)) {
          m_pMaterial = object_ptr->m_pMaterial;
          return (true);
        }

        ty_next += dty;
        iy += iy_step;

        if (iy == iy_stop)
          return (false);
      }
      else {
        //if (object_ptr && object_ptr->hit(ray, t, s) && t < tz_next) {
        if (object_ptr && object_ptr->hit(ray, t, s)) {
          m_pMaterial = object_ptr->m_pMaterial;
          return (true);
        }

        tz_next += dtz;
        iz += iz_step;

        if (iz == iz_stop)
          return (false);
      }
    }
  }
}

bool jlGrid::shadowHit(const jlRay& ray, float& tmin)
{
  return false;
}

jlVector3 
jlGrid::min_coord() {
  jlBBox bbox;
  jlVector3 p0 = { HUGE_VALF, HUGE_VALF, HUGE_VALF };
  //uint32 numObjects = m_objects.size(); //Cambiar a otro lado por si se llama demasiado
  //Usar mientras el numObjects de compound
  for (uint32 i = 0; i < m_numObjects; ++i) {
    bbox = *m_objects[i]->m_bbox.get();
    if (bbox.m_realMin.x < p0.x)
      p0.x = bbox.m_realMin.x;
    if (bbox.m_realMin.y < p0.y)
      p0.y = bbox.m_realMin.y;
    if (bbox.m_realMin.z < p0.z)
      p0.z = bbox.m_realMin.z;
  }
  p0.x -= kEpsilon; 
  p0.y -= kEpsilon; 
  p0.z -= kEpsilon;
  return p0;
}

jlVector3 
jlGrid::max_coord() {
  jlBBox bbox;
  jlVector3 p0 = { -HUGE_VAL, -HUGE_VAL, -HUGE_VAL };
  //uint32 numObjects = m_objects.size(); //Cambiar a otro lado por si se llama demasiado
  //Usar mientras el numObjects de compound
  for (uint32 i = 0; i < m_numObjects; ++i) {
    bbox = *m_objects[i]->m_bbox.get();
    if (bbox.m_realMax.x > p0.x)
      p0.x = bbox.m_realMax.x;
    if (bbox.m_realMax.y > p0.y)
      p0.y = bbox.m_realMax.y;
    if (bbox.m_realMax.z > p0.z)
      p0.z = bbox.m_realMax.z;
  }
  p0.x += kEpsilon;
  p0.y += kEpsilon;
  p0.z += kEpsilon;
  return p0;
}
