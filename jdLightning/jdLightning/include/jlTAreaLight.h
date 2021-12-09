/*****************************************************************************/
/**
	* @file    jlTRayCast.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    07/12/2021
	* @brief   A class for a Area Light tracer
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

class jlTAreaLight : public jlTracer {
public:
		/**
			* @brief default constructor
			*/
		jlTAreaLight() = default;

		/**
			* @brief constructor with world
			* @param world is a pointer to the world
			*/
		jlTAreaLight(jlWorld* world) { m_world = world; };

		/**
			* @brief default destructor
			*/
		~jlTAreaLight() {};

		/**
			* @brief virtual method for check if the ray hit with geometri with depth
			* @param ray is the ray with check the hits
			* @param depth is the depth with check it
			* @return a color
			*/
		virtual jlColor
		traceRay(const jlRay& ray, uint32 depth, uint32 sampleIndex = 0) const override {
				UNREFERENCED_PARAMETER(depth);
				jlShadeRec sr(m_world->hitObjects(ray));
				if (sr.m_hitAnObject) {
						sr.m_ray = ray;
						return sr.m_pMaterial->areaLightShade(sr, sampleIndex);
				}
				return m_world->m_backgroundColor;
		};

private:

};