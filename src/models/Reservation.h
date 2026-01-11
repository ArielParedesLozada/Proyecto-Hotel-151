#pragma once
#include <string>
#include "Client.h"
#include "Room.h"
#include "Date.h"
namespace Models
{
    struct Reservation
    {
        int id;
        Client* client;
        Room* room;
        DateInterval time;
        bool valid;
    };
    
} // namespace Models
