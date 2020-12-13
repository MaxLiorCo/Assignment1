This work was done by khtur9512300  &  madMax342
purpose: We are notified about cities hit by the pandemic and we put them under quarantine using contact tracers
ATTENTION: make sure to create an empty bin folder before running the aformentioned program.
         
Input: The program receives the path of the config file as the first command line argument
       writen as:   bin/cTrace [path to config.json]
       the json file contains a graph (of cities and their connections) a vector of agents (viruses and contact tracers),
       and a tree type that difines the algorithm by which we put cities under quarantine.
       file example:{"agents":[["V",0],["C",-1]],
                     "graph":[[0,1,0,0,1,0,0,0,0],
                              [1,0,1,1,0,1,1,0,0],
                              [0,1,0,1,0,1,0,0,0],
                              [0,1,1,0,0,1,0,0,0],
                              [1,0,0,0,0,1,0,0,0],
                              [0,1,1,1,1,0,0,1,0],
                              [0,1,0,0,0,0,0,1,1],
                              [0,0,0,0,0,1,1,0,0],
                              [0,0,0,0,0,0,1,0,0]],
                              "tree":"M"}
output: ./output.json that contains the cities after we ran the algorithm and removed the required paths between the cities 
        + the infected cities that we weren't able to save.
       file example: {"graph":[[0,0,0,0,1,0,0,0,0],
                               [0,0,0,0,0,0,0,0,0],
                               [0,0,0,1,0,0,0,0,0],
                               [0,0,1,0,0,0,0,0,0],
                               [1,0,0,0,0,0,0,0,0],
                               [0,0,0,0,0,0,0,0,0],
                               [0,0,0,0,0,0,0,1,1],
                               [0,0,0,0,0,0,1,0,0],
                               [0,0,0,0,0,0,1,0,0]],
                      "infected":[0,1,4,5]}
