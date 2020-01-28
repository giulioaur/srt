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

	Color operator+=(const Color& rhs)
	{
		x() += rhs.x();
		y() += rhs.y();
		z() += rhs.z();
		return *this;
	}
};

}