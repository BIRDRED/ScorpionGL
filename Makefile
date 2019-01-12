compile:
	@g++ -c Scorpion/*.cpp

link:
	@g++  -I/usr/include -L/usr/lib/x86_64-linux-gnu *.o -lGL -lglut -lGLU -o Scorpion.out

run:
	@./Scorpion.out

glhf:
	@g++ -c Scorpion/*.cpp
	@g++  -I/usr/include -L/usr/lib/x86_64-linux-gnu *.o -lGL -lglut -lGLU -o Scorpion.out
	@./Scorpion.out