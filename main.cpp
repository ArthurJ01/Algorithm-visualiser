#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <thread>

#include "headers/sorting.hpp"
#include "headers/draw.hpp"
#include "headers/initialize.hpp"
#include "headers/stepStruct.hpp"

enum class SortingAlgorithm { insertionSort, mergeSort };
enum class Windows { menu, sorting};
void runSortAlgo(sf::RenderWindow& window, SortingAlgorithm algoToRun);

int main()
{
    Windows currentWindow = Windows::menu;
    SortingAlgorithm algoToRun = SortingAlgorithm::insertionSort;
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    //TODO: import a font to the project or smth (maybe it can be like this though)
    sf::Font font("C:/Windows/fonts/arial.ttf");

    sf::Text text(font); // a font is required to make a text object
    text.setString("menu ");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);

   sf::RectangleShape insertionSortButton({200.f, 100.f});
   insertionSortButton.setPosition({100.f, 50.f}); 

    sf::Text insertionButtonText (font); // a font is required to make a text object
    insertionButtonText.setString("insertion sort ");
    insertionButtonText.setCharacterSize(24);
    insertionButtonText.setFillColor(sf::Color::Red);
    insertionButtonText.setPosition({insertionSortButton.getPosition().x * 1.2, insertionSortButton.getPosition().y * 1.2});

    sf::RectangleShape MergeSortButton({200.f, 100.f});
    MergeSortButton.setPosition({100.f, 200.f}); 

    sf::Text mergeButtonText (font); // a font is required to make a text object
    mergeButtonText.setString("merge sort ");
    mergeButtonText.setCharacterSize(24);
    mergeButtonText.setFillColor(sf::Color::Red);
    mergeButtonText.setPosition({MergeSortButton.getPosition().x * 1.2, MergeSortButton.getPosition().y * 1.2});

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

                sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));

                if(insertionSortButton.getGlobalBounds().contains(mouse_position)){
                    insertionSortButton.setFillColor(sf::Color::Yellow);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        currentWindow = Windows::sorting;
                        algoToRun = SortingAlgorithm::insertionSort;
                    } 
                }
                else{
                    insertionSortButton.setFillColor(sf::Color::White);
                }

                if(MergeSortButton.getGlobalBounds().contains(mouse_position)){
                    MergeSortButton.setFillColor(sf::Color::Yellow);
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)){
                        currentWindow = Windows::sorting;
                        algoToRun = SortingAlgorithm::mergeSort;
                    } 
                }
                else{
                    MergeSortButton.setFillColor(sf::Color::White);
                }



                window.draw(insertionSortButton);
                window.draw(MergeSortButton);
                window.draw(insertionButtonText);
                window.draw(mergeButtonText);
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

void runSortAlgo(sf::RenderWindow& window, SortingAlgorithm algoToRun){

    //click logic
    bool wasLeftPressed = false;
    bool wasRightPressed = false;
    bool algorithmIsDone = false;

    int arrSize = 35;
    std::vector<int> arr(arrSize);
    std::vector<stepStruct> steps;
    initialize(arr, arrSize);
    long long unsigned stepIndex = 0;
    steps.emplace_back(arr, 0, 0);


    if (algoToRun == SortingAlgorithm::insertionSort) {
        insertionSort(arr, arrSize, steps);
    }
    else if (algoToRun == SortingAlgorithm::mergeSort) {
        mergeSort(arr, 0, arrSize - 1, steps);
    }

    stepStruct currentStepStruct = steps.at(stepIndex);

    while(!algorithmIsDone && window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
                return;
            }
        }  
        }
        //fill display with black
        window.clear(sf::Color(0,0,0));
        
        drawRectangles(currentStepStruct, window);

        //display what is set up
        window.display();

        bool isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if(isLeftPressed && !wasLeftPressed){
            if(stepIndex < steps.size() - 1){
                stepIndex++;
            }

        }
        wasLeftPressed = isLeftPressed;

        bool isRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
        if(isRightPressed && !wasRightPressed){
            if(stepIndex >= 1){
                stepIndex--;
            }

        }
        wasRightPressed = isRightPressed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if(stepIndex < steps.size() - 1){
                stepIndex++;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if(stepIndex >= 1){
                stepIndex--;
            }
        }
                

        currentStepStruct = steps.at(stepIndex);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); 

    }
}

/*
 while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        //fill display with black
        window.clear(sf::Color(0,0,0));
        
        drawRectangles(currentStepStruct, window);

        //display what is set up
        window.display();

        bool isLeftPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
        if(isLeftPressed && !wasLeftPressed){
            if(stepIndex < steps.size() - 1){
                stepIndex++;
            }

        }
        wasLeftPressed = isLeftPressed;

        bool isRightPressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
        if(isRightPressed && !wasRightPressed){
            if(stepIndex >= 1){
                stepIndex--;
            }

        }
        wasRightPressed = isRightPressed;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {
            if(stepIndex < steps.size() - 1){
                stepIndex++;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {
            if(stepIndex >= 1){
                stepIndex--;
            }
        }
                

        currentStepStruct = steps.at(stepIndex);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    }
*/