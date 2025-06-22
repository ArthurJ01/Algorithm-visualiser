#include <vector>
#include<stack>

#include "../headers/node.hpp"
#include "../headers/traversal.hpp"


std::vector<Node*> dfs(Node* startNode){
    std::vector<Node*> visitOrder;
    std::stack<Node*> openList;
    openList.emplace(startNode);
    std::unordered_map<Node*, bool> visited;
    visited[startNode] = true;

    while (!openList.empty()){
        Node* n = openList.top(); //Visit Node n
        //could add some things here to show backtracking
        openList.pop();
        visitOrder.emplace_back(n); //Store visit order
        std::vector<Node*> adjacentNodes = n->getAdjacencyList();

        for(Node* m : adjacentNodes){
            if (visited.find(m) == visited.end()) {
                openList.push(m);
                visited[m] = true;
            }
        }
    }
    return visitOrder;
}
