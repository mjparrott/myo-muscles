all: Exercise.o Exercises.h Exercise.h
	g++ hello-myo.cpp Exercise.o -o myo_muscles -Iinclude -Llib -lmyo32 -lmyo64

Exercise.o: Exercise.cpp
	g++ Exercise.cpp -c 