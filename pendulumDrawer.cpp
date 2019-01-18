#include "pendulumDrawer.h"

PendulumDrawer::PendulumDrawer()
{

}

PendulumDrawer::~PendulumDrawer()
{

}

bool PendulumDrawer::drawPendulum(float teta1, float teta2, float length1, float length2)
{
    // Calculate position in cartesian space
    posX1 = int(sin(teta1) * length1);
    posY1 = int(cos(teta1) * length1);
    posX2 = posX1 + int(sin(teta2) * length2);
    posY2 = posY1 + int(cos(teta2) * length2);
    
    // draw
    queue_draw();

    return true;
}

bool PendulumDrawer::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{  
    // coordinates for the center of the window
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    int xc, yc;
    xc = width / 2;
    yc = height / 2;

    cr->set_line_width(5.0);


    // draw second line
    cr->set_source_rgb(0.0, 0.0, 0.8);
    cr->move_to(xc+posX1, yc+posY1);
    cr->line_to(xc+posX2, yc+posY2);
    cr->stroke();
    
    // draw second mass
    cr->arc(xc+posX2, yc+posY2, 5, 0.0, 2.0 * M_PI); // full circle
    cr->set_source_rgb(0.0, 0.0, 0.8);
    cr->fill_preserve();
    cr->stroke();

    // draw first line
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->move_to(xc, yc);
    cr->line_to(xc+posX1, yc+posY1);
    cr->stroke();

    // draw first mass
    cr->arc(xc+posX1, yc+posY1, 5, 0.0, 2.0 * M_PI); // full circle
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->fill_preserve();
    cr->stroke();

    return true;
}