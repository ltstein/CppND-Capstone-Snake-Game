#ifndef SNAKE_H
#define SNAKE_H

#include "SDL.h"
#include "planner.h"
#include <vector>

class Snake {
public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  Snake(int grid_width, int grid_height)
      : grid_width(grid_width), grid_height(grid_height),
        head_x(grid_width / 2), head_y(grid_height / 2),
        route(grid_width, grid_height),
        planner(route, (int)head_x, (int)head_y, food.x, food.y) {
          planner.m_Model.path.clear();
    
  }

  void Update();
  void GrowBody();
  bool SnakeCell(int x, int y);

  void FindMovesFromPath(std::vector<Route::Node> path);

  Direction direction = Direction::kUp;

  float speed{0.0f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;

  std::vector<Direction> moves{};
  SDL_Point food;

  Route route;
  Planner planner;

private:
  void UpdateHead();
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  void Navigate();

  bool growing{false};
  int grid_width;
  int grid_height;
  int move{0};
};

#endif