#include <gtkmm.h>
#include "myWindow.h"

int main(int argc, char *argv[])
{
  // Gtkmm stuff
  auto app =
    Gtk::Application::create(argc, argv,
      "org.gtkmm.examples.base");

  // construct new window
  MyWindow win(400, 400);

  // start main loop
  return app->run(win);
}