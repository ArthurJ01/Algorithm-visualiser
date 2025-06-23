#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "button.hpp"

enum class actionType {none, dfs, bfs, reset, clear, exit};

struct actionButton {
    actionType action;
    Button& button;
    actionButton(actionType a, Button& b) : action(a), button(b) {}
};

actionType getCurrentAction(const actionType& currentAction, const sf::Vector2f& mouse_position, const std::vector<std::unique_ptr<actionButton>>& buttonList);