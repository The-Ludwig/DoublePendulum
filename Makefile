all: main

main: main.cpp myWindow.cpp myWindow.h pendulumDrawer.cpp pendulumDrawer.h
	g++ -std=c++11 -DBOOST_LOG_DYN_LINK pendulumDrawer.cpp myWindow.cpp main.cpp -o main $$(pkg-config gtkmm-3.0 --cflags --libs) -lpthread -lboost_log -lboost_log_setup

debug: main.cpp myWindow.cpp myWindow.h pendulumDrawer.cpp pendulumDrawer.h
	g++ -g -std=c++11 -DBOOST_LOG_DYN_LINK pendulumDrawer.cpp myWindow.cpp main.cpp -o main $$(pkg-config gtkmm-3.0 --cflags --libs) -lpthread -lboost_log -lboost_log_setup

make clean:
	rm ./main
	rm *.o