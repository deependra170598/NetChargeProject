//#include <iostream>
//#include <cstdio
int readfile(TString filename="/mnt/home14/ankita/meanptNov2019/v2/MeanpT_7TeV_CR_0_RH_off.root",
		 TString tree="theTree",const Int_t arr_dim=500)
{
  //using namespace std;
  freopen("output.txt", "w", stdout);
  freopen("error.txt","w", stderr);

        cout<<tree<<endl;
	TFile* file=new TFile(filename,"read");
	TTree* pytree1=(TTree*)file->Get(tree);

	
	TH1I* NetCharge_Hist= new TH1I("NetHist","Netcharge, |eta|<0.8",1000,-60,60);
	
	TH1I* Mult_Hist=new TH1I("MultHist","Multiplicity, |eta|_V0M",1000,0,500);
	TH2I* Auto_correlation=new TH2I("auto_corre","Auto_correlation, |eta|_V0M vs |eta|<0.8",1000,0,500,1000,0,500);

		
	Int_t nEvents;
	nEvents=pytree1->GetEntries();
	cout<<"Total number of events="<<nEvents<<endl;

	// *******************Event Loop********************
	for(Int_t j=0;j<nEvents;j++){
	  
	Int_t ntrack;
	Int_t pid[arr_dim];
	Double_t eta[arr_dim];
	Double_t pT[arr_dim];
	pytree1->SetBranchAddress("ntrack",&ntrack);
	pytree1->SetBranchAddress("PID",&pid);
	pytree1->SetBranchAddress("Eta",&eta);
	pytree1->SetBranchAddress("pT",&pT);
	pytree1->GetEntry(j);

	if(j%10000==0) cout<<"i_th of events="<<j<<endl;//"\n"<<"total number of tracks="<<ntrack<<endl;

	Int_t number_of_pcharge=0;
	Int_t number_of_ncharge=0;
	Int_t iMult=0;
	Int_t iMult2=0;

//*************particle loop*************************
	//cout<<"i"<<" eta "<<" phi "<<" pid "<<" pT" <<" rap "<<endl;
	for(Int_t i=0; i<ntrack;i++){
		//cout<<i<<" "<<eta[i]<<" "<<phi[i]<<" "<<pid[i]<<" "<<pT[i]<<" "<<rap[i]<<endl;

		// eta and pT cuts for analysis applied here.
		if(TMath::Abs(eta[i])<0.8 && pT[i]>0.05)
		{
			Int_t charge=TMath::Abs(pid[i])/pid[i];
			if(charge==-1) number_of_ncharge++;
			if(charge==+1) number_of_pcharge++;
		}

		// eta and pT cuts for Multiplicity applied here.
		if((TMath::Abs(eta[i])>2.8 & TMath::Abs(eta[i])<5.1) || (TMath::Abs(eta[i])>-3.7 & TMath::Abs(eta[i])<-1.7)) //V0M condition
		  {
		    Int_t charge=TMath::Abs(pid[i])/pid[i];
		    if(charge!=0) iMult++;
		  }

		//
		if(TMath::Abs(eta[i])<0.8)
		  {
		    Int_t charge=TMath::Abs(pid[i])/pid[i];
		    if(charge!=0) iMult2++;
		  }


	}
//***************end of particle loop*********************

	//cout<<number_of_pcharge<<" "<<number_of_ncharge<<endl;
	
	Int_t Net_charge;
	Net_charge=(number_of_pcharge - number_of_ncharge);
	
	
	NetCharge_Hist->Fill(Net_charge);
	
	Mult_Hist->Fill(iMult);

	Auto_correlation->Fill(iMult,iMult2);


	
	} //***************end of event loop*******************

	TFile* file2=new TFile("Netcharge_and_multiplicity.root","RECREATE");
	
	NetCharge_Hist->Write();
	
	Mult_Hist->Write();
	
	Auto_correlation->Write();
	
	file2->Close();


	file->Close();
	return 0 ;
}
