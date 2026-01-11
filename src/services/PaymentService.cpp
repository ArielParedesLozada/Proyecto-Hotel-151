#include "services/PaymentService.h"

namespace Services
{
    Models::Payment createPayment(
        int id,
        const Models::Reservation *reservation,
        double amount,
        const Models::Date &paymentDate)
    {
        Models::Payment payment{};
        payment.valid = false;

        if (!reservation)
            return payment;

        if (!reservation->valid)
            return payment;

        if (amount <= 0.0 || amount < reservation->room->precio)
            return payment;

        payment.id = id;
        payment.reservation = reservation;
        payment.amount = amount;
        payment.paymentDate = paymentDate;
        payment.valid = true;
        return payment;
    } // namespace Services
}