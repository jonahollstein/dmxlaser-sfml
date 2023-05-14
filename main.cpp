#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <pigpio.h> //for serial connection
//#include <unistd.h> 
#include <iostream> //for cout


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
	float rot= 0.f;
	
	
	//setup serial
	gpioInitialise();
	s = serOpen("/dev/ttyS0", 115200, 0);
	
	//setup sfml window at 16:9, vsync enabled
	//sf::VideoMode desktop = sf::VideoMode::getDesktopMode(); //get desktop resolution
	sf::RenderWindow window(sf::VideoMode(800, 600), "testing");
	window.setVerticalSyncEnabled(true);
	sf::Vector2u windowSize = window.getSize();
	//sf::Clock clock;
	
	while (window.isOpen()) {
		
		//poll serial input
		if (serDataAvailable(s) >= dmxSize) {dmxc = serRead(s, dmx, dmxSize);}
		
		if (dmxc > 0) {
			for (int i = 0; i < dmxSize; i++) {
				dmxo[i] = (int)dmx[i];
				std::cout << dmxo[i] << "\t";
			}
			std::cout << "\n";
			dmxc = 0;
		}
		
		//set global rotation factor
		rot += (dmxo[9] - 128.f) *0.2;
		
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
			circle1.setRadius(dmxo[10]/(255.f/windowSize.y)/2);
			circle1.setPointCount(40);
			circle1.setOrigin(circle1.getRadius(), circle1.getRadius());
			circle1.setFillColor(sf::Color(dmxo[2], dmxo[3], dmxo[4], dmxo[0]));
			circle1.setPosition((dmxo[6]/(255.f/(windowSize.x - circle1.getRadius()*2))+circle1.getRadius()) , (dmxo[7]/(255.f/(windowSize.y  - circle1.getRadius()*2))+circle1.getRadius()));
			window.draw(circle1);
			
		}
		
		if (dmxo[5] == 2) { // single line
			sf::RectangleShape line1(sf::Vector2f(dmxo[10]/(255.f/windowSize.x), 5));
			line1.setOrigin(line1.getSize().x/2, 2.5);
			line1.setFillColor(sf::Color(dmxo[2], dmxo[3], dmxo[4], dmxo[0]));
			line1.setPosition(dmxo[6]/(255.f/windowSize.x) , dmxo[7]/(255.f/windowSize.y));
			line1.setRotation(rot);
			window.draw(line1);
		}
		
		if (dmxo[5] >= 3 && dmxo[5] <=8) { // single polygon
			sf::CircleShape poly1;
			poly1.setPointCount(dmxo[5]);
			poly1.setRadius(dmxo[10]/(255.f/windowSize.y)/2);
			poly1.setFillColor(sf::Color(dmxo[2], dmxo[3], dmxo[4], dmxo[0]));
			poly1.setPosition(dmxo[6]/(255.f/(windowSize.x - poly1.getRadius()*2)) , dmxo[7]/(255.f/(windowSize.y - poly1.getRadius()*2)));
			window.draw(poly1);
			
		}
		
		if (dmxo[5] == 25) { // duplicated circle horizontal???
			sf::CircleShape circle[dmxo[8]];
			for (int i = 0; i < dmxo[8]; i++) {
				circle[i].setRadius(dmxo[10]/(255.f/windowSize.y)/2);
				circle[i].setPointCount(40);
				circle[i].setOrigin(circle[i].getRadius(), circle[i].getRadius());
				circle[i].setFillColor(sf::Color(dmxo[2], dmxo[3], dmxo[4], dmxo[0]));
				circle[i].setPosition((dmxo[6]/(255.f/(windowSize.x - circle[i].getRadius()*2))+circle[i].getRadius()) + (dmxo[8]*i) , (dmxo[7]/(255.f/(windowSize.y  - circle[i].getRadius()*2))+circle[i].getRadius()));
				window.draw(circle[i]);
			}
		}
		if (dmxo[5] == 10) { // duplicated line circular
			
		}
		if (dmxo[5] >= 11 && dmxo[5] <= 16) { // duplicated polygon circular
			
		}
		if (dmxo[5] == 17) {
			
		}
		
		
		/*
		sf::RectangleShape rectangle(sf::Vector2f(1, 1));
		rectangle.setFillColor(sf::Color(100, 250, 50));
		rectangle.scale(dmxo[0]/(255.f/windowSize.x), dmxo[1]/(255.f/windowSize.y));
		window.draw(rectangle);
		* */
		
		window.display();
	}
	serClose(s);
	return 0;
}
