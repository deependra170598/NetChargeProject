# include <iostream>
# include <fstream>

int percentile(TString filename="Netcharge_and_multiplicity.root",TString mult="MultHist")
{
  Double_t percentile[]={0.5,10.0,20.0,40.0,60.0,80.0,100.0};
 
  TFile* file=new TFile(filename,"read"); // reading multiplicity from file
  TH1I* Mult_Hist=(TH1I*)file->Get(mult);

  //create and open a output text file
  ofstream outfile("percentile.txt");
  
  Double_t TotEntries;;
  TotEntries=(Double_t)Mult_Hist->GetEntries();
  cout<<"Total number of Entries="<<TotEntries<<endl;
  
  Double_t p[7]; //percentile calculator
  Double_t x[7];

  //Int_t uperbin; // variable upper_cut of multiplicity
  Int_t lowerbin=0;

  for(Int_t i=0;i<7;i++){//..........................percentile loop
    Double_t Area;
    //Int_t Area1;
  
    for(Int_t uperbin=999;uperbin>0;uperbin--){
    
      Area=(Double_t)Mult_Hist->Integral(lowerbin,uperbin);
      //cout<<"Area="<<Area<<endl;
    
      p[i]=100*(1-(Area/TotEntries));
      //cout<<"percentile1="<<percentile1<<endl;
    
      if(p[i]>percentile[i]){
	cout<<"uperbin="<<uperbin+1<<endl;
	break;
      }
    }

    x[i]=Mult_Hist->GetXaxis()->GetBinCenter(uperbin+1);
    outfile<<percentile[i]<<" "<<x[i]<<endl; // writing to outfile
  }


  return 0;
}
    
