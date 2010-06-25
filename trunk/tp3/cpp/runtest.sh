#!/bin/sh
dir=tests/
for f in `ls $dir`
do
	./test < $dir$f > /dev/null
done
