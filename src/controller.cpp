#include "controller.h"
#include "SDL.h"
#include "bug.h"
#include <chrono>
#include <iostream>
#include <thread>

void Controller::ChangeDirection(Bug &bug, Bug::Direction input,
                                 Bug::Direction opposite) const {
  if (bug.direction != opposite || bug.size == 1)
    bug.direction = input;
  return;
}

void Controller::HandleInput(bool &running, Bug &bug) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
      case SDLK_UP:
        ChangeDirection(bug, Bug::Direction::kUp, Bug::Direction::kDown);
        break;

      case SDLK_DOWN:
        ChangeDirection(bug, Bug::Direction::kDown, Bug::Direction::kUp);
        break;

      case SDLK_LEFT:
        ChangeDirection(bug, Bug::Direction::kLeft,
                        Bug::Direction::kRight);
        break;

      case SDLK_RIGHT:
        ChangeDirection(bug, Bug::Direction::kRight,
                        Bug::Direction::kLeft);
        break;
      }
    }
  }
}

void Controller::navigate(Bug &bug, int move) const {
  Bug::Direction dir = (Bug::Direction)move;
  switch (dir) {
  case Bug::Direction::kUp:
    ChangeDirection(bug, Bug::Direction::kUp, Bug::Direction::kDown);
    break;

  case Bug::Direction::kDown:
    ChangeDirection(bug, Bug::Direction::kDown, Bug::Direction::kUp);
    break;

  case Bug::Direction::kLeft:
    ChangeDirection(bug, Bug::Direction::kLeft, Bug::Direction::kRight);
    break;

  case Bug::Direction::kRight:
    ChangeDirection(bug, Bug::Direction::kRight, Bug::Direction::kLeft);
    break;
  }
}