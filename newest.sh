#!/bin/bash

SAVEIFS=$IFS
IFS=$(echo -en "\n\b")

  (find . -type f -path "*Assignment\ 1*" -not -path "*actual\ output*" -not -path "*expected\ output*" ! -name 'output.txt' ! -name 'CSCI*' ! -name 'dummy.txt' ! -name 'failedtests.txt' -name '*.txt' ) | while read -r fileLine
  do
    PRE=$(echo $fileLine | grep -o -P '\.(.*?admin|.*?standard)')
    POST=$(echo $fileLine | grep -o '\w*.txt')
    FILEOUT=$(echo "$PRE""/actual output/$POST")
    echo "Evaluating $fileLine..."
    #echo "Creating file $FILEOUT..."
    mkdir -p $PRE"/actual output/"
  while read fileContents
    do
      echo "$fileContents"
      COMMANDS+=($fileContents)
    done < $fileLine
      (for each in "${COMMANDS[@]}"; do echo "$each"; done) | ./Phase2_unix_prototype/Phase2.exe > "$FILEOUT"
      COMMANDS=()
  done

IFS=$SAVEIFS
