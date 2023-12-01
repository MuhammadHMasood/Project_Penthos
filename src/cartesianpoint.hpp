#ifndef CARTESIANPOINT_H
#define CARTESIANPOINT_H
// #include <icecream/icecream.hpp>
#include "point.hpp"
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
class CartesianPoint : public Point<CartesianPoint>
{
public:
    CartesianPoint() : Point(){};
    CartesianPoint(const std::vector<float> &coordinates) : Point(coordinates)
    {
        ;
        // IC(coordinates);
    };
    float distanceSquared() const override;
    float distanceFromSquared(CartesianPoint &p) const override;
    CartesianPoint add(const CartesianPoint &other) const override;
    CartesianPoint subtract(const CartesianPoint &other) const override;
    CartesianPoint floatMultiply(const float other) const override;
    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(dimension, coords);
        // Serialize additional members of CartesianPoint here (if any)
    }
};

#endif
