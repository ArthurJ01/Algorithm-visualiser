#include <SFML/Graphics.hpp>
#include <vector>
#include <thread>

#include "sortingVisualiser.hpp"
#include "button.hpp"

extern const sf::Font font;

void runSortAlgo(sf::RenderWindow& window, const SortingAlgorithm algoToRun){

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

    Button returnButton({100.f, 40.f}, {650.f, 535.f}, "Return");

    sf::Text text(font); // a font is required to make a text object
    text.setString("Use arrow keys and m1/m2");
    text.setCharacterSize(24); // in pixels, not points!
    text.setFillColor({240, 240, 240});
    text.setPosition({40.f, 550.f});


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

        //button to return to menu
        sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(window));
        if(returnButton.clicked(mouse_position)){
            algorithmIsDone = true;
        }
        
        //draw everything
        window.draw(returnButton);
        window.draw(text);
        drawRectangles(currentStepStruct, window);

        //controls: arrow left, right, m1, m2
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
                
        window.display();

        currentStepStruct = steps.at(stepIndex);
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); 

    }
}