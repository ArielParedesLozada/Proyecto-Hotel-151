#include "presentation/ClientMenu.h"
#include "services/ClientService.h"
#include <iostream>
#include <string>

namespace Presentation
{
    void showClientMenu(App::Context &ctx)
    {
        int option;
        do
        {
            std::cout << "Menu de clientes\n";
            std::cout << "1. Crear cliente\n";
            std::cout << "2. Mostrar clientes\n";
            std::cout << "3. Salir\n";
            std::cout << "Ingrese su opcion\n";
            std::cin >> option;
            switch (option)
            {
            case 1:
                createClientFLow(ctx);
                break;
            case 2:
                showClientsFlow(ctx);
                break;
            default:
                break;
            }
        } while (option != 3);
    }
    void createClientFLow(App::Context &ctx)
    {
        std::string name, cedula;
        int id;
        std::cout << "Ingrese un nombre\n";
        std::cin >> name;
        std::cout << "Ingrese una cedula\n";
        std::cin >> cedula;
        id = ctx.clients.size() + 1;
        Models::Client client = {id, name, cedula};
        Services::addClient(ctx.clients, client);
        std::cout << "Cliente creado\n";
    }
    void showClientsFlow(App::Context &ctx)
    {
        std::cout << "Mostrando clientes registrados" << std::endl;
        for (const auto &c : ctx.clients)
        {
            std::cout << "Id: " << c.id << std::endl;
            std::cout << "Nombre: " << c.name << std::endl;
            std::cout << "Cedula: " << c.cedula << std::endl;
        }
    }
} // namespace Presentation
