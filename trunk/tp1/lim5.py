fout=open("lim5.csv",'w')
x=-20
while x<=20:
	if x!=0: fout.write("%.2f, %.20f\n"%(x,(-15./x+8)))
	x+=.25
