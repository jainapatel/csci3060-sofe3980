#!/bin/sh
filename=$1

for f in `ls -a *.*`
do
 if diff -q "$f" "$filename"; then
    echo "$f and $filename are the same"
 else
    diff -q "$f" "$filename" >> log.txt
fi
done
