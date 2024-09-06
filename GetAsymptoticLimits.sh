#bin/bash
#declare -a multi=("2" "3" "4" "5" "6" "7" "8")
#declare -a multi=("3" "4" "5" "6" "7" "8" "9" "10")
declare -a multi=("7" "8")
#declare -a multi=("3" "4" "5" "6" "7" "8")
#declare -a stmin=("4500")
START=4300
END=8000
STEP=100
for j in "${multi[@]}" 
do
rm OutputLogFiles_Run2_UL17_sphericity_optfit_lumiUnc/asympLimit_mul${j}.log
touch OutputLogFiles_Run2_UL17_sphericity_optfit_lumiUnc/asympLimit_mul${j}.log
	#for i in "${stmin[@]}"
        for i in $(seq $START $STEP $END)
	do
	   if [ $i -lt "2500" ]; then 
		combine -M AsymptoticLimits DataCards_Run2_UL17_sphericity_optfit_lumiUnc/CardFiles_Mul${j}/realistic-counting-experiment_ST${i}_BHMI.txt --setParameters r=0.1 --setParameterRanges r=0,500 --run blind |grep 'r <' |cut -d "<" -f 2| echo $i `tr '\n' ' '`  | tee  OutputLogFiles_Run2_UL17_sphericity_optfit_lumiUnc/asympLimit_mul${j}.log 
	   elif [ $i -lt "4500" ]; then 
		combine -M AsymptoticLimits DataCards_Run2_UL17_sphericity_optfit_lumiUnc/CardFiles_Mul${j}/realistic-counting-experiment_ST${i}_BHMI.txt --setParameters r=0.1 --setParameterRanges r=0,100 --run blind |grep 'r <' |cut -d "<" -f 2| echo $i `tr '\n' ' '`  | tee  OutputLogFiles_Run2_UL17_sphericity_optfit_lumiUnc/asympLimit_mul${j}.log 
	   else 
	        combine -M AsymptoticLimits DataCards_Run2_UL17_sphericity_optfit_lumiUnc/CardFiles_Mul${j}/realistic-counting-experiment_ST${i}_BHMI.txt --setParameters r=0.1 --setParameterRanges r=0,5 --run blind | grep 'r <' |cut -d "<" -f 2| echo $i `tr '\n' ' '`  | tee  OutputLogFiles_Run2_UL17_sphericity_optfit_lumiUnc/asympLimit_mul${j}.log
	   fi
        rm higgsCombineTest.Asymptotic*root
	done
done
