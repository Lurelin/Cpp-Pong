g++ -c Pong/pong3.cpp -o Pong/pong.o
g++ Pong/pong.o -o Pong/pong -lsfml-graphics -lsfml-window -lsfml-system
./Pong/pong