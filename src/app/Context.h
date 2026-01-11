#pragma once

#include "models/Client.h"
#include "models/Room.h"
#include "models/Reservation.h"
#include "models/Payment.h"
#include <vector>

namespace App
{
    struct Context
    {
        std::vector<Models::Client> clients;
        std::vector<Models::Room> rooms;
        std::vector<Models::Reservation> reservations;
        std::vector<Models::Payment> payments;
    };

    Context createDefaultContext();
}
