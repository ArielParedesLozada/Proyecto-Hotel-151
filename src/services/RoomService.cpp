#include "services/RoomService.h"

namespace Services
{
    Models::Room *findRoom(RoomList &roomList, int roomNumber)
    {
        for (auto &room : roomList)
        {
            if (room.id == roomNumber)
            {
                return &room;
            }
        }
        return nullptr;
    }
    bool isRoomAvailable(const Models::Room &room)
    {
        return room.status == Models::FREE;
    }
    void bookRoom(Models::Room &room)
    {
        room.status = Models::RESERVED;
    }
    void cancelRoom(Models::Room &room)
    {
        room.status = Models::OCCUPIED;
    }
    void freeRoom(Models::Room &room)
    {
        room.status = Models::FREE;
    }

} // namespace Services
