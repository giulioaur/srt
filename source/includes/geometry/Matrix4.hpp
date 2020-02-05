////////////////////////////////////////////////////////////////////////
//																	  //
//								GU ENGINE							  //
//							   by Dr.Sushi							  //
//							   MIfloat License							  //
//																	  //
////////////////////////////////////////////////////////////////////////
#pragma once

#include "Vector4.hpp"

namespace srt::geometry
{


class Matrix4SIMD
{
public:

	Matrix4SIMD();					// Identity matrix
	Matrix4SIMD(const float val);
	Matrix4SIMD(const float x0, const float y0, const float z0, const float w0,
			const float x1, const float y1, const float z1, const float w1,
			const float x2, const float y2, const float z2, const float w2,
			const float x3, const float y3, const float z3, const float w3);
	//Matrix4(const float arr[4][4]);
	Matrix4SIMD(const Matrix4SIMD& other) noexcept;
	Matrix4SIMD(Matrix4SIMD&& other) noexcept;

	/*********************** GETTER ***********************/

	Vector4SIMD raw(const umsize index) const noexcept;
	Vector4SIMD col(const umsize index) const noexcept;

	float& elem(const umsize raw, const umsize col);
	float elem(const umsize raw, const umsize col) const;

	/*********************** OPERATIONS ***********************/

	/*
	 * Get the transposed matrix. The original matrix is not altered.
	 *
	 * @return The transposed matrix.
	 */
	Matrix4SIMD transpose() const noexcept;

	/*********************** OPERATORS ***********************/

	//float* operator[](const umsize index);
	//const float* const operator[](const umsize index) const;

	Matrix4SIMD& operator=(const Matrix4SIMD& rhs) noexcept;
	Matrix4SIMD& operator=(Matrix4SIMD&& rhs) noexcept;

	//Matrix4 operator+(const Matrix4& rhs) const;
	//Matrix4 operator-(const Matrix4& rhs) const;
	Matrix4SIMD operator*(const Matrix4SIMD& rhs) const;
	Vector4SIMD operator*(const Vector4SIMD& rhs) const;

private:

	Vector4SIMD vectorMul(const Vector4SIMD& lhs) const;

	/**
	 * The matrix is saved as col-matrix to allow faster vector-matrix multiplication.
	 */
	union u_matrix_data
	{
		__m128 cols[4];
		struct {
			float x0; float y0; float z0; float w0;
			float x1; float y1; float z1; float w1;
			float x2; float y2; float z2; float w2;
			float x3; float y3; float z3; float w3;
		} elems;
	} m_data;

public:

	friend Vector4SIMD operator*(const Vector4SIMD& lhs, const Matrix4SIMD& rhs)
	{
		return rhs.vectorMul(lhs);
	};

	friend void swap(Matrix4SIMD& a, Matrix4SIMD& b)
	{
		srt::swap(a.m_data.cols[0], b.m_data.cols[0]);
		srt::swap(a.m_data.cols[1], b.m_data.cols[1]);
		srt::swap(a.m_data.cols[2], b.m_data.cols[2]);
		srt::swap(a.m_data.cols[3], b.m_data.cols[3]);
	}

};




///////////////////////////////////////////////////////////////////////////////////////////////////
//											DEFINITIONS											 //
///////////////////////////////////////////////////////////////////////////////////////////////////

INLINE Matrix4SIMD::Matrix4SIMD()
{
	m_data.cols[0] = _mm_set_ps(0, 0, 0, 1);
	m_data.cols[1] = _mm_set_ps(0, 0, 1, 0);
	m_data.cols[2] = _mm_set_ps(0, 1, 0, 0);
	m_data.cols[3] = _mm_set_ps(1, 0, 0, 0);
}

INLINE Matrix4SIMD::Matrix4SIMD(const float val)
{
	m_data.cols[0] = _mm_set_ps(val, val, val, val);
	m_data.cols[1] = _mm_set_ps(val, val, val, val);
	m_data.cols[2] = _mm_set_ps(val, val, val, val);
	m_data.cols[3] = _mm_set_ps(val, val, val, val);
}

INLINE Matrix4SIMD::Matrix4SIMD(
	const float x0, const float x1, const float x2, const float x3,
	const float y0, const float y1, const float y2, const float y3,
	const float z0, const float z1, const float z2, const float z3,
	const float w0, const float w1, const float w2, const float w3)
{
	m_data.cols[0] = _mm_set_ps(w0, z0, y0, x0);
	m_data.cols[1] = _mm_set_ps(w1, z1, y1, x1);
	m_data.cols[2] = _mm_set_ps(w2, z2, y2, x2);
	m_data.cols[3] = _mm_set_ps(w3, z3, y3, x3);
}

INLINE Matrix4SIMD::Matrix4SIMD(const Matrix4SIMD& other) noexcept
{
	m_data.cols[0] = _mm_load_ps((float*)&other.m_data.cols[0]);
	m_data.cols[1] = _mm_load_ps((float*)&other.m_data.cols[1]);
	m_data.cols[2] = _mm_load_ps((float*)&other.m_data.cols[2]);
	m_data.cols[3] = _mm_load_ps((float*)&other.m_data.cols[3]);
}

INLINE Matrix4SIMD::Matrix4SIMD(Matrix4SIMD&& other) noexcept
{
	swap(*this, other);
}

INLINE Vector4SIMD Matrix4SIMD::raw(const umsize index) const noexcept
{
	switch (index)
	{
	case 0:
		return Vector4SIMD{ m_data.elems.x0, m_data.elems.x0, m_data.elems.x0, m_data.elems.x0 };
	case 1:
		return Vector4SIMD{ m_data.elems.y0, m_data.elems.y0, m_data.elems.y0, m_data.elems.y0 };
	case 2:
		return Vector4SIMD{ m_data.elems.z0, m_data.elems.z0, m_data.elems.z0, m_data.elems.z0 };
	case 3:
		return Vector4SIMD{ m_data.elems.w0, m_data.elems.w0, m_data.elems.w0, m_data.elems.w0 };
	default:
		//#TODO_EXCEPTIONS Trigger an ensure.
		return Vector4SIMD{0};
	}
}

INLINE Vector4SIMD Matrix4SIMD::col(const umsize index) const noexcept
{
	return Vector4SIMD{m_data.cols[index]};
}


INLINE float& Matrix4SIMD::elem(const umsize raw, const umsize col)
{
	return ((float*)(&m_data.cols[col]))[raw];
}

INLINE float Matrix4SIMD::elem(const umsize raw, const umsize col) const
{
	return ((float*)(&m_data.cols[col]))[raw];
}

INLINE Matrix4SIMD Matrix4SIMD::transpose() const noexcept
{
	return Matrix4SIMD{
		m_data.elems.x0, m_data.elems.y0, m_data.elems.z0, m_data.elems.w0,
		m_data.elems.x1, m_data.elems.y1, m_data.elems.z1, m_data.elems.w1,
		m_data.elems.x2, m_data.elems.y2, m_data.elems.z2, m_data.elems.w2,
		m_data.elems.x3, m_data.elems.y3, m_data.elems.z3, m_data.elems.w3,
	};
}

INLINE Matrix4SIMD& Matrix4SIMD::operator=(const Matrix4SIMD& rhs) noexcept
{
	Matrix4SIMD ret{ rhs };
	srt::swap(*this, ret);
	return *this;
}

INLINE Matrix4SIMD& Matrix4SIMD::operator=(Matrix4SIMD&& rhs) noexcept
{
	srt::swap(*this, rhs);
	return *this;
}

INLINE Matrix4SIMD Matrix4SIMD::operator*(const Matrix4SIMD& rhs) const
{
	Matrix4SIMD matRows = this->transpose();
	Matrix4SIMD ret{ 0 };

	__m128 tmp0;
	__m128 tmp1;

	tmp0 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[0], rhs.m_data.cols[0], 0xF1), _mm_dp_ps(matRows.m_data.cols[1], rhs.m_data.cols[0], 0xF2));
	tmp1 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[2], rhs.m_data.cols[0], 0xF4), _mm_dp_ps(matRows.m_data.cols[3], rhs.m_data.cols[0], 0xF8));
	ret.m_data.cols[0] = _mm_add_ps(tmp0, tmp1);

	tmp0 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[0], rhs.m_data.cols[1], 0xF1), _mm_dp_ps(matRows.m_data.cols[1], rhs.m_data.cols[1], 0xF2));
	tmp1 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[2], rhs.m_data.cols[1], 0xF4), _mm_dp_ps(matRows.m_data.cols[3], rhs.m_data.cols[1], 0xF8));
	ret.m_data.cols[1] = _mm_add_ps(tmp0, tmp1);

	tmp0 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[0], rhs.m_data.cols[2], 0xF1), _mm_dp_ps(matRows.m_data.cols[1], rhs.m_data.cols[2], 0xF2));
	tmp1 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[2], rhs.m_data.cols[2], 0xF4), _mm_dp_ps(matRows.m_data.cols[3], rhs.m_data.cols[2], 0xF8));
	ret.m_data.cols[2] = _mm_add_ps(tmp0, tmp1);

	tmp0 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[0], rhs.m_data.cols[3], 0xF1), _mm_dp_ps(matRows.m_data.cols[1], rhs.m_data.cols[3], 0xF2));
	tmp1 = _mm_add_ps(_mm_dp_ps(matRows.m_data.cols[2], rhs.m_data.cols[3], 0xF4), _mm_dp_ps(matRows.m_data.cols[3], rhs.m_data.cols[3], 0xF8));
	ret.m_data.cols[3] = _mm_add_ps(tmp0, tmp1);

	return ret;
}

INLINE Vector4SIMD Matrix4SIMD::operator*(const Vector4SIMD& rhs) const
{
	return rhs * this->transpose();
}

Vector4SIMD Matrix4SIMD::vectorMul(const Vector4SIMD& lhs) const
{
	Vector4SIMD ret{ 0 };

	__m128 tmp0;
	__m128 tmp1;

	tmp0 = _mm_add_ps(_mm_dp_ps(lhs.m_data.raw, m_data.cols[0], 0xF1), _mm_dp_ps(lhs.m_data.raw, m_data.cols[1], 0xF2));
	tmp1 = _mm_add_ps(_mm_dp_ps(lhs.m_data.raw, m_data.cols[2], 0xF4), _mm_dp_ps(lhs.m_data.raw, m_data.cols[3], 0xF8));
	ret.m_data.raw = _mm_add_ps(tmp0, tmp1);

	return ret;
}


class Matrix4Arr
{
public:

	Matrix4Arr();					// Identity matrix
	Matrix4Arr(const float val);
	Matrix4Arr(const float x0, const float x1, const float x2, const float x3,
			const float y0, const float y1, const float y2, const float y3,
			const float z0, const float z1, const float z2, const float z3,
			const float w0, const float w1, const float w2, const float w3);
	//Matrix4Arr(const float arr[4][4]);
	Matrix4Arr(const Matrix4Arr& other) noexcept;
	Matrix4Arr(Matrix4Arr&& other) noexcept;

	/*********************** GETTER ***********************/

	Vector4Arr raw(const umsize index) noexcept;
	Vector4Arr col(const umsize index) noexcept;

	float elem(const umsize raw, const umsize col);
	float elem(const umsize raw, const umsize col) const;

	/*********************** OPERATIONS ***********************/

	/*
		* Get the transposed matrix. The original matrix is not altered.
		*
		* @return The transposed matrix.
		*/
	Matrix4Arr transpose() const noexcept;

	/*********************** OPERATORS ***********************/

	float* operator[](const umsize index);
	const float* const operator[](const umsize index) const;

	Matrix4Arr& operator=(const Matrix4Arr& rhs) noexcept;
	Matrix4Arr& operator=(Matrix4Arr&& rhs) noexcept;

	Matrix4Arr operator+(const Matrix4Arr& rhs) const;
	Matrix4Arr operator-(const Matrix4Arr& rhs) const;
	Matrix4Arr operator*(const Matrix4Arr& rhs) const;
	Vector4Arr operator*(const Vector4& rhs) const;

private:

	Vector4Arr vectorMul(const Vector4Arr& lhs) const;

	union u_matrix_data
	{
		float raw[4][4];
		struct {
			float x0; float x1; float x2; float x3;
			float y0; float y1; float y2; float y3;
			float z0; float z1; float z2; float z3;
			float w0; float w1; float w2; float w3;
		} elems;

		u_matrix_data() = default;

		u_matrix_data(float x0, float x1, float x2, float x3,
			float y0, float y1, float y2, float y3,
			float z0, float z1, float z2, float z3,
			float w0, float w1, float w2, float w3)
			: raw{ { x0, x1, x2, x3},
					{ y0, y1, y2, y3},
					{ z0, z1, z2, z3},
					{ w0, w1, w2, w3} } { };
	} m_data;

public:

	friend Vector4 operator*(const Vector4& lhs, const Matrix4Arr& rhs)
	{
		return rhs.vectorMul(lhs);
	};

	friend void swap(Matrix4Arr& a, Matrix4Arr& b)
	{
		srt::swap(a.m_data.raw, b.m_data.raw);
	}

};





///////////////////////////////////////////////////////////////////////////////////////////////////
//											DEFINITIONS											 //
///////////////////////////////////////////////////////////////////////////////////////////////////




INLINE Matrix4Arr::Matrix4Arr()
	: m_data{ 1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1 }
{
}


INLINE Matrix4Arr::Matrix4Arr(const float val)
	: m_data{ val, val, val, val,
				val, val, val, val,
				val, val, val, val,
				val, val, val, val }
{
}


INLINE Matrix4Arr::Matrix4Arr(const float x0, const float x1, const float x2, const float x3,
	const float y0, const float y1, const float y2, const float y3,
	const float z0, const float z1, const float z2, const float z3,
	const float w0, const float w1, const float w2, const float w3)
	: m_data{ x0, x1, x2, x3,
				y0, y1, y2, y3,
				z0, z1, z2, z3,
				w0, w1, w2, w3 }
{
}


//INLINE Matrix4Arr::Matrix4Arr(const float arr[4][4])
//	: m_data{ arr[0][0], arr[0][1], arr[0][2], arr[0][3],
//			  arr[1][0], arr[1][1], arr[1][2], arr[1][3],
//			  arr[2][0], arr[2][1], arr[2][2], arr[2][3],
//			  arr[3][0], arr[3][1], arr[3][2], arr[3][3] }
//{
//}


INLINE Matrix4Arr::Matrix4Arr(const Matrix4Arr& other) noexcept
{
	for (umsize i = 0; i < 4; ++i)
	{
		for (umsize j = 0; j < 4; ++j)
		{
			m_data.raw[i][j] = other.m_data.raw[i][j];
		}
	}
}


INLINE Matrix4Arr::Matrix4Arr(Matrix4Arr&& other) noexcept
{
	srt::swap(*this, other);
}



INLINE Vector4Arr Matrix4Arr::raw(const umsize index) noexcept
{
	return index > 0 && index < 4 ? Vector4{ m_data.raw[index] } : Vector4{ };
}


INLINE Vector4Arr Matrix4Arr::col(const umsize index) noexcept
{
	return index > 0 && index < 4 ?
		Vector4{ m_data.raw[0][index], m_data.raw[1][index], m_data.raw[2][index], m_data.raw[3][index] } :
		Vector4{ };
}


INLINE float Matrix4Arr::elem(const umsize raw, const umsize col)
{
	return m_data.raw[raw][col];
}


INLINE float Matrix4Arr::elem(const umsize raw, const umsize col) const
{
	return m_data.raw[raw][col];
}


INLINE Matrix4Arr Matrix4Arr::transpose() const noexcept
{
	return Matrix4Arr{
		m_data.elems.x0, m_data.elems.y0, m_data.elems.z0, m_data.elems.w0,
			m_data.elems.x1, m_data.elems.y1, m_data.elems.z1, m_data.elems.w1,
			m_data.elems.x2, m_data.elems.y2, m_data.elems.z2, m_data.elems.w2,
			m_data.elems.x3, m_data.elems.y3, m_data.elems.z3, m_data.elems.w3,
	};
}


INLINE Matrix4Arr& Matrix4Arr::operator=(const Matrix4Arr& rhs) noexcept
{
	Matrix4Arr ret{ rhs };
	srt::swap(*this, ret);
	return *this;
}


INLINE Matrix4Arr& Matrix4Arr::operator=(Matrix4Arr&& rhs) noexcept
{
	srt::swap(*this, rhs);
	return *this;
}


INLINE float* Matrix4Arr::operator[](const umsize index)
{
	return m_data.raw[index];
}


INLINE const float* const Matrix4Arr::operator[](const umsize index) const
{
	return m_data.raw[index];
}


INLINE Matrix4Arr Matrix4Arr::operator+(const Matrix4Arr& rhs) const
{
	Matrix4Arr ret{ 0 };

	for (umsize i = 0; i < 4; ++i)
	{
		for (umsize j = 0; j < 4; ++j)
		{
			ret.m_data.raw[i][j] = m_data.raw[i][j] + rhs.m_data.raw[i][j];
		}
	}

	return ret;
}


INLINE Matrix4Arr Matrix4Arr::operator-(const Matrix4Arr& rhs) const
{
	Matrix4Arr ret{ 0 };

	for (umsize i = 0; i < 4; ++i)
	{
		for (umsize j = 0; j < 4; ++j)
		{
			ret.m_data.raw[i][j] = m_data.raw[i][j] - rhs.m_data.raw[i][j];
		}
	}

	return ret;
}


INLINE Matrix4Arr Matrix4Arr::operator*(const Matrix4Arr& rhs) const
{
	Matrix4Arr ret{ 0 };

	for (umsize i = 0; i < 4; ++i)
	{
		for (umsize j = 0; j < 4; ++j)
		{
			for (umsize k = 0; k < 4; ++k)
			{
				ret.m_data.raw[i][j] += m_data.raw[i][k] * rhs.m_data.raw[k][j];
			}
		}
	}

	return ret;
}


INLINE Vector4Arr Matrix4Arr::operator*(const Vector4& rhs) const
{
	return rhs * this->transpose();
}


Vector4Arr Matrix4Arr::vectorMul(const Vector4Arr& lhs) const
{
	Vector4Arr ret{ };

	// Row vector * matrix
	for (umsize i = 0; i < 4; ++i)
	{
		for (umsize j = 0; j < 4; ++j)
		{
			ret.m_data.raw[i] += m_data.raw[j][i] * lhs.m_data.raw[j];
		}
	}

	return ret;
}




#ifdef MATH_USE_SIMD

typedef Matrix4SIMD Matrix4;

#else 

typedef Matrix4Arr Matrix4;

#endif




}