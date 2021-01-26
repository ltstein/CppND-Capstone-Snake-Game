#include "game.h"
#include "SDL.h"
#include "planner.h"
#include "route.h"
#include <future>
#include <iostream>

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : bug(grid_width, grid_height), engine(dev()),
      random_w(0, static_cast<int>(grid_width-1)),
      random_h(0, static_cast<int>(grid_height-1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  std::chrono::time_point<std::chrono::system_clock> lastUpdate;
  lastUpdate = std::chrono::system_clock::now();

  int w_center = 32 / 2;
  int h_center = 32 / 2;
  SDL_Point tc = {w_center, h_center - 10};
  SDL_Point tr = {w_center + 10, h_center - 10};
  SDL_Point br = {w_center + 10, h_center};
  SDL_Point bc = {w_center, h_center};

  // std::cout << " tc " << tc.x << ":" << tc.y << "\n";
  // std::cout << " tr " << tr.x << ":" << tr.y << "\n";
  // std::cout << " br " << br.x << ":" << br.y << "\n";
  // std::cout << " bc " << bc.x << ":" << bc.y << "\n";

  // std::vector<int> path{0, 2, 0, 3, 0, 4, 0, 1, 0, 2, 4, 0, 1, 0, 3, 0};
  // std::vector<int> turns{4, 2, 3, 1};
  // std::vector<SDL_Point> points{tc, tr, br, bc};

  // Route route{32, 32};
  // route.MakeNodes();
  // Planner planner{route, 16, 16, 27, 23};

  // planner.AStarSearch();

  // Print out all nodes
  // for (int i = 0; i < route.m_Nodes.size(); i++) {
  //       for (int j = 0; j < route.m_Nodes[i].size(); j++)
  //           std::cout << "(" << i << ":" << j << ")" << route.m_Nodes[i][j].x
  //           << ":" << route.m_Nodes[i][j].y << " ";
  //       std::cout << "\n";
  //   }

  // for (int i = 0; i < planner.m_Model.path.size(); i++) {
  //   std::cout << planner.m_Model.path[i].x << ":" <<
  //   planner.m_Model.path[i].y
  //             << " ";
  //   std::cout << "\n";
  // }

  // bug.FindMovesFromPath(planner.m_Model.path);

  // for (int i = 0; i < bug.moves.size(); i++) {
  //   std::cout << (int)bug.moves[i] << " ";
  //   std::cout << "\n";
  // }

  int move = 0;
  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, bug);

    long timeSinceLastUpdate =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - lastUpdate)
            .count();

    Update();
    renderer.Render(bug, food);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a bug item before placing
    // food.
    if (!bug.BugCell(x, y)) {
      food.x = x;
      food.y = y;
      bug.food = food;
      return;
    }
  }
}

void Game::Update() {
  if (!bug.alive)
    return;

  bug.Update();

  int new_x = static_cast<int>(bug.head_x);
  int new_y = static_cast<int>(bug.head_y);

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y) {
    score++;
    PlaceFood();
    // Grow bug and increase speed.
    // bug.GrowBody();
    bug.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return bug.size; }
SDL_Point Game::GetFood() const { return food; }