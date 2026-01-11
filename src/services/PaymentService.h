#pragma once
#include <vector>
#include "models/Payment.h"
#include "models/Reservation.h"
#include "models/Date.h"
namespace Services
{
    using PaymentList = std::vector<Models::Payment>;
    Models::Payment createPayment(int id, const Models::Reservation *reservation, double amount, const Models::Date &paymentDate);
    void addPayment(PaymentList &paymentList, const Models::Payment &payment);
} // namespace Services
