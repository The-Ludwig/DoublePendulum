#include "myWindow.h"

MyWindow::MyWindow(unsigned int sizeX, unsigned int sizeY)
    : pd(),
    hBoxMaster(Gtk::Orientation::ORIENTATION_HORIZONTAL, 10),
    vBoxSettings(Gtk::Orientation::ORIENTATION_VERTICAL, 10),
    mass1(Gtk::Adjustment::create(0.0, 0.0, 101.0, 0.1, 1.0, 1.0)),
    mass2(),
    length1(),
    length2()
{
    // window init
    set_title("Double Pendulum");
    set_default_size(sizeX, sizeY);

    add(hBoxMaster);
    hBoxMaster.set_homogeneous(false);
    hBoxMaster.pack_start(pd);
    hBoxMaster.pack_start(vBoxSettings, Gtk::PACK_EXPAND_PADDING);

    vBoxSettings.pack_end(mass1);
    vBoxSettings.pack_end(mass2);
    vBoxSettings.pack_end(length1);
    vBoxSettings.pack_end(length2);


    show_all_children();
}

MyWindow::~MyWindow()
{
    timeout.disconnect();
}

void MyWindow::start(unsigned int milliSecondsDT)
{
    // Recalculate 60 times a second
    timeout = Glib::signal_timeout().connect( sigc::mem_fun(pd,
              &PendulumDrawer::reCalculatePendulum), milliSecondsDT);
}