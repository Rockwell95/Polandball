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
    for a_file in $a/test\ input/*;
    do
      echo "====================="

      # Finds the expected output file and its corresponding actual output file
      a_file_base="${a_file##*/}"
      output_t=${a_file_base%.*}
      out_file="$output_t"_o.txt
      printf "\nquit\nquit" >> "$a_file"

    done
  done
done
