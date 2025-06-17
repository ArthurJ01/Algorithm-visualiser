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
        sf::Text buttonText;

        Button(const sf::Vector2f &size, const sf::Vector2f &position, const std::string &text)
            : button(size), buttonText(font)
        {
            button.setPosition(position);

            buttonText.setString(text);
            buttonText.setCharacterSize(24);
            buttonText.setFillColor(sf::Color::Red);

            float position_x = button.getPosition().x + (button.getSize().x / 2);
            float position_y = button.getPosition().y + (button.getSize().y / 2);
            buttonText.setOrigin({buttonText.getGlobalBounds().getCenter()});
            buttonText.setPosition({position_x, position_y});  
        }

        bool contains (sf::Vector2f point) const{
            return button.getGlobalBounds().contains(point);
        }

        void setFillColor(const sf::Color &color){
            button.setFillColor(color);
        }

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
            target.draw(button, states);
            target.draw(buttonText, states);
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
                Button newButton ({200.f, 100.f}, {400.f, 50.f}, "testing new");
                Button insertionSortButton({200.f, 100.f}, {100.f, 50.f}, "insertion sort");
                Button MergeSortButton({200.f, 100.f}, {100.f, 200.f}, "merge sort");

                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.contains(mouse_position)){
                    insertionSortButton.setFillColor(sf::Color::Yellow);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        currentWindow = Windows::sorting;
                        algoToRun = SortingAlgorithm::insertionSort;
                    } 
                }
                else{
                    insertionSortButton.setFillColor(sf::Color::White);
                }

                if(MergeSortButton.contains(mouse_position)){
                    MergeSortButton.setFillColor(sf::Color::Yellow);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        currentWindow = Windows::sorting;
                        algoToRun = SortingAlgorithm::mergeSort;
                    } 
                }
                else{
                    MergeSortButton.setFillColor(sf::Color::White);
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

