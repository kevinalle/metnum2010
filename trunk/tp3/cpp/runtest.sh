#!/bin/sh
for f in `ls tests/`
do
	./test < tests/$f > /dev/null
done
