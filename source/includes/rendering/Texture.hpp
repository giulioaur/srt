#pragma once

#include <vector>

#include "Color.hpp"

namespace srt::rendering
{

class Texture
{
public:

	/**
	 * @brief Creates a texture with a uniform color.
	 *
	 * @param uniformColor - The diffuse color.
	 */
	Texture(const Color& uniformColor);

	const Color& getColor(const float u, const float v);

private:

	int16_t m_width;
	int16_t m_height;
	std::vector<Color> m_colors;

};

}