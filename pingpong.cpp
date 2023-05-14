
#include "main.hpp"



const int ioPin = 1;
const int chCount = 12;

int dmx[chCount];

const int xres = 1920;
const int yres = 1080;



int xoff = 5;
int yoff = 5;



bool getDMXarr(int ioPin, int chCount){

    for(int i = 0; i < chCount; i++){
        

    }

    return true;
}

int getDMXch(int ioPin, int ch){

}




void flipDirectionX(){
    xoff =  xoff * -1;

}

void flipDirectionY(){
    yoff =  yoff * -1;

}



int main()
{

    sf::RenderWindow window(sf::VideoMode(xres, yres), "laser", sf::Style::Fullscreen);

    window.setFramerateLimit(60);
    
    sf::CircleShape shape1(40);
    shape1.setPosition(xres/2, yres/2);

    


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(0, 0, 0, 0));

        window.draw(shape1);
    
        int x = shape1.getPosition().x;
        int y = shape1.getPosition().y;

        if(y == yres - (shape1.getRadius() * 2) || y == 0){
            flipDirectionY();
            shape1.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
        }

        if( x == xres - (shape1.getRadius() * 2)|| x == 0){
            flipDirectionX();
            shape1.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
        }

        shape1.move(xoff, yoff);
        
        window.display();
    }

    return 0;
}