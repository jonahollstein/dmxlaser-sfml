#include <SFML/Graphics.hpp>


int xoff = 5;
int yoff = 5;

void flipDirectionX(){
    xoff =  xoff * -1;

}

void flipDirectionY(){
    yoff =  yoff * -1;

}


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!", sf::Style::Fullscreen);
    sf::CircleShape shape1(40);
    shape1.setFillColor(sf::Color::Green);
    shape1.setPosition(1920/2, 1080/2);

    window.setFramerateLimit(60);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(10, 10, 50, 255));
        window.draw(shape1);
    
        int x = shape1.getPosition().x;
        int y = shape1.getPosition().y;

        if(y == 1000 || y == 0){
            flipDirectionY();
            shape1.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
        }

        if( x == 1860 || x == 0){
            flipDirectionX();
            shape1.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, 255));
        }

        shape1.move(xoff, yoff);
        
        window.display();
    }

    return 0;
}


/*

#include <iostream>
using namespace std;

int main() {

    cout << "hello" ;

    return 0;
}

*/