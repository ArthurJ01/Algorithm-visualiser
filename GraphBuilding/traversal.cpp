#include <vector>
#include <stack>
#include <queue>
#include <unordered_set>

#include "../headers/node.hpp"
#include "../headers/traversal.hpp"


std::vector<Node*> dfs(Node* startNode){
    std::vector<Node*> visitOrder;
    std::stack<Node*> openList;
    openList.emplace(startNode);
    std::unordered_set<Node*> visited;
    visited.insert(startNode);

    while (!openList.empty()){
        Node* n = openList.top(); //Visit Node n
        openList.pop();
        visitOrder.emplace_back(n); //Store visit order
        std::vector<Node*> adjacentNodes = n->getAdjacencyList();

        for(Node* m : adjacentNodes){
            if (visited.find(m) == visited.end()) {
                openList.push(m);
                visited.insert(m);
            }
        }
    }
    return visitOrder;
}

std::vector<Node*> bfs(Node* startNode){
    std::vector<Node*> visitOrder;
    std::queue<Node*> openList;
    openList.emplace(startNode);
    std::unordered_set<Node*> visited;
    visited.insert(startNode);

    while (!openList.empty()){
        Node* n = openList.front(); //Visit Node n
        openList.pop();
        visitOrder.emplace_back(n); //Store visit order
        std::vector<Node*> adjacentNodes = n->getAdjacencyList();

        for(Node* m : adjacentNodes){
            if (visited.find(m) == visited.end()) {
                openList.push(m);
                visited.insert(m);
            }
        }
    }
    return visitOrder;
}