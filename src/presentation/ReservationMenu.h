#pragma once
#include "app/Context.h"
#include "models/Date.h"
namespace Presentation
{
    void showReservationMenu(App::Context &ctx);
    void createReservationFlow(App::Context &ctx);
    void deleteReservationFlow(App::Context &ctx);
    void showReservationsFlow(App::Context &ctx);
    Models::Date createDateUserInput();
} // namespace Presentation
