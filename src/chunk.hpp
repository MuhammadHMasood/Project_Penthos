#ifndef CHUNK_H
#define CHUNK_H

#include "point.hpp"
#include <optional>
#include <queue>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
// #include <icecream/icecream.hpp>
template <typename PointType>
class Chunk
{
public:
    Chunk() {}
    // Constructor
    Chunk(PointType &origin, PointType &proportions) : min_point(minmax_points(origin, proportions)[0]), max_point(minmax_points(origin, proportions)[1]) { dimension = min_point.getDimension(); };

    // Destructor
    ~Chunk() = default;

    // Origin of chunk, define as the corner from which the rest of the chunk extends away from in positive direction
    PointType min_point;

    // The maximum values of the chunk
    PointType max_point;

    // the points in the chunk
    std::vector<PointType> points;

    template <class Archive>
    void serialize(Archive &archive)
    {
        archive(max_point, min_point, points);
    }

    // True if p is in the chunk
    bool inChunk(const PointType &p) const
    {
        auto &c = p.getCoords();
        auto &min = (min_point).getCoords();
        auto &max = (max_point).getCoords();
        for (size_t i = 0; i < this->min_point.getDimension(); i++)
        {
            if (c[i] < min[i] || c[i] > max[i])
            {
                return false;
            }
        }
        return true;
    };

    size_t getDimension() const
    {
        return dimension;
    }

    // given an array of points, returns the ones in the chunk
    std::vector<PointType> pointsInChunk(const std::vector<PointType> &p) const
    {
        std::vector<PointType> in{};
        for (auto &point : p)
        {
            if (this->inChunk(point))
            {
                in.push_back(point);
            }
        }
        return in;
    }

    // given a point p, returns the closest point rho that is located in this chunk
    // PointType &closestPoint(PointType &p) const;

    // returns a vector of the n nearest points, in an order from closest (first) to furthest (last)
    // if the chunk contains less than n points, then the length of the vector will decrease
    std::vector<std::reference_wrapper<PointType>> closestPoints(const PointType &p1, size_t n)
    {
        std::vector<std::reference_wrapper<PointType>> cpoints{};
        using MinHeap = std::priority_queue<std::reference_wrapper<PointType>, std::vector<std::reference_wrapper<PointType>>, pointComparator<PointType>>;
        pointComparator<PointType> comp(p1);
        MinHeap min_heap(comp);
        for (PointType &p : this->points)
        {
            min_heap.push(std::ref(p));
        }

        for (int i = 0; i < n && !min_heap.empty(); i++)
        {
            cpoints.push_back(min_heap.top());
            min_heap.pop();
        }
        return cpoints;
    };

    // returns true if the point was in the chunk and thus inserted, returns false if it was outside the bounds and couldn't be placed
    bool insertPoint(PointType &p)
    {
        Point<PointType>::checkDim(this->dimension, p);
        if (inChunk(p))
        {
            this->points.push_back(p);
            return true;
        }
        return false;
    };

    // returns an array containing the max and min point
    std::array<PointType, 2> minmax_points(const PointType &p1, const PointType &p2)
    {
        size_t num = p1.getDimension();
        const auto &p1_coords = p1.getCoords();
        const auto &p2_coords = p2.getCoords();
        std::vector<float> min_coords(num);
        std::vector<float> max_coords(num);
        // which dimension you pick doesn't matter because they should all be the same
        for (size_t i = 0; i < num; i++)
        {
            // the points shouldn't be equal usually, but in that case it doesn't matter which is assigned to which
            if (p1_coords[i] < p2_coords[i])
            {
                min_coords[i] = p1_coords[i];
                max_coords[i] = p2_coords[i];
            }
            else
            {
                max_coords[i] = p1_coords[i];
                min_coords[i] = p2_coords[i];
            }
        }
        return std::array<PointType, 2>{PointType(min_coords), PointType(max_coords)};
    };

protected:
    size_t dimension;

private:
};

#endif
