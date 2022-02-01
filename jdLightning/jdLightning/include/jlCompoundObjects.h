/*****************************************************************************/
/**
	* @file    jlCompoundObject.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    01/02/2022
	* @brief   A virtual class for compound objects
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once

#include "jlGeometriObject.h"
#include "jlVector3.h"
#include "jlNormal.h"
#include "jlMaterial.h"
class jlCompoundObject : public jlGeometricObject {
 public:
   jlCompoundObject();
		~jlCompoundObject();

  /**
   * @brief function to add Material to object
   * @param material is a weakSptr with the material to set
   */
		virtual void
  setMaterial(WeakSptr<jlMaterial> material);

  /**
   * @brief function to add object to Compound
   * @param material is a weakSptr with the material to set
   */
		void 
		addObject(WeakSptr<jlGeometricObject> object) {
    m_objects.push_back(object.lock());
    m_numObjects = m_objects.size();
  }

  /**
   * @brief function to detected a hit
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @pram sr is the shade rec
   * @return true if tha ray hit with it
   */
  virtual bool
  hit(const jlRay& ray, double& tmin, jlShadeRec& sr) override;

  /**
   * @brief function to detected if the object is in shadow
   * @param ray is the ray whit check the hit
   * @pram tmin is to check the nearest
   * @return true if tha ray hit with it
   */
  virtual bool
  shadowHit(const jlRay& ray, float& tmin) override;

 protected:
  Vector<SPtr<jlGeometricObject>> m_objects;
  uint32 m_numObjects = 0;

};
