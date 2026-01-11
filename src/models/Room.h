#pragma once
#include <string>
namespace Models
{
    enum RoomState
    {
        FREE = 0,
        RESERVED = 1,
        OCCUPIED = 2,
    };
    enum RoomType
    {
        NORMAL = 0,
        SUITE = 1,
        DOUBLE = 2,
    };
    struct Room
    {
        int id;
        RoomState status;
        RoomType type;
        double precio;
        int capacidad;
    };
} // namespace Models
