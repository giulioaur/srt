/*******************************************************
 *                                                     *
 *  srt: Sushi RayTracer                               *
 *                                                     *
 *  VECTOR HEADER FILE                                 *
 *                                                     *
 *  Giulio Auriemma                                    *
 *                                                     *
 *******************************************************/
#ifndef S_GEOMETRY_VEC3_S
#define S_GEOMETRY_VEC3_S

#ifdef _WIN32
#define VM_INLINE inline
#elif
#define VM_INLINE __attribute__((always_inline))
#endif

// System includes
#include <array>

#include <cmath>
#include <functional>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

namespace srt{
namespace geometry{

/// This class represents a classic 3D vector.
class Vec3{
private:
    // ATTRIBUTES

    std::array<float, 3> comps;

    // FRIENDS

    friend class Mat3;
    
public:

    /**
     * @brief Creates a vector with all components setted to 0.
     * 
     */
    Vec3() : comps{{0, 0, 0}} { }

    /**
     * @brief Construct a new Vec 3 object with the same value for all components.
     * 
     * @param n - The value for all the components.
     */
    Vec3(const float n) : comps{{n, n, n}} { }

    /**
     * @brief Creates a new 3D vector.
     * 
     * @param x - The x axis component.
     * @param y - The y axis component.
     * @param z - The z axis component. 
     */
    Vec3(const float x, const float y, const float z) : 
        comps{{x, y, z}} { }

    /**
     * @brief Creates a new 3D vector copying the first three components of a std::vector. The std::vector must
     *        be long at least three. 
     * 
     * @param vec - The vector from which copy the component.
     */
    Vec3(const std::vector<float> &vec){
        if(vec.size() < 3)
            throw std::invalid_argument("The size of the vector must be greater or equal than 3.");

        std::copy(vec.begin(), vec.begin() + 3, this->comps.begin());
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
    }

    /**
     * @brief Creates a new vector with the same components of the old one.
     * 
     */
    Vec3(const Vec3 &old) : comps{old.comps} { }

    /**
     * @brief Construct a new Vec 3 object using move semantic.
     * 
     * @param old - The vector to move.
     */
    Vec3(Vec3 &&old) : comps{std::move(old.comps)} { }

    /**
     * @brief Copy assignment.
     * 
     */
    VM_INLINE Vec3 operator = (const Vec3& v){
        this->comps = v.comps;
        return *this;
    }

    /**
     * @brief Move assignment.
     * 
     */
    VM_INLINE Vec3 operator = (Vec3&& v){
        this->comps = std::move(v.comps);
        return *this;
    }

    /**
     * @brief Componentwise addition.
     * 
     */
    VM_INLINE Vec3 operator + (const Vec3& v) const{
        return Vec3(this->comps[0] + v.comps[0], this->comps[1] + v.comps[1], this->comps[2] + v.comps[2]);
    }

    /**
     * @brief Componentwise addition.
     * 
     */
    VM_INLINE Vec3 operator += (const Vec3& v){
        this->comps[0] += v.comps[0]; this->comps[1] += v.comps[1]; this->comps[2] += v.comps[2];
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        return *this;
    }

    /**
     * @brief Componentwise subtraction.
     * 
     */ 
    VM_INLINE Vec3 operator - (const Vec3& v) const{
        return Vec3(this->comps[0] - v.comps[0], this->comps[1] - v.comps[1], this->comps[2] - v.comps[2]);
    }

    /**
     * @brief Opposite vector computation.
     * 
     */
    VM_INLINE Vec3 operator - () const{
        return Vec3(-this->comps[0], -this->comps[1], -this->comps[2]);
    }

    /**
     * @brief Multiplication.
     * 
     */
    VM_INLINE Vec3 operator * (const float d) const{
        return Vec3(this->comps[0] * d, this->comps[1] * d, this->comps[2] * d);
    }

    /**
     * @brief Multiplication.
     */
    VM_INLINE Vec3 operator *= (const float d){
        this->comps[0] *= d; this->comps[1] *= d; this->comps[2] *= d;
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        return *this;
    }

    /**
     * @brief Dot multiplication.
     * 
     */
    VM_INLINE float operator * (const Vec3& v) const{
        return this->comps[0] * v.comps[0] + this->comps[1] * v.comps[1] + this->comps[2] * v.comps[2];
    }

    friend VM_INLINE Vec3 operator * (const float d, const Vec3 &vec){
        return Vec3(vec.comps[0] * d, vec.comps[1] * d, vec.comps[2] * d);
    }

    /**
     * @brief Componentwise division.
     * 
     */
    VM_INLINE Vec3 operator / (const float d) const{
        return Vec3(this->comps[0] / d, this->comps[1] / d, this->comps[2] / d);
    }

    /**
     * @brief Componentwise division.
     */
    VM_INLINE Vec3 operator /= (const float d){
        this->comps[0] /= d; this->comps[1] /= d; this->comps[2] /= d;
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
        return *this;
    }
    
    /**
     * @brief Componentwise division.
     * 
     */
    VM_INLINE Vec3 operator / (const Vec3 vec) const{
        return Vec3(this->comps[0] / vec.comps[0], this->comps[1] / vec.comps[1], this->comps[2] / vec.comps[2]);
    }

    /**
     * @brief Vector equality.
     */
    VM_INLINE bool operator == (const Vec3 &v) const{ 
        return this->comps[0] == v.comps[0] && this->comps[1] == v.comps[1] && this->comps[2] == v.comps[2];
    }

    /**
     * @brief Vector disequality.
     */
    VM_INLINE bool operator != (const Vec3 &v) const{
        return this->comps[0] != v.comps[0] || this->comps[1] != v.comps[1] || this->comps[2] != v.comps[2];
    }

    /**
     * @brief 
     */
    VM_INLINE float operator [] (const int i) const{
        return this->comps[i];
    }

    /**
     * @brief Returns the x components.
     * 
     * @return const float& - The x components.
     */
    VM_INLINE const float& x() const{
        return this->comps[0];
    }

    /**
     * @brief Returns the y components.
     * 
     * @return const float& - The y components.
     */
    VM_INLINE const float& y() const{
        return this->comps[1];
    }

    /**
     * @brief Returns the z components.
     * 
     * @return const float& - The z components.
     */
    VM_INLINE const float& z() const{
        return this->comps[2];
    }

    /**
     * @brief Elementwise multiplication.
     * 
     */
    VM_INLINE Vec3 multiplication(const Vec3 &vec) const{
        return Vec3{this->comps[0] * vec.comps[0], this->comps[1] * vec.comps[1], this->comps[2] * vec.comps[2]};
    }

    /**
     * @brief Returns the euclidean distance between two vectors.
     * 
     * @param vec - The vector from which compute euclidean distance.
     * @return float - The euclidean distance between two vectors.
     */
    VM_INLINE float distance(const Vec3 &vec) const{
        float disx = vec.comps[0] - this->comps[0], disy = vec.comps[1] - this->comps[1], disz = vec.comps[2] - this->comps[2];
        return sqrt(disx * disx + disy * disy + disz * disz);
    }

    /**
     * @brief Clamps all the components of the vector between a min and a max values.
     * 
     * @param min - The min value.
     * @param max - The max value.
     */
    VM_INLINE void clamp(const float min, const float max){
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
    VM_INLINE void makeInteger(const bool useFloor){
        if(useFloor){
            this->comps[0] = floor(this->comps[0]); this->comps[1] = floor(this->comps[1]); this->comps[2] = floor(this->comps[2]); 
        }
        else{
            this->comps[0] = ceil(this->comps[0]); this->comps[1] = ceil(this->comps[1]); this->comps[2] = ceil(this->comps[2]); 
        }
        // this->comps[3] = sqrt(this->comps[0] * this->comps[0] + this->comps[1] * this->comps[1] + this->comps[2] * this->comps[2]);
    }

    // /**
    //  * @brief This is an overloading for allowing output stream to print the vector class.
    //  * 
    //  */
    // friend VM_INLINE std::ostream& operator << (std::ostream &os, const Vec3 &vec)
    // {
    //     os << vec.comps[0] << ' ' << vec.comps[1] << ' ' << vec.comps[2];
    //     return os;
    // }

    /**
     * @brief Norm operation.
     *  
     */
    inline float operator ^ (const short &n) const{
        switch(n){
            case 1:
                return max({this->x(), this->y(), this->z()});
            case 2:
                return this->x() * this->x() + this->y() * this->y() + this->z() * this->z();
        }
        return -1;
    }

    /**
     * @brief Cross product.
     */
    VM_INLINE Vec3 cross(const Vec3 &vec) const{
        return Vec3{this->y() * vec.z() - this->z() * vec.y(), 
                    this->z() * vec.x() - this->x() * vec.z(), 
                    this->x() * vec.y() - this->y() * vec.x()};
    }

    /**
     * @brief Returns the length of the vector.
     * 
     * @return const float& - The length.
     */
    VM_INLINE float length() const{
        return sqrt(*this * *this);
    }

    /**
     * @brief Normalizes the vector.
     * 
     * @return Vec3 - A vector with the normalized component of the vector on which the method has been called.
     */
    VM_INLINE Vec3 normalize() const{
        const float norm = this->length();
        if(norm != 0)
            return *this / norm;
        return Vec3{*this};
    }

    /**
     * @brief Computes the projection of a vector onto the current vector.
     * 
     * @param vec - The vector to project.
     * @return Vec3 projection - The projection.
     */
    VM_INLINE Vec3 projection(const Vec3 &vec) const{
        float length = this->length();
        return ((*this * vec) / (length * length)) * *this;
    }

    /**
     * @brief Returns a new vector applying a map pattern to the old one.
     * 
     * @param func - The function to apply in the map.
     * @return Vec3 - The vector transformed.
     */
    inline Vec3 map(std::function<float(float)> func){
        return {func(this->x()), func(this->y()), func(this->z())};
    }
};

VM_INLINE Vec3 operator * (const float d, const Vec3 &vec);
}
}
#endif