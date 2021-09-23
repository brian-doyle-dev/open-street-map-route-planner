#include "route_planner.h"
#include <algorithm>

/**
 * @brief Constructor for RoutePlanner
 * 
 * Initialise the RoutePlanner object with the start and end node data
 * 
 * @param model The RoutePlanner model
 * @param start_x x-coordinate of the start node
 * @param start_y y-coordinate of the start node
 * @param end_x x-coordinate of the end node
 * @param end_y y-coordinate of the end node
 */
RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // Find the closest nodes to the start and end points specified by the user
    start_node = &(m_Model.FindClosestNode(start_x, start_y));
    end_node = &(m_Model.FindClosestNode(end_x, end_y));
}

/**
 * @brief Calculate the Heuristic Value
 * 
 * Get the distance from the node passed in to the end node
 * 
 * @param node The node for which to find the distance
 * @return The distance calculated
 */
float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}


/**
 * @brief Add neighbours to the open_list
 * 
 * Find neighbours of the current_node and add them open_list
 * 
 * @param current_node The node for which to find the neighbours
 * @return (void)
 */
void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
    current_node->FindNeighbors();
    for (auto node : current_node->neighbors)
    {
        node->parent = current_node;
        node->h_value = CalculateHValue(node);
        node->g_value = current_node->g_value + current_node->distance(*node);
        node->visited = true;

        open_list.push_back(node);
    }
}


/**
 * @brief Compare the nodes
 * 
 * Compare the sum g + h of the nodes to be compared.
 * 
 * @param node1 Node to be compared
 * @param node2 Node to be compared
 * @return true if g + h for node1 is greater than that for node2, false otherwise
 */
bool CompareNodes(RouteModel::Node *node1, RouteModel::Node *node2)
{
    if ((node1->g_value + node1->h_value) > (node2->g_value + node2->h_value))
    {
        return true;
    }

    return false;
}

/**
 * @brief Find the next node in the path
 * 
 * Sorts the open_list in order of decreasing distance from the end node.
 * CompareNodes() is used by the sort() function to sort the nodes in the correct order.
 * 
 * @return The next node
 */
RouteModel::Node *RoutePlanner::NextNode() {
    RouteModel::Node *node;
    sort(open_list.begin(), open_list.end(), CompareNodes);
    node = open_list.back();
    open_list.pop_back();
    return node;
}


/**
 * @brief Construct the final path
 * 
 * Creates a vector of RouteModel::Nodes starting with node passed in. 
 * Traverses the list of nodes using the parent pointer to find the next node in the path.
 * The path is then reversed, as the list will be starting from the end node.
 * 
 * The distance along the path is also calculated.
 * 
 * @param current_node The node from which to start.
 * @return The vector contining the list of nodes in the path.
 */
std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while(current_node != nullptr)
    {
        if (current_node->parent != nullptr)
        {
            distance += current_node->distance(*current_node->parent);
        }
        path_found.push_back(*current_node);

        current_node = current_node->parent;
    }

    std::reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}

/**
 * @brief Do the A* Search
 * 
 * Initialise the open_list with the start_node.
 * 
 * Then use NextNode() and AddNeighbors() to find the path through the map.
 * When the end_node is reached, the final path is constructed.
 * 
 * @return (void)
 */
void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = start_node;

    current_node->parent = nullptr;
    current_node->g_value = 0;
    current_node->h_value = CalculateHValue(end_node);
    current_node->visited = true;

    AddNeighbors(current_node);

    while (*current_node != *end_node)
    {
        current_node = NextNode();

        if(*current_node == *end_node)
        {
            m_Model.path = ConstructFinalPath(current_node);
            return;
        }

        AddNeighbors(current_node);
    }
}