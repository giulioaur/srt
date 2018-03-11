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
    Vec3::Vec3() : _x(0), _y(0), _z(0), _length(0) {}

    /**
     * @brief Creates a new 3D vector.
     * 
     * @param x - The x axis component.
     * @param y - The y axis component.
     * @param z - The z axis component. 
     */
    Vec3::Vec3(const float x, const float y, const float z) : _x(x), _y(y), _z(z), 
        _length(sqrt(x * x + y * y + z * z)) {}

    /**
     * @brief Creates a new 3D vector copying the first three components of a std::vector. The std::vector must
     *        be long at least three. 
     * 
     * @param vec - The vector from which copy the component.
     */
    Vec3::Vec3(const std::vector<float> &vec){
        if(vec.size() < 3)
            throw std::invalid_argument("The size of the vector must be greater or equal than 3.");
        this->_x = vec[0]; this->_y = vec[1]; this->_z = vec[2];
        this->_length = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
    }

    /**
     * @brief Creates a new vector with the same components of the old one.
     * 
     */
    Vec3::Vec3(const Vec3 &old) : _x(old._x), _y(old._y), _z(old._z), _length(old._length){}

    /**
     * @brief Componentwise addition.
     * 
     */
    Vec3 Vec3::operator + (const Vec3& v) const{
        return Vec3(this->_x + v._x, this->_y + v._y, this->_z + v._z);
    }

    /**
     * @brief Componentwise addition.
     * 
     */
    Vec3 Vec3::operator += (const Vec3& v){
        this->_x += v._x; this->_y += v._y; this->_z += v._z;
        this->_length = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
        return *this;
    }

    /**
     * @brief Componentwise subtraction.
     * 
     */ 
    Vec3 Vec3::operator - (const Vec3& v) const{
        return Vec3(this->_x - v._x, this->_y - v._y, this->_z - v._z);
    }

    /**
     * @brief Opposite vector computation.
     * 
     */
    Vec3 Vec3::operator - () const{
        return Vec3(-this->_x, -this->_y, -this->_z);
    }

    /**
     * @brief Multiplication.
     * 
     */
    Vec3 Vec3::operator * (const float d) const{
        return Vec3(this->_x * d, this->_y * d, this->_z * d);
    }

    /**
     * @brief Multiplication.
     */
    Vec3 Vec3::operator *= (const float d){
        this->_x *= d; this->_y *= d; this->_z *= d;
        this->_length = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
        return *this;
    }

    /**
     * @brief Multiplication.
     */
    Vec3 operator * (const float d, const Vec3 &vec){
        return Vec3(vec._x * d, vec._y * d, vec._z * d);
    }

    /**
     * @brief Dot multiplication.
     * 
     */
    float Vec3::operator * (const Vec3& v) const{
        return this->_x * v._x + this->_y * v._y + this->_z * v._z;
    }

    /**
     * @brief Norm operation.
     *  
     */
    float Vec3::operator ^ (const short &n) const{
        switch(n){
            case 1:
                return this->_x >= this->_y ? 
                            this->_x >= this->_z ? this->_x : this->_z : 
                            this->_y >= this->_z ? this->_y : this->_z;
            case 2:
                return this->_x * this->_x + this->_y * this->_y + this->_z * this->_z;
        }
        return -1;
    }

    /**
     * @brief Componentwise division.
     * 
     */
    Vec3 Vec3::operator / (const float d) const{
        return Vec3(this->_x / d, this->_y / d, this->_z / d);
    }

    /**
     * @brief Componentwise division.
     */
    Vec3 Vec3::operator /= (const float d){
        this->_x /= d; this->_y /= d; this->_z /= d;
        this->_length = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
        return *this;
    }

    /**
     * @brief Vector equality.
     */
    bool Vec3::operator == (const Vec3 &v) const{ 
        return this->_x == v._x && this->_y == v._y && this->_z == v._z;
    }

    /**
     * @brief Vector disequality.
     */
    bool Vec3::operator != (const Vec3 &v) const{
        return this->_x != v._x || this->_y != v._y || this->_z != v._z;
    }

    /**
     * @brief 
     */
    float Vec3::operator [] (const int i) const{
        switch (i){
            case 0:
                return this->_x; break;
            case 1:
                return this->_y; break;
            case 2:
                return this->_z; break;
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
        return this->_x;
    }

    /**
     * @brief Returns the y components.
     * 
     * @return const float& - The y components.
     */
    const float& Vec3::y() const{
        return this->_y;
    }

    /**
     * @brief Returns the z components.
     * 
     * @return const float& - The z components.
     */
    const float& Vec3::z() const{
        return this->_z;
    }

    /**
     * @brief Returns the length of the vector.
     * 
     * @return const float& - The length.
     */
    const float& Vec3::length() const{
        return this->_length;
    }

    /**
     * @brief Normalizes the vector.
     * 
     * @return Vec3 - A vector with the normalized component of the vector on which the method has been called.
     */
    Vec3 Vec3::normalize() const{
        const float norm = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
        if(norm != 0)
            return *this / norm;
        return Vec3{*this};
    }

    /**
     * @brief Elementwise multiplication.
     * 
     */
    Vec3 Vec3::multiplication(const Vec3 &vec) const{
        return Vec3{this->_x * vec._x, this->_y * vec._y, this->_z * vec._z};
    }

    /**
     * @brief Cross product.
     */
    Vec3 Vec3::cross(const Vec3 &vec) const{
        return Vec3{this->_y * vec._z - this->_z * vec._y, 
                    this->_z * vec._x - this->_x * vec._z, 
                    this->_x * vec._y - this->_y * vec._x};
    }

    /**
     * @brief Returns the euclidean distance between two vectors.
     * 
     * @param vec - The vector from which compute euclidean distance.
     * @return float - The euclidean distance between two vectors.
     */
    float Vec3::distance(const Vec3 &vec) const{
        float disx = vec._x - this->_x, disy = vec._y - this->_y, disz = vec._z - this->_z;
        return sqrt(disx * disx + disy * disy + disz * disz);
    }

    /**
     * @brief COmpute the projection of a vector onto the current vector.
     * 
     * @param vec - The vector to project.
     * @return Vec3 projection - The projection.
     */
    Vec3 Vec3::projection(const Vec3 &vec) const{
        return ((*this * vec) / (this->_length * this->_length)) * *this;
    }


    /**
     * @brief Clamps all the components of the vector between a min and a max values.
     * 
     * @param min - The min value.
     * @param max - The max value.
     */
    void Vec3::clamp(const float min, const float max){
        this->_x = this->_x > max ? max : this->_x < min ? min : this->_x;
        this->_y = this->_y > max ? max : this->_y < min ? min : this->_y;
        this->_z = this->_z > max ? max : this->_z < min ? min : this->_z;
        this->_length = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
    }

    /**
     * @brief Makes all the components of the vector integer number. If floor is setted to true, it uses the
     *        floor function, otherwise it uses ceil.
     * 
     * @param floor - True if floor function must be used.
     */
    void Vec3::makeInteger(const bool useFloor){
        if(useFloor){
            this->_x = floor(this->_x); this->_y = floor(this->_y); this->_z = floor(this->_z); 
        }
        else{
            this->_x = ceil(this->_x); this->_y = ceil(this->_y); this->_z = ceil(this->_z); 
        }
        this->_length = sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
    }

    /**
     * @brief This is an overloading for allowing output stream to print the vector class.
     * 
     */
    std::ostream& operator << (std::ostream &os, const Vec3 &vec)
    {
        os << vec._x << ' ' << vec._y << ' ' << vec._z;
        return os;
    }

    /**
     * @brief Returns a new vector applying a map pattern to the old one.
     * 
     * @param func - The function to apply in the map.
     * @return Vec3 - The vector transformed.
     */
    Vec3 Vec3::map(std::function<float(float)> func){
        return {func(this->_x), func(this->_y), func(this->_z)};
    }
}
}