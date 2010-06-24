#! /usr/bin/env python
 
import pygame
from pygame.time import Clock
import pygame.gfxdraw
from threading import Thread
import sys
from math import sqrt
import cuadmin
from spline import spline

def poli(coef,x):
	return sum(coef[i]*x**i for i in range(len(coef)))
	
class App:
	screen = pygame.display.set_mode((640, 480))
	running=True
	bg=(170,180,240)
	black=(50,50,50)
	red=(200,50,50)
	mousedown=False
	mousepos=(0,0)
	framecount=0
	dots=[]
	fromfile=0
	
	def __init__(self):
		self.clear()
	
	def clear(self):
		self.screen.fill(self.bg)
	
	def drawdot(self,pos,col=None):
		if not col: col=self.black
		pygame.gfxdraw.aacircle(self.screen,pos[0],pos[1],2,col)
		pygame.gfxdraw.filled_circle(self.screen,pos[0],pos[1],2,col)
	
	def dbg(self,li,col=(0,0,0)):
		for i in range(len(li)):
			self.drawdot((i*10+50,int(li[i]*.2+150)),col)
	
	def do(self,cant=0):
		if len(self.dots)>2:
			xs,ys=zip(*self.dots[:cant or len(self.dots)])
			n=len(xs)
			
			"""xa=cuadmin.cuadmin(range(n),xs,3)
			ya=cuadmin.cuadmin(range(n),ys,3)
			
			self.dbg([poli(xa,t) for t in range(n+10)], col=(255,0,0))
			self.dbg(xs)
			return [(poli(xa,t),poli(ya,t)) for t in range(n+20)]"""
		try:
			Sx=spline(zip(range(n),xs))[-1]
			Sy=spline(zip(range(n),ys))[-1]
			return [(poli(Sx[:-1],t-Sx[-1]),poli(Sy[:-1],t-Sy[-1])) for t in range(n-1,n+20)]
		except: print "ups";return [(0,0),(0,0)]
		else: return [(0,0),(0,0)]
	
	"""
	def do(self,cant=0):
		if len(self.dots)>2:
			xs,ys=zip(*self.dots[:cant or len(self.dots)])
			#print [xs[i]-xs[i-1] for i in range(1,len(xs))]
			dx=[xs[i]-xs[i-1] for i in range(1,len(xs))]
			dy=[ys[i]-ys[i-1] for i in range(1,len(ys))]
			ts=[sqrt((ys[1]-ys[0])**2+(xs[1]-xs[0])**2)]
			n=len(dx)
			for i in range(1,n): ts.append(ts[-1]+sqrt((ys[i]-ys[i-1])**2+(xs[i]-xs[i-1])**2))
			#ts=[sqrt((ys[i]-ys[i-1])**2+(xs[i]-xs[i-1])**2) for i in range(1,len(xs))]
			#self.dbg(dx)
			#cuadrados minimos para x=at+b
			sum2=n*(n-1)*(2*(n-1)+1)/6
			#sum2=sum(t*t for t in ts)
			suma=n*(n-1)/2
			#suma=sum(ts)
			sumxi=sum(i*dx[i] for i in range(n))
			#sumxi=sum(ts[i]*dx[i] for i in range(n))
			sumx=sum(dx)
			sumyi=sum(i*dy[i] for i in range(n))
			#sumyi=sum(ts[i]*dy[i] for i in range(n))
			sumy=sum(dy)
			xa=(suma*sumx-n*sumxi)/float(suma*suma-n*sum2)
			xb=(sumx-xa*suma)/float(n)
			ya=(suma*sumy-n*sumyi)/float(suma*suma-n*sum2)
			yb=(sumy-ya*suma)/float(n)
			#avgdx=sum(dx)/len(dx)
			#avgdy=sum(dy)/len(dy)
			#self.dbg([xa*t+xb for t in ts],(255,0,0))
			#print dx,[xa*t+xb for t in range(len(dx))]
			if cant and cant<len(self.dots): next=[self.dots[cant-1]]
			else: next=[self.dots[-1]]
			for t in range(n,n+40):
			#for t in range(int(ts[-1]),int(ts[-1]+40)):
				#next.append((next[-1][0]+avgdx,next[-1][1]+avgdy))
				next.append((next[-1][0]+xa*t+xb,next[-1][1]+ya*t+yb))
			return next
		else: return [(0,0),(0,0)]
		"""
app=App()

class EventListener(Thread):
	def run(self):
		global app
		while True:
			event=pygame.event.wait()
			if event.type == pygame.QUIT or event.type==pygame.KEYDOWN and event.key==pygame.K_ESCAPE:
				app.running = False
				break
			elif event.type ==  pygame.MOUSEBUTTONDOWN and event.button==1:
				app.mousedown=True
				app.dots=[]
				app.clear()
			elif event.type ==  pygame.MOUSEBUTTONUP and event.button==1:
				app.mousedown=False
				next=app.do()
				pygame.draw.aalines(app.screen,app.red,False,next)
			elif event.type ==  pygame.MOUSEMOTION:
				app.mousepos=event.pos
			elif event.type == pygame.USEREVENT and event.name=="EnterFrame":
				if app.mousedown and app.framecount%3==0:
					app.drawdot(app.mousepos)
					app.dots.append(app.mousepos)
					if len(app.dots)>1: pygame.draw.aaline(app.screen,app.black,app.dots[-2],app.dots[-1])
				app.framecount+=1
			elif event.type == pygame.KEYDOWN and event.key==pygame.K_SPACE and app.fromfile:
				app.fromfile+=1
				app.clear()
				next=app.do(app.fromfile)
				pygame.draw.aalines(app.screen,app.black,False,app.dots[:app.fromfile])
				pygame.draw.aalines(app.screen,app.red,False,next)


EventListener().start()

if len(sys.argv)>1:
	tests=map(lambda x:map(lambda y:float(y)*50+200,x.split()[1:]),open(sys.argv[1]).read().split("\n")[:-1])
	print tests
	app.fromfile=4
	app.dots=tests
	pygame.event.post(pygame.event.Event(pygame.KEYDOWN,key=pygame.K_SPACE))
	#pygame.draw.aalines(app.screen,app.black,False,app.dots)
	#pygame.event.post(pygame.event.Event(pygame.MOUSEBUTTONUP,button=1))

timer=Clock()
while app.running:
	pygame.event.post(pygame.event.Event(pygame.USEREVENT,name="EnterFrame"))
	pygame.display.flip()
	timer.tick(40)
