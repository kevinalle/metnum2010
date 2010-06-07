FLAGS=`wx-config --cppflags`  `wx-config --libs`
OBJ=MainDialog.o AppModel.o TestResultsDialog.o ShotAnimationDialog.o

all: clean main

main: Mundial2010App.cpp ArqueroSimpleCompleto.cpp $(OBJ) 
	g++ Mundial2010App.cpp $(FLAGS) $(OBJ) -o Mundial2010App
	g++ ArqueroSimpleCompleto.cpp -o Arquero.exe

%.o: %.cpp
	g++ -c  $< $(FLAGS) 

clean: 
	rm -f *.o
	rm -f Mundial2010App
	rm -f Arquero.exe
