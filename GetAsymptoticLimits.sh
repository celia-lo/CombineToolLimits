#bin/bash
#declare -a multi=("2" "3" "4" "5" "6" "7" "8")
declare -a multi=("5" "6" "7" "8" "9" "10")
#declare -a stmin=("4500")
START=2700
END=8000
STEP=100
for j in "${multi[@]}" 
do
rm OutputLogFiles/asympLimit_mul${j}.log
touch OutputLogFiles/asympLimit_mul${j}.log
	#for i in "${stmin[@]}"
        for i in $(seq $START $STEP $END)
	do
	   if [ $i -lt "2500" ]; then 
		combine -M Asymptotic DataCards/CardFiles_Mul${j}/realistic-counting-experiment_ST${i}_BHMI.txt --setPhysicsModelParameters r=0.1 --setPhysicsModelParameterRanges r=0,500 |grep 'r <' |cut -d "<" -f 2| echo $i `tr '\n' ' '` >> OutputLogFiles/asympLimit_mul${j}.log 
	   elif [ $i -lt "4500" ]; then 
		combine -M Asymptotic DataCards/CardFiles_Mul${j}/realistic-counting-experiment_ST${i}_BHMI.txt --setPhysicsModelParameters r=0.1 --setPhysicsModelParameterRanges r=0,100 |grep 'r <' |cut -d "<" -f 2| echo $i `tr '\n' ' '` >> OutputLogFiles/asympLimit_mul${j}.log 
	   else 
	        combine -M Asymptotic DataCards/CardFiles_Mul${j}/realistic-counting-experiment_ST${i}_BHMI.txt --setPhysicsModelParameters r=0.1 --setPhysicsModelParameterRanges r=0,5 | grep 'r <' |cut -d "<" -f 2| echo $i `tr '\n' ' '` >> OutputLogFiles/asympLimit_mul${j}.log
	   fi
        rm higgsCombineTest.Asymptotic*root
	done
done
