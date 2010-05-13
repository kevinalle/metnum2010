all: simulador

simulador: simulador.cpp Vector.h Matriz.h
	@echo "Compiling..."
	@g++ simulador.cpp -o simulador

test: test.cpp Matriz.h
	g++ -W -o $@ $<

run: simulador
	@echo "Running"
	@./simulador

