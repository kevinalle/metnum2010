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

tests=[
'test_recto1.txt',
'test_recto2.txt',
'test_recto3.txt',
'test_comba1.txt',
'test_comba2.txt',
'test_comba3.txt',
'test_comba4.txt',
'test_comba_ruido1.txt',
'test_comba_ruido2.txt',
'test_comba_ruido3.txt',
'test_comba_ruido4.txt']
carpeta='../Tp_3_Mundial2010v1/tests/'
test=5
pnts=map(lambda x: map(lambda y: float(y) if '.' in y else int(y),x.split()),open(carpeta+tests[test]).read().split("\n")[:-1])

n=1
arq=0
lastdir=0
step=.05
view=(0,2.3,2.5) #x,y,width

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
	drawdot((arq,0))
	for t,x,y in pnts[:n+1]: drawdot((x,y),red)
	pygame.display.flip()
	
def do():
	screen.fill(bg)
	global arq,lastdir
	
	#ts,xs,ys=map(list,zip(*pnts[n-3>0 and n-3 or 0:n+1]))
	ts,xs,ys=map(list,zip(*pnts[0:n+1]))
	
	#coef_x=cuadmin(ts+[ts[-1]+1],xs+[arq],4)
	coef_x=cuadmin(ts,xs,3)
	xxs=[poli(coef_x,t) for t in range(n+20)]
	
	#coef_y=cuadmin(ts+[ts[-1]+1],ys+[0],4)
	coef_y=cuadmin(ts,ys,3)
	yys=[poli(coef_y,t) for t in range(n+20)]
	plot(zip(xxs,yys))
	
	t=ts[-1]
	y=ys[-1]
	yans=ys[-2]
	while y>0:
		t+=1
		yans=y
		y=poli(coef_y,t)
		if yans<y: break
	gol=poli(coef_x,t+y/(yans-y))
	if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2: arq+=step; lastdir=1
	elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1: arq-=step; lastdir=-1
	else: lastdir=0
	
	render()

render()
while running:
	event=pygame.event.wait()
	if event.type==pygame.QUIT or (event.type==pygame.KEYDOWN and event.key==pygame.K_ESCAPE):
		running = False
		break
	elif (event.type==pygame.KEYDOWN and event.key==pygame.K_SPACE) or event.type==pygame.MOUSEBUTTONDOWN:
		n+=1
		if n<len(pnts): do()

