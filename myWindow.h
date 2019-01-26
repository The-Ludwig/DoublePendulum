#pragma once

#include "pendulumDrawer.h"
#include <chrono>
#include <cmath>
#include <gtkmm.h>
#include <gtkmm-3.0/gtkmm/window.h>


// Wrapper for everything which happens inside the window
class MyWindow : public Gtk::Window
{
private: 
    // drawing area for pendulums
    PendulumDrawer pd;
    // Slot wich povides a call every x seconds
    sigc::connection timeout;

    Gtk::Box hBoxMaster, vBoxSettings;
    Gtk::Scale mass1, mass2, length1, length2;

public:
    /**
     * @brief Construct a new My Window object
     * 
     * @param sizeX Width of the window
     * @param sizeY Height of the window
     */
    MyWindow(unsigned int sizeX, unsigned int sizeY);

    /**
     * @brief Destroy the My Window object
     * 
     */
    virtual ~MyWindow();

    /**
     * @brief starts the calculating
     * 
     * @param milliSecondsDT time between each calculating step (the smaller the better) 
     */
    void start(unsigned int milliSecondsDT);

};