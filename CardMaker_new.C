
{

    for(Int_t obji=2; obji<12 ; obji++){

        TString multi;
        stringstream om; om << obji;
        multi=om.str();


        int wd=10;
        cout.setf(ios::fixed);
        //TString inputFile="InputTxtFiles_UL17_OptFit/myOutputFile_UL17_Inclusive"+multi+".txt";
	TString inputFile="InputTxtFiles_Run2_UL17_sphericity_optfit/myOutputFile_Run2_UL17_sphericity_cut_optfit_Inclusive"+multi+".txt";
	TString inputFile_sig="/eos/user/y/ylo/draw_test/output_Inc_N"+multi+".txt";
        //TString inputFile="InputTxtFiles/myOutputFile_dataPreApprove_2016_origin_addHT_SphericityCutP1_fixNormRange_Inclusive"+multi+".txt";
        //TString inputFile="/afs/cern.ch/user/k/kakwok/work/public/Blackhole/CMSSW_7_4_2/src/HiggsAnalysis/CombinedLimit/CombineToolLimits/InputTxtFiles/fullData_preApprove_Inclusive"+multi+".txt";
	//TString inputFile="InputTxtFiles_CeliaData/myOutputFile_origin_Run2016_2016_addHT_bin50GeV_Inclusive"+multi+".txt";
        //TString inputFile="InputTxtFiles/fullData_preApprove_newNorm_Inclusive"+multi+".txt";
        //TString inputFile="InputTxtFiles/2016Fit_Jun23_Inclusive"+multi+".txt";
        ifstream infile(inputFile);
        ifstream myfile(inputFile);
	ifstream infile_sig(inputFile_sig);
        ifstream myfile_sig(inputFile_sig);
        Int_t nlines = 0;
        string line;
	Int_t nlines_sig = 0;
        string line_sig;
        if (myfile.is_open()){while(!myfile.eof()){ getline(myfile,line); nlines++; } myfile.close();}
	if (myfile_sig.is_open()){while(!myfile_sig.eof()){ getline(myfile_sig,line_sig); nlines_sig++; } myfile_sig.close();}
        cout<<"nlines="<<nlines-1<<endl;
        Int_t n = nlines-1;
	Int_t n_sig = nlines_sig-1;
        Int_t STmin[n],ObsN[n];
        Double_t BkgN[n], UBkg_down[n], UBkg_up[n], UBkg_norm[n];
	Int_t STmin_sig[n_sig];
     	Double_t UncMET[n_sig], JuncFlavorQCD[n_sig], JuncRelativeBal[n_sig], JuncHF[n_sig], JuncBBEC1[n_sig], JuncEC2[n_sig], JuncAbsolute[n_sig], JuncAbsolute2018[n_sig], JuncHF2018[n_sig], JuncEC22018[n_sig], JuncRelativeSample2018[n_sig], JuncBBEC12018[n_sig], JuncTotal[n_sig], Jer[n_sig];	
        cout<<"@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<"@  Multiplicity >= "<<multi<<" @"<<endl;
        cout<<"@@@@@@@@@@@@@@@@@@@@@@"<<endl;
        cout<<"----------------------------------------------------------------"<<endl;
        cout<<"STmin     Obs_N    Bkg_N    Unc_Bkg_down    Unc_Bkg_up"<<endl;
        cout<<"----------------------------------------------------------------"<<endl;
        if (infile.is_open() && infile_sig.is_open())
        {
	    cout<<"start infile loop"<<endl;
            TString strBuf;
            //infile >> strBuf >> strBuf >> strBuf >> strBuf >> strBuf >> strBuf >> strBuf >> strBuf >> strBuf >> strBuf;
            infile >> strBuf;

	    for (int iiiiii = 0; iiiiii < 29 + 1; iiiiii++) 
	    infile_sig >> strBuf;
            cout << strBuf << endl;
            for(Int_t i = 0; i < n-1; i++)
	    //for(Int_t i = 2; i < n-1; i++)
            {
		cout<<"===in 11111 loop==="<<endl;
                infile >> STmin[i] >> ObsN[i] >> BkgN[i] >> UBkg_down[i] >> UBkg_up[i] >> UBkg_norm[i];
		infile_sig >> STmin_sig[i] >> UncMET[i] >> JuncFlavorQCD[i] >> JuncRelativeBal[i] >> JuncHF[i] >> JuncBBEC1[i] >> JuncEC2[i] >> JuncAbsolute[i] >> JuncAbsolute2018[i] >> JuncHF2018[i] >> JuncEC22018[i] >> JuncRelativeSample2018[i] >> JuncBBEC12018[i] >> JuncTotal[i] >> Jer[i];
                //infile >> STmin[i] >> strBuf >> ObsN[i] >> strBuf >> BkgN[i] >> strBuf >> UBkg_up[i];
                //UBkg_down[i] = 0.0;
                cout <<setprecision(1)<<STmin[i]<<setprecision(2)<<setw(wd)<< ObsN[i]<<setw(wd)<<BkgN[i]<<setw(wd)<<UBkg_down[i]<<setw(wd)<<UBkg_up[i]<<endl;
		cout <<setprecision(1)<<STmin_sig[i]<<setprecision(2)<<setw(wd)<< UncMET[i]<<endl;
                TString stmin;
                stringstream st; st << STmin[i];
                stmin=st.str();
		//ofstream outfile("DataCards_Sphericity_FixRange/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
		//ofstream outfile("DataCards_UL18/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
		//ofstream outfile("DataCards_UL17_OptFit/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
		ofstream outfile("DataCards_Run2_UL17_sphericity_optfit_lumiUnc/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
		//ofstream outfile("DataCards_2016/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
                //ofstream outfile("DataCards_2016sym/CardFiles_Mul"+multi+"/realistic-counting-experiment_ST"+stmin+"_BHMI.txt");
                if (outfile.is_open())
                {
		    cout<<"====in outfile loop===="<<endl;
                    double jesUOnData=1.05;
                    double pdfOnData=1.06;
                    double jerUOnSig=1.04;
                    double UncOnLumi=1.023;
                    outfile<<"# Simple counting experiment with observed and Background Events for BH Analysis"<<endl;
                    outfile<<"# Simple counting experiment with observed and Background Events for BH Analysis"<<endl;
                    outfile<<"imax 1  number of channels"<<endl;
                    outfile<<"jmax *  number of backgrounds"<<endl;
                    outfile<<"kmax *  number of nuisance parameters (sources of systematical uncertainties)"<<endl;
                    outfile<<"------------"<<endl;
                    outfile<<"# we have just one channel, in which we observe 0 events"<<endl;
                    outfile<<"bin bin1"<<endl;
                    outfile<<"observation "<<ObsN[i]<<endl;
                    //outfile<<"observation "<<BkgN[i]<<endl;
                    outfile<<"------------"<<endl;
                    outfile<<"# now we list the expected events for signal and all backgrounds in that bin"<<endl;
                    outfile<<"# the second 'process' line must have a positive number for backgrounds, and 0 for signal"<<endl;
                    outfile<<"# then we list the independent sources of uncertainties, and give their effect (syst. error)"<<endl;
                    outfile<<"# on each process and bin"<<endl;
                    outfile<<"bin         bin1       bin1"<<endl;
                    outfile<<"process     BH      Background"<<endl;
                    outfile<<"process     0       1"<<endl;
                    outfile<<"rate        1.0     "<<BkgN[i]<<endl;
                    outfile<<"------------"<<endl;
                    outfile<<"lumi       lnN    "<<UncOnLumi<<"   -"<<endl;
                    //outfile<<"jesUp_unc  lnN    "<<jesUOnData<<"    -"<<endl;
                    // outfile<<"pdf_unc    lnN    "<<pdfOnData<<"    -"<<endl;
                    // outfile<<"jerUp_unc  lnN    "<<jerUOnSig<<"    -"<<endl;
                    //outfile<<"xs_Bkg_shp     lnN    -       "<<1.0+sqrt((UBkg_up[i]-1.0)*(UBkg_up[i]-1.0)+(UBkg_norm[i]-1.0)*(UBkg_norm[i]-1.0))<<endl;
                    //outfile<<"xs_Bkg_shp     lnN    -       "<<1.0+max(abs(UBkg_down[i]-1.0),abs(UBkg_up[i]-1.0))<<endl;
                    outfile<<"xs_Bkg_shp     lnN    -       "<<UBkg_down[i]<<"/"<<UBkg_up[i]<<endl;
                    //outfile<<"xs_Bkg_shp     lnN    -       "<<UBkg_up[i]<<endl;
                    outfile<<"xs_Bkg_norm     lnN    -       "<<UBkg_norm[i]<<endl;
		    //outfile<<"UncMET     lnN "<<UncMET[i]<<"    -       -"<<endl;
		    //outfile<<"JuncFlavorQCD    lnN  "<<JuncFlavorQCD[i]<<"    -       -"<<endl;
		    //outfile<<"JuncRelativeBal     lnN "<<JuncRelativeBal[i]<<"    -       -"<<endl;
		    //outfile<<"JuncHF     lnN "<<JuncHF[i]<<"    -       -"<<endl;
		    //outfile<<"JuncBBEC1     lnN "<<JuncBBEC1[i]<<"    -       -"<<endl;
		    //outfile<<"JuncEC2     lnN "<<JuncEC2[i]<<"    -       -"<<endl;
		    //outfile<<"JuncAbsolute    lnN  "<<JuncAbsolute[i]<<"    -       -"<<endl;
		    //outfile<<"JuncAbsolute2018    lnN  "<<JuncAbsolute2018[i]<<"    -       -"<<endl;
		    //outfile<<"JuncHF2018     lnN "<<JuncHF2018[i]<<"    -       -"<<endl;
		    //outfile<<"JuncEC22018    lnN  "<<JuncEC22018[i]<<"    -       -"<<endl;
		    //outfile<<"JuncRelativeSample2018   lnN  "<<JuncRelativeSample2018[i]<<"    -       -"<<endl;
		    //outfile<<"JuncBBEC12018    lnN "<<JuncBBEC12018[i]<<"    -       -"<<endl;
		    //// outfile<<"JuncTotal   lnN  "<<JuncTotal[i]<<"    -       -"<<endl;
		    //outfile<<"Jer    lnN  "<<Jer[i]<<"    -       -"<<endl;

                }
                outfile.close();
		cout<<"end infile loop"<<endl;
            }
            infile.close();
	    infile_sig.close();
        }
    }//Object Multiplicity
}
