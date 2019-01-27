#pragma once
#include <gtkmm-3.0/gtkmm.h>
#include <boost/log/trivial.hpp>
#include <deque>

class PendulumDrawer : public Gtk::DrawingArea
{
protected:
    // relative position to the center of 1: first pendulum and 2: second pendulum
    int posX1, posY1, posX2, posY2;

    // Physical values (M = mass constant, calculated later, aa1 = angular acceleration 1)
    double aa1, aa2;
    // for checking time differences
    std::chrono::system_clock::time_point lastTime;

    // Physical values which change (a1 = angle 1, ..., av1 = angular velocity 1, ...)
    double a1, a2, av1, av2; 
    
    //buttons pressed?
    bool button1, button3;
    double pointerX, pointerY;

    //to draw a trace
    struct point
    {
        unsigned int x;
        unsigned int y;
        double av1, av2;
    };
    //modify from outside (again to lazy to write setters)
public:
    unsigned int trace_size;
protected:
    std::deque<point> trace;
    double maxAv1, maxAv2;

    // Physical constants (l1 = length 1, ..., m1 = mass1, ..., g = gravitationl acceleration), which can be saved from outside (too lazy to implement setters...)
public:
    double l1, l2, m1, m2, g;

protected:
    // Scale text
    Glib::RefPtr<Pango::Layout> scaleText;
    int text_width, text_height;

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

    /**
     * @brief clears the trace
     * 
     */
    void clearTrace();

    sigc::signal1<void, double> signalEnergy;

protected:
    /**
     * @brief overwritten drawing method, which does the actual drawing
     * 
     * @param cr 
     * @return true 
     * @return false 
     */
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;


    /**
     * @brief Get button press to set the pendulums
     * 
     * @param event 
     * @return true 
     * @return false 
     */
    bool onButtonPress(GdkEventButton* event);

    /**
     * @brief Get button release to set the pendulums
     * 
     * @param event 
     * @return true 
     * @return false 
     */
    bool onButtonRelease(GdkEventButton* event);

    /**
     * @brief Get button Motion to set the pendulums
     * 
     * @param event 
     * @return true 
     * @return false 
     */
    bool onButtonMotion(GdkEventMotion* event);


};