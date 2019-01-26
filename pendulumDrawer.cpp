#include "pendulumDrawer.h"

PendulumDrawer::PendulumDrawer()
    : a1(M_PI), a2(M_PI), av1(0), av2(0), aa1(0), aa2(0), 
    l1(3), l2(2), m1(1), m2(3), g(9.81),
    button1(false), button3(false)
{
    lastTime = std::chrono::system_clock::now();

    add_events(Gdk::EventMask::BUTTON_PRESS_MASK | Gdk::EventMask::BUTTON_RELEASE_MASK | Gdk::EventMask::BUTTON1_MOTION_MASK | Gdk::EventMask::BUTTON3_MOTION_MASK);

    signal_button_press_event().connect(sigc::mem_fun(this, &PendulumDrawer::onButtonPress));
    signal_button_release_event().connect(sigc::mem_fun(this, &PendulumDrawer::onButtonRelease));
    signal_motion_notify_event().connect(sigc::mem_fun(this, &PendulumDrawer::onButtonMotion));

    Pango::FontDescription font;
    font.set_family("Monospace");
    font.set_weight(Pango::Weight::WEIGHT_NORMAL);
    font.set_size(6*PANGO_SCALE);
    scaleText = create_pango_layout("1 meter");
    scaleText->set_font_description(font);
    scaleText->get_pixel_size(text_width, text_height);
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
    
    // draw
    queue_draw();

    lastTime = std::chrono::system_clock::now();

    //BOOST_LOG_TRIVIAL(debug) << "Total Energy in the system: " << ((m1+m2)/2.0) * l1 * l1* av1 * av1 + (m2/2.0) * l2 * l2 * av2 * av2 + m2 * l1 * l2 * av1* av2 * cos(a1 -a2)
    //- (m1 + m2) * g * l1 * cos(a1) - m2 * g * l2 * cos(a2);

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

    // check if buttons are pressed
    if(button1)
    {
        av1 = 0;
        aa1 = 0;
        if(pointerY < yc)
            a1 = atan((pointerX - xc)/(pointerY - yc)) + M_PI;
        else 
            a1 = atan((pointerX - xc)/(pointerY - yc));
    }
    if(button3)
    {
        aa2 = 0;
        av2 = 0;
        if(pointerY < yc)
            a2 = atan((pointerX - xc)/(pointerY - yc)) + M_PI;
        else 
            a2 = atan((pointerX - xc)/(pointerY - yc));
    }

    double scale = 1; 
    if(width > height)
    {
        scale = yc / (l1 + l2);
    }
    else
    {
        scale = xc / (l1 + l2);
    }

    scale *= 0.95;

    // Calculate position in cartesian space
    posX1 = int(sin(a1) * l1 * scale);
    posY1 = int(cos(a1) * l1 * scale);
    posX2 = posX1 + int(sin(a2) * l2 * scale);
    posY2 = posY1 + int(cos(a2) * l2 * scale);

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

    // draw scale
    cr->set_line_width(1);
    cr->set_source_rgb(0.8, 0.8, 0.8);

    cr->move_to(10+(scale-text_width+10)/2.0, (height-16-text_height));
    scaleText->show_in_cairo_context(cr);

    cr->move_to(20, height - 10 - 5);
    cr->line_to(20, height - 10 + 5);
    cr->stroke();
    cr->move_to(20, height - 10);
    cr->line_to(10+scale, height - 10);
    cr->stroke(); 
    cr->move_to(10+scale, height - 10 - 5);
    cr->line_to(10+scale, height - 10 + 5);
    cr->stroke();

    return true;
}

bool PendulumDrawer::onButtonPress(GdkEventButton* event)
{
    if(event->type != GDK_BUTTON_PRESS)
        return false;
    BOOST_LOG_TRIVIAL(debug) << "Button " << event->button << "  was pressed";
    if(event->button != 1  && event->button != 3)
        return false;

    if(event->button == 1)
    {
        button1 = true;
        return true;
    }
    if(event->button == 3)
    {
        button3 = true;
        return true;
    }

    return false;
}

bool PendulumDrawer::onButtonRelease(GdkEventButton* event)
{
    if(event->type != GDK_BUTTON_RELEASE)
        return false;
    BOOST_LOG_TRIVIAL(debug) << "Button " << event->button << "  was released";
    if(event->button != 1  && event->button != 3)
        return false;

    if(event->button == 1)
    {
        button1 = false;
        return true;
    }
    if(event->button == 3)
    {
        button3 = false;
        return true;
    }

    return false;
}

bool PendulumDrawer::onButtonMotion(GdkEventMotion* event)
{
    if(event->type != GDK_MOTION_NOTIFY)
        return false;
    if(!button1 && !button3)
        return false;

    pointerX = event->x;
    pointerY = event->y;
    
    return true;
}