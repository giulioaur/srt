#pragma once

#include "geometry/Vector4.hpp"

namespace srt::rendering
{

class Color : public geometry::Vector4SIMD
{
public:

	using Super = geometry::Vector4SIMD;

	Color()
		: Super() { }

	Color(float r, float g, float b)
		: Super(r, g, b, 0){ }

	Color(const Super& other)
		: Super(other) { }

	Color(Super&& other)
		: Super(other) { }

	Color(const Color& other) noexcept
		: Super(other) { }

	Color(Color&& other) noexcept
		: Super(other) { }

	Color operator* (const Color& rhs) const
	{
		return Super::mul(rhs);
	}

	Color operator= (const Color& rhs) noexcept
	{
		Super::operator=(rhs);
		return *this;
	}

	Color operator= (Color&& rhs) noexcept
	{
		Super::operator=(rhs);
		return *this;
	}
};

}