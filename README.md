# Concurrent Traffic Simulation

<img src="data/traffic_simulation.gif"/>

This project is based on the [Udacity Concurrency Course](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213) 

This project will render a map with traffic lights at various intersections. Multiple cars, represented by moving circles, will enter and exit the intersections when appropriate. The lights are toggled at random intervals (4-6 seconds). When multiple cars approach the same intersection, they will form a queue, and must wait their turn to enter the intersecion. All cars operate on their own thread, and must communicate and share memory safely so they do not crash...or crash the program.

This project focuses on thread safety using mutexes, locks, and message queues.


## Dependencies for Running Locally
* cmake >= 2.8
  * All OSes: [click here for installation instructions](https://cmake.org/install/)

* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)

* OpenCV >= 4.1
  * The OpenCV 4.1.0 source code can be found [here](https://github.com/opencv/opencv/tree/4.1.0)
  * Before installing OpenCV, you may need to install dev packages for GUI support.
    * Install dev packages: `sudo apt-get install libgtk2.0-dev pkg-config`
  * Now install OpenCV
    * Donwload the latest OpenCV snapshot: `wget -O opencv.zip https://github.com/opencv/opencv/archive/4.x.zip`
    * Unzip: `unzip opencv.zip`
    * Rename the extracted folder: `mv opencv-4.x opencv`
    * Create a temporary build folder: `mkdir -p build && cd build`
    * Generate build setup with cmake: `cmake ../opencv`
    * Build OpenCV (this will take a while): `make-j4`
    * Install the built OpenCV files to your system: `sudo make install`
      * This will install OpenCV to /usr/local by default.
      * Cmake will now recognize OpenCV dependencies.
  * Delete the OpenCV zip, extracted folder, and temporary build folder.
    * Navigate to the directory where the openCV zip was downloaded:
    * `rm -rf opencv && rm -rf build && rm opencv.zip``
    
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./traffic_simulation`.
