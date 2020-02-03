#include "rendering/Texture.hpp"

namespace srt::rendering
{

Texture::Texture(const Color& uniformColor)
	: m_colors({ uniformColor })
	, m_width(1)
	, m_height(1)
{
}

const srt::rendering::Color& Texture::getColor(const float u, const float v)
{
	// The u/v coords are computed from bottom-left angle, we have upper-left angle as origin.
	size_t x = static_cast<size_t>(u * m_width),
		   y = static_cast<size_t>((1 - v) * m_height - 0.0001f);

	// Be sure that they are in the right range.
	x = x >= 0 && x < m_width ? x : (x < 0 ? 0 : m_width - 1);
	y = y >= 0 && y < m_height ? y : (y < 0 ? 0 : m_height - 1);

	return m_colors[y * m_width + x];
}


}

