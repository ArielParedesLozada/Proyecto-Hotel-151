#include "services/ReservationService.h"
#include "services/DateService.h"
#include "services/RoomService.h"

namespace Services
{
    bool roomHasConflict(const ReservationList &reservationList, const Models::Room *room, const Models::DateInterval &newInterval)
    {
        for (const auto &r : reservationList)
        {
            if (r.room == room)
            {
                if (overlap(r.time, newInterval))
                {
                    return true;
                }
            }
        }
        return false;
    }
    Models::Reservation createReservation(const ReservationList &reservationList, int id, Models::Client *client, Models::Room *room, Models::Date startDate, Models::Date endDate)
    {
        Models::DateInterval interval = createDateInterval(startDate, endDate);
        Models::Reservation reservation{};
        reservation.valid = false;
        if (!room || !client || roomHasConflict(reservationList, room, interval))
        {
            return reservation;
        }
        reservation.id = id;
        reservation.client = client;
        reservation.room = room;
        reservation.time = interval;
        reservation.valid = true;
        bookRoom(*room);
        return reservation;
    }
    void addReservation(ReservationList &reservationList, const Models::Reservation &reservation)
    {
        if (reservation.valid)
        {
            reservationList.push_back(reservation);
        }
    }
    bool deleteReservation(ReservationList &reservationList, int reservationId)
    {
        for (auto it = reservationList.begin(); it != reservationList.end(); ++it)
        {
            if (it->id == reservationId && it->room)
            {
                freeRoom(*it->room);
                reservationList.erase(it);
                return true;
            }
        }
        return false;
    }
} // namespace Services
