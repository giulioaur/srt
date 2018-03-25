/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  MATRIX CLASS FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Mat3.hpp"

namespace srt{
namespace geometry{

    /**
     * @brief Constructs a new unitary matrix object.
     * 
     */
    Mat3::Mat3() : comps{{1, 0, 0, 0, 1, 0, 0, 0, 1}} { }

    /**
     * @brief Constructs a new matrix with the same value everywhere.
     * 
     */
    Mat3::Mat3(const float n) : comps{{n, n, n, n, n, n, n, n, n}} { }

    /**
     * @brief Constructs a new Mat 3:: Mat 3 object
     * 
     * @param x0 - The element 0, 0.
     * @param y0 - The element 0, 1.
     * @param z0 - The element 0, 1.
     * @param x1 - The element 1, 0.
     * @param y1 - The element 1, 1.
     * @param z1 - The element 1, 2.
     * @param x2 - The element 2, 0.
     * @param y2 - The element 2, 1.
     * @param z2 - The element 2, 2.
     */
    Mat3::Mat3(const float x0, const float y0, const float z0, const float x1, const float y1, const float z1,
         const float x2, const float y2, const float z2) : comps{{x0, y0, z0, x1, y1, z1, x2, y2, z2}} { }

    /**
     * @brief Constructs a new Mat 3 object using a vector with length > 9.
     * 
     * @param vec - The vector from which take the element.
     */
    Mat3::Mat3(const std::vector<float> &vec){
        if(vec.size() < 9)
            throw std::invalid_argument("The size of the vector must be greater or equal than 9.");

        std::copy(vec.begin(), vec.begin() + 9, this->comps.begin());
    }

    /**
     * @brief Constructs a new Mat 3 object using a vector of vector.
     * 
     * @param vec - The vector from which take the element.
     */
    Mat3::Mat3(const std::vector<std::vector<float>> &vec){
        if(vec.size() < 3)
            throw std::invalid_argument("The rows have to be more than 3.");
        
        for(uint8_t i = 0; i < 3; ++i){
            if(vec[i].size() < 3)
                throw std::invalid_argument("The cols have to be more than 3.");
            
            std::copy(vec[i].begin(), vec[i].begin() + 3, this->comps.begin() + 3 * i);
        }
    }

    /**
     * @brief Constructs a new Mat 3 object coping the old one.
     * 
     * @param old - The matrix to copy.
     */
    Mat3::Mat3(const Mat3 &old) : comps{old.comps} { }

    /**
     * @brief Constructs a new Mat 3 object moving the old one.
     * 
     * @param old - The matrix to move.
     */
    Mat3::Mat3(Mat3 &&old) : comps {std::move(old.comps)} { }

    /**
     * @brief Copy assignment.
     * 
     */
    Mat3 Mat3::operator = (const Mat3 &mat){
        this->comps = mat.comps;
        return *this;
    }

    /**
     * @brief Move assignment.
     * 
     */
    Mat3 Mat3::operator = (Mat3 &&mat){
        this->comps = std::move(mat.comps);
        return *this;
    }

    /**
     * @brief Matrix - scalar multiplication. 
     */
    Mat3 Mat3::operator * (const float d) const{
        Mat3 ret{*this};

        for(uint8_t i = 0; i < 9; ++i)
            ret.comps[i] *= d;

        return ret;
    }

    /**
     * @brief Matrix - column vector multiplication.
     */
    Vec3 Mat3::operator * (const Vec3 &vec) const{
        return Vec3{ comps[0] * vec.comps[0] + comps[1] * vec.comps[1] + comps[2] * vec.comps[2],
                     comps[3] * vec.comps[0] + comps[4] * vec.comps[1] + comps[5] * vec.comps[2],
                     comps[6] * vec.comps[0] + comps[7] * vec.comps[1] + comps[8] * vec.comps[2]};
    }

}
}