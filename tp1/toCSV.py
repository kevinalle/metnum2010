ofile=open('xn.csv','w'); for line in open('math.out').read().split("\n"): ofile.write(','.join(line.split())+"\n")
