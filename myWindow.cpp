#include "myWindow.h"
#include <boost/log/trivial.hpp>

MyWindow::MyWindow(unsigned int sizeX, unsigned int sizeY)
    : pd(), a1(3), a2(0), av1(0), av2(0), aa1(0), aa2(0), l1(1), l2(1), m1(1), m2(1), g(9.81)
{
    M = m2/(m1+m2); 

    // window init
    set_title("Double Pendulum");
    set_default_size(sizeX, sizeY);
    add(pd);
    pd.show();

    lastTime = std::chrono::system_clock::now();
}

MyWindow::~MyWindow()
{
    timeout.disconnect();
}

bool MyWindow::reCalculatePendulum()
{
    double dT = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastTime).count()/1000.0;

    // approximate penduluum every micorsecond
    double physicalTime = 0.000001;

    while(dT > physicalTime)
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

    pd.drawPendulum(a1, a2, l1 * 100, l2 * 100);
    lastTime = std::chrono::system_clock::now();

    BOOST_LOG_TRIVIAL(debug) << "Total Energy in the system: " << ((m1+m2)/2.0) * l1 * l1* av1 * av1 + (m2/2.0) * l2 * l2 * av2 * av2 + m2 * l1 * l2 * av1* av2 * cos(a1 -a2)
    - (m1 + m2) * g * l1 * cos(a1) - m2 * g * l2 * cos(a2);

    return true;
}

void MyWindow::start(unsigned int milliSecondsDT)
{
    // Recalculate 60 times a second
    timeout = Glib::signal_timeout().connect( sigc::mem_fun(*this,
              &MyWindow::reCalculatePendulum), milliSecondsDT);
}