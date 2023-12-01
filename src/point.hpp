#ifndef POINT_H
#define POINT_H
#include <vector>
#include <span>
#include <stdexcept>
#include <string>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
// #include <icecream/icecream.hpp>
// vector of a point (linear algebra definition of vector)
// In cartesian 2D and 3D, the convention for coordinates is x, y, (z)
template <typename PointType>
class Point
{
public:
    Point(){};
    virtual ~Point() = default;
    virtual float distanceSquared() const = 0;
    virtual float distanceFromSquared(PointType &p) const = 0;
    // virtual void serialize(cereal::BinaryOutputArchive &archive) const = 0;
    // virtual std::unique_ptr<Point> clone() const = 0;

    // Ensure PointType classes implement + operator
    friend PointType operator+(const PointType &lhs, const PointType &rhs)
    {
        return lhs.add(rhs);
    }

    // Ensure PointType classes implement - operator
    friend PointType operator-(const PointType &lhs, const PointType &rhs)
    {
        return lhs.subtract(rhs);
    }

    // Ensure PointType classes implement left float * operator
    friend PointType operator*(const float lhs, const PointType &rhs)
    {
        return rhs.floatMultiply(lhs);
    }

    // Ensure PointType classes implement right float * operator
    friend PointType operator*(const PointType &lhs, const float rhs)
    {
        return lhs.floatMultiply(rhs);
    }

    Point(const std::vector<float> &coordinates) : dimension(coordinates.size()), coords(coordinates){};

    const std::vector<float> &getCoords() const
    {
        // IC(this->coords);
        return this->coords;
    };

    static void checkDim(const size_t &p1_dim, const PointType &p2)
    {
        if (p1_dim != p2.dimension)
        {
            throw std::invalid_argument("p1 has dimension : {" + std::to_string(p1_dim) + "}, p2 has dimension: {" + std::to_string(p2.dimension) + "}, but they need to be the same");
        }
    }

    size_t getDimension() const
    {
        return dimension;
    }

protected:
    size_t dimension;
    // std::span<float> coords;
    std::vector<float> coords;
    // std::vector<float> coords_;
    virtual PointType add(const PointType &other) const = 0;
    virtual PointType subtract(const PointType &other) const = 0;
    virtual PointType floatMultiply(const float other) const = 0;
    // std::unique_ptr<float[]> coords_;
};

template <typename PointType>
class pointComparator
{
public:
    const PointType origin_point;
    pointComparator(const PointType &p) : origin_point((p))
    {
    }
    bool operator()(const std::reference_wrapper<PointType> p1, const std::reference_wrapper<PointType> p2) const
    {
        return origin_point.distanceFromSquared(p1.get()) > origin_point.distanceFromSquared(p2.get());
    }
};

// Point::~Point() {}

#endif