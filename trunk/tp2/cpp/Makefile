all: simulador

simulador: simulador.cpp Vector.h Matriz.h
	@echo "Compiling..."
	@g++ -W simulador.cpp -o simulador

test: test.cpp Matriz.h
	g++ -W -o $@ $<

run: simulador plot.py horizon/100612.in
	@echo "Running"
	@#@./simulador -d 365 -dt .05 -m 1 -t 3 -s Misil < horizon/100612.in > lastrun.out
	@./simulador -d 1200 -dt .05 -m 1 -t 3 -s Misil -or 5000 < horizon/100612.in > lastrun.out
	@make plot

plot: plot.py lastrun.out
	./plot.py --sinnombres --zoom all --center -1 < lastrun.out
	./plot.py --sinnombres --zoom 2.2 --center -1 < lastrun.out
	./plot.py --sinnombres --zoom .2  --center -1 < lastrun.out

mindist: simulador horizon/100612.in
	./simulador -d 365 -dt .05 -m 1 -t 3 -s MinDist < horizon/100612.in > mindist.out

CONJ = validacion.in
validar: simulador plot.py $(CONJ)
	@echo "Running"

	@./simulador 30 30 30 < $(CONJ) > validacion_30_1.out
	./plot.py -q -o validacion_30_1 < validacion_30_1.out
	@./simulador 30 120 120 < $(CONJ) > validacion_30_4.out
	./plot.py -q -o validacion_30_4 < validacion_30_4.out
	@./simulador 30 360 360 < $(CONJ) > validacion_30_12.out
	./plot.py -q -o validacion_30_12 < validacion_30_12.out
	@./simulador 30 720 720 < $(CONJ) > validacion_30_24.out
	./plot.py -q -o validacion_30_24 < validacion_30_24.out

	@./simulador 365 365 365 < $(CONJ) > validacion_365_1.out
	./plot.py -q -o validacion_365_1 < validacion_365_1.out
	@./simulador 365 1460 1460 < $(CONJ) > validacion_365_4.out
	./plot.py -q -o validacion_365_4 < validacion_365_4.out
	@./simulador 365 4380 4380 < $(CONJ) > validacion_365_12.out
	./plot.py -q -o validacion_365_12 < validacion_365_12.out
	@./simulador 365 8760 8760 < $(CONJ) > validacion_365_24.out
	./plot.py -q -o validacion_365_24 < validacion_365_24.out

	@./simulador 1825 1825 1825 < $(CONJ) > validacion_1825_1.out
	./plot.py -q -o validacion_1825_1 < validacion_1825_1.out
	@./simulador 1825 7300 7300 < $(CONJ) > validacion_1825_4.out
	./plot.py -q -o validacion_1825_4 < validacion_1825_4.out
	@./simulador 1825 21900 21900 < $(CONJ) > validacion_1825_12.out
	./plot.py -q -o validacion_1825_12 < validacion_1825_12.out
	@./simulador 1825 43800 43800 < $(CONJ) > validacion_1825_24.out
	./plot.py -q -o validacion_1825_24 < validacion_1825_24.out
	
