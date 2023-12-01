#ifndef CHUNKFILEIO_H
#define CHUNKFILEIO_H
#include <vector>
#include <stdexcept>
#include <string>
#include <cereal/types/vector.hpp>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include <iostream>
// #include <icecream/icecream.hpp>
// template <typename PointType>
// class ChunkFileIO
// {
// public:
//     std::string filepath;
//     std::ofstream os;
//     std::ifstream is;
//     ChunkFileIO(std::string file_path) : filepath(file_path)
//     {
//         os = std::ofstream(file_path, std::ios::binary);
//         if (!os.is_open())
//         {
//             throw std::runtime_error("Unable to open file for writing");
//         }
//     };
//     ~ChunkFileIO() = default;
// };
template <typename PointType>
class ChunkFileIO
{
public:
    static void saveToFile(const Chunk<PointType> &chunk, const std::string &filename)
    {
        try
        {
            std::ofstream os(filename, std::ios::binary);
            if (!os.is_open())
            {
                throw std::runtime_error("Unable to open file for writing: " + filename);
            }
            cereal::BinaryOutputArchive archive(os);
            archive(chunk);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error saving to file: " << e.what() << std::endl;
            throw; // Re-throwing to allow the caller to handle the exception
        }
    }

    static void loadFromFile(Chunk<PointType> &chunk, const std::string &filename)
    {
        try
        {
            std::ifstream is(filename, std::ios::binary);
            if (!is.is_open())
            {
                throw std::runtime_error("Unable to open file for reading: " + filename);
            }
            cereal::BinaryInputArchive archive(is);
            archive(chunk);
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error loading from file: " << e.what() << std::endl;
            throw; // Re-throwing to allow the caller to handle the exception
        }
    }
};

#endif