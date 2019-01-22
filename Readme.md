# Double Pendulum in c++

This is currently only a quick try to implement a visualization of a double pendulum in c++ using the cross platform graphics lib "gtkmm".

## The Physics
I tried to calculate the equation myself by deriving them in the Lagrange-formalism. 
The calculations seem to be wrong, the total energy seems to change. Will recalculate that soon.

## The code
There are some obvious improvements to be done, they are coming.

## Starting the hole thing
I only tried to build it on linux. You need to have the *gnu compiler collection* and *make* (both probably allready installed under linux). Install [gtkmm](https://www.gtkmm.org/en/download.html) (also installed on most linux-systems), too. 

### Building 
In the main directory of this repo:
~~~
$ make
~~~

### Starting
With the right path, after building:
~~~
$ ./main
~~~

## Port to other operating systems
All software I used is available on Windows, Mac and all Linux-Distributions. So for non-linux users it should not be that hard to port the whole thing, let me know if you do something in that direction.