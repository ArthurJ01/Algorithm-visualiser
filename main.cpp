#include <SFML/Graphics.hpp>

int main()
{


    std::vector<int> arr(20);
    int arrSize = arr.size();

    for (int i = 0; i < arrSize; i++){
        arr[i] = i + 1;
    }

   

    //create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");
    
    float windowSizeX = window.getSize().x;
    std::vector<sf::RectangleShape> rectangleList(arrSize);

    for (int i = 0; i < arrSize; i++){

        float height = -10.f * arr[i];
        sf::RectangleShape rectangle({10.f, height});
        float currentXPosition = (windowSizeX/arrSize) * i;
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
        window.clear(sf::Color(150,150,150));

        for(sf::RectangleShape rectangle : rectangleList){
            window.draw(rectangle);
        }

        //draw rectangle
        //window.draw(rectangle);

        //display what is set up
        window.display();

    }

}



/*
    sf::RenderWindow window(sf::VideoMode({200, 200}), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.display();
    }
*/