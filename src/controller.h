#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "bug.h"

class Controller {
 public:
  void HandleInput(bool &running, Bug &bug) const;
  void navigate(Bug &bug, int move) const;

 private:
  void ChangeDirection(Bug &bug, Bug::Direction input,
                       Bug::Direction opposite) const;

//   Bug::Direction[] calculatePath(SDL_Point goalLocation, SDL_Point startLocation);

  


};

#endif