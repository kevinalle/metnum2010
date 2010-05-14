all: simulador

simulador: simulador.cpp Vector.h Matriz.h
	@echo "Compiling..."
	@g++ simulador.cpp -o simulador

test: test.cpp Matriz.h
	g++ -W -o $@ $<

run: simulador planetas.in plot.py
	@echo "Running"
	@./simulador < planetas.in 2> sim.log | ./plot.py 4
