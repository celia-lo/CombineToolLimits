#bin/bash
multi=`echo Argument: "$1"| grep -o -E '[0-9]+'`
sec=`echo Argument: "$2"| grep -o -E '[0-9]+'`
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
echo "Checking progress of FullCLs calculator for:"
echo "*** MULTIPLICITY >= "${multi}", AFTER EVERY "${sec}" SECONDS ***"
echo "The number of root files should increase after"
echo "a minute or so."
echo "TO QUIT, PLEASE PRESS Crt+c KEYS"
echo "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
while sleep ${sec}; 
do 
  rfile=`ls -lR DataCards/CardFiles_Mul${multi}/higgsCombineTest.HybridNew.mH120.*root | wc -l`
  echo "FullCLs has generated "${rfile}" root files" 
done
