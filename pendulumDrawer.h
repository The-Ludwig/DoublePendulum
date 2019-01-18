#pragma once
#include <gtkmm-3.0/gtkmm/drawingarea.h>


class PendulumDrawer : public Gtk::DrawingArea
{
private:
    // relative position to the center of 1: first pendulum and 2: second pendulum
    int posX1, posY1, posX2, posY2;

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
     * @brief Draws pendulum in the middle with the given parameters
     * 
     * @param teta1 angle 1
     * @param teta2 angle 2
     * @param length1 length 1
     * @param length2 length 2
     * @return true success
     * @return false not implemented
     */
    bool drawPendulum(float teta1, float teta2, float length1, float length2);

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