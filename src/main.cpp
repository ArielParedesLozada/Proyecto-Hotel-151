#include "app/Context.h"
#include "presentation/GeneralMenu.h"

int main()
{
    App::Context ctx = App::createDefaultContext();
    Presentation::showMainMenu(ctx);
    return 0;
}
