#pragma once
#include <vector>
#include "models/Client.h"
namespace Services
{
    using ClientList = std::vector<Models::Client>;
    void addClient(ClientList &clients, const Models::Client &client);
    Models::Client *getClientById(ClientList &clients, int id);
    bool updateClient(ClientList &clients, const Models::Client &updatedClient);
    bool deleteClient(ClientList &clients, int id);
} // namespace Services
