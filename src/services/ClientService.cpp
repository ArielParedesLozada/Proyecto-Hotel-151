#include "services/ClientService.h"

namespace Services
{
    void addClient(ClientList &clients, const Models::Client &client)
    {
        clients.push_back(client);
    }

    Models::Client *getClientById(ClientList &clients, int id)
    {
        for (auto &client : clients)
        {
            if (client.id == id)
                return &client;
        }
        return nullptr;
    }

    bool updateClient(ClientList &clients, const Models::Client &updatedClient)
    {
        for (auto &client : clients)
        {
            if (client.id == updatedClient.id)
            {
                client = updatedClient;
                return true;
            }
        }
        return false;
    }

    bool deleteClient(ClientList &clients, int id)
    {
        for (auto it = clients.begin(); it != clients.end(); ++it)
        {
            if (it->id == id)
            {
                clients.erase(it);
                return true;
            }
        }
        return false;
    }
} // namespace Services
