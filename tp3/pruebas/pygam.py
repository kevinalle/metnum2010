#! /usr/bin/env python
 
import pygame
from pygame.time import Clock
import pygame.gfxdraw
from threading import Thread

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
	
	def drawdot(self,pos):
		pygame.gfxdraw.aacircle(self.screen,pos[0],pos[1],2,self.black)
		pygame.gfxdraw.filled_circle(self.screen,pos[0],pos[1],2,self.black)
	
	def do(self):
		xs,ys=zip(*self.dots)
		print [xs[i]-xs[i-1] for i in range(1,len(xs))]
		dx=[xs[i]-xs[i-1] for i in range(1,len(xs))]
		dy=[ys[i]-ys[i-1] for i in range(1,len(ys))]
		avgdx=sum(dx)/len(dx)
		avgdy=sum(dy)/len(dy)
		next=[self.dots[-1]]
		for i in range(10):
			next.append((next[-1][0]+avgdx,next[-1][1]+avgdy))
		return next

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
				if app.mousedown and app.framecount%10==0:
					app.drawdot(app.mousepos)
					app.dots.append(app.mousepos)
					if len(app.dots)>1: pygame.draw.aaline(app.screen,app.black,app.dots[-2],app.dots[-1])
				app.framecount+=1



EventListener().start()

timer=Clock()
while app.running:
	pygame.event.post(pygame.event.Event(pygame.USEREVENT,name="EnterFrame"))
	pygame.display.flip()
	timer.tick(40)
