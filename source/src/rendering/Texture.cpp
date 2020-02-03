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
	int x = u * m_width, y = (1 - v) * m_height - 0.0001;

	// Be sure that they are in the right range.
	x = x >= 0 && x <= m_width ? x : (x < 0 ? 0 : m_width - 1);
	y = y >= 0 && y <= m_height ? y : (y < 0 ? 0 : m_height - 1);

	// Return the color in a range from 0 to 1.
	return m_colors[y * m_width + x];
}


}

