#include "cartesianpoint.hpp"
#include "array"
#include <iostream>

float CartesianPoint::distanceSquared() const
{
    float distance = 0.0;
    for (float coord : this->coords)
    {
        distance += coord * coord;
    }
    return distance;
}

float CartesianPoint::distanceFromSquared(CartesianPoint &p) const
{
    // inline const std::__1::span<float> &Point<CartesianPoint>::getCoords() const
    // inline const std::__1::span<float> &Point<CartesianPoint>::getCoords() const
    checkDim(this->dimension, p);
    auto dist_vec_coords = (*this - p).getCoords();
    float distance = 0.0;
    for (float coord : dist_vec_coords)
    {
        distance += coord * coord;
    }
    return distance;
}

CartesianPoint CartesianPoint::add(const CartesianPoint &other) const
{
    checkDim(this->dimension, other);
    size_t dim = this->dimension;
    std::vector<float> new_coords(dim);
    auto &other_coords = other.getCoords();
    for (size_t i = 0; i < dim; i++)
    {
        new_coords[i] = this->coords[i] + other_coords[i];
    }
    return CartesianPoint(new_coords);
}

CartesianPoint CartesianPoint::floatMultiply(const float other) const
{
    size_t dim = this->dimension;
    std::vector<float> new_coords(dim);
    for (size_t i = 0; i < dim; i++)
    {
        new_coords[i] = this->coords[i] * other;
    }
    return CartesianPoint(new_coords);
}

CartesianPoint CartesianPoint::subtract(const CartesianPoint &other) const
{
    return this->add(other.floatMultiply(-1));
}
