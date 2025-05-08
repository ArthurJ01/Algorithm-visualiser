#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

int main()
{

    std::vector<int> arr(35);
    int arrSize = arr.size();

    for (int i = 0; i < arrSize; i++){
        arr[i] = i + 1;
    }

    //shuffle array, first get seed, then shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));

    //create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");
    
    float windowSizeX = window.getSize().x;
    std::vector<sf::RectangleShape> rectangleList(arrSize);

    for (int i = 0; i < arrSize; i++){

        float height = -10.f * arr[i];
        sf::RectangleShape rectangle({10.f, height});
        float currentXPosition = (windowSizeX/arrSize) * i + 5.f;
        rectangle.setPosition({currentXPosition, 400.f});
        window.draw(rectangle);
        rectangleList[i] = rectangle;
    }



    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        //fill display with black
        window.clear(sf::Color(0,0,0));

        for(sf::RectangleShape rectangle : rectangleList){
            window.draw(rectangle);
        }

        //display what is set up
        window.display();

    }

}

