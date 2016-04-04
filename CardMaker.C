 
{


for(Int_t obji=2; obji<9 ; obji++){

TString multi;
stringstream om; om << obji;
multi=om.str();


int wd=10;
cout.setf(ios::fixed);
TString inputFile="InputTxtFiles/NumbersforLimits_N"+multi+"_inc.txt";
ifstream infile(inputFile);
ifstream myfile(inputFile);
Int_t nlines = 0;
string line;
if (myfile.is_open()){while(!myfile.eof()){ getline(myfile,line); nlines++; } myfile.close();}
cout<<"nlines="<<nlines-1<<endl;
Int_t n = nlines-1;
Int_t STmin[n],ObsN[n];
Double_t BkgN[n], UBkg[n];   
cout<<"@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout<<"@  Multiplicity >= "<<multi<<" @"<<endl;
cout<<"@@@@@@@@@@@@@@@@@@@@@@"<<endl;
cout<<"----------------------------------------------------------------"<<endl;
cout<<"STmin     Obs_N	 Bkg_N	 Unc_Bkg "<<endl;
cout<<"----------------------------------------------------------------"<<endl;
if (infile.is_open())
    {
for(Int_t i = 0; i < n; i++)
      {
   infile >> STmin[i] >> ObsN[i] >> BkgN[i] >>  UBkg[i];
   cout <<setprecision(1)<<STmin[i]<<setprecision(2)<<setw(wd)<< ObsN[i]<<setw(wd)<<BkgN[i]<<setw(wd)<<UBkg[i]<<endl;

TString stmin;
stringstream st; st << STmin[i];
stmin=st.str();
ofstream outfile("DataCards/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
if (outfile.is_open())
{
double jesUOnData=1.05;
double pdfOnData=1.06;
double jerUOnBkg=1.04;
double UncOnLumi=1.046;
outfile<<"# Simple counting experiment with observed and Background Events for BH Analysis"<<endl;
outfile<<"# Simple counting experiment with observed and Background Events for BH Analysis"<<endl;
outfile<<"imax 1  number of channels"<<endl;
outfile<<"jmax *  number of backgrounds"<<endl;
outfile<<"kmax *  number of nuisance parameters (sources of systematical uncertainties)"<<endl;
outfile<<"------------"<<endl;
outfile<<"# we have just one channel, in which we observe 0 events"<<endl;
outfile<<"bin 1"<<endl;
outfile<<"observation "<<ObsN[i]<<endl;
outfile<<"------------"<<endl;
outfile<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
outfile<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
outfile<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
outfile<<"# on each process and bin"<<endl;
outfile<<"bin         1       1"<<endl;
outfile<<"process     BH      Background"<<endl;
outfile<<"process     0       1"<<endl;
outfile<<"rate        1.0     "<<BkgN[i]<<endl;
outfile<<"------------"<<endl;
outfile<<"lumi       lnN    "<<UncOnLumi<<"   -"<<endl;
outfile<<"jesUp_unc  lnN    "<<jesUOnData<<"    -"<<endl;
outfile<<"pdf_unc    lnN    "<<pdfOnData<<"    -"<<endl;
outfile<<"xs_Bkg     lnN    -       "<<UBkg[i]<<endl;
outfile<<"jerUp_unc  lnN    -       "<<jerUOnBkg<<endl;
}
outfile.close();
      }
   infile.close();
 }
  }//Object Multiplicity
}
