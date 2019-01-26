#include "pendulumDrawer.h"

PendulumDrawer::PendulumDrawer()
    : a1(3), a2(0), av1(0), av2(0), aa1(0), aa2(0), 
    l1(3), l2(2), m1(1), m2(3), g(9.81)
{
    lastTime = std::chrono::system_clock::now();
}

PendulumDrawer::~PendulumDrawer()
{

}

bool PendulumDrawer::reCalculatePendulum()
{
    double dT = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastTime).count()/1000.0;

    // approximate penduluum every micorsecond
    double physicalTime = 0.000001;

    while(dT > physicalTime)
    {
        double denom = 2 * m1 + m2 - m2 * cos(2 * a1 - 2* a2);
        // double my_aa1 = (-M * av1 * av1 * sin(a1 - a2) * cos(a1-a2) + (g/l1) * M * sin(a1) * cos(a1-a2) - M * (l2/l1) * av2 * av2 * sin(a1-a2) - (g/l1) * sin(a1))
                // / (1.0 - M * cos(a1-a2) * cos(a1-a2));

        aa1 = (-g*(2*m1+m2)*sin(a1) - m2 * g * sin(a1 - 2 * a2) - 2 *sin(a1-a2) * m2 * (av2 * av2 * l2 + av1 * av1 * l1 * cos(a1 - a2)))
                / (l1 * denom);

        aa2 = (2 * sin(a1-a2) * (av1 * av1 * l1 * (m1+m2)+ g*(m1+m2)*cos(a1) + av2 * av2 * l2 * m2* cos(a1-a2)))
                /(l2 * denom);

        av1 += aa1 * physicalTime;
        av2 += aa2 * physicalTime;

        a1 += av1 * physicalTime;
        a2 += av2 * physicalTime;

        dT -= physicalTime;
    }

    // catch up to real time pased
    if(dT != 0)
    {
        double denom = 2 * m1 + m2 - m2 * cos(2 * a1 - 2* a2);
        aa1 = (-g*(2*m1+m2)*sin(a1) - m2 * g * sin(a1 - 2 * a2) - 2 *sin(a1-a2) * m2 * (av2 * av2 * l2 + av1 * av1 * l1 * cos(a1 - a2)))
                / (l1 * denom);

        aa2 = (2 * sin(a1-a2) * (av1 * av1 * l1 * (m1+m2)+ g*(m1+m2)*cos(a1) + av2 * av2 * l2 * m2* cos(a1-a2)))
                /(l2 * denom);

        av1 += aa1 * physicalTime;
        av2 += aa2 * physicalTime;

        a1 += av1 * physicalTime;
        a2 += av2 * physicalTime;
    }

    // Calculate position in cartesian space
    posX1 = int(sin(a1) * l1 * 100);
    posY1 = int(cos(a1) * l1 * 100);
    posX2 = posX1 + int(sin(a2) * l2 * 100);
    posY2 = posY1 + int(cos(a2) * l2 * 100);
    
    // draw
    queue_draw();

    lastTime = std::chrono::system_clock::now();

    BOOST_LOG_TRIVIAL(debug) << "Total Energy in the system: " << ((m1+m2)/2.0) * l1 * l1* av1 * av1 + (m2/2.0) * l2 * l2 * av2 * av2 + m2 * l1 * l2 * av1* av2 * cos(a1 -a2)
    - (m1 + m2) * g * l1 * cos(a1) - m2 * g * l2 * cos(a2);

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
    cr->arc(xc+posX2, yc+posY2, 5 * std::sqrt(m2), 0.0, 2.0 * M_PI); // full circle
    cr->set_source_rgb(0.0, 0.0, 0.8);
    cr->fill_preserve();
    cr->stroke();

    // draw first line
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->move_to(xc, yc);
    cr->line_to(xc+posX1, yc+posY1);
    cr->stroke();

    // draw first mass
    cr->arc(xc+posX1, yc+posY1, 5 * std::sqrt(m1), 0.0, 2.0 * M_PI); // full circle
    cr->set_source_rgb(0.8, 0.0, 0.0);
    cr->fill_preserve();
    cr->stroke();

    return true;
}