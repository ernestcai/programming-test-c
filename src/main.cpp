#include <iostream>
#include <tuple>
#include "map.h"

int main (int argc, const char * argv[]){
    Map raw_map;
    while(!std::cin.eof()){
        std::string line;
        std::cin >> line;
        // std::cout << "Received: " << line << std::endl;
        raw_map.add_line(line);
    }

    // get the path
    std::vector<Node> path = raw_map.get_maximum_path();

    // print it out
    raw_map.printout_path(path);

    return 0;
}