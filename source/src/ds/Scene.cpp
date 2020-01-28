#include "ds/Scene.hpp"


namespace srt::ds
{

Scene::Scene(const float width, const float height, const std::string &name, 
	const float t0 /*= 0*/, const float t1 /*= 1*/)
	: width(width)
	, height(height)
	, name(name)
	, t0(t0)
	, t1(t1)
{

}

}

