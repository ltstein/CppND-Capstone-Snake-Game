#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"

class Controller {
 public:
  void HandleInput(bool &running, Snake &snake) const;
  void navigate(Snake &snake, int move) const;

 private:
  void ChangeDirection(Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;

//   Snake::Direction[] calculatePath(SDL_Point goalLocation, SDL_Point startLocation);

  


};

#endif