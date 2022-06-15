#!/bin/bash
#----------------------------------------------------------------------------
# Simple command exercises
# student copy
#----------------------------------------------------------------------------

# Create a 2 word variable and print it out
x="dog cat"
echo "The variable is" $x

# Read a number from the command line
echo "Enter a number"
read number
echo "The number is" $number

# Use the number in a simple if statement
#if > 3
#print number is greater than 3
#else
#print number is less than or equal to 
if [ $number -gt 3 ]; then
   echo $number "is greater than 3"
else
   echo $number "is less than or equal to 3"
fi

# Do some math with the number
number1=$((number+2))
echo $number "plus 2 is" $number1

# Do some math with the number using the alternative method
number1=$number
let number1+=1
echo $number "plus 1 is" $number1


# Count from 0 to 3
i=0
while [ $i -lt 3 ]; do
   let i+=1
   echo $i
done

# Cycle through a list
l="one two three"
for item in $l
do
   echo "item processed:" $item
done


# Verify string comparison functions 
echo "Enter dog (or not)"
read word
if [ $word == "dog" ]; then
   echo "dog ==" $word
else
   echo "dog !=" $word
fi


# Exercise the case statement
echo "Enter a number [1-3]"
read x
case $x in
   1)
      echo "A one was entered"
   ;;

   2)
      echo "A two was entered"
   ;;

   3)
      echo "A three was entered"
   ;;

   *)
      echo "Entered 'other'"
   ;;
esac

# Get and print the current directory
directory=`ls`
echo "Current directory:" $directory














