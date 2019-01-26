#pragma once

#include "pendulumDrawer.h"
#include <chrono>
#include <cmath>
#include <gtkmm.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <boost/log/trivial.hpp>

// Wrapper for everything which happens inside the window
class MyWindow : public Gtk::Window
{
protected: 
    // drawing area for pendulums
    PendulumDrawer pd;
    Gtk::Frame pendulumFrame;
    // Slot wich povides a call every x seconds
    sigc::connection timeout;

    Gtk::HBox hBoxMaster, hBoxMass1, hBoxMass2, hBoxLength1, hBoxLength2, hBoxG;
    Gtk::VBox vBoxSettings;
    Gtk::SpinButton mass1, mass2, length1, length2, gValue;
    Gtk::Label labelMass1, labelMass2, labelLength1, labelLength2, labelG;
    Gtk::Label unitMass1, unitLength1, unitMass2, unitLength2, unitG;

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

protected:
    void onMass1Change();
    void onMass2Change();
    void onLength1Change();
    void onLength2Change();
    void onGChange();
};