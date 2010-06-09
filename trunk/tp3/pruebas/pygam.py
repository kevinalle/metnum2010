#! /usr/bin/env python
 
import pygame
from pygame.time import Clock
import pygame.gfxdraw
from threading import Thread
import sys

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
			self.drawdot((i*10+50,int(li[i]*2+150)),col)
	
	def do(self):
		if len(self.dots)>2:
			xs,ys=zip(*self.dots)
			#print [xs[i]-xs[i-1] for i in range(1,len(xs))]
			dx=[xs[i]-xs[i-1] for i in range(1,len(xs))]
			dy=[ys[i]-ys[i-1] for i in range(1,len(ys))]
			self.dbg(dx)
			#cuadrados minimos para x=at+b
			n=len(dx)
			sum2=n*(n-1)*(2*(n-1)+1)/6
			suma=n*(n-1)/2
			sumxi=sum(i*dx[i] for i in range(n))
			sumx=sum(dx)
			sumyi=sum(i*dy[i] for i in range(n))
			sumy=sum(dy)
			xa=(suma*sumx-n*sumxi)/float(suma*suma-n*sum2)
			xb=(sumx-xa*suma)/float(n)
			ya=(suma*sumy-n*sumyi)/float(suma*suma-n*sum2)
			yb=(sumy-ya*suma)/float(n)
			#avgdx=sum(dx)/len(dx)
			#avgdy=sum(dy)/len(dy)
			self.dbg([xa*t+xb for t in range(len(dx))],(255,0,0))
			#print dx,[xa*t+xb for t in range(len(dx))]
			next=[self.dots[-1]]
			for t in range(len(xs),len(xs)+40):
				#next.append((next[-1][0]+avgdx,next[-1][1]+avgdy))
				next.append((next[-1][0]+xa*t+xb,next[-1][1]+ya*t+yb))
			return next
		else: return [(0,0),(0,0)]
app=App()

class EventListener(Thread):
	def run(self):
		global app
		while True:
			event=pygame.event.wait()
			if event.type == pygame.QUIT:
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



EventListener().start()

if len(sys.argv)>1:
	tests=map(lambda x:map(lambda y:float(y)*50+200,x.split()[1:]),open(sys.argv[1]).read().split("\n")[:-1])
	print tests
	app.dots=tests
	pygame.draw.aalines(app.screen,app.black,False,app.dots)
	pygame.event.post(pygame.event.Event(pygame.MOUSEBUTTONUP,button=1))

timer=Clock()
while app.running:
	pygame.event.post(pygame.event.Event(pygame.USEREVENT,name="EnterFrame"))
	pygame.display.flip()
	timer.tick(40)
