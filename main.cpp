#include <gtkmm.h>
#include "myWindow.h"

int main(int argc, char *argv[])
{
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

   MyWindow win(400, 400);

   return app->run(win);
}