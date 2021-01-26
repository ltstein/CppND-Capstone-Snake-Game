#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() {
  if (planner.m_Model.path.empty() && 0 == speed) {
    planner.start_node = &(planner.m_Model.m_Nodes[(int)head_x][(int)head_y]);
    planner.end_node = &(planner.m_Model.m_Nodes[food.x][food.y]);
    planner.AStarSearch();
    FindMovesFromPath(planner.m_Model.path);

    std::vector<Route::Node>::iterator it;
    it = planner.m_Model.path.begin();
    planner.m_Model.path.insert(it, *planner.start_node);

    // std::cout << "start" << planner.start_node->x << ":" <<
    // planner.start_node->y << "\n"; std::cout << "end" << planner.end_node->x
    // << ":" << planner.end_node->y << "\n";

    // std::cout << "Path\n";
    // for (int i = 0; i < planner.m_Model.path.size(); i++) {
    // std::cout << planner.m_Model.path[i].x << ":" <<
    // planner.m_Model.path[i].y
    // << " ";
    // std::cout << "\n";
    // }

    // std::cout << "moves\n";
    // for (int i = 0; i < moves.size(); i++) {
    //   std::cout << (int)moves[i] << " ";
    //   std::cout << "\n";
    // }
  }

  // if (0 == speed) {
    // std::cout << "Start Point " << planner.m_Model.path[0].x << ":"
              // << planner.m_Model.path[0].y << "\n";
    // std::cout << "Head Point " << head_x << ":" << head_y << "\n";
  // }

  if (!planner.m_Model.path.empty()) {
    if ((int)head_x == planner.m_Model.path[move].x &&
        (int)head_y == planner.m_Model.path[move].y) {
      // std::cout << " Reached Point " << planner.m_Model.path[move].x << ":"
      //           << planner.m_Model.path[move].y << "\n";
      // std::cout << " Executing Move " << (int)moves[move] << "-" << move <<
      // ":"
      //           << moves.size() << "\n";
      if (move < moves.size()) {
        direction = moves[move];
        speed = 0.1f;
        move++;
      }
    }
  }

  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)}; // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)}; // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }

  if ((int)head_x == planner.end_node->x &&
      (int)head_y == planner.end_node->y) {
    move = 0;
    // snake.moves.clear();
    speed = 0.0f;
    planner.m_Model.path.clear();
  }
}

void Snake::UpdateHead() {
  switch (direction) {
  case Direction::kUp:
    head_y -= speed;
    break;

  case Direction::kDown:
    head_y += speed;
    break;

  case Direction::kLeft:
    head_x -= speed;
    break;

  case Direction::kRight:
    head_x += speed;
    break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell,
                       SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::FindMovesFromPath(std::vector<Route::Node> path) {
  this->moves.clear();
  SDL_Point current{(int)head_x, (int)head_y};
  for (auto node : path) {
    SDL_Point next{node.x, node.y};
    SDL_Point delta{next.x - current.x, next.y - current.y};

    if (0 > delta.x) {
      moves.push_back(Direction::kLeft);
    } else if (0 < delta.x) {
      moves.push_back(Direction::kRight);
    } else if (0 > delta.y) {
      moves.push_back(Direction::kUp);
    } else if (0 < delta.y) {
      moves.push_back(Direction::kDown);
    }

    current = next;
  }
}