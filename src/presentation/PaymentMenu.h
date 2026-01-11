#pragma once

#include "app/Context.h"

namespace Presentation
{
    void showPaymentMenu(App::Context &ctx);
    void payReservationFlow(App::Context &ctx);
    void cancelReservationFlow(App::Context &ctx);
    void showPaymentsFlow(App::Context &ctx);
    Models::Date createDateFromInput();
}
