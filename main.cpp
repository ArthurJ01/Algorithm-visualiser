#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "headers/initialize.hpp"
#include "headers/stepStruct.hpp"
#include "headers/sortingVisualiser.hpp"

enum class Windows {menu, sorting};
extern const sf::Font font("C:/Windows/fonts/arial.ttf");

class Button : public sf::Drawable{
    public:

        sf::RectangleShape button;
        sf::Text text;
        sf::Window* window;

        Button(const sf::Vector2f &size, const sf::Vector2f &position, const std::string &s)
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
        bool clicked(sf::Vector2f point){
            bool inside = button.getGlobalBounds().contains(point);
            button.setFillColor(inside ? sf::Color::Yellow : sf::Color::White);
            return inside && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        }

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(button, states);
            target.draw(text, states);
        }
};

int main()
{
    Windows currentWindow = Windows::menu;
    SortingAlgorithm algoToRun = SortingAlgorithm::insertionSort;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                    currentWindow = Windows::sorting;
                }
            }  
        }
        switch (currentWindow){
            case Windows::menu: {
                window.clear(sf::Color(100,100,100));

                sf::Text text(font); // a font is required to make a text object
                text.setString("menu ");
                text.setCharacterSize(24); // in pixels, not points!
                text.setFillColor(sf::Color::Red);
                text.setStyle(sf::Text::Bold | sf::Text::Underlined);

                //testing stuff

                sf::Vector2f buttonSize = {200.f, 100.f};
                Button newButton (buttonSize, {400.f, 50.f}, "testing new");
                Button insertionSortButton(buttonSize, {100.f, 50.f}, "insertion sort");
                Button MergeSortButton(buttonSize, {100.f, 200.f}, "merge sort");

                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::insertionSort;
                }

                if(MergeSortButton.clicked(mouse_position)){
                    currentWindow = Windows::sorting;
                    algoToRun = SortingAlgorithm::mergeSort;
                }

                window.draw(newButton);
                window.draw(insertionSortButton);
                window.draw(MergeSortButton);
                window.draw(text);
                window.display();

                break;
            }
            case Windows::sorting: {
                //run sorting algo and when it is done, go back to menu
                runSortAlgo(window, algoToRun);
                currentWindow = Windows::menu;
                break;
            }

        }
    }
}

