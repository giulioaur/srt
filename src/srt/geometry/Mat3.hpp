/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  MATRIX HEADER FILE                                 *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_GEOMETRY_MAT3_S
#define S_GEOMETRY_MAT3_S

// System includes.
#include <vector>
#include <array>

// My includes.
#include "Vec3.hpp"

namespace srt{
namespace geometry{

/// This class represents a classic 3D transformation matrix (3 x 3).
class Mat3{
private:
    // ATTRIBUTES

    std::array<float, 9> comps;
    
public:

    // CONSTRUCTORS
    Mat3();
    Mat3(const float n);
    Mat3(const float x0, const float y0, const float z0, 
         const float x1, const float y1, const float z1,
         const float x2, const float y2, const float z2);
    Mat3(const std::vector<float> &vec);
    Mat3(const std::vector<std::vector<float>> &vec);
    Mat3(const Mat3 &old);
    Mat3(Mat3 &&old);

    // OPERATION

    Mat3 operator = (const Mat3 &mat);
    Mat3 operator = (Mat3 &&mat);
    Mat3 operator * (const float d) const;
    Vec3 operator * (const Vec3 &vec) const;

    // METHOD

};

Vec3 operator * (const float d, const Mat3 &vec);
// Mat3 operator * (const float Vec3, const Mat3 &vec);

}
}
#endif