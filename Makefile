all: Exercise.o UI.o Mouse.o DataCollector.o DataCollector.h Exercises.h Exercise.h Mouse.h
	g++ hello-myo.cpp Exercise.o UI.o Mouse.o DataCollector.o -o myo_muscles -Iinclude -Llib -lmyo32 -lmyo64 -lallegro-5.0.10-mt -lallegro_font-5.0.10-mt -lallegro_ttf-5.0.10-mt

Exercise.o: Exercise.cpp Exercise.h
	g++ Exercise.cpp -c 

UI.o: UI.cpp UI.h
	g++ UI.cpp -c -Iinclude

Mouse.o: Mouse.cpp Mouse.h
	g++ Mouse.cpp -c

DataCollector.o: DataCollector.cpp DataCollector.h
	g++ DataCollector.cpp -c -Iinclude