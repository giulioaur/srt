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

    /// The type of the box face.
    /// The directions refer to the viewpoint of a spectator that face the XY faces with negative normal.
    enum class e_face : uint8_t { BACK_FACE, FRONT_FACE, UP_FACE, BOT_FACE, RIGHT_FACE, LEFT_FACE };

public:

    AABox(const Vector4& min, const Vector4& max, const std::shared_ptr<srt::rendering::Material> material);

    virtual bool intersect(const Ray& ray, const float tmin, const float tmax,
        s_hit_record& hit_record) const override;
    virtual const AABB getAABB(const float t0, const float t1) const noexcept override;
    const AARectangle& getFace(const e_face face) const noexcept;

private:

    const std::array<AARectangle, 6> m_sides;

};

}
