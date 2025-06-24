#include <SFML/Graphics.hpp>

#include "button.hpp"

extern const sf::Font font;

Button::Button(const sf::Vector2f &size, const sf::Vector2f &position, const std::string &s)
    : button(size), text(font)
{
    button.setPosition(position);
    button.setFillColor({45, 50, 70});

    text.setString(s);
    text.setCharacterSize(24);
    text.setFillColor({240, 240, 240});

    float position_x = button.getPosition().x + (button.getSize().x / 2);
    float position_y = button.getPosition().y + (button.getSize().y / 2);
    text.setOrigin({text.getGlobalBounds().getCenter()});
    text.setPosition({position_x, position_y});  
}

//changes colour of rectangle while mouse inside button, returns wether it has been clicked or not
bool Button::clicked(sf::Vector2f point){
    bool inside = button.getGlobalBounds().contains(point);
    button.setFillColor(inside ? sf::Color(0, 153, 255) : sf::Color(45, 50, 70));
    text.setFillColor(inside ? sf::Color(255, 255, 255) : sf::Color(240, 240, 240));
    return inside && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(button, states);
    target.draw(text, states);
}
