## [Project Description](#project-description)
This project is a built as a starting point for exploring and explaining autonomous motion. Currently, it takes a basic 2D world with no obstacles and extends the character with crude autonomous capabilites to plan and execute a path to achieve the goal of reaching the food pellet placed randomly in the world. 

### Basic Code Structure
The demo is implemented with the following classes:

Game: Handles game logic and updating, contains Bug object.
Renderer: Handles drawing the game view.
Bug: Encapsulates functionality for bug attributes, contains route and planner.

The autonomous nature is achieved primarily through the addition of the following classes:
Route: Contains logic and data structures for managing the representation of the 2D world.
Planner: Implements logic for A* path planning using Route object.

### What You See
The demo launches through the entry point main which sets up the required resources. A Bug instance is represented by a blue dot and the food is represented by a yellow dot. The bug will automatically begin by analyzing the game space, planning a path, and executing that path. If you intervene by pressing directional arrows, the bugs path following routine will be interuppted. If you guid the bug to the food, they will resuming autonomous behavior once again.

### Rubric Points Discussion 
For notes on rubric points see [here](rubric.md)


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## [Basic Build Instructions](#basic-build-instructions)

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./BugDemo`.

## Planned Extensions
- [ ] Implement visualization of path planning
- [ ] Implement obstacles
- [ ] Clean up dead code
- [ ] Implement thread for logging/std out

Based on Udacity C++ Nanodegree Snake Game
# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.