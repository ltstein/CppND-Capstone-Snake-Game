//Adapted from Udacity C++ Nanodegree Route Planner Project code
//https://github.com/udacity/CppND-Route-Planning-Project/tree/master/src 
// commit 3bf4b8e0aa87620cb1ab640e7abcb90f2cbe7bc3

#include "route.h"
#include <iostream>

// Route::Route(const std::vector<std::byte> &xml) : Model(xml) {
//     // Create Route nodes.
//     int counter = 0;
//     for (Node node : this->m_nodes) {
//         m_Nodes.emplace_back(Node(counter, this, node));
//         counter++;
//     }
//     CreateNodeToRoadHashmap();
// }

// Route::Route()

// void Route::CreateNodeToRoadHashmap() {
//     for (const Model::Road &road : Roads()) {
//         if (road.type != Model::Road::Type::Footway) {
//             for (int node_idx : Ways()[road.way].nodes) {
//                 if (node_to_road.find(node_idx) == node_to_road.end()) {
//                     node_to_road[node_idx] = std::vector<const Model::Road *>
//                     ();
//                 }
//                 node_to_road[node_idx].push_back(&road);
//             }
//         }
//     }
// }

// Route::Node *Route::Node::FindNeighbor(std::vector<int> node_indices) {
//     Node *closest_node = nullptr;
//     Node node;

//     for (int node_index : node_indices) {
//         node = parent_model->SNodes()[node_index];
//         if (this->distance(node) != 0 && !node.visited) {
//             if (closest_node == nullptr || this->distance(node) <
//             this->distance(*closest_node)) {
//                 closest_node = &parent_model->SNodes()[node_index];
//             }
//         }
//     }
//     return closest_node;
// }

// Generate map of node for current game grid
void Route::MakeNodes() {
  for (int x = 0; x < Route::_width; x++) {
    std::vector<Route::Node> col;
    for (int y = 0; y < Route::_height; y++) {
      col.emplace_back(Route::Node(x, y, this));
    }
    m_Nodes.emplace_back(col);
  }
}

void Route::Node::FindNeighbors() {
  std::vector<SDL_Point> toNeighbors{{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
  for (auto neighbor : toNeighbors) {
    int n_x = this->x + neighbor.x;
    int n_y = this->y + neighbor.y;
    if ((n_x >= 0 && n_x < this->route->_width) && (n_y >= 0 && n_y < this->route->_height))
    {
      Route::Node *new_neighbor = &(route->m_Nodes[n_x][n_y]);
      this->neighbors.emplace_back(new_neighbor);
    }
  }
};

// Route::Node &Route::FindClosestNode(float x, float y) {
//     Node input;
//     input.x = x;
//     input.y = y;

//     float min_dist = std::numeric_limits<float>::max();
//     float dist;
//     int closest_idx;

//     for (const Model::Road &road : Roads()) {
//         if (road.type != Model::Road::Type::Footway) {
//             for (int node_idx : Ways()[road.way].nodes) {
//                 dist = input.distance(SNodes()[node_idx]);
//                 if (dist < min_dist) {
//                     closest_idx = node_idx;
//                     min_dist = dist;
//                 }
//             }
//         }
//     }

//     return SNodes()[closest_idx];
// }