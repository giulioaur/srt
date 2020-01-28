#pragma once

#include "geometry/Vector4.hpp"

namespace srt::rendering
{

class Color : public geometry::Vector4
{
public:

	Color()
		: geometry::Vector4() { }

	Color(float r, float g, float b)
		: geometry::Vector4(r, g, b, 0){ }

	Color(const Color& other)
		: geometry::Vector4(other.x(), other.y(), other.z(), 0) { }

	Color operator+(const Color& rhs) const
	{
		return Color{
			x() + rhs.x(),
			y() + rhs.y(),
			z() + rhs.z()
		};
	}

	Color operator+=(const Color& rhs)
	{
		x() += rhs.x();
		y() += rhs.y();
		z() += rhs.z();
		return *this;
	}

	Color operator * (const float rhs) const
	{
		return Color{
			x() * rhs,
			y() * rhs,
			z() * rhs
		};
	}

	friend Color operator* (const float lhs, const Color& rhs) 
	{
		return rhs * lhs;
	}
};

}