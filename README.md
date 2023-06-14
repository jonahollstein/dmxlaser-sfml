# dmxlaser-sfml
Aulatechnik's DMX Laser project using SFML, pigpio and raspberry pi, arduino hardware


Compile with:

sfml:
	`g++ test.cpp -o test -lsfml-graphics -lsfml-window -lsfml-system && ./test`

pigpio:
	`g++ -Wall -pthread -o test serialTest2.cpp -lpigpio -lrt && sudo ./test`

complete:
	`g++ -Wall -pthread -o test main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lpigpio -lrt && sudo ./test`
	`g++ -Wall -pthread -o ~/bin/laser-v1.0 main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lpigpio -lrt`

DMX channels:

1 - dimmer
2 - shutter
3 - red
4 - green
5 - blue
6 - preset / gobo
7 - xpos
8 - ypos
9 - amount
10 - rotation
11 - size
12 - free


asdsdaf
