#!/bin/bash

if [ -f failedtests.txt ] ; then
  rm failedtests.txt
fi
# For each command
for d in */;
do
  # For admin and standard in each command
  for a in $d/*/;
  do
    # for each file in the output folders
    for a_file in $a/expected\ output/*;
    do
      echo "====================="

      # Finds the expected output file and its corresponding actual output file
      a_file_base="${a_file##*/}"
      output_t=${a_file_base%.*}
      out_file="$output_t"_o.txt

      # Compares the two files
      DIFF=$(diff $a/expected\ output/$a_file_base $a/actual\ output/$out_file)
      if [[ $DIFF = "" ]]; then
        echo "$a_file_base and $out_file are the same, test passed"
      else
        echo "$a_file_base and $out_file are not the same, test failed"
        printf "$a_file_base\n\n$DIFF\n\n=======================\n" >> failedtests.txt
      fi
    done
  done
done
