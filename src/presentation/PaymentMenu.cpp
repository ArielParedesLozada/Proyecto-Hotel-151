#include "presentation/PaymentMenu.h"
#include "services/PaymentService.h"
#include "services/ReservationService.h"
#include "services/DateService.h"

#include <iostream>

namespace Presentation
{
    static Models::Reservation *findReservationById(
        App::Context &ctx,
        int reservationId)
    {
        for (auto &r : ctx.reservations)
        {
            if (r.id == reservationId && r.valid)
                return &r;
        }
        return nullptr;
    }

    void showPaymentMenu(App::Context &ctx)
    {
        int option = 0;

        do
        {
            std::cout << "\n--- Menu de Pagos ---\n";
            std::cout << "1. Pagar reservacion\n";
            std::cout << "2. Cancelar reservacion\n";
            std::cout << "3. Volver\n";
            std::cout << "Opcion: ";
            std::cin >> option;

            switch (option)
            {
            case 1:
                payReservationFlow(ctx);
                break;
            case 2:
                cancelReservationFlow(ctx);
                break;
            }
        } while (option != 3);
    }

    void payReservationFlow(App::Context &ctx)
    {
        int reservationId;
        double amount;

        std::cout << "ID reservacion: ";
        std::cin >> reservationId;

        Models::Reservation *reservation = findReservationById(ctx, reservationId);

        if (!reservation)
        {
            std::cout << "Reservacion no encontrada\n";
            return;
        }

        std::cout << "Monto a pagar: ";
        std::cin >> amount;

        Models::Date paymentDate = createDateFromInput();

        Models::Payment payment =
            Services::createPayment(
                ctx.payments.size() + 1,
                reservation,
                amount,
                paymentDate);

        if (!payment.valid)
        {
            std::cout << "No se pudo procesar el pago\n";
            return;
        }

        ctx.payments.push_back(payment);
        std::cout << "Pago registrado correctamente\n";
    }

    void cancelReservationFlow(App::Context &ctx)
    {
        int reservationId;

        std::cout << "ID reservacion: ";
        std::cin >> reservationId;

        for (const auto &p : ctx.payments)
        {
            if (p.reservation && p.reservation->id == reservationId)
            {
                std::cout << "No se puede cancelar: tiene pagos asociados\n";
                return;
            }
        }

        if (Services::deleteReservation(ctx.reservations, reservationId))
            std::cout << "Reservacion cancelada\n";
        else
            std::cout << "No se pudo cancelar la reservacion\n";
    }
    void showPaymentsFlow(App::Context &ctx)
    {
        std::cout << "Mostrando pagos\n";
        for (const auto &p : ctx.payments)
        {
            std::cout << "Id: " << p.id << std::endl;
            std::cout << "Reservation: " << p.reservation->id << std::endl;
            std::cout << "Pago de la habitacion: " << p.amount << std::endl;
            std::cout << "Validez: " << p.valid << std::endl;
        }
    }

    Models::Date createDateFromInput()
    {
        int y, m, d;

        while (true)
        {
            std::cout << "Fecha\n";
            std::cout << "Anio: ";
            std::cin >> y;
            std::cout << "Mes: ";
            std::cin >> m;
            std::cout << "Dia: ";
            std::cin >> d;

            Models::Date date = Services::createDate(y, m, d);

            if (!Services::isValidDate(date))
            {
                std::cout << "Fecha invalida\n";
                continue;
            }

            if (!Services::isFutureDate(date))
            {
                std::cout << "La fecha debe ser posterior a hoy\n";
                continue;
            }

            return date;
        }
    }
}
