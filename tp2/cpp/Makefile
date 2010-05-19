all: simulador

simulador: simulador.cpp Vector.h Matriz.h
	@echo "Compiling..."
	@g++ -W simulador.cpp -o simulador

test: test.cpp Matriz.h
	g++ -W -o $@ $<

run: simulador planetas4.in plot.py
	@echo "Running"
	@./simulador 300 600 600 < planetas4.in | ./plot.py

CONJ = validacion.in
validar: simulador plot.py $(CONJ)
	@echo "Running"

	@./simulador 30 30 30 < $(CONJ) > validacion_30_1.out
	./plot.py 30 1 < validacion_30_1.out
	@./simulador 30 120 120 < $(CONJ) > validacion_30_4.out
	./plot.py 30 4 < validacion_30_4.out
	@./simulador 30 360 360 < $(CONJ) > validacion_30_12.out
	./plot.py 30 12 < validacion_30_12.out
	@./simulador 30 720 720 < $(CONJ) > validacion_30_24.out
	./plot.py 30 24 < validacion_30_24.out

	@./simulador 365 365 365 < $(CONJ) > validacion_365_1.out
	./plot.py 365 1 < validacion_365_1.out
	@./simulador 365 1460 1460 < $(CONJ) > validacion_365_4.out
	./plot.py 365 4 < validacion_365_4.out
	@./simulador 365 4380 4380 < $(CONJ) > validacion_365_12.out
	./plot.py 365 12 < validacion_365_12.out
	@./simulador 365 8760 8760 < $(CONJ) > validacion_365_24.out
	./plot.py 365 24 < validacion_365_24.out

	@./simulador 1825 1825 1825 < $(CONJ) > validacion_1825_1.out
	./plot.py 1825 1 < validacion_1825_1.out
	@./simulador 1825 7300 7300 < $(CONJ) > validacion_1825_4.out
	./plot.py 1825 4 < validacion_1825_4.out
	@./simulador 1825 21900 21900 < $(CONJ) > validacion_1825_12.out
	./plot.py 1825 12 < validacion_1825_12.out
	@./simulador 1825 43800 43800 < $(CONJ) > validacion_1825_24.out
	./plot.py 1825 24 < validacion_1825_24.out
	
