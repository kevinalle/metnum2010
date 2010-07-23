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
MET = 3
validar: simulador plot.py $(CONJ)
	@echo "Running"

	@./simulador -m $(MET) -d 30 -dt 1 -or 30 < $(CONJ) > validacion_30_1.out
	./plot.py -q --zoom 2.2 -o validacion_30_1 < validacion_30_1.out
	@./simulador -m $(MET) -d 30 -dt .25 -or 120 < $(CONJ) > validacion_30_4.out
	./plot.py -q --zoom 2.2 -o validacion_30_4 < validacion_30_4.out
	@./simulador -m $(MET) -d 30 -dt .08333 -or 360  < $(CONJ) > validacion_30_12.out
	./plot.py -q --zoom 2.2 -o validacion_30_12 < validacion_30_12.out
	@./simulador -m $(MET) -d 30 -dt .04166 -or 720 < $(CONJ) > validacion_30_24.out
	./plot.py -q --zoom 2.2 -o validacion_30_24 < validacion_30_24.out

	@./simulador -m $(MET) -d 365 -dt 1.0000 -or 365 < $(CONJ) > validacion_365_1.out
	./plot.py -q --zoom 3.5 -o validacion_365_1 < validacion_365_1.out
	@./simulador -m $(MET) -d 365 -dt .25000 -or 1460 < $(CONJ) > validacion_365_4.out
	./plot.py -q --zoom 2.2 -o validacion_365_4 < validacion_365_4.out
	@./simulador -m $(MET) -d 365 -dt .08333 -or 4380 < $(CONJ) > validacion_365_12.out
	./plot.py -q --zoom 2.2 -o validacion_365_12 < validacion_365_12.out
	@./simulador -m $(MET) -d 365 -dt .04166 -or 8760 < $(CONJ) > validacion_365_24.out
	./plot.py -q --zoom 2.2 -o validacion_365_24 < validacion_365_24.out

	@./simulador -m $(MET) -d 1825 -dt 1.0000 -or 1825 < $(CONJ) > validacion_1825_1.out
	./plot.py -q --zoom 5 -o validacion_1825_1 < validacion_1825_1.out
	@./simulador -m $(MET) -d 1825 -dt .25000 -or 7300 < $(CONJ) > validacion_1825_4.out
	./plot.py -q --zoom 3 -o validacion_1825_4 < validacion_1825_4.out
	@./simulador -m $(MET) -d 1825 -dt .08333 -or 21900 < $(CONJ) > validacion_1825_12.out
	./plot.py -q --zoom 2.2 -o validacion_1825_12 < validacion_1825_12.out
	@./simulador -m $(MET) -d 1825 -dt .04166 -or 43800 < $(CONJ) > validacion_1825_24.out
	./plot.py -q --zoom 4 -o validacion_1825_24 < validacion_1825_24.out
	
validar3: simulador plot.py $(CONJ)
	@echo "Running"

	@./simulador -m $(MET) -d 30 -dt .001 -or 120 < $(CONJ) > validacion_30_1000.out
	./plot.py -q --zoom 2.2 -o validacion_30_1000 < validacion_30_1000.out

	@./simulador -m $(MET) -d 365 -dt .001 -or 1460 < $(CONJ) > validacion_365_1000.out
	./plot.py -q --zoom 2.2 -o validacion_365_1000 < validacion_365_1000.out

	@./simulador -m $(MET) -d 1825 -dt .001 -or 7300 < $(CONJ) > validacion_1825_1000.out
	./plot.py -q --zoom 2.2 -o validacion_1825_1000 < validacion_1825_1000.out

CONJ = planetas_.in
MET = 3
validar_error: simulador $(CONJ)
	@echo "Running"

	@./simulador -m 1 -d 1825 -dt 1.0000 -or 1825 < $(CONJ) > error/validacion_m1_1.out
	@./simulador -m 1 -d 1825 -dt .25000 -or 1825 < $(CONJ) > error/validacion_m1_4.out
	@./simulador -m 1 -d 1825 -dt .08333 -or 1825 < $(CONJ) > error/validacion_m1_12.out
	@./simulador -m 1 -d 1825 -dt .04166 -or 1825 < $(CONJ) > error/validacion_m1_24.out

	@./simulador -m 2 -d 1825 -dt 1.0000 -or 1825 < $(CONJ) > error/validacion_m2_1.out
	@./simulador -m 2 -d 1825 -dt .25000 -or 1825 < $(CONJ) > error/validacion_m2_4.out
	@./simulador -m 2 -d 1825 -dt .08333 -or 1825 < $(CONJ) > error/validacion_m2_12.out
	@./simulador -m 2 -d 1825 -dt .04166 -or 1825 < $(CONJ) > error/validacion_m2_24.out

	@./simulador -m 3 -d 1825 -dt 1.0000 -or 1825 < $(CONJ) > error/validacion_m3_1.out
	@./simulador -m 3 -d 1825 -dt .25000 -or 1825 < $(CONJ) > error/validacion_m3_4.out
	@./simulador -m 3 -d 1825 -dt .08333 -or 1825 < $(CONJ) > error/validacion_m3_12.out
	@./simulador -m 3 -d 1825 -dt .04166 -or 1825 < $(CONJ) > error/validacion_m3_24.out
