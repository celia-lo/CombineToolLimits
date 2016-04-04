#!/bin/bash
multi="$1"
oDir=/afs/cern.ch/work/a/asaddiqu/HiggsCombinedTool/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/data/BH/OutputLogFiles
CLsLimitFile=FullCLs_Mul${multi}_CL95.log
cat ${oDir}/asympLimit_mul${multi}.log | cut -d " " -f 2- > ${oDir}/tmp_asymp_Mul${multi}_CL95.log
AsymLimitFile=${oDir}/tmp_asymp_Mul${multi}_CL95.log
rm ${oDir}/${CLsLimitFile}
rm higgsCombineTest.*
touch ${oDir}/${CLsLimitFile}
stmin=( $(cut -d ' ' -f 1 "${oDir}/asympLimit_mul${multi}.log") )
declare -a quantile=("0.025" "0.160" "0.500" "0.840" "0.975")
declare -i i
i=0
cat ${AsymLimitFile} | while read LINE 
do
       spLogFile=step_ST${stmin[i]}.log
       DataCard=realistic-counting-experiment_ST${stmin[i]}_BHMI.txt
       GridRootFile=grid_ST${stmin[i]}.root
       WSRootFile=ws_ST${stmin[i]}_BHMI.root
       tmpFile=tmp_FullCLs_ST${stmin[i]}_CL95.log
       rm ${spLogFile}
       rm ${GridRootFile}
       rm ${WSRootFile}
       touch ${spLogFile}
       min=`echo $LINE | tr ' ' '\n' | sort -t. -k1,1n -k2,2n | head -1` 
       max=`echo $LINE | tr ' ' '\n' | sort -t. -k1,1n -k2,2n | tail -1` 
       intS=`echo "${min} - (${min} * 0.1)" | bc`
       intE=`echo "${max} + (${min} * 0.1)" | bc`
       echo "--Proscessing Line   "${LINE}" for STmin ="${stmin[i]}
       echo "intS ="${intS}", intE ="${intE}
       step=`echo "(${intS})*0.2" | bc`
       rmax=`echo "((${intE}*3)/2) + 10" | bc`
       text2workspace.py ${DataCard} -o ${WSRootFile}
       for j in $(seq $intS $step $intE)
       do
           #echo "Single Point = "$j" with rmax ="${rmax}
           combine ${WSRootFile} -M HybridNew --rMin=0 --rMax=${rmax} --freq --fullBToys -s -1 -T 1000 -i 5 --saveToys --saveHybridResult --clsAcc 0 -v9 --singlePoint ${j} >> ${spLogFile}
       done
       
       #mv higgsCombineTest.HybridNew.mH120.*root ${iDir}/
       hadd -f ${GridRootFile} higgsCombineTest.HybridNew.mH120.*root
       rm higgsCombineTest.HybridNew.mH120.*root
       combine -M HybridNew --frequentist --testStat LHC ${DataCard} -H ProfileLikelihood | tail -10 | grep "@ 95% CL" > ${tmpFile}
       for k in "${quantile[@]}"
       do
          #echo "Quantil Processing" ${k}
          combine ${WSRootFile} -M HybridNew --freq --grid=${GridRootFile} -v9 --expectedFromGrid=${k}  | grep "@ 95% CL" >> ${tmpFile}
       done
       cat ${tmpFile} | cut -d "+" -f 1|cut -d "<" -f 2| echo ${stmin[i]} `tr '\n' ' '` >> ${oDir}/${CLsLimitFile}
       rm ${tmpFile}
       rm ${WSRootFile}
       rm ${GridRootFile}
       rm ${spLogFile}
       rm higgsCombineTest.HybridNew.mH120*.root
       i=i+1
done #stmin loop ends here
rm ${oDir}/tmp_asymp_Mul${multi}_CL95.log
