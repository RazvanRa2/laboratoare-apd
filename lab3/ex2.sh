#!/bin/bash
# Write a script that runs a program and redirects its output to a file.
$1 > $1_first.output
# It then runs the same program again 100 times,
# redirects the output to a different file
counter=1
flag=0
while [ $counter -le 1000 ]
do
$1 > $1_$counter.output
# uses the diff application to compare the two files
diff $1_first.output $1_$counter.output > /dev/null 2>&1
# If the diff application finds a difference between two files
# it displays its output and an error message
if [ $? -eq 1 ]; then
  echo "Error: files $1_first.output and $1_$counter.output differ"
  diff $1_first.output $1_$counter.output
  flag=1
  break;
fi
((counter++))
done
# If the script reaches the end, and all files are the same,
# it displays the text "OK"
if [ $flag -eq 0 ]; then
echo "OK"
fi
