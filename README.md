# dmxlaser-sfml
Aulatechnik's DMX Laser project using SFML, pigpio and raspberry pi, arduino hardware



*Prerelease v1.0:*
14.June 2023, finally ready for on-site testing. Running on a modified pi OS lite version with openbox, and libsfml-dev.

Compile with:

sfml:
	`g++ test.cpp -o test -lsfml-graphics -lsfml-window -lsfml-system && ./test`

pigpio:
	`g++ -Wall -pthread -o test serialTest2.cpp -lpigpio -lrt && sudo ./test`

complete:
	`g++ -Wall -pthread -o test main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lpigpio -lrt && sudo ./test`
	`g++ -Wall -pthread -o ~/bin/laser-v1.0 ~/dmxlaser-sfml/main/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lpigpio -lrt`

DMX channels:

1 - shutter //not implemented
2 - preset / gobo
3 - red
4 - green
5 - blue
6 - size
7 - infill //not implemented
8 - xpos
9 - ypos
10 - amount
11 - individual rotation
12 - global rotation