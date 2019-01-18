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
    // Physical values (M = mass constant, calculated later, aa1 = angular acceleration 1)
    double M, aa1, aa2;
    // drawing area for pendulums
    PendulumDrawer pd;
    // Slot wich povides a call every x seconds
    sigc::connection timeout;
    // for checking time differences
    std::chrono::system_clock::time_point lastTime;

public:
    // Physical values which change (a1 = angle 1, ..., av1 = angular velocity 1, ...)
    double a1, a2, av1, av2; 
    // Physical constants (l1 = length 1, ..., m1 = mass1, ..., g = gravitationl acceleration)
    double l1, l2, m1, m2, g;

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
    //start();

private:
    /**
     * @brief Called upon each physical frame 
     * 
     * @return true success
     * @return false not implemented yet
     */
    bool reCalculatePendulum();

};