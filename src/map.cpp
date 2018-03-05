#include <iostream>
#include "map.h"

Map::Map():raw_map_(), map_width_(0){}

void Map::add_line(const std::string &line) {
    if (line.size() == 0)       return;

    // use first line as the standard map_width_ for the map
    if (map_width_ == 0)        map_width_ = line.length();

    // add the line to the map
    long line_num = raw_map_.size();
    raw_map_.push_back(line);

    // iterate through the line to search for holes
    for (long i = 0; i < (long)line.length(); i++){
        // add to availability map (mark as wall / hole)
        if (line[i] == '.') {
            availability_map_[Node{line_num,i}] = true;
        } else{
            // mark as wall in availability map
            availability_map_[Node{line_num,i}] = false;
        }
    }
}

std::vector<Node> Map::get_maximum_path() const {
    // update starting holes first, only holes around the boarder of
    // the labyrinth would be regarded as staring point
    // first line
    std::vector<Node> starting_holes_;
    for (long i = 0; i < map_width_; i++){
        if (raw_map_[0][i] == '.')                      starting_holes_.push_back(Node{0,i});
    }
    // last line
    for (long i = 0; i < map_width_; i++){
        if (raw_map_[raw_map_.size() - 1][i] == '.'){
            starting_holes_.push_back(Node{(long)(raw_map_.size() - 1),i});
        }
    }
    // middle part
    for (long j = 1; j < (long)(raw_map_.size() - 1); j ++){
        if (raw_map_[j][0] == '.')                      starting_holes_.push_back(Node{j,0});
    }
    for (long j = 1; j < (long)(raw_map_.size() - 1); j ++){
        if (raw_map_[j][map_width_ - 1] == '.')         starting_holes_.push_back(Node{j,map_width_ - 1});
    }

    // create a local copy of availability map
    std::map<Node,bool> available_map = availability_map_;

    // start exploring
    std::vector<Node> maximum_path;
    for (Node starting_node : starting_holes_){
        std::vector<Node> path_temp = keep_exploring(starting_node,available_map,std::vector<Node>());
        if (path_temp.size() > maximum_path.size()){
            maximum_path = path_temp;
        }
    }
    return maximum_path;
}

std::vector<Node> Map::keep_exploring(const Node& current_node, std::map<Node, bool> available_map,
                                      std::vector<Node> visited_path) const {
    // add current node to the path
    visited_path.push_back(current_node);
    available_map[current_node] = false;

    std::vector<Node> path_left, path_right, path_up, path_down;
    // exploring the left (try moving left)
    Node left_node = current_node;
    left_node.y -= 1;
    if (is_node_available(left_node,available_map)){
        // recursively exploring left
        path_left = keep_exploring(left_node,available_map,visited_path);
    }

    // exploring right
    Node right_node = current_node;
    right_node.y += 1;
    if (is_node_available(right_node,available_map)){
        // recursively exploring
        path_right = keep_exploring(right_node,available_map,visited_path);
    }
    // exploring up
    Node up_node = current_node;
    up_node.x -= 1;
    if (is_node_available(up_node,available_map)){
        // recursively exploring
        path_up = keep_exploring(up_node,available_map,visited_path);
    }
    // exploring down
    Node down_node = current_node;
    down_node.x += 1;
    if (is_node_available(down_node,available_map)){
        // recursively exploring
        path_down = keep_exploring(down_node,available_map,visited_path);
    }

    if (path_left > visited_path)                   visited_path = path_left;
    if (path_right > visited_path)                  visited_path = path_right;
    if (path_up > visited_path)                     visited_path = path_up;
    if (path_down > visited_path)                   visited_path = path_down;
    return visited_path;
}

bool Map::is_node_available(const Node& node, std::map<Node, bool> available_map) const {
    if (available_map.count(node) == 0)         return false;
    return available_map[node];
}

void Map::printout_path(const std::vector<Node> &path) const {
    // build position codebook
    std::map<Node,unsigned long> code_book;
    for (unsigned long i = 0; i < path.size(); i++){
        const Node& node= path[i];
        code_book[node] = i;
    }

    // print it out
    for (long i = 0; i < (long)raw_map_.size(); i++){
        std::string line_buffer;
        for (long j = 0; j < map_width_; j++){
            if (raw_map_[i][j] == '.'){
                Node hole{i,j};
                if (code_book.count(hole) == 0)         line_buffer += ".";
                else        line_buffer += std::to_string(code_book[Node{i,j}]);
            }
            else{
                line_buffer += "#";
            }
        }
        std::cout << line_buffer << std::endl;
    }
}