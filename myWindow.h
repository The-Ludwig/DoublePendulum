#pragma once

#include <chrono>
#include <cmath>
#include <gtkmm.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <gtkmm-3.0/gtkmm/drawingarea.h>

class PendulumDrawer : public Gtk::DrawingArea
{
private:
    int posX1, posY1, posX2, posY2;

public:
    PendulumDrawer();
    virtual ~PendulumDrawer();
    bool drawPendulum(float teta1, float teta2, float length1, float length2);

private:
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};

class MyWindow : public Gtk::Window
{
private: 
    double a1, a2, l1, l2;
    double av1, av2, aa1, aa2;
    double M;
    double g;
    PendulumDrawer pd;
    sigc::connection timeout;
    std::chrono::system_clock::time_point lastTime;
    int counter;

public:
    MyWindow(unsigned int sizeX, unsigned int sizeY);
    virtual ~MyWindow();

private:
    bool reCalculatePendulum();

};