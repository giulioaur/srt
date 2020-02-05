#pragma once

#include "Hitable.hpp"

#include "geometry/Matrix4.hpp"


namespace srt::geometry::hitables
{

/// This class represents an axis aligned box.
class Instance : public Hitable
{
public:

    /// The type of the box face.
    /// The directions refer to the viewpoint of a spectator that face the XY faces with negative normal.
    enum class e_transform : uint8_t { ROTATION, TRANSLATION };

public:

    Instance(const e_transform transform_type, const Vector4& transformVector,
        const std::shared_ptr<Hitable> instanced);

    virtual bool intersect(const Ray& ray, const float tmin, const float tmax,
        s_hit_record& hit_record) const override;
    virtual const AABB getAABB(const float t0, const float t1) const noexcept override;

private:

    Matrix4 getTransformationMatrix(const e_transform transform_type, const Vector4& transformVector) const;
    Matrix4 getRotationMatrix(const Vector4& rotationVector) const;
    Matrix4 getTranslationMatrix(const Vector4& translationVector) const;

    Matrix4 getInvertedMatrix(const e_transform transform_type, const Vector4& transformVector) const;
    Matrix4 getInvertedRotationMatrix(const Vector4& rotationVector) const;
    Matrix4 getInvertedTranslationMatrix(const Vector4& translationVector) const;

    const e_transform m_type;
    const std::shared_ptr<Hitable> m_instanced;
    const Matrix4 m_transformation;
    const Matrix4 m_invert;

};

}
