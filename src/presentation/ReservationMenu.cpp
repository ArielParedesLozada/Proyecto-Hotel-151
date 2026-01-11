#include "presentation/ReservationMenu.h"
#include "services/ReservationService.h"
#include "services/DateService.h"
#include "services/ClientService.h"
#include "services/RoomService.h"
#include <iostream>

namespace Presentation
{
    void showReservationMenu(App::Context &ctx)
    {
        int option;
        do
        {
            std::cout << "Menu de reservaciones\n";
            std::cout << "1. Reservar habitacion\n";
            std::cout << "2. Eliminar reservacion\n";
            std::cout << "3. Mostrar reservaciones\n";
            std::cout << "4. Salir\n";
            std::cout << "Seleccione una opcion\n";
            std::cin >> option;
            switch (option)
            {
            case 1:
                createReservationFlow(ctx);
                break;
            case 2:
                deleteReservationFlow(ctx);
                break;
            case 3:
                showReservationsFlow(ctx);
                break;
            default:
                std::cout << "Opcion invalida\n";
                break;
            }
        } while (option != 4);
    }
    void createReservationFlow(App::Context &ctx)
    {
        int roomId, clientId;
        std::cout << "ID cliente: ";
        std::cin >> clientId;
        std::cout << "ID cuarto: ";
        std::cin >> roomId;

        Models::Client *client = Services::getClientById(ctx.clients, clientId);
        Models::Room *room = Services::findRoom(ctx.rooms, roomId);

        if (!client || !room)
        {
            std::cout << "Cliente o cuarto no encontrado\n";
            return;
        }

        Models::Date start = createDateUserInput();
        Models::Date end = createDateUserInput();

        Models::Reservation r = Services::createReservation(
            ctx.reservations,
            ctx.reservations.size() + 1,
            client,
            room,
            start,
            end);

        if (!r.valid)
        {
            std::cout << "No se pudo crear la reservacion\n";
            return;
        }

        Services::addReservation(ctx.reservations, r);
        std::cout << "Reservacion creada\n";
    }
    void deleteReservationFlow(App::Context &ctx)
    {
        int reservationId;
        std::cout << "Ingrese el id de la reservacion";
        std::cin >> reservationId;
        Services::deleteReservation(ctx.reservations, reservationId);
        std::cout << "Reservacion eliminada\n";
    }
    void showReservationsFlow(App::Context &ctx)
    {
        std::cout << "Mostrando reservaciones\n";
        for (const auto &r : ctx.reservations)
        {
            std::cout << "Id: " << r.id << std::endl;
            std::cout << "Habitacion: " << r.room->id << std::endl;
            std::cout << "Persona: " << r.client->name << std::endl;
            std::cout << "Validez: " << r.valid << std::endl;
        }
    }
    Models::Date createDateUserInput()
    {
        int year, month, day;
        std::cout << "Ingrese el año\n";
        std::cin >> year;
        std::cout << "Ingrese el mes\n";
        std::cin >> month;
        std::cout << "Ingrese el dia\n";
        std::cin >> day;
        return Services::createDate(year, month, day);
    }

} // namespace Presentation
