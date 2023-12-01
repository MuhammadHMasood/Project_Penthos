#include <raylib/raylib.h>
#include <raylib/raymath.h>
#include <iostream>
#include "cartesianpoint.hpp"
#include "chunk.hpp"
#include "chunkfileio.hpp"
#include <icecream/icecream.hpp>

int main(void)
{
    std::vector<float> coords{10, 5, 10};
    CartesianPoint p1 = CartesianPoint(coords);

    CartesianPoint p2 = CartesianPoint(std::vector<float>{5, 10, 5});

    Chunk<CartesianPoint> myChunk(p1, p2);

    std::vector<CartesianPoint> test_points{};

    for (int i = 7; i < 10; i++)
    {
        for (int j = 7; j < 10; j++)
        {
            for (int k = 7; k < 10; k++)
            {
                auto p = CartesianPoint(std::vector<float>{static_cast<float>(i) + 0.1f, static_cast<float>(j), static_cast<float>(k)});
                test_points.push_back(p);
                myChunk.insertPoint(p);
            }
        }
    }

    // ChunkFileIO<CartesianPoint>::saveToFile(myChunk, "chunk.dat");

    Chunk<CartesianPoint> loadedChunk;
    ChunkFileIO<CartesianPoint>::loadFromFile(loadedChunk, "chunk.dat");

    // CartesianPoint p3 = CartesianPoint(std::vector<float>{8, 8, 8});

    // auto t = myChunk.closestPoints(p3, 3);

    // auto result = myChunk.pointsInChunk(test_points);

    // for (auto p : t)
    // {
    //     IC((p.get()).getCoords(), p3.distanceFromSquared(p));
    // }

    // std::cout << "vs all points" << std::endl;

    // for (auto p : loadedChunk.points)
    // {
    //     IC(p.getCoords());
    // }

    // for (auto q : result)
    // {
    //     IC(q.getCoords());
    // }

    return 0;
}