#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//#include <pigpio.h> //for serial connection
//#include <unistd.h> 
#include <iostream> //for cout
#include <cmath>
#include <fstream>


/*
class dmx {
	public:
		const int size = 12;
		int dmxo[size];
		int dmxc = -1;
		
		//write dmx values from char dmx[] to public int dmxo[] 
		void setDmx(char dmx[size]) {
			for (int i = 0; i < size; i ++){
				dmxo[i] = (uint8_t)dmx[i];
			}
			printf("setDmx"); //print success
		}
		
		//print entire dmxo[] in one line
		void printDmx(){
			for (int i = 0; i < size; i ++){
				std::cout << dmxo[i] << "\t";
			}
			std::cout << "\n";
		}
};
* */


int main() {
	
	//declare shit
	int s = -1; 		//serial identifier
	int dmxc = -1;		//counter for serial bytes read
	int dmxSize = 12;	//nr of dmx adresses used
	char dmx[dmxSize];	//char[] for serial buffer
	int dmxo[dmxSize];	//int[] for storing dmx values

	sf::Color color1;
	float rot;
	float radius;
	
	
	/*setup serial
	gpioInitialise();
	s = serOpen("/dev/ttyS0", 115200, 0);
	*/
	
	//setup sfml window at 16:9, 60fps
	//sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); //get desktop resolution
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "sfml-app");
	window.setFramerateLimit(60);
	sf::Vector2u windowSize = window.getSize();
	//sf::Clock clock;
	
	while (window.isOpen()) {
		
		//poll serial input
		/*if (serDataAvailable(s) >= dmxSize) {dmxc = serRead(s, dmx, dmxSize);}
		
		if (dmxc > 0) {
			for (int i = 0; i < dmxSize; i++) {
				dmxo[i] = (int)dmx[i];
				std::cout << dmxo[i] << "\t";
			}
			std::cout << "\n";
			dmxc = 0;
		}*/
		
		//poll dmxval file
		std::ifstream dmxfile("dmxval.txt");
		if(dmxfile.is_open()){ for(int i = 0; i < 12; i++){dmxfile >> dmxo[i];}}
		dmxfile.close();
		
		//calculate global values
		color1 = sf::Color(dmxo[2], dmxo[3], dmxo[4], dmxo[0]); //color
		rot += (dmxo[9] - 128.f) *0.2; //rotation factor
		radius = dmxo[10]/(255.f/windowSize.y)/2;
		
		//poll sf::close, close window on event 'Closed'
		sf::Event wclose;
		while (window.pollEvent(wclose)) {
			if (wclose.type == sf::Event::Closed) {window.close();}
		}
		
	//TBA poll window resize, adjust if neccesary
		
		//clear window with black color
		window.clear(sf::Color::Black);
		
		//start drawing
		if (dmxo[5] == 0) {
			
		}
		if (dmxo[5] == 1) { // single circle
			sf::CircleShape circle1;
			circle1.setRadius(radius);
			circle1.setPointCount(40);
			circle1.setOrigin(circle1.getRadius(), circle1.getRadius());
			circle1.setFillColor(color1);
			circle1.setPosition((dmxo[6]/(255.f/(windowSize.x - circle1.getRadius()*2))+circle1.getRadius()) , (dmxo[7]/(255.f/(windowSize.y  - circle1.getRadius()*2))+circle1.getRadius()));
			window.draw(circle1);
			
		}
		
		if (dmxo[5] == 2) { // single line
			sf::RectangleShape line1(sf::Vector2f(dmxo[10]/(255.f/windowSize.x), 5));
			line1.setOrigin(line1.getSize().x/2, 2.5);
			line1.setFillColor(color1);
			line1.setPosition(dmxo[6]/(255.f/windowSize.x) , dmxo[7]/(255.f/windowSize.y));
			line1.setRotation(rot);
			window.draw(line1);
		}
		
		if (dmxo[5] >= 3 && dmxo[5] <=8) { // single polygon
			sf::CircleShape poly1;
			poly1.setPointCount(dmxo[5]);
			poly1.setRadius(radius);
			poly1.setFillColor(color1);
			poly1.setPosition(dmxo[6]/(255.f/(windowSize.x - poly1.getRadius()*2)) , dmxo[7]/(255.f/(windowSize.y - poly1.getRadius()*2)));
			window.draw(poly1);
			
		}
		if (dmxo[5] == 9) { // duplicated circle circular???
			sf::CircleShape circle[dmxo[8]];
			float deg = 0;
			for (int i = 0; i < dmxo[8]; i++) {
				deg = 360.f/dmxo[8]*i+dmxo[7]*360/255; // + y
				circle[i].setRadius(radius);
				circle[i].setPointCount(40);
				circle[i].setOrigin(radius, radius);
				circle[i].setFillColor(color1);
			circle[i].setPosition(windowSize.x/2 + cos(deg/180.f*3.1415926535)*2*dmxo[6], windowSize.y/2 + sin(deg/180.f*3.1415926535)*2*dmxo[6]);
				window.draw(circle[i]);
			}
		}
		
		if (dmxo[5] == 25) { // duplicated circle horizontal
			sf::CircleShape circle[dmxo[8]];
			for (int i = 0; i < dmxo[8]; i++) {
				circle[i].setRadius(radius);
				circle[i].setPointCount(40);
				circle[i].setOrigin(radius, radius);
				circle[i].setFillColor(color1);
				circle[i].setPosition(dmxo[6]*windowSize.x/1050*(i-(dmxo[8]-1)/2)+windowSize.x/2, (dmxo[7]/(255.f/(windowSize.y - radius*2)))+radius); //divide by 0 on dmxo[8] = 1
				window.draw(circle[i]);
			}
		}
		
		if (dmxo[5] >= 11 && dmxo[5] <= 16) { // duplicated polygon circular
			
		}
		if (dmxo[5] == 17) {
			
		}
		
		
		window.display();
	}
	//serClose(s);
	return 0;
}
