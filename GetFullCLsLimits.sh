#!/bin/bash
multi=`echo Argument: "$1"| grep -o -E '[0-9]+'`
iDir=/afs/cern.ch/work/a/asaddiqu/HiggsCombinedTool/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/data/BH/DataCards/CardFiles_Mul${multi}
sDir=/afs/cern.ch/work/a/asaddiqu/HiggsCombinedTool/CMSSW_7_1_5/src/HiggsAnalysis/CombinedLimit/data/BH/FullCLs
cp ${sDir}/FullCLsLimits.sh ${iDir}/
cd ${iDir}/
./FullCLsLimits.sh ${multi}
rm FullCLsLimits.sh
