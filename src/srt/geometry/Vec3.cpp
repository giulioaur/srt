/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  VECTOR CLASS FILE                                  *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#include "Vec3.hpp"

// System include libraries.
#include <cmath>
#include <stdexcept>

namespace srt{
namespace geometry{ 

    /**
     * @brief Creates a vector with all components setted to 0.
     * 
     */
    Vec3::Vec3() : comps{{0, 0, 0}} { }

    /**
     * @brief Construct a new Vec 3 object with the same value for all components.
     * 
     * @param n - The value for all the components.
     */
    Vec3::Vec3(const float n) : comps{{n, n, n}} { }

    /**
     * @brief Creates a new 3D vector.
     * 
     * @param x - The x axis component.
     * @param y - The y axis component.
     * @param z - The z axis component. 
     */
    Vec3::Vec3(const float x, const float y, const float z) : 
        comps{{x, y, z}} { }

    /**
     * @brief Creates a new 3D vector copying the first three components of a std::vector. The std::vector must
     *        be long at least three. 
     * 
     * @param vec - The vector from which copy the component.
     */
    Vec3::Vec3(const std::vector<float> &vec){
        if(vec.size() < 3)
            throw std::invalid_argument("The size of the vector must be greater or equal than 3.");

        std::copy(vec.begin(), vec.begin() + 3, this->comps.begin());
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
    }

    /**
     * @brief Creates a new vector with the same components of the old one.
     * 
     */
    Vec3::Vec3(const Vec3 &old) : comps{old.comps} { }

    /**
     * @brief Construct a new Vec 3 object using move semantic.
     * 
     * @param old - The vector to move.
     */
    Vec3::Vec3(Vec3 &&old) : comps{std::move(old.comps)} { }

    /**
     * @brief Copy assignment.
     * 
     */
    Vec3 Vec3::operator = (const Vec3& v){
        this->comps = v.comps;
        return *this;
    }

    /**
     * @brief Move assignment.
     * 
     */
    Vec3 Vec3::operator = (Vec3&& v){
        this->comps = std::move(v.comps);
        return *this;
    }

    /**
     * @brief Componentwise addition.
     * 
     */
    Vec3 Vec3::operator + (const Vec3& v) const{
        return Vec3(this->comps[0] + v.comps[0], this->comps[1] + v.comps[1], this->comps[2] + v.comps[2]);
    }

    /**
     * @brief Componentwise addition.
     * 
     */
    Vec3 Vec3::operator += (const Vec3& v){
        this->comps[0] += v.comps[0]; this->comps[1] += v.comps[1]; this->comps[2] += v.comps[2];
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        return *this;
    }

    /**
     * @brief Componentwise subtraction.
     * 
     */ 
    Vec3 Vec3::operator - (const Vec3& v) const{
        return Vec3(this->comps[0] - v.comps[0], this->comps[1] - v.comps[1], this->comps[2] - v.comps[2]);
    }

    /**
     * @brief Opposite vector computation.
     * 
     */
    Vec3 Vec3::operator - () const{
        return Vec3(-this->comps[0], -this->comps[1], -this->comps[2]);
    }

    /**
     * @brief Multiplication.
     * 
     */
    Vec3 Vec3::operator * (const float d) const{
        return Vec3(this->comps[0] * d, this->comps[1] * d, this->comps[2] * d);
    }

    /**
     * @brief Multiplication.
     */
    Vec3 Vec3::operator *= (const float d){
        this->comps[0] *= d; this->comps[1] *= d; this->comps[2] *= d;
        this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        return *this;
    }

    /**
     * @brief Multiplication.
     */
    Vec3 operator * (const float d, const Vec3 &vec){
        return Vec3(vec.comps[0] * d, vec.comps[1] * d, vec.comps[2] * d);
    }

    /**
     * @brief Dot multiplication.
     * 
     */
    float Vec3::operator * (const Vec3& v) const{
        return this->comps[0] * v.comps[0] + this->comps[1] * v.comps[1] + this->comps[2] * v.comps[2];
    }

    /**
     * @brief Norm operation.
     *  
     */
    float Vec3::operator ^ (const short &n) const{
        switch(n){
            case 1:
                return this->comps[0] >= this->comps[1] ? 
                            this->comps[0] >= this->comps[2] ? this->comps[0] : this->comps[2] : 
                            this->comps[1] >= this->comps[2] ? this->comps[1] : this->comps[2];
            case 2:
                return this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2];
        }
        return -1;
    }

    /**
     * @brief Componentwise division.
     * 
     */
    Vec3 Vec3::operator / (const float d) const{
        return Vec3(this->comps[0] / d, this->comps[1] / d, this->comps[2] / d);
    }

    /**
     * @brief Componentwise division.
     */
    Vec3 Vec3::operator /= (const float d){
        this->comps[0] /= d; this->comps[1] /= d; this->comps[2] /= d;
        this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        return *this;
    }

    /**
     * @brief Vector equality.
     */
    bool Vec3::operator == (const Vec3 &v) const{ 
        return this->comps[0] == v.comps[0] && this->comps[1] == v.comps[1] && this->comps[2] == v.comps[2];
    }

    /**
     * @brief Vector disequality.
     */
    bool Vec3::operator != (const Vec3 &v) const{
        return this->comps[0] != v.comps[0] || this->comps[1] != v.comps[1] || this->comps[2] != v.comps[2];
    }

    /**
     * @brief 
     */
    float Vec3::operator [] (const int i) const{
        switch (i){
            case 0:
                return this->comps[0]; break;
            case 1:
                return this->comps[1]; break;
            case 2:
                return this->comps[2]; break;
            default:
                throw std::out_of_range("Vector out of bound exception: The size of the vector is 3.");
        }
    }

    /**
     * @brief Returns the x components.
     * 
     * @return const float& - The x components.
     */
    const float& Vec3::x() const{
        return this->comps[0];
    }

    /**
     * @brief Returns the y components.
     * 
     * @return const float& - The y components.
     */
    const float& Vec3::y() const{
        return this->comps[1];
    }

    /**
     * @brief Returns the z components.
     * 
     * @return const float& - The z components.
     */
    const float& Vec3::z() const{
        return this->comps[2];
    }

    /**
     * @brief Returns the length of the vector.
     * 
     * @return const float& - The length.
     */
    float Vec3::length() const{
        return sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        // return this->comps[3];
    }

    /**
     * @brief Normalizes the vector.
     * 
     * @return Vec3 - A vector with the normalized component of the vector on which the method has been called.
     */
    Vec3 Vec3::normalize() const{
        const float norm = this->length();
        if(norm != 0)
            return *this / norm;
        return Vec3{*this};
    }

    /**
     * @brief Elementwise multiplication.
     * 
     */
    Vec3 Vec3::multiplication(const Vec3 &vec) const{
        return Vec3{this->comps[0] * vec.comps[0], this->comps[1] * vec.comps[1], this->comps[2] * vec.comps[2]};
    }

    /**
     * @brief Cross product.
     */
    Vec3 Vec3::cross(const Vec3 &vec) const{
        return Vec3{this->comps[1] * vec.comps[2] - this->comps[2] * vec.comps[1], 
                    this->comps[2] * vec.comps[0] - this->comps[0] * vec.comps[2], 
                    this->comps[0] * vec.comps[1] - this->comps[1] * vec.comps[0]};
    }

    /**
     * @brief Returns the euclidean distance between two vectors.
     * 
     * @param vec - The vector from which compute euclidean distance.
     * @return float - The euclidean distance between two vectors.
     */
    float Vec3::distance(const Vec3 &vec) const{
        float disx = vec.comps[0] - this->comps[0], disy = vec.comps[1] - this->comps[1], disz = vec.comps[2] - this->comps[2];
        return sqrt(disx * disx + disy * disy + disz * disz);
    }

    /**
     * @brief COmpute the projection of a vector onto the current vector.
     * 
     * @param vec - The vector to project.
     * @return Vec3 projection - The projection.
     */
    Vec3 Vec3::projection(const Vec3 &vec) const{
        float length = this->length();
        return ((*this * vec) / (length * length)) * *this;
    }


    /**
     * @brief Clamps all the components of the vector between a min and a max values.
     * 
     * @param min - The min value.
     * @param max - The max value.
     */
    void Vec3::clamp(const float min, const float max){
        this->comps[0] = this->comps[0] > max ? max : this->comps[0] < min ? min : this->comps[0];
        this->comps[1] = this->comps[1] > max ? max : this->comps[1] < min ? min : this->comps[1];
        this->comps[2] = this->comps[2] > max ? max : this->comps[2] < min ? min : this->comps[2];
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
    }

    /**
     * @brief Makes all the components of the vector integer number. If floor is setted to true, it uses the
     *        floor function, otherwise it uses ceil.
     * 
     * @param floor - True if floor function must be used.
     */
    void Vec3::makeInteger(const bool useFloor){
        if(useFloor){
            this->comps[0] = floor(this->comps[0]); this->comps[1] = floor(this->comps[1]); this->comps[2] = floor(this->comps[2]); 
        }
        else{
            this->comps[0] = ceil(this->comps[0]); this->comps[1] = ceil(this->comps[1]); this->comps[2] = ceil(this->comps[2]); 
        }
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
    }

    /**
     * @brief This is an overloading for allowing output stream to print the vector class.
     * 
     */
    std::ostream& operator << (std::ostream &os, const Vec3 &vec)
    {
        os << vec.comps[0] << ' ' << vec.comps[1] << ' ' << vec.comps[2];
        return os;
    }

    /**
     * @brief Returns a new vector applying a map pattern to the old one.
     * 
     * @param func - The function to apply in the map.
     * @return Vec3 - The vector transformed.
     */
    Vec3 Vec3::map(std::function<float(float)> func){
        return {func(this->comps[0]), func(this->comps[1]), func(this->comps[2])};
    }
}
}