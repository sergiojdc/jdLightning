/*****************************************************************************/
/**
	* @file    jlLAmbientOccluder.h
	* @author  Sergio Diaz (sergio_jdc@hotmail.com)
	* @date    15/11/2021
	* @brief   A class for a ambient occluder light
	*
	*
	* @bug	    No known bugs.
	*/
	/*****************************************************************************/
#pragma once
#include "Prerequisites.h"
#include "jlLight.h"

class jlSampler;

class jlLAmbientOccluder : public jlLight {
public:
		/**
			* @brief default constructor
			*/
		jlLAmbientOccluder() {
				m_type = LIGHTTYPES::AMBIENTOCCLUDER;
		};

		/**
			* @brief constructor with params
			*/
		jlLAmbientOccluder(const float& ls, const jlColor& color) : m_ls(ls), m_color(color) {
				m_type = LIGHTTYPES::AMBIENTOCCLUDER;
		};

		/**
			* @brief default destructor
			*/
		~jlLAmbientOccluder() {};

		/**
			* @brief returns the direction of the incoming light at a hit point
			* @param sr is the shadeRec with data
			* @param u is right vector for hemisphere
			* @param v is up vector for hemisphere
			* @param w is front vector for hemisphere
			* @param sampleIndex iuf for optimized sampler only, is the index of sampler
			* @return a vector3 with the direction
			*/
		virtual jlVector3
		getDirection(jlShadeRec& sr, 
               const jlVector3& u, 
               const jlVector3& v, 
               const jlVector3& w, 
               uint32 sampleIndex = 0) override;

		/**
			* @brief returns the incident radiance at a hit point
			* @param sr is the shadeRec with data
			* @param sampleIndex iuf for optimized sampler only, is the index of sampler
			* @return a color with the incident radiance
			*/
		virtual jlColor
		L(jlShadeRec& sr, uint32 sampleIndex = 0) override;

		/**
		 * @brief returns if ray hit with another 
			* @param ray is the ray to cast
			* @param sr is the shadeRec with data
		 * @return true if is hit, and that means there is a shadow
		 */
		virtual bool
		inShadow(const jlRay& ray, jlShadeRec& sr) override;

		/**
			* @brief function to set sampler
			* @param sampler is the sampler to set
			*/
		void
		setSampler(WeakSptr<jlSampler> sampler);

  /**
			* @brief function to set the min amount
			* @param minAmount is the value to set
			*/
		void
		setMinAmount(const jlColor& minAmount) {
				m_minAmount = minAmount;
		}

		/**
			* @brief function to set the w vector (front)
			* @param w is the vector to set
			*/
		void
		setWvector(const jlVector3& w) {
				//m_w = w;
		}

		/**
			* @brief function to set the U vector (right)
			* @param u is the vector to set
			*/
		void
		setUvector(const jlVector3& u) {
				//m_u = u;
		}

		/**
			* @brief function to set the V vector (up)
			* @param v is the vector to set
			*/
		void
		setVvector(const jlVector3& v) {
				//m_v = v;
		}
		/**
			* @brief function to set the UVW vectorS (right, up, front)
			* @param u is the vector U to set
			* @param v is the vector V to set
			* @param w is the vector W to set
			*/
		void
		setUVWvectors(const jlVector3& u, const jlVector3& v, const jlVector3& w) {
				//m_u = u;
				//m_v = v;
				//m_w = w;
		}

 private:
friend class jlWorld;
		/**
			* @brief radiance scaling factor
			*/
		float m_ls = 1.0f;

		/**
			* @brief the color of light
			*/
		jlColor m_color = { 1, 1, 1 };

		/**
			* @brief pointer to sampler
			*/
		SPtr<jlSampler> m_pSampler;

		/**
			* @brief the min amount
			*/
		jlColor m_minAmount = { 1, 1, 1 };

		/**
			* @brief direction vectors
			*/
		//jlVector3 m_u = { 1, 0, 0 };
		//jlVector3 m_v = { 0, 1, 0 };
		//jlVector3 m_w = { 0, 0, 1 };

};
