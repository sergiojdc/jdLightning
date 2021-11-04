/*****************************************************************************/
/**
	* @file    jlTRayCast.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    2/11/2021
	* @brief   A class for a RayCast tracer
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlTracer.h"
#include "jlShadeRec.h"
#include "jlWorld.h"
#include "jlMaterial.h"

class jlTRayCast : public jlTracer { 
 public:
		/**
			* @brief default constructor
			*/
		jlTRayCast() = default;

		/**
			* @brief constructor with world
			* @param world is a pointer to the world
			*/
		jlTRayCast(jlWorld* world) { m_world = world; };

		/**
			* @brief default destructor
			*/
		~jlTRayCast() {};

		/**
			* @brief virtual method for check if the ray hit with geometri with depth
			* @param ray is the ray with check the hits
			* @param depth is the depth with check it
			* @return a color
			*/
		virtual jlColor
		traceRay(const jlRay& ray, uint32 depth) const override {
				UNREFERENCED_PARAMETER(depth);
				jlShadeRec sr(m_world->hitObjects(ray));
				if (sr.m_hitAnObject)	{
						sr.m_ray = ray;
						return sr.m_pMaterial->shade(sr);
				}
				return m_world->m_backgroundColor;
		};

 private:

};
