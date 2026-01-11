#pragma once
#include <vector>
#include "models/Room.h"
namespace Services
{
    using RoomList = std::vector<Models::Room>;
    Models::Room *findRoom(RoomList &roomList, int roomNumber);
    bool isRoomAvailable(const Models::Room &room);
    void bookRoom(Models::Room &room);
    void cancelRoom(Models::Room &room);
    void freeRoom(Models::Room &room);
} // namespace Service
