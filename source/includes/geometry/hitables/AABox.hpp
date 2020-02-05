#pragma once

#include "Hitable.hpp"

#include "AARectangle.hpp"
#include "rendering/Material.hpp"

namespace srt::geometry::hitables
{

/// This class represents an axis aligned box.
class AABox : public Hitable 
{
public:

    AABox(const Vector4& min, const Vector4& max, const std::shared_ptr<srt::rendering::Material> material);

    virtual bool intersect(const Ray& ray, float tmin, float tmax,
        s_hit_record& hit_record) const override;
    virtual const AABB getAABB(const float t0, const float t1) const noexcept override;

private:

    Vector4 getNormal(const Vector4& point) const noexcept;
    TextureCoords getTextureCoords(const Vector4& point) const noexcept;

    const Vector4 m_min;
    const Vector4 m_max;
    const std::shared_ptr<srt::rendering::Material> m_material;

};

}
