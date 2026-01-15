#include <vector>
#include <string>
#include <ctime>
#include <iostream>

/** Models */
struct Date
{
    int year;
    int month;
    int day;
};
struct DateInterval
{
    Date start;
    Date end;
};
enum RoomState
{
    FREE = 0,
    RESERVED = 1,
    OCCUPIED = 2,
};
struct Room
{
    int id;
    RoomState status;
    std::vector<std::string> characteristics;
    double precio;
    int capacidad;
};
struct Client
{
    int id;
    std::string name;
    std::string cedula;
};
struct Reservation
{
    int id;
    Client *client;
    Room *room;
    DateInterval time;
    bool valid;
};
struct Payment
{
    int id;
    const Reservation *reservation;
    double amount;
    Date paymentDate;
    bool valid;
};
struct Context
{
    std::vector<Client> clients;
    std::vector<Room> rooms;
    std::vector<Reservation> reservations;
    std::vector<Payment> payments;
};

/** Services */
/** Declarations */
using ClientList = std::vector<Client>;
using RoomList = std::vector<Room>;
using ReservationList = std::vector<Reservation>;
using PaymentList = std::vector<Payment>;
/* Dates */
bool dateGreaterThan(const Date &date1, const Date &date2);
Date createDate(int year, int month, int day);
DateInterval createDateInterval(const Date &date1, const Date &date2);
bool overlap(const DateInterval &interval1, const DateInterval &interval2);
bool isValidDate(const Date &d);
Date today();
bool isFutureDate(const Date &d);
Date createDateFromInput();

/* Clients */
void createClientFLow(Context &ctx);
void showClientsFlow(Context &ctx);

/* Reservations */
void createReservationFlow(Context &ctx);
void deleteReservationFlow(Context &ctx);
void showReservationsFlow(Context &ctx);

/* Payments */
void payReservationFlow(Context &ctx);
void cancelReservationFlow(Context &ctx);
/** Implementation */
/** Clients */
void addClient(ClientList &clients, const Client &client)
{
    clients.push_back(client);
}
Client *getClientById(ClientList &clients, int id)
{
    for (auto &client : clients)
    {
        if (client.id == id)
            return &client;
    }
    return nullptr;
}
bool updateClient(ClientList &clients, const Client &updatedClient)
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
/** Dates */
Date createDate(int year, int month, int date)
{
    return Date{year, month, date};
}
DateInterval createDateInterval(const Date &date1, const Date &date2)
{
    if (dateGreaterThan(date1, date2))
    {
        return DateInterval{date2, date1};
    }

    return DateInterval{date1, date2};
}
bool dateGreaterThan(const Date &date1, const Date &date2)
{
    if (date1.year != date2.year)
        return date1.year > date2.year;

    if (date1.month != date2.month)
        return date1.month > date2.month;

    return date1.day > date2.day;
}
bool overlap(const DateInterval &interval1, const DateInterval &interval2)
{
    return !dateGreaterThan(interval2.start, interval1.end) && !dateGreaterThan(interval1.start, interval2.end);
}
bool isValidDate(const Date &d)
{
    if (d.month < 1 || d.month > 12)
        return false;

    if (d.day < 1 || d.day > 31)
        return false;

    if (d.year < 1900)
        return false;

    return true;
}
Date today()
{
    std::time_t t = std::time(nullptr);
    std::tm *now = std::localtime(&t);

    return createDate(
        now->tm_year + 1900,
        now->tm_mon + 1,
        now->tm_mday);
}
bool isFutureDate(const Date &d)
{
    Date t = today();
    return dateGreaterThan(d, t);
}
/** Rooms */
Room *findRoom(RoomList &roomList, int roomNumber)
{
    for (auto &room : roomList)
    {
        if (room.id == roomNumber)
        {
            return &room;
        }
    }
    return nullptr;
}
void bookRoom(Room &room)
{
    room.status = RESERVED;
}
void freeRoom(Room &room)
{
    room.status = FREE;
}
/** Reservation */
bool roomHasConflict(const ReservationList &reservationList, const Room *room, const DateInterval &newInterval)
{
    for (const auto &r : reservationList)
    {
        if (r.room == room)
        {
            if (overlap(r.time, newInterval))
            {
                return true;
            }
        }
    }
    return false;
}
Reservation createReservation(const ReservationList &reservationList, int id, Client *client, Room *room, Date startDate, Date endDate)
{
    DateInterval interval = createDateInterval(startDate, endDate);
    Reservation reservation{};
    reservation.valid = false;
    if (!room || !client || roomHasConflict(reservationList, room, interval))
    {
        return reservation;
    }
    reservation.id = id;
    reservation.client = client;
    reservation.room = room;
    reservation.time = interval;
    reservation.valid = true;
    bookRoom(*room);
    return reservation;
}
void addReservation(ReservationList &reservationList, const Reservation &reservation)
{
    if (reservation.valid)
    {
        reservationList.push_back(reservation);
    }
}
bool deleteReservation(ReservationList &reservationList, int reservationId)
{
    for (auto it = reservationList.begin(); it != reservationList.end(); ++it)
    {
        if (it->id == reservationId && it->room)
        {
            freeRoom(*it->room);
            reservationList.erase(it);
            return true;
        }
    }
    return false;
}
/** Payments */
Payment createPayment(
    int id,
    const Reservation *reservation,
    double amount,
    const Date &paymentDate)
{
    Payment payment{};
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
/** Context */
Context createDefaultContext()
{
    Context ctx;
    ctx.clients.push_back({1, "Juan", "0102030405"});
    ctx.clients.push_back({2, "Maria", "0504030201"});
    ctx.rooms.push_back({1, FREE, {"Normal"}, 100, 1});
    ctx.rooms.push_back({2, FREE, {"Wifi", "Cama grande", "Grande"}, 200, 2});
    ctx.rooms.push_back({3, FREE, {"Wifi", "Cama doble", "Grande", "Ducha caliente"}, 300, 4});

    return ctx;
}
/** Presentation */
/** ClientMenu */
void showClientMenu(Context &ctx)
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
void createClientFLow(Context &ctx)
{
    std::string name, cedula;
    int id;
    std::cout << "Ingrese un nombre\n";
    std::cin >> name;
    std::cout << "Ingrese una cedula\n";
    std::cin >> cedula;
    id = ctx.clients.size() + 1;
    Client client = {id, name, cedula};
    addClient(ctx.clients, client);
    std::cout << "Cliente creado\n";
}
void showClientsFlow(Context &ctx)
{
    std::cout << "Mostrando clientes registrados" << std::endl;
    for (const auto &c : ctx.clients)
    {
        std::cout << "Id: " << c.id << std::endl;
        std::cout << "Nombre: " << c.name << std::endl;
        std::cout << "Cedula: " << c.cedula << std::endl;
    }
}
/** Reservation */
void showReservationMenu(Context &ctx)
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
void createReservationFlow(Context &ctx)
{
    int roomId, clientId;
    std::cout << "ID cliente: ";
    std::cin >> clientId;
    std::cout << "ID cuarto: ";
    std::cin >> roomId;

    Client *client = getClientById(ctx.clients, clientId);
    Room *room = findRoom(ctx.rooms, roomId);

    if (!client || !room)
    {
        std::cout << "Cliente o cuarto no encontrado\n";
        return;
    }

    Date start = createDateFromInput();
    Date end = createDateFromInput();

    Reservation r = createReservation(
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

    addReservation(ctx.reservations, r);
    std::cout << "Reservacion creada\n";
}
void deleteReservationFlow(Context &ctx)
{
    int reservationId;
    std::cout << "Ingrese el id de la reservacion";
    std::cin >> reservationId;
    deleteReservation(ctx.reservations, reservationId);
    std::cout << "Reservacion eliminada\n";
}
void showReservationsFlow(Context &ctx)
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
/** PaymentMenu */
Reservation *findReservationById(
    Context &ctx,
    int reservationId)
{
    for (auto &r : ctx.reservations)
    {
        if (r.id == reservationId && r.valid)
            return &r;
    }
    return nullptr;
}
void showPaymentMenu(Context &ctx)
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

void payReservationFlow(Context &ctx)
{
    int reservationId;
    double amount;

    std::cout << "ID reservacion: ";
    std::cin >> reservationId;

    Reservation *reservation = findReservationById(ctx, reservationId);

    if (!reservation)
    {
        std::cout << "Reservacion no encontrada\n";
        return;
    }

    std::cout << "Monto a pagar: ";
    std::cin >> amount;

    Date paymentDate = createDateFromInput();
    Payment payment =
        createPayment(
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

void cancelReservationFlow(Context &ctx)
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

    if (deleteReservation(ctx.reservations, reservationId))
        std::cout << "Reservacion cancelada\n";
    else
        std::cout << "No se pudo cancelar la reservacion\n";
}
void showPaymentsFlow(Context &ctx)
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
/** Dates */
Date createDateFromInput()
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
        Date date = createDate(y, m, d);
        if (!isValidDate(date))
        {
            std::cout << "Fecha invalida\n";
            continue;
        }
        if (!isFutureDate(date))
        {
            std::cout << "La fecha debe ser posterior a hoy\n";
            continue;
        }
        return date;
    }
}

/** MainMenu */
void showMainMenu(Context &ctx)
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

int main()
{

    Context ctx = createDefaultContext();
    showMainMenu(ctx);
    return 0;
}