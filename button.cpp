#include <SFML/Graphics.hpp>

#include "headers/button.hpp"

extern const sf::Font font;

Button::Button(const sf::Vector2f &size, const sf::Vector2f &position, const std::string &s)
    : button(size), text(font)
{
    button.setPosition(position);

    text.setString(s);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);

    float position_x = button.getPosition().x + (button.getSize().x / 2);
    float position_y = button.getPosition().y + (button.getSize().y / 2);
    text.setOrigin({text.getGlobalBounds().getCenter()});
    text.setPosition({position_x, position_y});  
}

//changes colour of rectangle while mouse inside button, returns wether it has been clicked or not
bool Button::clicked(sf::Vector2f point){
    bool inside = button.getGlobalBounds().contains(point);
    button.setFillColor(inside ? sf::Color::Yellow : sf::Color::White);
    return inside && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(button, states);
    target.draw(text, states);
}
