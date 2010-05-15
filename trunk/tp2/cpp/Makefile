all: simulador

simulador: simulador.cpp Vector.h Matriz.h
	@echo "Compiling..."
	@g++ -W simulador.cpp -o simulador

test: test.cpp Matriz.h
	g++ -W -o $@ $<

run: simulador planetas.in plot.py
	@echo "Running"
	@./simulador 365 14400 10000 < planetas4.in  | ./plot.py
