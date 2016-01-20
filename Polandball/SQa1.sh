#!/bin/bash

file=$1;

FILES=*;

if [ -f file.txt ] ; then
rm file.txt
fi

equals="=";

for (( i = 0; i < 20; i++ )); do
	#statements
	equals="$equals=";
done


for f in $FILES
do
	DIFF=$(diff $file $f)
	echo "Processing $f...";
	if [[ $DIFF = "" ]]; then
		#statements
		echo "Files are same!"
	else
		echo "Files are not the same, writing to log file"
		printf "$DIFF\n\n$equals\n" >> file.txt

	fi
done


#echo $fileCount;
