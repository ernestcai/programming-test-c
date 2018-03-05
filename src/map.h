#ifndef PROGRAMMING_TEST_C_MAP_H
#define PROGRAMMING_TEST_C_MAP_H

#include <vector>
#include <string>
#include <map>
#include "node.h"

class Map {
public:
    Map();
    void add_line(const std::string& line);
    std::vector<Node> get_maximum_path() const;

    void printout_path(const std::vector<Node>& path) const;

private:
    // determine if the node is available, given visited_map (only unvisited holes are true there)
    bool is_node_available(const Node& node, std::map<Node, bool> available_map) const;

    // return the maximum path
    // Input:
    //      current_node: the current node
    //      visited_map: a map driven from raw_map, (all unvisited holes are flags as true)
    //      visited_path: the whole path way so far
    std::vector<Node> keep_exploring(const Node& current_node, std::map<Node,bool> available_map,
                                     std::vector<Node> visited_path) const;

    std::vector<std::string> raw_map_;
    std::map<Node,bool> availability_map_;
    long map_width_;
};


#endif //PROGRAMMING_TEST_C_MAP_H
