#include "myWindow.h"

MyWindow::MyWindow(unsigned int sizeX, unsigned int sizeY)
    : pd(),
    hBoxMaster(false, 30),
    vBoxSettings(false, 10),
    hBoxMass1(false, 10),
    hBoxMass2(false, 10),
    hBoxLength1(false, 10),
    hBoxLength2(false, 10),
    hBoxG(false, 10),
    mass1(Gtk::Adjustment::create(1, 0.001, 1000, 0.5, 1, 42), 0, 1),
    mass2(Gtk::Adjustment::create(1, 0.001, 1000, 0.5, 1, 42), 0, 1),
    length1(Gtk::Adjustment::create(1, 0.01, 1000, 0.01, 0.1, 42), 0, 2),
    length2(Gtk::Adjustment::create(1, 0.01, 1000, 0.01, 0.1, 42), 0, 2),
    gValue(Gtk::Adjustment::create(9.81, 0.01, 100, 0.01, 0.1, 42), 0, 3),
    labelMass1("Mass 1 = "),
    labelMass2("Mass 2 = "),
    labelLength1("Length 1 = "),
    labelLength2("Length 2 = "),
    labelG("g = "),
    unitLength1("m"),
    unitLength2("m"),
    unitMass1("kg"),
    unitMass2("kg"),
    unitG("m/s²")
{
    // window init
    set_title("Double Pendulum");
    set_default_size(sizeX, sizeY);
    set_border_width(10);

    //signal connect convienetly set the proberties
    mass1.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onMass1Change));
    pd.m1 = mass1.get_value();
    mass2.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onMass2Change));
    pd.m2 = mass2.get_value();
    length1.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onLength1Change));
    pd.l1 = length1.get_value();
    length2.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onLength2Change));
    pd.l2 = length2.get_value();
    gValue.signal_value_changed().connect(sigc::mem_fun(this, &MyWindow::onGChange));
    pd.g = gValue.get_value();

    // pack everything
    add(hBoxMaster);
    pendulumFrame.add(pd);
    hBoxMaster.pack_start(pendulumFrame);
    hBoxMaster.pack_start(vBoxSettings, Gtk::PackOptions::PACK_SHRINK);

    hBoxMass1.add(labelMass1);
    hBoxMass1.add(mass1);
    hBoxMass1.add(unitMass1);
    
    hBoxMass2.add(labelMass2);
    hBoxMass2.add(mass2);
    hBoxMass2.add(unitMass2);
    
    hBoxLength1.add(labelLength1);
    hBoxLength1.add(length1);
    hBoxLength1.add(unitLength1);

    hBoxLength2.add(labelLength2);
    hBoxLength2.add(length2);
    hBoxLength2.add(unitLength2);

    hBoxG.add(labelG);
    hBoxG.add(gValue);
    hBoxG.add(unitG);
    
    vBoxSettings.pack_start(hBoxMass1, Gtk::PackOptions::PACK_EXPAND_PADDING);
    vBoxSettings.pack_start(hBoxMass2, Gtk::PackOptions::PACK_EXPAND_PADDING);
    vBoxSettings.pack_start(hBoxLength1, Gtk::PackOptions::PACK_EXPAND_PADDING);
    vBoxSettings.pack_start(hBoxLength2, Gtk::PackOptions::PACK_EXPAND_PADDING);
    vBoxSettings.pack_start(hBoxG, Gtk::PackOptions::PACK_EXPAND_PADDING);

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

void MyWindow::onMass1Change()
{
    BOOST_LOG_TRIVIAL(debug) << "Value of mass1 changed to " << mass1.get_value();
    pd.m1 = mass1.get_value();
}

void MyWindow::onMass2Change()
{
    BOOST_LOG_TRIVIAL(debug) << "Value of mass2 changed to " << mass2.get_value();
    pd.m2 = mass2.get_value();
}

void MyWindow::onLength1Change()
{
    BOOST_LOG_TRIVIAL(debug) << "Value of length1 changed to " << length1.get_value();
    pd.l1 = length1.get_value();
}

void MyWindow::onLength2Change()
{
    BOOST_LOG_TRIVIAL(debug) << "Value of length2 changed to " << length2.get_value();
    pd.l2 = length2.get_value();
}

void MyWindow::onGChange()
{
    BOOST_LOG_TRIVIAL(debug) << "Value of g changed to " << gValue.get_value();
    pd.g = gValue.get_value();
}