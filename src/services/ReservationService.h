#pragma once
#include <vector>
#include "models/Date.h"
#include "models/Reservation.h"
namespace Services
{
    using ReservationList = std::vector<Models::Reservation>;
    Models::Reservation createReservation(const ReservationList &reservationList,int id, Models::Client *client, Models::Room *room, Models::Date startDate, Models::Date endDate);
    void addReservation(ReservationList &reservationList, const Models::Reservation &reservation);
    bool deleteReservation(ReservationList &reservationList, int reservationId);
} // namespace Service
