//
// Created by valentin on 08.11.21.
//

#include <fstream>
#include <networkit/algebraic/algorithms/AlgebraicADP.hpp>


int main(int argc, char *argv[]){

    std::ifstream input_file;
    input_file.open(argv[0]);
    std::string graph = "";
    if (input_file.is_open()) {
        std::string line;
        while ( std::getline (input_file,line) )
        {
            graph += line;
        }
        input_file.close();
    }
    AlgebraicADP adp = AlgebraicADP(graph);
    adp.run();
    return 0;
}
