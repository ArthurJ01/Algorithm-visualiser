#pragma once
#include <vector>
#include <memory>
#include <utility>

class Node;   // forward declaration
class Button; // forward declaration

using NodeEdge = std::pair<Node*, Node*>;
using EdgeList = std::vector<NodeEdge>;
using NodeList = std::vector<std::unique_ptr<Node>>;
using ButtonList = std::vector<Button*>;