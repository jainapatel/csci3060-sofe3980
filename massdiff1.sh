filename=$1
for f in $(ls);do
    difference=$(diff f filename)
    if [ $difference==0 ]
    then
        echo "$f and $filename are the same"
    else
        difference >> log.txt
    fi
done
