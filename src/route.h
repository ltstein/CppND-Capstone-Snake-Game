//Adapted from Udacity C++ Nanodegree Route Planner Project code
//https://github.com/udacity/CppND-Route-Planning-Project/tree/master/src 
// commit 3bf4b8e0aa87620cb1ab640e7abcb90f2cbe7bc3

#pragma once

#include <limits>
#include <cmath>
#include <unordered_map>
#include <iostream>
#include <vector>
#include <memory>
#include "SDL.h"

class Route {

  public:
    
    class Node {
      public:
        int x;
        int y;
        Node * parent = nullptr;
        float h_value = std::numeric_limits<float>::max();
        float g_value = 0.0;
        bool visited = false;
        std::vector<Node *> neighbors;

        void FindNeighbors();
        float distance(Node other) const {
            return std::sqrt(std::pow((x - other.x), 2) + std::pow((y - other.y), 2));
        }

        Node(){}
        Node(int x, int y, Route * route) : x(x), y(y), route(route) {}
        // Node(int idx, Route * search_model, Node node) : Node(node), parent_model(search_model), index(idx) {}

      private:
        int index;
        Node * FindNeighbor(std::vector<int> node_indices);
        Route * route = nullptr;
    };

void MakeNodes();
int IndexAtPoint(int x, int y);
    // Route(const std::vector<std::byte> &xml);
Route(int width, int height) : _width(width), _height(height){
  MakeNodes();
}
//     Node &FindClosestNode(float x, float y);
//     auto &SNodes() { return m_Nodes; }
    std::vector<Node> path;

//   private:
//     void CreateNodeToRoadHashmap();
//     std::unordered_map<int, std::vector<const Road *>> node_to_road;
    std::vector<std::vector<Node>> m_Nodes;
    int _width;
    int _height;


};


