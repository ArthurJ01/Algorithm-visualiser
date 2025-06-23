
#include <SFML/Graphics.hpp>
#include <vector>

#include "button.hpp"
#include "graphInputHandler.hpp"



actionType getCurrentAction(const actionType& currentAction, const sf::Vector2f& mouse_position, const std::vector<std::unique_ptr<actionButton>>& buttonList){
    for (const auto& actionButton : buttonList){
        if(actionButton->button.clicked(mouse_position)){
            return actionButton->action;
        }
    }
    //stay on the same action
    return currentAction;
};
