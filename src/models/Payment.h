#pragma once
#include "Reservation.h"
#include "Date.h"
namespace Models
{
    struct Payment
    {
        int id;
        const Reservation *reservation;
        double amount;
        Date paymentDate;
        bool valid;
    };

} // namespace Models
