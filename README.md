# Upper Limits by HiggsCombineTool
Please follow these steps in sequence:
## 1) Preparation of Data Cards
We have input numbers for each multiplicity in a separate file in directory "InputTxtFiles".
Each input file has four columns and following format:
```
STMin    ::   Observed Data   ::   Expected Bkg   ::  Shape Unc
2500 167 153.272 1.11136
2600 132 130.851 1.12925
```
Please delete the first row containing strings, as our code already knows about these four columns. 
Now the code "CardMaker.C" is ready to make the data cards required for the combine tool. You will run:
```
root CardMaker.C
```
It should create data cards for all the multiplicities 2-10, in corresponding directory, for example, "DataCards/CardFiles_Mul4", for all 
the STmin given in the input text files. 
One can also set the range of multiplicities inside "CardMaker.C". Now we are ready to compute asymptotic limits.
## 2) The Asymptotic Limits
We have to compute asymptotic limits first, before the FullCLs. As FullCLs limits are computed around a single point, 
which is guessed from the asymptotic limits. For example, multiplicities 4,5,6 and 7 are starting from STmin = 2700 GeV, 
therfore, we need to tell the code "GetAsymptoticLimits.sh" where to start and where to end along with the step size.  
Let's say we want to compute limits with 100 GeV step size for these multiplicities. Then  
the code structure should contain followings:
```
declare -a multi=("4" "5" "6" "7")
START=2700
END=8000
STEP=100
```
Now we run asymptotic calculator:
```
./GetAsymptoticLimits.sh
```
It should create output log files, for example, "asympLimit_mul4.log", "asympLimit_mul5.log" etc. in the "OutputLogFiles"
directory. The "asympLimit_mul4.log" type of files containing asymptotic limits in format of 7 columns:
```
2700 914.4808 528.0414 687.8232 929.0625 1251.2482 1613.9818
2800 766.9390 449.9438 583.9409 786.2500 1052.6422 1350.6073
2900 593.3474 370.5505 479.1544 643.1250 855.8975 1092.1722
3000 503.3524 315.9613 410.6682 544.6875 720.5505 914.2830
```
Here the first column corresponds to the STmin, and rest of six columns correspond to the observed, -2 sigma, -1 sigma, expected, +1 sigma, +2 sigma
limits respectively. Once we have such files from asymptotic calculator then we are good to proceed for plotting them and move towards the FullCLs limits.

#### Plotting Asymptotic Limits
Now one can easily draw asymptotic limits by using "DrawUpperLimits.C" code. First set the multiplicity
range, 4-7, inside this code as following:
```
for(Int_t obji=4; obji<8 ;obji++)
```
and then run following:
```
root -l -b 'DrawUpperLimits.C("Asymptotic")' 
```
All the plots will be stored in directory "Plots/Asymptotic/". 

## 3). The FullCLs Limits
The FullCLs calculator will use "asympLimit_mul4.log" type of files as an input to make the guess of single points at each STmin value. The code is intelligent enough to define a range of single points based on the asymptotic values. For example, in order to obtain the FullCLs limits for multiplicity 4 case, we will be running:
```
./GetFullCLsLimits.sh N=4
```
Here argument "N=4" could be "multiplicity=4" or anything "asif=4", as the code will extract only number and ignore the string from argument. Normally, on lxplus I use "nohup" bash command or you can also use "screen" because if you close your terminal window it will keep on running on lxplus machine. So we can run:
```
nohup ./GetFullCLsLimits.sh N=4 > n4.log &
```
If something goes wrong, it should be written inside "n4.log". Similarly you can run other mulitiplicities, even in parallel. 
Normally I run couple of multiplicities on one lxplus session, and couple in other session.  
#### Checking progress of FullCLs calculator
As the FullCLs caluculator runs, it will keep on creating root files for a given STmin, therefore, if the root files are increasing
with the time it would mean that limits caluclation is in progress. We can check progress by running:
```
./progress N=4 sec=10
```
It will be printing something like:
```
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
Checking progress of FullCLs calculator for:
*** MULTIPLICITY >= 4, AFTER EVERY 10 SECONDS ***
The number of root files should increase after
a minute or so.
TO QUIT, PLEASE PRESS Crt+c KEYS
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
FullCLs has generated 1 root files
FullCLs has generated 2 root files
FullCLs has generated 2 root files
FullCLs has generated 2 root files
FullCLs has generated 2 root files
FullCLs has generated 3 root files
FullCLs has generated 3 root files
```
You can check progress of calculator for any multiplcity and any "n" seconds.

#### Plotting FullCLs Limits
Once FullsCLs running is finished, it will create an output log file, for example, "FullCLs_Mul4_CL95.log" inside directory "OutputLogFiles". Now one can
easily plot limits by:
Now you can run
```
root -l -b 'DrawUpperLimits.C("FullCLs")'
```
All the plots will be stored in directory "Plots/FullCLs/", for each multiplicity.
#### Starting from a particular STmin or a single STmin calculation 
If lxplus stops your code due to time limitations, and you have FullCLs limits up to 5000 GeV. Now you want to start computing from 5100 GeV STmin.
Then first copy these FullCLs limits upto 5000 GeV in another file, and go to asymptotic limit file "asympLimit_mul4.log" to delete rows upto 5000 GeV.
Run the "GetFullCLsLimits.sh" again, and it will start computing from STmin = 5100 GeV. Similarly, if you want to compute FullCLs limits for a single
STmin value, then you have to provide only one line corresponding to that value in the asymptotic limit file, and run the FullCLs.
