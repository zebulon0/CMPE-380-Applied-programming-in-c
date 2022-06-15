#!/bin/bash

#function parmFun 
#passes 2 parameters and returns nothing
#clearly prints the two input parameters
function parmFun {
   echo "In the function, the passed parameters are:" $1 $2
}

#create a function that returns the number 999
#and takes no passed parameters
function returnNum {
   x=999
   echo $x
}

#create a function globVar that creates var1 and var2
#set them to 'dog' and 'cat'
function globVar {
   echo "Entered globVar" $var1 $var2
   var1="dog"
   var2="cat"
   echo "Leaving globVar" $var1 $var2
}


#body
var1="one"
var2="two"
echo "Calling parmfun with 2 parameters:" $var1 $var2
parmFun $var1 $var2
echo "before calling globVar:" $var1 $var2
globVar
echo "after calling globVar:" $var1 $var2
echo "calling returnNum"
val="$(returnNum)"
echo "The result was:" $val
