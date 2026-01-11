#include "presentation/GeneralMenu.h"

#include "presentation/ClientMenu.h"
#include "presentation/ReservationMenu.h"
#include "presentation/PaymentMenu.h"

#include <iostream>
namespace Presentation
{
    void showMainMenu(App::Context &ctx)
    {
        int option = 0;

        do
        {
            std::cout << "\n=========================\n";
            std::cout << "   SISTEMA DE HOTEL\n";
            std::cout << "=========================\n";
            std::cout << "1. Gestion de clientes\n";
            std::cout << "2. Gestion de reservaciones\n";
            std::cout << "3. Gestion de pagos\n";
            std::cout << "4. Salir\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> option;

            switch (option)
            {
            case 1:
                showClientMenu(ctx);
                break;

            case 2:
                showReservationMenu(ctx);
                break;

            case 3:
                showPaymentMenu(ctx);
                break;

            case 4:
                std::cout << "Saliendo del sistema...\n";
                break;

            default:
                std::cout << "Opcion invalida\n";
                break;
            }
        } while (option != 4);
    }
} // namespace Presentation
