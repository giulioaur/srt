#include "geometry/hitables/Instance.hpp"

namespace srt::geometry::hitables
{

Instance::Instance(const e_transform transform_type, 
	const Vector4& transformVector, const std::shared_ptr<Hitable> instanced)
	: m_type(transform_type)
	, m_instanced(instanced)
	, m_transformation(getTransformationMatrix(transform_type, transformVector))
	, m_invert(getInvertedMatrix(transform_type, transformVector))
{
}

bool Instance::intersect(const Ray& ray, const float tmin, const float tmax, s_hit_record& hit_record) const
{
	Ray transformedRay{ ray.getOrigin() * m_transformation, ray.getDirection() * m_transformation };
	if (m_instanced->intersect(transformedRay, tmin, tmax, hit_record))
	{
		hit_record.point = hit_record.point * m_invert;
		if (m_type == e_transform::ROTATION)
		{
			hit_record.normal = hit_record.normal * m_invert;
		}

		return true;
	}

	return false;
}

const AABB Instance::getAABB(const float t0, const float t1) const noexcept
{
	return m_instanced->getAABB(t0, t1);
}

Matrix4 Instance::getTransformationMatrix(const e_transform transform_type, const Vector4& transformVector) const
{
	switch (transform_type)
	{
	case e_transform::ROTATION:
		return getRotationMatrix(transformVector);
	case e_transform::TRANSLATION:
	default:
		return getTranslationMatrix(transformVector);
	}
}

Matrix4 Instance::getRotationMatrix(const Vector4& rotationVector) const
{
	Matrix4 yawMatrix{
		cos(rotationVector[2]), -sin(rotationVector[2]), 0, 0,
		sin(rotationVector[2]), cos(rotationVector[2]),  0, 0,
		0,                      0,                       1, 0,
		0,                      0,                       0, 0
	};
	Matrix4 pitchMatrix{
		cos(rotationVector[1]), 0, -sin(rotationVector[1]), 0,
		0,                      1,                       0, 0,
		sin(rotationVector[1]), 0, cos(rotationVector[1]),  0,
		0,                      0,                       0, 0
	};
	Matrix4 rollMatrix{
		1,                      0,                       1, 0,
		0, cos(rotationVector[0]), -sin(rotationVector[0]), 0,
		0, sin(rotationVector[0]), cos(rotationVector[0]),  0,
		0,                      0,                       0, 0
	};

	// This is subjected to Gimbal Lock, may use quaternion instead.
	return yawMatrix * pitchMatrix * rollMatrix;
}

Matrix4 Instance::getTranslationMatrix(const Vector4& translationVector) const
{
	return Matrix4{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		translationVector[0], translationVector[1], translationVector[2], 0
	};
}

Matrix4 Instance::getInvertedMatrix(const e_transform transform_type, const Vector4& transformVector) const
{
	switch (transform_type)
	{
	case e_transform::ROTATION:
		return getInvertedRotationMatrix(transformVector);
	case e_transform::TRANSLATION:
	default:
		return getInvertedTranslationMatrix(transformVector);
	}
}

Matrix4 Instance::getInvertedRotationMatrix(const Vector4& rotationVector) const
{
	Matrix4 yawMatrix{
		cos(rotationVector[2]), sin(rotationVector[2]),  0, 0,
		-sin(rotationVector[2]), cos(rotationVector[2]), 0, 0,
		0,                      0,                       1, 0,
		0,                      0,                       0, 0
	};
	Matrix4 pitchMatrix{
		cos(rotationVector[1]), 0, sin(rotationVector[1]),  0,
		0,                      1,                       0, 0,
		-sin(rotationVector[1]), 0, cos(rotationVector[1]), 0,
		0,                      0,                       0, 0
	};
	Matrix4 rollMatrix{
		1,                      0,                       1, 0,
		0, cos(rotationVector[0]), sin(rotationVector[0]),  0,
		0, -sin(rotationVector[0]), cos(rotationVector[0]), 0,
		0,                      0,                       0, 0
	};

	// This is subjected to Gimbal Lock, may use quaternion instead.
	return yawMatrix * pitchMatrix * rollMatrix;
}

Matrix4 Instance::getInvertedTranslationMatrix(const Vector4& translationVector) const
{
	return Matrix4{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-translationVector[0], -translationVector[1], -translationVector[2], 0
	};
}

}

