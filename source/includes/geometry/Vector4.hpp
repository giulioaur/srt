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
#include <sstream>
#include <string>

namespace srt::geometry
{

#ifdef MATH_USE_SIMD

#include <xmmintrin.h>
#include <intrin.h>

///////////////////////////////////////////////////////////////////////////////////////////////////
//										SIMD IMPLEMENTATION										 //
///////////////////////////////////////////////////////////////////////////////////////////////////

class Vector4
{
public:

	Vector4();
	Vector4(const float val);
	Vector4(const float x, const float y, const float z, const float w);
	Vector4(const __m128 raw);
	//Vector4(float arr[]);
	Vector4(const Vector4& other);
	Vector4(Vector4&& other);

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
	Vector4 mul(const Vector4& rhs) const;
	float dot(const Vector4& rhs) const;

	/*
	 * This is a cross product in three-dimensional space. The function consider the two operand
	 * to be omogenous vector (a point will be considered as a vector).
	 *
	 * @args rhs The right operand.
	 *
	 * @return The perpendicular vector in three-dimensional space.
	 */
	Vector4 cross(const Vector4& rhs) const;


	/*********************** OPERATORS ***********************/

	float& operator[](const umsize index);
	const float& operator[](const umsize index) const;

	Vector4& operator=(const Vector4& rhs);
	Vector4& operator=(Vector4&& rhs);

	Vector4 operator-() const;

	Vector4 operator+(const Vector4& rhs) const;
	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator*(const float& rhs) const;
	float operator*(const Vector4& rhs) const;

	/**
	 * Return a string representing the array.
	 *
	 * @return A readable format of the vector.
	 */
	core::dataStructures::String toString() const;

private:

	union u_vector_data
	{
		__m128 raw;
		struct {
			float x; float y; float z; float w;
		} elems;
	} m_data;

	friend class Matrix4<float>;

public:

	friend void swap(Vector4& a, Vector4& b)
	{
		srt::swap(a.m_data.raw, b.m_data.raw);
	}

};








///////////////////////////////////////////////////////////////////////////////////////////////////
//											DEFINITIONS											 //
///////////////////////////////////////////////////////////////////////////////////////////////////



INLINE Vector4::Vector4()
{
	m_data.raw = _mm_set_ps(0, 0, 0, 0);
}

INLINE Vector4::Vector4(const float val)
{
	m_data.raw = _mm_set_ps(val, val, val, val);
}

INLINE Vector4::Vector4(const float x, const float y, const float z, const float w)
{
	m_data.raw = _mm_set_ps(w, z, y, x);
}

INLINE Vector4::Vector4(const __m128 raw)
{
	m_data.raw = raw;
}

//INLINE Vector4::Vector4(float arr[])
//{
//	// Check arr alignment.
//	m_data.raw = _mm_load_ps(arr);
//}

INLINE Vector4::Vector4(const Vector4& other)
{
	m_data.raw = _mm_load_ps((float*)(&other.m_data.raw));
}

INLINE Vector4::Vector4(Vector4&& other)
{
	swap(*this, other);
}

INLINE float Vector4::squaredMagnitude() const
{
	return _mm_cvtss_f32(_mm_dp_ps(m_data.raw, m_data.raw, 0xF1));
}

INLINE Vector4 Vector4::mul(const Vector4& rhs) const
{
	Vector4 ret;
	ret.m_data.raw = _mm_mul_ps(m_data.raw, rhs.m_data.raw);
	return ret;
}

INLINE float Vector4::dot(const Vector4& rhs) const
{
	return _mm_cvtss_f32(_mm_dp_ps(m_data.raw, rhs.m_data.raw, 0xF1));
}

INLINE Vector4 Vector4::cross(const Vector4& rhs) const
{
	return Vector4{
		m_data.elems.y* rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.y,
			m_data.elems.x* rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.x,
			m_data.elems.x* rhs.m_data.elems.y + m_data.elems.y * rhs.m_data.elems.x,
			0
	};
}

INLINE float& Vector4::operator[](const umsize index)
{
	return ((float*)&m_data.raw)[index];
}

INLINE const float& Vector4::operator[](const umsize index) const
{
	return ((float*)&m_data.raw)[index];
}

INLINE Vector4& Vector4::operator=(const Vector4& rhs)
{
	Vector4 tmp{ rhs };
	swap(*this, tmp);
	return *this;
}

INLINE Vector4& Vector4::operator=(Vector4&& rhs)
{
	swap(*this, rhs);
	return *this;
}

INLINE Vector4 Vector4::operator+(const Vector4& rhs) const
{
	Vector4 ret;
	ret.m_data.raw = _mm_add_ps(m_data.raw, rhs.m_data.raw);
	return ret;
}

INLINE Vector4 Vector4::operator-(const Vector4& rhs) const
{
	Vector4 ret;
	ret.m_data.raw = _mm_sub_ps(m_data.raw, rhs.m_data.raw);
	return ret;
}

INLINE Vector4 Vector4::operator*(const float& rhs) const
{
	Vector4 ret;
	ret.m_data.raw = _mm_mul_ps(m_data.raw, _mm_set1_ps(rhs));
	return ret;
}

INLINE float Vector4::operator*(const Vector4& rhs) const
{
	return dot(rhs);
}


INLINE core::dataStructures::String Vector4::toString() const
{
	float* printable = (float*)&m_data.raw;
	return core::dataStructures::String::printf(STRING("{ %f, %f, %f, %f }"),
		printable[0], printable[1], printable[2], printable[3]);
}

#else

class Matrix4;

class Vector4
{
public:

	Vector4();
	Vector4(const float val);
	Vector4(const float x, const float y, const float z, const float w);
	Vector4(const float arr[4]);
	Vector4(const Vector4& other) noexcept;
	Vector4(Vector4&& other) noexcept;

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
	Vector4 normalize() const;
	Vector4 mul(const Vector4& rhs) const;	// Element-wise multiplication.
	float dot(const Vector4& rhs) const;			// Dot product.

	/*
	 * This is a cross product in three-dimensional space. The function consider the two operand
	 * to be omogenous vector (a point will be considered as a vector).
	 *
	 * @args rhs The right operand.
	 *
	 * @return The perpendicular vector in three-dimensional space.
	 */
	Vector4 cross(const Vector4& rhs) const;		

	std::string toString() const;

	/*********************** OPERATORS ***********************/

	float operator[](const umsize index);
	const float operator[](const umsize index) const;

	Vector4& operator=(const Vector4& rhs) noexcept;
	Vector4& operator=(Vector4&& rhs) noexcept;

	bool operator==(const Vector4& rhs) const;
	bool operator!=(const Vector4& rhs) const;

	Vector4 operator-() const;

	Vector4 operator+(const Vector4& rhs) const;	
	Vector4 operator-(const Vector4& rhs) const;
	Vector4 operator*(const float rhs) const;				// Scalar product.
	Vector4 operator*=(const float rhs);					// Scalar product.
	float operator*(const Vector4& rhs) const;				// Dot product.
	Vector4 operator/(const float rhs) const;				// Scalar division.
	Vector4 operator/=(const float rhs);					// Scalar division.

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


	friend class Matrix4;

public:

	friend Vector4 operator* (const float lhs, const Vector4 rhs)
	{
		return rhs * lhs;
	}

	friend void swap(Vector4& a, Vector4& b)
	{
		srt::swap(a.m_data.raw, b.m_data.raw);
	}

};





///////////////////////////////////////////////////////////////////////////////////////////////////
//											DEFINITIONS											 //
///////////////////////////////////////////////////////////////////////////////////////////////////




INLINE Vector4::Vector4()
	: m_data(0, 0, 0, 0)
{
}


INLINE Vector4::Vector4(const float val)
	: m_data(val, val, val, val)
{
}


INLINE Vector4::Vector4(const float x, const float y, const float z, const float w)
	: m_data(x, y, z, w)
{
}


INLINE Vector4::Vector4(const float arr[4])
	: m_data(arr[0], arr[1], arr[2], arr[3])
{
}


INLINE Vector4::Vector4(const Vector4& other) noexcept
	: Vector4(other.m_data.raw)
{
}


INLINE Vector4::Vector4(Vector4&& other) noexcept
{
	srt::swap(*this, other);
}


INLINE float Vector4::length() const
{
	return sqrt(squaredMagnitude());
}


INLINE float Vector4::squaredMagnitude() const
{
	return m_data.elems.x * m_data.elems.x +
		   m_data.elems.y * m_data.elems.y +
		   m_data.elems.z * m_data.elems.z +
		   m_data.elems.w * m_data.elems.w;
}


INLINE Vector4 Vector4::normalize() const
{
	return *this / (m_data.elems.x + m_data.elems.y + m_data.elems.z);
}


INLINE Vector4 Vector4::mul(const Vector4& rhs) const
{
	return Vector4{ m_data.elems.x * rhs.m_data.elems.x,
					  m_data.elems.y * rhs.m_data.elems.y,
					  m_data.elems.z * rhs.m_data.elems.z,
					  m_data.elems.w * rhs.m_data.elems.w };
}


INLINE float Vector4::dot(const Vector4& rhs) const
{
	return m_data.elems.x * rhs.m_data.elems.x +
		   m_data.elems.y * rhs.m_data.elems.y +
		   m_data.elems.z * rhs.m_data.elems.z +
		   m_data.elems.w * rhs.m_data.elems.w;
}


INLINE Vector4 Vector4::cross(const Vector4& rhs) const
{
	return Vector4{
		m_data.elems.y * rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.y,
		m_data.elems.x * rhs.m_data.elems.z + m_data.elems.z * rhs.m_data.elems.x,
		m_data.elems.x * rhs.m_data.elems.y + m_data.elems.y * rhs.m_data.elems.x,
		0
	};
}

INLINE std::string Vector4::toString() const
{
	std::ostringstream stringStream;
	stringStream << x() << ", " << y() << ", " << z();
	return stringStream.str();
}


INLINE float Vector4::operator[](const umsize index)
{
	return m_data.raw[index];
}


INLINE const float Vector4::operator[](const umsize index) const
{
	return m_data.raw[index];
}


INLINE Vector4& Vector4::operator=(const Vector4& rhs) noexcept
{
	Vector4 tmp(rhs);
	srt::swap(*this, tmp);
	return *this;
}


INLINE Vector4& Vector4::operator=(Vector4&& rhs) noexcept
{
	srt::swap(*this, rhs);
	return *this;
}

INLINE bool Vector4::operator==(const Vector4& rhs) const
{
	return m_data.elems.x == rhs.m_data.elems.x &&
		   m_data.elems.y == rhs.m_data.elems.y &&
		   m_data.elems.z == rhs.m_data.elems.z &&
		   m_data.elems.w == rhs.m_data.elems.w;
}

INLINE bool Vector4::operator!=(const Vector4& rhs) const
{
	return !(*this == rhs);
}


INLINE Vector4 Vector4::operator-() const
{
	return Vector4 {
		- m_data.elems.x,
		- m_data.elems.y,
		- m_data.elems.z,
		- m_data.elems.w,
	};
}


INLINE Vector4 Vector4::operator+(const Vector4& rhs) const
{
	return Vector4 {
		m_data.elems.x + rhs.m_data.elems.x,
		m_data.elems.y + rhs.m_data.elems.y,
		m_data.elems.z + rhs.m_data.elems.z,
		m_data.elems.w + rhs.m_data.elems.w,
	};
}


INLINE Vector4 Vector4::operator-(const Vector4& rhs) const
{
	return Vector4 {
		m_data.elems.x - rhs.m_data.elems.x,
		m_data.elems.y - rhs.m_data.elems.y,
		m_data.elems.z - rhs.m_data.elems.z,
		m_data.elems.w - rhs.m_data.elems.w,
	};
}


INLINE Vector4 Vector4::operator*(const float rhs) const
{
	return Vector4 {
		m_data.elems.x * rhs,
		m_data.elems.y * rhs,
		m_data.elems.z * rhs,
		m_data.elems.w * rhs,
	};
}

INLINE Vector4 Vector4::operator*=(const float rhs)
{
	*this = *this * rhs;
	return *this;
}


INLINE float Vector4::operator*(const Vector4& rhs) const
{
	return dot(rhs);
}


INLINE Vector4 Vector4::operator/(const float rhs) const
{
	return Vector4{
		m_data.elems.x / rhs,
		m_data.elems.y / rhs,
		m_data.elems.z / rhs,
		m_data.elems.w / rhs,
	};
}

INLINE Vector4 Vector4::operator/=(const float rhs)
{
	*this = *this / rhs;
	return *this;
}



#endif





}
