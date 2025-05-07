#include <SFML/Graphics.hpp>

int main()
{
    //create window
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");

    //create rectangle
    sf::RectangleShape rectangle({400.f, 300.f});

    //loop to keep open
    while(window.isOpen()){

        while (const std::optional event = window.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                window.close();
            }
        }
        //fill display with black
        window.clear(sf::Color(150,150,150));

        //draw rectangle
        window.draw(rectangle);

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