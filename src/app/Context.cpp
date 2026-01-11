#include "app/Context.h"

namespace App
{
    Context createDefaultContext()
    {
        Context ctx;
        ctx.clients.push_back({1, "Juan", "0102030405"});
        ctx.clients.push_back({2, "Maria", "0504030201"});
        ctx.rooms.push_back({101, Models::FREE, Models::NORMAL, 100, 1});
        ctx.rooms.push_back({101, Models::FREE, Models::SUITE, 200, 2});
        ctx.rooms.push_back({101, Models::FREE, Models::DOUBLE, 300, 4});

        return ctx;
    }
} // namespace Presentation
