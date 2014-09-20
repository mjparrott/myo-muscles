all:
	g++ hello-myo.cpp -o myo_muscles -Iinclude -Llib -lmyo32 -lmyo64
