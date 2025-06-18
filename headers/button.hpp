#pragma once

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable{
    public:
        Button(const sf::Vector2f &size, const sf::Vector2f &position, const std::string &s);

        //changes colour of rectangle while mouse inside button, returns wether it has been clicked or not
        bool clicked(sf::Vector2f point);
    private:
        sf::RectangleShape button;
        sf::Text text;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};