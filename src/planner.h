//Adapted from Udacity C++ Nanodegree Route Planner Project code
//https://github.com/udacity/CppND-Route-Planning-Project/tree/master/src 
// commit 3bf4b8e0aa87620cb1ab640e7abcb90f2cbe7bc3

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "route.h"


class Planner {
  public:
    Planner(Route &model, int start_x, int start_y, int end_x, int end_y);
//     // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}
    void AStarSearch();

//     // The following methods have been made public so we can test them individually.
    void AddNeighbors(Route::Node *current_node);
    float CalculateHValue(Route::Node const *node);
    std::vector<Route::Node> ConstructFinalPath(Route::Node *);
    Route::Node *NextNode();

//   private:
//     // Add private variables or methods declarations here.
    std::vector<Route::Node*> open_list;
    Route::Node *start_node;
    Route::Node *end_node;

    float distance = 0.0f;
    Route &m_Model;
};

// #endif