#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

void insertionSort(std::vector<int> &arr, int n);

/*
First set up an array, shuffle it and then create window and a list of rectangles of same size as array (array is vector)

Then we come to the for loop,
    Set up a rectangle with height depending on value in array at that position
    Add this to our rectangleList
    This is just initial setup

In while loop, sort array (fix pause after every iteration)

Then we redraw all rectangles with new sizes (maybe not performant but very flexible)
    Rectangle sizes are set to be equal to array value at same position
    This means we just have to focus on sorting array in different ways and the rectangles will always update properly

*/


int main()
{

    float rectangleSizeX = 10.f;

    std::vector<int> arr(35);
    int arrSize = arr.size();

    for (int i = 0; i < arrSize; i++){
        arr[i] = i + 1;
    }

    //shuffle array, first get seed, then shuffle
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));

    //create window, get size (size should probably be taken in main every frame)
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Algorithm visualiser");
    float windowSizeX = window.getSize().x;

    std::vector<sf::RectangleShape> rectangleList(arrSize);

    for (int i = 0; i < arrSize; i++){

        float height = -10.f * arr[i];
        sf::RectangleShape rectangle({rectangleSizeX, height});
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

        insertionSort(arr, arrSize);
        
        for (int i = 0; i < arrSize; i++){

            float height = -10.f * arr[i];
            sf::RectangleShape rectangle = rectangleList[i];
            rectangle.setSize({rectangleSizeX, height});
            float currentXPosition = (windowSizeX/arrSize) * i + 5.f;
            rectangle.setPosition({currentXPosition, 400.f});
            window.draw(rectangle);
        }

        //display what is set up
        window.display();
    }
}


bool insertionSortStep(std::vector<int>& arr, int arraySize, int& i, int& j){

if(i >= arraySize){
    return true;
}

int key = arr[i];
    if(j >= 0 && arr[j]>key){
        arr[j + 1] = arr[j];
        j = j -1;
    }
    if(j <= 0 && i < arraySize){
        j = i -1;
    }
    arr[j + 1] = key;
    i++;

    return false;
}

void insertionSort(std::vector<int>& arr, int n)
{
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
