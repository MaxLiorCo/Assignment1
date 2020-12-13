#include <iostream>
#include <fstream>
#include "../include/Session.h"                                //I ADDED THE "../include/"
#include "../include/json.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char** argv){
    if(argc != 2){
        cout << "usage cTrace <nlohmann/config1.json>" << endl;
        return 0;
    }
    Session sess(argv[1]);
    sess.simulate();
    
    return 0;

    //--------------------------------------------

}

