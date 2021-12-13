//#include <iostream>
//#include <cstdio>
int Netcharge_and_multiplicity_with_percentile(TString filename="/mnt/home14/ankita/meanptNov2019/v2/MeanpT_7TeV_CR_0_RH_off.root",
	     TString tree="theTree",const Int_t dim=500)
{
  //using namespace std;
  freopen("output.txt", "w", stdout);
  freopen("error.txt","w", stderr);

  cout<<"output message from Netcharge_and_multiplicity_with_percentile"<<endl;
  cerr<<"Error message from Netcharge_and_multiplicity_with_percentile"<<endl;

	TFile* file=new TFile(filename,"read");
	TTree* pytree1=(TTree*)file->Get(tree);

	Int_t m_cut[]={103,60,43,23,15,8,0};//multiplicity cut
	//corresponding percentile={0.5,10,20,40,60,80,100}
	

	TH1I* NetCharge_Hist[7];
	TH1I* Mult_Hist[7];

	for(Int_t c=0;c<7;c++){
	  NetCharge_Hist[c]=new TH1I(Form("NetHist_%d",c),Form("Netcharge_%d, |eta|<0.8,pT>0.05",c),1000,-60,60);
	  Mult_Hist[c]=new TH1I(Form("MultHist_%d",c),Form("Multiplicity_%d, |eta|_V0M",c),1000,0,500);
	}
	
		
	Int_t nEvents;
	nEvents=pytree1->GetEntries();
	cout<<"Total number of events="<<nEvents<<endl;

	// *******************Event Loop********************
	for(Int_t j=0;j<nEvents;j++){
	//for(Int_t j=0;j<200000;j++){
	  //pytree1->Show(j);
	  //Int_t ntrack=total_number_of_track(j,tree,filename);
	

	  //if(j%1000==0) cout<<"i_th of events="<<j<<"\n"<<"total number of tracks="<<ntrack<<endl;
	

	  Int_t ntrack;
	  Int_t pid[dim];
	  Double_t eta[dim];
	  Double_t pT[dim];
	  pytree1->SetBranchAddress("PID",&pid);
	  pytree1->SetBranchAddress("Eta",&eta);
	  pytree1->SetBranchAddress("pT",&pT);
	  pytree1->SetBranchAddress("ntrack",&ntrack);
	  pytree1->GetEntry(j);

	  if(j%100000==0) cout<<j<<endl;//<<"\n"<<"total number of tracks="<<ntrack<<endl;

	  Int_t number_of_pcharge=0;
	  Int_t number_of_ncharge=0;
	  Int_t iMult=0;

	  
	    //*************particle_loop*************************
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
	      if((TMath::Abs(eta[i])>2.8 & TMath::Abs(eta[i])<5.1) || (TMath::Abs(eta[i])>-3.7 & TMath::Abs(eta[i])<-1.7)) //V0M conditionif(TMath::Abs(eta[i])>1.5)
		 {
		    Int_t charge=TMath::Abs(pid[i])/pid[i];
		    if(charge!=0) iMult++;
		  }


	    }
	    //***************end of particle_loop*********************

	    Int_t Net_charge;
	    Net_charge=(number_of_pcharge - number_of_ncharge);
	    //cout<<number_of_pcharge<<" "<<number_of_ncharge<<endl;

	    if(iMult>m_cut[0] & iMult<=500)
	      {
	    NetCharge_Hist[0]->Fill(Net_charge);
	    Mult_Hist[0]->Fill(iMult);
	      }
	    if(iMult>m_cut[1] & iMult<=m_cut[0])
	      {
	    NetCharge_Hist[1]->Fill(Net_charge);
	    Mult_Hist[1]->Fill(iMult);
	      }
	    if(iMult>m_cut[2] & iMult<=m_cut[1])
	      {
	    NetCharge_Hist[2]->Fill(Net_charge);
	    Mult_Hist[2]->Fill(iMult);
	      }
	    if(iMult>m_cut[3] & iMult<=m_cut[2])
	      {
	    NetCharge_Hist[3]->Fill(Net_charge);
	    Mult_Hist[3]->Fill(iMult);
	      }
	    if(iMult>m_cut[4] & iMult<=m_cut[3])
	      {
	    NetCharge_Hist[4]->Fill(Net_charge);
	    Mult_Hist[4]->Fill(iMult);
	      }
	    if(iMult>m_cut[5] & iMult<=m_cut[4])
	      {
	    NetCharge_Hist[5]->Fill(Net_charge);
	    Mult_Hist[5]->Fill(iMult);
	      }
	    if(iMult>m_cut[6] & iMult<=m_cut[5])
	      {
	    NetCharge_Hist[6]->Fill(Net_charge);
	    Mult_Hist[6]->Fill(iMult);
	      }
	     
	} //***************end of event loop*******************
	//cout<<"writing into file"<<endl;
	TFile* file2=new TFile("Netcharge_and_multiplicity_with_percentile.root","RECREATE");

	for(Int_t c=0;c<7;c++){
	NetCharge_Hist[c]->Write();
	Mult_Hist[c]->Write();
	}
	file2->Close();


	file->Close();
	return 0 ;
}
