#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <pigpio.h> //for serial connection
//#include <unistd.h> //??
#include <iostream> //for cout
#include <cmath>
#include <fstream>  //for file read


int main() {
	
	//declare shit
	int s = -1; 		//serial identifier
	int dmxc = -1;		//counter for serial bytes read
	int dmxSize = 12;	//nr of dmx adresses used
	char dmx[dmxSize];	//char[] for serial buffer
	int dmxo[12] = {0, 0, 0, 0, 0, 128, 128, 0, 0, 128};	//int[] for storing dmx values

	int shutter = 0;	// 0
	int preset = 0;		// 1
	sf::Color color1;	// 2,3,4
	float radius = 0.0;	// 5
	float infill = 0.0;	// 6
	int xpos = 0;		// 7
	int ypos = 0;		// 8
	int amount = 0;		// 9 
	float rot = 0.0;	// 10
	float grot = 0.0;	// 11

	
	//setup serial
	gpioInitialise();
	s = serOpen("/dev/ttyS0", 115200, 0);
	
	
	//setup sfml window at 16:9, 60fps
	// 
	sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); //get desktop resolution
	sf::RenderWindow window(sf::VideoMode(desktop.width, desktop.height), "sfml-app", sf::Style::Fullscreen);
	window.setFramerateLimit(60);
	window.setMouseCursorVisible(false);
	sf::Vector2u windowSize = window.getSize();

	while (window.isOpen()) {
		
		//poll serial input
		
		
		if (serDataAvailable(s) >= dmxSize) {dmxc = serRead(s, dmx, dmxSize);}
		
		if (dmxc > 0) {
			for (int i = 0; i < dmxSize; i++) {
				dmxo[i] = (int)dmx[i];
				//std::cout << dmxo[i] << "\t";
			}
			//std::cout << "\n";
			dmxc = 0;
		}
		
		
		
		//poll dmxval file
		/*
		std::ifstream dmxfile("dmxval.txt");
		if(dmxfile.is_open()){ for(int i = 0; i < 12; i++){dmxfile >> dmxo[i];}}
		dmxfile.close();
		*/
		
		//calculate global values
		shutter = dmxo[0];
		preset = dmxo[1];
		color1 = sf::Color(dmxo[2], dmxo[3], dmxo[4], dmxo[0]); //color
		radius = dmxo[5]/(255.f/windowSize.y)/2;
		infill = dmxo[6]; ///TBA
		xpos = dmxo[7];
		ypos = dmxo[8];
		amount = dmxo[9];
		rot += (dmxo[10] - 128.f) *0.2; // individual rotation factor
		grot += (dmxo[11] - 128.f) *0.2; // global rotation factor
		
		
		
		//poll sf::close, close window on event 'Closed'
		sf::Event wclose;
		while (window.pollEvent(wclose)) {
			if (wclose.type == sf::Event::Closed) {window.close();}
			if (wclose.type == sf::Event::KeyPressed) { if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {window.close();}}
		}
		
	//TBA poll window resize, adjust if neccesary
		
		//clear window with black color
		window.clear(sf::Color::Black);
		
		//start drawing
		if (preset == 0) {
			
		}
		
		if (preset == 1) { // single circle
			sf::CircleShape circle1;
			circle1.setRadius(radius);
			circle1.setPointCount(40);
			circle1.setOrigin(radius, radius);
			circle1.setFillColor(color1);
			circle1.setPosition(xpos/(255.f/(windowSize.x - radius*2))+radius , ypos/(255.f/(windowSize.y - radius*2))+radius);
			circle1.setRotation(rot);
			window.draw(circle1);
			
		}
		
		if (preset == 2) { // single line
			sf::RectangleShape line1(sf::Vector2f(dmxo[5]/(255.f/windowSize.x), 5));
			line1.setOrigin(line1.getSize().x/2, 2.5);
			line1.setFillColor(color1);
			line1.setPosition(xpos/(255.f/windowSize.x) , ypos/(255.f/windowSize.y));
			line1.setRotation(rot);
			window.draw(line1);
		}
		
		if (preset >= 3 && preset <=8) { // single polygon
			sf::CircleShape poly1;
			poly1.setRadius(radius);
			poly1.setPointCount(preset);
			poly1.setOrigin(radius, radius);
			poly1.setFillColor(color1);
			poly1.setPosition(xpos/(255.f/(windowSize.x - radius*2))+radius , ypos/(255.f/(windowSize.y - radius*2))+radius);
			poly1.setRotation(rot);
			window.draw(poly1);
		}

		if (preset == 9) { // duplicated circle circular
			sf::CircleShape circle[amount];
			float deg = 0; // declare globally!
			for (int i = 0; i < amount; i++) {
				deg = 360.f/amount*i+ypos*360/255+grot; // + y - ypos rotates globally
				circle[i].setRadius(radius);
				circle[i].setPointCount(40);
				circle[i].setOrigin(radius, radius);
				circle[i].setFillColor(color1);
				circle[i].setPosition(windowSize.x/2 + cos(deg/180.f*3.1415926535)*2*xpos, windowSize.y/2 + sin(deg/180.f*3.1415926535)*2*xpos); //adjust to window size
				window.draw(circle[i]);
			}
		}

		if (preset == 10) { // duplicated line circular
			sf::RectangleShape line[amount];
			float deg = 0;
			for (int i = 0; i < amount; i++) {
				deg = 360.f/amount*i+ypos*360/255+grot; // + y - ypos rotates globally
				line[i].setSize(sf::Vector2f(dmxo[5]/(255.f/windowSize.x), 5));
				line[i].setOrigin(line[i].getSize().x/2, 2.5);
				line[i].setFillColor(color1);
				line[i].setPosition(windowSize.x/2 + cos(deg/180.f*3.1415926535)*2*xpos, windowSize.y/2 + sin(deg/180.f*3.1415926535)*2*xpos);
				line[i].setRotation(rot);
				window.draw(line[i]);
			}
		}

		if (preset >= 11 && preset <= 16) { // duplicated polygon circular
			sf::CircleShape poly[amount];
			float deg = 0;
			for (int i = 0; i < amount; i++) {
				deg = 360.f/amount*i+ypos*360/255+grot; // + y - ypos rotates globally
				poly[i].setRadius(radius);
				poly[i].setPointCount(preset-8);
				poly[i].setOrigin(radius, radius);
				poly[i].setFillColor(color1);
				poly[i].setPosition(windowSize.x/2 + cos(deg/180.f*3.1415926535)*2*xpos, windowSize.y/2 + sin(deg/180.f*3.1415926535)*2*xpos); //adjust to window size!!
				poly[i].setRotation(rot);
				window.draw(poly[i]);
			}
		}

		if (preset == 17) { // duplicated circle vertical
			sf::CircleShape circle[amount];
			for (int i = 0; i < amount; i++) {
				circle[i].setRadius(radius);
				circle[i].setPointCount(40);
				circle[i].setOrigin(radius, radius);
				circle[i].setFillColor(color1);
				circle[i].setPosition((xpos/(255.f/(windowSize.x - radius*2)))+radius, ypos*windowSize.y/800*(i-(amount-1)/2.f)+windowSize.y/2); //divide by 0 on amount = 1
				window.draw(circle[i]);
			}
		}

		if (preset == 18) { // duplicated line vertical
			sf::RectangleShape line[amount];
			for (int i = 0; i < amount; i++) {
				line[i].setSize(sf::Vector2f(dmxo[5]/(255.f/windowSize.x), 5));
				line[i].setOrigin(line[i].getSize().x/2, 2.5);
				line[i].setFillColor(color1);
				line[i].setPosition((xpos/(255.f/(windowSize.x - radius*2)))+radius, ypos*windowSize.y/800*(i-(amount-1)/2.f)+windowSize.y/2);
				line[i].setRotation(rot);
				window.draw(line[i]);
			}
		}
		
		if (preset >= 19 && preset <= 24) { // duplicated polygon vertical
			sf::CircleShape poly[amount];
			for (int i = 0; i < amount; i++) {
				poly[i].setRadius(radius);
				poly[i].setPointCount(preset-16);
				poly[i].setOrigin(radius, radius);
				poly[i].setFillColor(color1);
				poly[i].setPosition((xpos/(255.f/(windowSize.x - radius*2)))+radius, ypos*windowSize.y/800*(i-(amount-1)/2.f)+windowSize.y/2); //adjust to window size!!
				poly[i].setRotation(rot);
				window.draw(poly[i]);
			}
			
		}
		
		if (preset == 25) { // duplicated circle horizontal
			sf::CircleShape circle[amount];
			for (int i = 0; i < amount; i++) {
				circle[i].setRadius(radius);
				circle[i].setPointCount(40);
				circle[i].setOrigin(radius, radius);
				circle[i].setFillColor(color1);
				circle[i].setPosition(xpos*windowSize.x/1050*(i-(amount-1)/2.f)+windowSize.x/2, (ypos/(255.f/(windowSize.y - radius*2)))+radius); //divide by 0 on amount = 1
				window.draw(circle[i]);
			}
		}

		if (preset == 26) { // duplicated line horizontal
			sf::RectangleShape line[amount];
			for (int i = 0; i < amount; i++) {
				line[i].setSize(sf::Vector2f(dmxo[5]/(255.f/windowSize.x), 5));
				line[i].setOrigin(line[i].getSize().x/2, 2.5);
				line[i].setFillColor(color1);
				line[i].setPosition(xpos*windowSize.x/1050*(i-(amount-1)/2.f)+windowSize.x/2, (ypos/(255.f/(windowSize.y - radius*2)))+radius);
				line[i].setRotation(rot);
				window.draw(line[i]);
			}
		}

		if (preset >= 27 && preset <= 32) { // duplicated polygon horizontal
			sf::CircleShape poly[amount];
			for (int i = 0; i < amount; i++) {
				poly[i].setRadius(radius);
				poly[i].setPointCount(preset-24);
				poly[i].setOrigin(radius, radius);
				poly[i].setFillColor(color1);
				poly[i].setPosition(xpos*windowSize.x/1050*(i-(amount-1)/2.f)+windowSize.x/2, (ypos/(255.f/(windowSize.y - radius*2)))+radius); //divide by 0 on amount = 1
				poly[i].setRotation(rot);
				window.draw(poly[i]);
			}
		}
		
		window.display();
	}
	//serClose(s);
	return 0;
}
