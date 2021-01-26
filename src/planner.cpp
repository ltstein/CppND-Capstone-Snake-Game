//Adapted from Udacity C++ Nanodegree Route Planner Project code
//https://github.com/udacity/CppND-Route-Planning-Project/tree/master/src 
// commit 3bf4b8e0aa87620cb1ab640e7abcb90f2cbe7bc3

#include "planner.h"
#include <algorithm>

Planner::Planner(Route &model, int start_x, int start_y, int end_x, int end_y) : m_Model(model)
{
    // Convert inputs to percentage:
    // start_x *= 0.01;
    // start_y *= 0.01;
    // end_x *= 0.01;
    // end_y *= 0.01;

//     // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
//     // Store the nodes you find in the Planner's start_node and end_node attributes.
    start_node = &(m_Model.m_Nodes[start_x][start_y]);
    end_node = &(m_Model.m_Nodes[end_x][end_y]);
}

// // TODO 3: Implement the CalculateHValue method.
// // Tips:
// // - You can use the distance to the end_node for the h value.
// // - Node objects have a distance method to determine the distance to another node.

float Planner::CalculateHValue(Route::Node const *node)
{
    return node->distance(*end_node);
}

// // TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// // Tips:
// // - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// // - For each node in current_node.neighbors, set the parent, the h_value, the g_value.
// // - Use CalculateHValue below to implement the h-Value calculation.
// // - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void Planner::AddNeighbors(Route::Node *current_node)
{
    current_node->FindNeighbors();
    // std::cout << "Current Node: " << current_node->x << ":" << current_node->y << "\n";
    
    for (auto neighbor : current_node->neighbors)
    {
        // std::cout << "Neighbor Node: " << neighbor->x << ":" << neighbor->y << "\n";
        if (neighbor->visited == false)
        {
            neighbor->parent = current_node;
            neighbor->h_value = CalculateHValue(neighbor);
            neighbor->g_value = current_node->g_value + current_node->distance(*neighbor);
            open_list.emplace_back(neighbor);
            neighbor->visited = true;
        }
    }
}

// // TODO 5: Complete the NextNode method to sort the open list and return the next node.
// // Tips:
// // - Sort the open_list according to the sum of the h value and g value.
// // - Create a pointer to the node in the list with the lowest sum.
// // - Remove that node from the open_list.
// // - Return the pointer.
// /**
//  * Compare the F values of two cells(Sum of cost accrued reach cell(g) plus heuristic(h)).
//  */
bool CompareNodes(const Route::Node *a, const Route::Node *b)
{
    float f1 = (a->g_value + a->h_value);
    float f2 = (b->g_value + b->h_value);

    return f1 < f2;
}
Route::Node *Planner::NextNode() {
    //Sort list using compare function
    std::sort(open_list.begin(), open_list.end(), CompareNodes);
    //Create a pointer to the node in the list with the lowest sum.
    //Erase node from https://knowledge.udacity.com/questions/253423
    Route::Node * next_node = open_list.front();
    open_list.erase(open_list.begin());
    //Return the pointer.
    return next_node;
}

// // TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// // Tips:
// // - This method should take the current (final) node as an argument and iteratively follow the
// //   chain of parents of nodes until the starting node is found.
// // - For each node in the chain, add the distance from the node to its parent to the distance variable.
// // - The returned vector should be in the correct order: the start node should be the first element
// //   of the vector, the end node should be the last element.

std::vector<Route::Node> Planner::ConstructFinalPath(Route::Node *current_node)
{
    // Create path_found vector
    distance = 0.0f;
    std::vector<Route::Node> path_found;

    // TODO: Implement your solution here.
    
    while ((current_node->x != start_node->x) && (current_node->y != start_node->y))
    {
        // std::cout << "Path: Adding Node: " << current_node->x << ":" << current_node->y << "\n";
        path_found.push_back(*current_node);
        distance = distance + current_node->distance(*current_node->parent);
        current_node = current_node->parent;
        // std::cout << "Current Node: " << current_node->x << ":" << current_node->y << "\n";
        // std::cout << "Parent Node: " << current_node->parent->x << ":" << current_node->parent->y << "\n";
    }
    path_found.push_back(*current_node);
    // std::cout << "Path Construction Final Node: " << current_node->x << ":" << current_node->y << "\n";
    std::reverse(path_found.begin(), path_found.end());

    // distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;
}

// // TODO 7: Write the A* Search algorithm here.
// // Tips:
// // - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// // - Use the NextNode() method to sort the open_list and return the next node.
// // - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// // - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void Planner::AStarSearch()
{
    Route::Node *current_node = nullptr;

    //Clear node information for next planning iteration

  for (int x = 0; x < m_Model._width; x++) {
    std::vector<Route::Node> col;
    for (int y = 0; y < m_Model._height; y++) {
      m_Model.m_Nodes[x][y].visited = false;
      m_Model.m_Nodes[x][y].g_value = 0.0;
      m_Model.m_Nodes[x][y].h_value = std::numeric_limits<float>::max();
      m_Model.m_Nodes[x][y].parent = nullptr;
    }
  }

    // TODO: Implement your solution here.
    current_node = start_node;
    current_node->visited = true;

    while (current_node != end_node)
    {
    AddNeighbors(current_node);
    current_node = NextNode();
    }
    current_node = end_node;

    m_Model.path = ConstructFinalPath(current_node);
}