#!/bin/sh
dir=tests/
for f in `ls $dir`
do
	#echo $dir$f
	./test < $dir$f > /dev/null
done
