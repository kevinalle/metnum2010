#!/usr/bin/env python
from sys import stdin,argv
from math import sqrt

def prueba(m,p):
	nombre = "error/validacion_"+"m"+str(m)+"_"+str(p)+".out"
	f = open(nombre,'r')
	print "abriendo",nombre

	cuerpos=f.readline().split()
	N=len(cuerpos)
	posiciones=map(list,zip(*[map(eval,l.split()) for l in f.read().strip().split("\n")]))[:N]

	for c in range(len(cuerpos)):

		nombre = "error/error_"+cuerpos[c]+"_m"+str(m)+"_"+str(p)+".out"
		print "	generando",nombre
		
		f1 = open("horizon/horizon_results_"+cuerpos[c],'r')
		f_out = open(nombre,'w')
		f_out.write("metodo_"+str(m)+"_dt_1:"+str(p)+'\n')
		
		aux_NASA = [ map(eval,l.split()) for l in f1.read().strip().split("\n") ]
		posiciones_NASA = [ aux_NASA[i] for i in range(0,len(aux_NASA),2) ]
		#posiciones_NASA = aux_NASA
		for i in range(min(len(posiciones[c]),len(posiciones_NASA))):
			#print posiciones_NASA[i],posiciones[c][i]
			errores = [ posiciones_NASA[i][j]-posiciones[c][i][j] for j in range(3) ]
			error = sqrt( errores[0]*errores[0] + errores[1]*errores[1] + errores[2]*errores[2] )
			#f_out.write(' '.join(error) + '\n')
			f_out.write(str(error) + '\n')

		f1.close()
		f_out.close()

	f.close()

metodos = [1,2]
precisiones = [6,24]

for m in metodos:
	for p in precisiones:
		prueba(m,p)
