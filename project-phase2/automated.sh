#!/bin/sh


expected=../csci3060-sofe3980/project-phase2/Inputs
actual=../csci3060-sofe3980/project-phase2/Inputs_actual

cd $actual


for f in 'ls -a *.*'
  do

    echo "Running test: $f"
    #run all the input files on the executable program file
    ./build/banksystem "../Accountsfile.txt" "../input-output file/$t/Input/$f.txt"


      for i in ../../project-phase2/Inputs/$t/*.txt

        do
          cat "$i" | ./console > outputs_log.out
          echo "${i%.txt}"
          #if the expected terminal output is different than actual -> write to the terminal_outlog.txt
          diff -q outputs_log.out "${i%.txt}" >> terminal_outlog.txt
          #if the expected transaction_log is different than actual -> write to the trans_log.txt
          diff -q transaction_log.txt "${i%.txt}" >> trans_log.txt
      done
done
 
