#! /usr/bin/env python
 
import pygame
import pygame.gfxdraw
import sys
from spline import spline
from cuadmin import cuadmin

size=(640, 500)
screen = pygame.display.set_mode(size)
running=True
bg=(170,180,240)
black=(50,50,50)
red=(200,50,50)
screen.fill(bg)
pygame.display.flip()

#test='../Tp_3_Mundial2010v1/tests/test_comba1.txt'
#test='../Tp_3_Mundial2010v1/tests/test_comba2.txt'
#test='../Tp_3_Mundial2010v1/tests/test_comba3.txt'
#pnts=map(lambda x: map(lambda y: float(y) if '.' in y else int(y),x.split()),open(test).read().split("\n")[:-1])

n=3
arq=0
step=.05
view=(0,2.3,2.5) #x,y,width

data = map(lambda x: x.split(),(open(sys.argv[1]).read().split("\n")[:-1]))

for d in data:
	print d

def transformation(p):
	s=min(size)/2.
	return map(int,((p[0]-view[0])*s/view[2]+size[0]/2.,(p[1]-view[1])*s/view[2]+size[1]/2.))

def drawdot(pos,col=None):
	pos=transformation(pos)
	if not col: col=(50,50,50)
	pygame.gfxdraw.aacircle(screen,pos[0],pos[1],2,col)
	pygame.gfxdraw.filled_circle(screen,pos[0],pos[1],2,col)

def drawline(fro,to,col=None):
	fro=transformation(fro)
	to=transformation(to)
	if not col: col=(50,50,50)
	pygame.draw.aalines(screen,col,False,(fro,to))

def plot(ps,col=None):
	pst=map(transformation, ps)
	if not col: col=(50,50,50)
	pygame.draw.aalines(screen,col,False,pst)

def poli(coef,x):
	return sum(coef[i]*x**i for i in range(len(coef)))

def setup():
	drawline((-1,0),(1,0),red)

def render():
	setup()
	#drawdot((arq,0))
	#for t,x,y in pnts[:n+1]: drawdot((x,y),red)
	pygame.display.flip()
	
def do():
	
	drawdot([float(data[n][0]) , 0])
	drawdot([float(data[n][1]) , float(data[n][2])])
	
	coef_x = [ float(data[n][3]) , float(data[n][4]) , float(data[n][5]) , float(data[n][6]) ]
	coef_y = [ float(data[n][7]) , float(data[n][8]) , float(data[n][9]) , float(data[n][10]) ]
	xxs=[poli(coef_x,t) for t in range(n+20)]
	yys=[poli(coef_y,t) for t in range(n+20)]
	plot(zip(xxs,yys))
	
	render()

render()
while running:
	event=pygame.event.wait()
	if event.type==pygame.QUIT or (event.type==pygame.KEYDOWN and event.key==pygame.K_ESCAPE):
		running = False
		break
	elif (event.type==pygame.KEYDOWN and event.key==pygame.K_SPACE):
		n+=1
		#if n<len(pnts): do()
		do()

