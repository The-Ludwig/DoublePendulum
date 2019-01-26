#pragma once
#include <gtkmm-3.0/gtkmm/drawingarea.h>
#include <boost/log/trivial.hpp>


class PendulumDrawer : public Gtk::DrawingArea
{
private:
    // relative position to the center of 1: first pendulum and 2: second pendulum
    int posX1, posY1, posX2, posY2;
    float mass1, mass2;

    // Physical values (M = mass constant, calculated later, aa1 = angular acceleration 1)
    double aa1, aa2;
    // for checking time differences
    std::chrono::system_clock::time_point lastTime;

    // Physical values which change (a1 = angle 1, ..., av1 = angular velocity 1, ...)
    double a1, a2, av1, av2; 
    // Physical constants (l1 = length 1, ..., m1 = mass1, ..., g = gravitationl acceleration)
    double l1, l2, m1, m2, g;

public:
    /**
     * @brief Construct a new Pendulum Drawer object
     * 
     */
    PendulumDrawer();
    
    /**
     * @brief Destroy the Pendulum Drawer object
     * 
     */
    virtual ~PendulumDrawer();

    /**
     * @brief Called upon each physical frame 
     * 
     * @return true success
     * @return false not implemented yet
     */
    bool reCalculatePendulum();

private:
    /**
     * @brief overwritten drawing method, which does the actual drawing
     * 
     * @param cr 
     * @return true 
     * @return false 
     */
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;

};