#include "myWindow.h"
#include <boost/log/trivial.hpp>

MyWindow::MyWindow(unsigned int sizeX, unsigned int sizeY)
    : pd(), a1(1.5), a2(0), av1(0), av2(0), aa1(0), aa2(0), l1(1), l2(1), M(0.5), g(10)
{
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
    aa1 = (-M * av1 * av1 * sin(a1 - a2) * cos(a1-a2) + g/l1 * M * sin(a1) * cos(a1-a2) - M * l2/l1 * av2 * av2 * sin(a1-a2) - g/l1 * sin(a1))
            / (1 - M * cos(a1-a2) * cos(a1-a2));

    aa2 = (M * av2 * av2 * sin(a1-a2) * cos(a1-a2) + g/l2 * sin(a1) * cos(a1-a2) + l1/l2 * av1 * av1 * sin(a1-a2) - g/l2 *sin(a2))
            /(1-M*cos(a1-a2)*cos(a1-a2));

    av1 += aa1 * dT;
    av2 += aa2 * dT;

    a1 += av1 * dT;
    a2 += av2 * dT;

    pd.drawPendulum(a1, a2, l1 * 100, l2 * 100);
    lastTime = std::chrono::system_clock::now();

    BOOST_LOG_TRIVIAL(debug) << "Teta1'' = " << int(aa1) << "\t" << "Teta1' = " << int(av1) << "\t" << "Teta1 = " << int(a1);
    BOOST_LOG_TRIVIAL(debug) << "Teta2'' = " << int(aa2) << "\t" << "Teta2' = " << int(av2) << "\t" << "Teta2 = " << int(a2);

    return true;
}

void MyWindow::start(unsigned int milliSecondsDT)
{
    // Recalculate 60 times a second
    timeout = Glib::signal_timeout().connect( sigc::mem_fun(*this,
              &MyWindow::reCalculatePendulum), milliSecondsDT);
}