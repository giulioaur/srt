////////////////////////////////////////////////////////////////////////
//																	  //
//								GU ENGINE							  //
//							   by Dr.Sushi							  //
//							   MIfloat License							  //
//																	  //
////////////////////////////////////////////////////////////////////////
#pragma once

#include "srt.h"

#include <cmath>
#include <intrin.h>
#include <sstream>
#include <string>
#include <xmmintrin.h>

namespace srt::geometry
{

///////////////////////////////////////////////////////////////////////////////////////////////////
//										SIMD IMPLEMENTATION										 //
///////////////////////////////////////////////////////////////////////////////////////////////////

class Vector4SIMD
{
public:

	Vector4SIMD();
	Vector4SIMD(const float val);
	Vector4SIMD(const float x, const float y, const float z, const float w);
	Vector4SIMD(const __m128 raw);
	//Vector4SIMD(float arr[]);
	Vector4SIMD(const Vector4SIMD& other) noexcept;
	Vector4SIMD(Vector4SIMD&& other) noexcept;

	/*********************** GETTER ***********************/

	float& x() { return m_data.elems.x; }
	float& y() { return m_data.elems.y; }
	float& z() { return m_data.elems.z; }
	float& w() { return m_data.elems.w; }
	const float& x() const { return m_data.elems.x; }
	const float& y() const { return m_data.elems.y; }
	const float& z() const { return m_data.elems.z; }
	const float& w() const { return m_data.elems.w; }

	/*********************** OPERATIONS ***********************/

	float length() const;
	float squaredMagnitude() const;
	Vector4SIMD mul(const Vector4SIMD& rhs) const;
	float dot(const Vector4SIMD& rhs) const;

	/*
	 * This is a cross product in three-dimensional space. The function consider the two operand
	 * to be omogenous vector (a point will be considered as a vector).
	 *
	 * @args rhs The right operand.
	 *
	 * @return The perpendicular vector in three-dimensional space.
	 */
	Vector4SIMD cross(const Vector4SIMD& rhs) const;


	/*********************** OPERATORS ***********************/

	float& operator[](const umsize index);
	const float& operator[](const umsize index) const;

	Vector4SIMD& operator=(const Vector4SIMD& rhs) noexcept;
	Vector4SIMD& operator=(Vector4SIMD&& rhs) noexcept;

	Vector4SIMD operator-() const;

	Vector4SIMD operator+(const Vector4SIMD& rhs) const;
	Vector4SIMD operator+=(const Vector4SIMD& rhs);
	Vector4SIMD operator-(const Vector4SIMD& rhs) const;
	Vector4SIMD operator*(const float& rhs) const;
	Vector4SIMD operator*=(const Vector4SIMD& rhs);
	Vector4SIMD operator/=(const float rhs);
	float operator*(const Vector4SIMD& rhs) const;

	/**
	 * Return a string representing the array.
	 *
	 * @return A readable format of the vector.
	 */
	std::string toString() const;

private:

	union u_vector_data
	{
		__m128 raw;
		struct {
			float x; float y; float z; float w;
		} elems;
	} m_data;

	friend class Matrix4SIMD;

public:

	friend void swap(Vector4SIMD& a, Vector4SIMD& b)
	{
		srt::swap(a.m_data.raw, b.m_data.raw);
	}

};








///////////////////////////////////////////////////////////////////////////////////////////////////
//											DEFINITIONS											 //
///////////////////////////////////////////////////////////////////////////////////////////////////



INLINE Vector4SIMD::Vector4SIMD()
{
	m_data.raw = _mm_set_ps(0, 0, 0, 0);
}

INLINE Vector4SIMD::Vector4SIMD(const float val)
{
	m_data.raw = _mm_set_ps(val, val, val, val);
}

INLINE Vector4SIMD::Vector4SIMD(const float x, const float y, const float z, const float w)
{
	m_data.raw = _mm_set_ps(w, z, y, x);
}

INLINE Vector4SIMD::Vector4SIMD(const __m128 raw)
{
	m_data.raw = raw;
}

//INLINE Vector4SIMD::Vector4SIMD(float arr[])
//{
//	// Check arr alignment.
//	m_data.raw = _mm_load_ps(arr);
//}

INLINE Vector4SIMD::Vector4SIMD(const Vector4SIMD& other) noexcept
{
	m_data.raw = _mm_load_ps((float*)(&other.m_data.raw));
}

INLINE Vector4SIMD::Vector4SIMD(Vector4SIMD&& other) noexcept
{
	swap(*this, other);
}

INLINE float Vector4SIMD::squaredMagnitude() const
{
	return _mm_cvtss_f32(_mm_dp_ps(m_data.raw, m_data.raw, 0xF1));
}

INLINE Vector4SIMD Vector4SIMD::mul(const Vector4SIMD& rhs) const
{
	Vector4SIMD ret;
	ret.m_data.raw = _mm_mul_ps(m_data.raw, rhs.m_data.raw);
	return ret;
}

INLINE float Vector4SIMD::dot(const Vector4SIMD& rhs) const
{
	return _mm_cvtss_f32(_mm_dp_ps(m_data.raw, rhs.m_data.raw, 0xF1));
}

INLINE Vector4SIMD Vector4SIMD::cross(const Vector4SIMD& rhs) const
{
	return Vector4SIMD{
		m_data.elems.y* rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.y,
			m_data.elems.x* rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.x,
			m_data.elems.x* rhs.m_data.elems.y + m_data.elems.y * rhs.m_data.elems.x,
			0
	};
}

INLINE float& Vector4SIMD::operator[](const umsize index)
{
	return ((float*)&m_data.raw)[index];
}

INLINE const float& Vector4SIMD::operator[](const umsize index) const
{
	return ((float*)&m_data.raw)[index];
}

INLINE Vector4SIMD& Vector4SIMD::operator=(const Vector4SIMD& rhs) noexcept
{
	Vector4SIMD tmp{ rhs };
	swap(*this, tmp);
	return *this;
}

INLINE Vector4SIMD& Vector4SIMD::operator=(Vector4SIMD&& rhs) noexcept
{
	swap(*this, rhs);
	return *this;
}

INLINE Vector4SIMD Vector4SIMD::operator+(const Vector4SIMD& rhs) const
{
	Vector4SIMD ret;
	ret.m_data.raw = _mm_add_ps(m_data.raw, rhs.m_data.raw);
	return ret;
}

INLINE Vector4SIMD Vector4SIMD::operator+=(const Vector4SIMD& rhs) 
{
	m_data.raw = _mm_add_ps(m_data.raw, rhs.m_data.raw);
	return *this;
}

INLINE Vector4SIMD Vector4SIMD::operator-(const Vector4SIMD& rhs) const
{
	Vector4SIMD ret;
	ret.m_data.raw = _mm_sub_ps(m_data.raw, rhs.m_data.raw);
	return ret;
}

INLINE Vector4SIMD Vector4SIMD::operator*(const float& rhs) const
{
	Vector4SIMD ret;
	ret.m_data.raw = _mm_mul_ps(m_data.raw, _mm_set1_ps(rhs));
	return ret;
}

INLINE float Vector4SIMD::operator*(const Vector4SIMD& rhs) const
{
	return dot(rhs);
}

INLINE Vector4SIMD Vector4SIMD::operator*=(const Vector4SIMD& rhs)
{
	*this = mul(rhs);
	return *this;
}

INLINE Vector4SIMD Vector4SIMD::operator/=(const float rhs)
{
	m_data.raw = _mm_div_ps(m_data.raw, _mm_set1_ps(rhs));
	return *this;
}


INLINE std::string Vector4SIMD::toString() const
{
	std::ostringstream stringStream;
	stringStream << x() << ", " << y() << ", " << z();
	return stringStream.str();
}
















class Vector4Arr
{
public:

	Vector4Arr();
	Vector4Arr(const float val);
	Vector4Arr(const float x, const float y, const float z, const float w);
	Vector4Arr(const float arr[4]);
	Vector4Arr(const Vector4Arr& other) noexcept;
	Vector4Arr(Vector4Arr&& other) noexcept;

	/*********************** GETTER ***********************/

	float& x() { return m_data.elems.x; }
	float& y() { return m_data.elems.y; }
	float& z() { return m_data.elems.z; }
	float& w() { return m_data.elems.w; }
	const float x() const { return m_data.elems.x; }
	const float y() const { return m_data.elems.y; }
	const float z() const { return m_data.elems.z; }
	const float w() const { return m_data.elems.w; }

	/*********************** OPERATIONS ***********************/

	float length() const;
	float squaredMagnitude() const;
	Vector4Arr normalize() const;
	Vector4Arr mul(const Vector4Arr& rhs) const;	// Element-wise multiplication.
	float dot(const Vector4Arr& rhs) const;			// Dot product.

	/*
	 * This is a cross product in three-dimensional space. The function consider the two operand
	 * to be omogenous vector (a point will be considered as a vector).
	 *
	 * @args rhs The right operand.
	 *
	 * @return The perpendicular vector in three-dimensional space.
	 */
	Vector4Arr cross(const Vector4Arr& rhs) const;		

	std::string toString() const;

	/*********************** OPERATORS ***********************/

	float operator[](const umsize index);
	const float operator[](const umsize index) const;

	Vector4Arr& operator=(const Vector4Arr& rhs) noexcept;
	Vector4Arr& operator=(Vector4Arr&& rhs) noexcept;

	bool operator==(const Vector4Arr& rhs) const;
	bool operator!=(const Vector4Arr& rhs) const;

	Vector4Arr operator-() const;

	Vector4Arr operator+(const Vector4Arr& rhs) const;
	Vector4Arr operator+=(const Vector4Arr& rhs);
	Vector4Arr operator-(const Vector4Arr& rhs) const;
	Vector4Arr operator*(const float rhs) const;					// Scalar product.
	Vector4Arr operator*=(const float rhs);							// Scalar product.
	float operator*(const Vector4Arr& rhs) const;					// Dot product.
	Vector4Arr operator*=(const Vector4Arr& rhs);					// Elementwise product.
	Vector4Arr operator/(const float rhs) const;					// Scalar division.
	Vector4Arr operator/=(const float rhs);							// Scalar division.

private:

	union u_vector_data
	{
		float raw[4];
		struct {
			float x; float y; float z; float w;
		} elems;

		u_vector_data() = default;

		u_vector_data(const float x, const float y, const float z, const float w)
			: raw{ x, y, z, w } { };
	} m_data;


	friend class Matrix4Arr;

public:

	friend Vector4Arr operator* (const float lhs, const Vector4Arr rhs)
	{
		return rhs * lhs;
	}

	friend void swap(Vector4Arr& a, Vector4Arr& b)
	{
		srt::swap(a.m_data.raw, b.m_data.raw);
	}

};





///////////////////////////////////////////////////////////////////////////////////////////////////
//											DEFINITIONS											 //
///////////////////////////////////////////////////////////////////////////////////////////////////




INLINE Vector4Arr::Vector4Arr()
	: m_data(0, 0, 0, 0)
{
}


INLINE Vector4Arr::Vector4Arr(const float val)
	: m_data(val, val, val, val)
{
}


INLINE Vector4Arr::Vector4Arr(const float x, const float y, const float z, const float w)
	: m_data(x, y, z, w)
{
}


INLINE Vector4Arr::Vector4Arr(const float arr[4])
	: m_data(arr[0], arr[1], arr[2], arr[3])
{
}


INLINE Vector4Arr::Vector4Arr(const Vector4Arr& other) noexcept
	: Vector4Arr(other.m_data.raw)
{
}


INLINE Vector4Arr::Vector4Arr(Vector4Arr&& other) noexcept
{
	srt::swap(*this, other);
}


INLINE float Vector4Arr::length() const
{
	return sqrt(squaredMagnitude());
}


INLINE float Vector4Arr::squaredMagnitude() const
{
	return m_data.elems.x * m_data.elems.x +
		   m_data.elems.y * m_data.elems.y +
		   m_data.elems.z * m_data.elems.z +
		   m_data.elems.w * m_data.elems.w;
}


INLINE Vector4Arr Vector4Arr::normalize() const
{
	return *this / length();
}


INLINE Vector4Arr Vector4Arr::mul(const Vector4Arr& rhs) const
{
	return Vector4Arr{ m_data.elems.x * rhs.m_data.elems.x,
					  m_data.elems.y * rhs.m_data.elems.y,
					  m_data.elems.z * rhs.m_data.elems.z,
					  m_data.elems.w * rhs.m_data.elems.w };
}


INLINE float Vector4Arr::dot(const Vector4Arr& rhs) const
{
	return m_data.elems.x * rhs.m_data.elems.x +
		   m_data.elems.y * rhs.m_data.elems.y +
		   m_data.elems.z * rhs.m_data.elems.z +
		   m_data.elems.w * rhs.m_data.elems.w;
}


INLINE Vector4Arr Vector4Arr::cross(const Vector4Arr& rhs) const
{
	return Vector4Arr{
		m_data.elems.y * rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.y,
		m_data.elems.x * rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.x,
		m_data.elems.x * rhs.m_data.elems.y + m_data.elems.y * rhs.m_data.elems.x,
		0
	};
}

INLINE std::string Vector4Arr::toString() const
{
	std::ostringstream stringStream;
	stringStream << x() << ", " << y() << ", " << z();
	return stringStream.str();
}


INLINE float Vector4Arr::operator[](const umsize index)
{
	return m_data.raw[index];
}


INLINE const float Vector4Arr::operator[](const umsize index) const
{
	return m_data.raw[index];
}


INLINE Vector4Arr& Vector4Arr::operator=(const Vector4Arr& rhs) noexcept
{
	Vector4Arr tmp(rhs);
	srt::swap(*this, tmp);
	return *this;
}


INLINE Vector4Arr& Vector4Arr::operator=(Vector4Arr&& rhs) noexcept
{
	srt::swap(*this, rhs);
	return *this;
}

INLINE bool Vector4Arr::operator==(const Vector4Arr& rhs) const
{
	return m_data.elems.x == rhs.m_data.elems.x &&
		   m_data.elems.y == rhs.m_data.elems.y &&
		   m_data.elems.z == rhs.m_data.elems.z &&
		   m_data.elems.w == rhs.m_data.elems.w;
}

INLINE bool Vector4Arr::operator!=(const Vector4Arr& rhs) const
{
	return !(*this == rhs);
}


INLINE Vector4Arr Vector4Arr::operator-() const
{
	return Vector4Arr {
		- m_data.elems.x,
		- m_data.elems.y,
		- m_data.elems.z,
		- m_data.elems.w,
	};
}


INLINE Vector4Arr Vector4Arr::operator+(const Vector4Arr& rhs) const
{
	return Vector4Arr {
		m_data.elems.x + rhs.m_data.elems.x,
		m_data.elems.y + rhs.m_data.elems.y,
		m_data.elems.z + rhs.m_data.elems.z,
		m_data.elems.w + rhs.m_data.elems.w,
	};
}

INLINE Vector4Arr Vector4Arr::operator+=(const Vector4Arr& rhs) 
{
	*this = *this + rhs;
	return *this;
}


INLINE Vector4Arr Vector4Arr::operator-(const Vector4Arr& rhs) const
{
	return Vector4Arr {
		m_data.elems.x - rhs.m_data.elems.x,
		m_data.elems.y - rhs.m_data.elems.y,
		m_data.elems.z - rhs.m_data.elems.z,
		m_data.elems.w - rhs.m_data.elems.w,
	};
}


INLINE Vector4Arr Vector4Arr::operator*(const float rhs) const
{
	return Vector4Arr {
		m_data.elems.x * rhs,
		m_data.elems.y * rhs,
		m_data.elems.z * rhs,
		m_data.elems.w * rhs,
	};
}

INLINE Vector4Arr Vector4Arr::operator*=(const float rhs)
{
	*this = *this * rhs;
	return *this;
}


INLINE float Vector4Arr::operator*(const Vector4Arr& rhs) const
{
	return dot(rhs);
}

INLINE Vector4Arr Vector4Arr::operator*=(const Vector4Arr& rhs)
{
	*this = mul(rhs);
	return *this;
}


INLINE Vector4Arr Vector4Arr::operator/(const float rhs) const
{
	return Vector4Arr{
		m_data.elems.x / rhs,
		m_data.elems.y / rhs,
		m_data.elems.z / rhs,
		m_data.elems.w / rhs,
	};
}

INLINE Vector4Arr Vector4Arr::operator/=(const float rhs)
{
	*this = *this / rhs;
	return *this;
}


#ifdef MATH_USE_SIMD

typedef Vector4SIMD Vector4;

#else 

typedef Vector4Arr Vector4;

#endif


}
