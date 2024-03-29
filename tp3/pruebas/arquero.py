#! /usr/bin/env python
 
import pygame
import pygame.gfxdraw
import sys
from spline import spline
from cuadmin import cuadmin

pygame.font.init()
size=(640, 500)
screen = pygame.display.set_mode(size)
running=True
bg=(170,180,240)
black=(50,50,50)
red=(200,50,50)
green=(50,200,50)
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
'test_comba_ruido4.txt',
'test_corner1.txt',
'test_corner2.txt',
'test_corner3.txt',
'test_ruido1.txt',
'test_ruido2.txt',
'test_ruido3.txt',
'test_ruido4.txt']
carpeta='../Tp_3_Mundial2010v1/tests/'


view=(0,2.3,2.5) #x,y,width
step=.05
tst=0
def init(tst):
	global n,arq,lastdir,pnts,test
	test=tst
	n=1
	arq=0
	lastdir=0
	pnts=map(lambda x: map(lambda y: float(y) if '.' in y else int(y),x.split()),open(carpeta+tests[test]).read().split("\n")[:-1])
init(tst)

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

def text(txt,size=20,pos=(0,0),color=None):
	if not color: color=(50,50,50)
	font=pygame.font.Font(None,size).render(txt,True,color)
	screen.blit(font,(pos[0]-font.get_width()/2.,pos[1]-font.get_height()/2.))

def poli(coef,x):
	return sum(coef[i]*x**i for i in range(len(coef)))

def setup():
	drawline((-1,0),(1,0),red)

def render():
	setup()
	drawdot((arq,0))
	for t,x,y in pnts[:n+1]: drawdot((x,y),red)
	pygame.display.flip()


def metodo_spline(ts,xs,ys):
	global arq,lastdir
	cx=cuadmin(ts,xs,3)
	cy=cuadmin(ts,ys,3)
	xs=[poli(cx,t) for t in ts]
	ys=[poli(cy,t) for t in ts]
	plot(zip([poli(cx,t) for t in ts+range(ts[-1],ts[-1]+40)], [poli(cy,t) for t in ts+range(ts[-1],ts[-1]+40)]),red)
	
	Sx=spline(zip(ts,xs))[-2]
	Sy=spline(zip(ts,ys))[-2]
	plot([(poli(Sx[:-1],t-Sx[-1]),poli(Sy[:-1],t-Sy[-1])) for t in range(n+40)])
	
	t=ts[-1]
	y=ys[-1]
	yans=ys[-2]
	while y>0 and t<200:
		t+=1
		yans=y
		y=poli(Sy[:-1],t-Sy[-1])
		#if yans<y: text("whops",pos=(100,100)); break;
	gol=poli(Sx[:-1],t-Sx[-1]+y/(yans-y))
	
	if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2: arq+=step; lastdir=1
	elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1: arq-=step; lastdir=-1
	else: lastdir=0

def metodo_CM(ts,xs,ys):
	global arq,lastdir
	cx=cuadmin(ts,xs,3)
	cy=cuadmin(ts,ys,3)
	xs=[poli(cx,t) for t in ts]
	ys=[poli(cy,t) for t in ts]
	plot(zip([poli(cx,t) for t in ts+range(ts[-1],ts[-1]+40)], [poli(cy,t) for t in ts+range(ts[-1],ts[-1]+40)]),red)
	
	t=ts[-1]
	y=ys[-1]
	yans=ys[-2]
	while y>0 and t<200:
		t+=1
		yans=y
		y=poli(cy,t)
		#if yans<y: text("whops",pos=(100,100)); break;
	gol=poli(cx,t)#+y/(yans-y))
	if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2: arq+=step; lastdir=1
	elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1: arq-=step; lastdir=-1
	else: lastdir=0

def metodo_CM2(ts,xs,ys):
	global arq,lastdir
	#eta=ys[0]/(sum(ys[i]-ys[i+1] for i in range(len(ys)-1))/(len(ys)-1))
	cxa=cuadmin(ts,xs,4)
	cya=cuadmin(ts,ys,4)
	xs=[poli(cxa,t) for t in ts]
	ys=[poli(cya,t) for t in ts]
	plot(zip(xs,ys),(50,200,50))
	
	cx=cuadmin(ts[-6:],xs[-6:],2)
	cy=cuadmin(ts[-6:],ys[-6:],2)
	plot([(poli(cx,t),poli(cy,t)) for t in ts[-5:]+range(ts[-1],ts[-1]+40)],red)
	
	t=ts[-1]
	y=ys[-1]
	yans=ys[-2]
	while y>0 and t<200:
		t+=1
		yans=y
		y=poli(cy,t)
	gol=poli(cx,t+y/(yans-y))
	if t-n<50:
		if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2: arq+=step; lastdir=1
		elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1: arq-=step; lastdir=-1
		else: lastdir=0
	elif abs(arq)>step:
		arq+=step*(arq/abs(arq))


def goto(gol):
	global arq,lastdir
	if gol>arq+step/2 and lastdir!=-1 and arq<1-step/2:
		arq+=step
		lastdir=1
	elif gol<arq-step/2 and lastdir!=1 and arq>step/2-1:
		arq-=step
		lastdir=-1
	else:
		lastdir=0

def metodo_spline2(ts,xs,ys):
	global arq,lastdir
	Sx=spline(zip(ts,xs))[-2]
	Sy=spline(zip(ts,ys))[-2]
	
	plot([(poli(Sx[:-1],t-Sx[-1]),poli(Sy[:-1],t-Sy[-1])) for t in range(n+40)])

	t=ts[-1]
	y=ys[-1]
	yans=ys[-2]
	while y>0 and t<200:
		t+=1
		yans=y
		y=poli(Sy[:-1],t-Sy[-1])
	gol=poli(Sx[:-1],t-Sx[-1]+y/(yans-y))
	goto(gol)

def metodo_12(ts,xs,ys):
	global arq,lastdir
	if len(ts)>=4:
		cxa=cuadmin(ts,xs,6)
		cya=cuadmin(ts,ys,6)
		ts=ts[-6:]
		xs=[poli(cxa,t) for t in ts]
		ys=[poli(cya,t) for t in ts]
		plot([(poli(cxa,t),poli(cya,t)) for t in range(ts[-1]+4)],red)
		
		cx=cuadmin(ts,xs,2)
		cy=cuadmin(ts,ys,2)
		plot([(poli(cx,t),poli(cy,t)) for t in range(ts[-1]+40)],(50,50,200))
		xs=[poli(cx,t) for t in ts]
		ys=[poli(cy,t) for t in ts]
		#metodo_spline2(ts,xs,ys)
		t=ts[-1]
		y=ys[-1]
		yans=ys[-2]
		while y>0 and t<200:
			t+=1
			yans=y
			y=poli(cy,t)
		gol=poli(cx,t+y/(yans-y))
		goto(gol)
		
	elif len(ts)>1:
		cx=cuadmin(ts,xs,1)
		cy=cuadmin(ts,ys,1)
		t=ts[-1]
		y=ys[-1]
		yans=ys[-2]
		while y>0 and t<200:
			t+=1
			yans=y
			y=poli(cy,t)
		gol=poli(cx,t+y/(yans-y))
		goto(gol)

	else: lastdir=0

def do():
	screen.fill(bg)
	global arq,lastdir
	
	#ts,xs,ys=map(list,zip(*pnts[n-3>0 and n-3 or 0:n+1]))
	ts,xs,ys=map(list,zip(*pnts[0:n+1]))
	
	#metodo_spline(ts,xs,ys)
	#metodo_CM(ts,xs,ys)
	#metodo_CM2(ts,xs,ys)
	metodo_12(ts,xs,ys)
	"""#coef_x=cuadmin(ts+[ts[-1]+1],xs+[arq],4)
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
	else: lastdir=0"""
	
	if pnts[n][2]<=0.:
		if abs(arq-pnts[n][1])<step: text("atajada :)",size=100,pos=map(lambda x:x/2.,size))
		else: text("gool!",size=200,pos=map(lambda x:x/2.,size))
	
	render()

render()
while running:
	event=pygame.event.wait()
	if event.type==pygame.QUIT or (event.type==pygame.KEYDOWN and event.key==pygame.K_ESCAPE):
		pygame.quit()
		running = False
		break
	elif (event.type==pygame.KEYDOWN and event.key==pygame.K_SPACE) or event.type==pygame.MOUSEBUTTONDOWN:
		n+=1
		if n<len(pnts): do()
	elif (event.type==pygame.KEYDOWN and event.key==pygame.K_RETURN):
		tst=(tst+1)%len(tests)
		init(tst)
		screen.fill(bg)
		text(tests[tst],pos=(100,20))
		render()
