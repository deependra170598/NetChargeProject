int plot_Netcharge_vs_mean_multiplicity(TString filename="Netcharge_and_multiplicity_with_percentile.root"){

  freopen("output.txt","w",stdout);
  freopen("error.txt","w", stderr);

  

  cout<<"output message from plot_Netcharge_vs_mean_multiplicity"<<endl;
  cerr<<"Error message from plot_Netcharge_vs_mean_multiplicity "<<endl;

  TFile* file=new TFile(filename,"READ");
  
  TH1I* NetCharge_Hist[7];
  TH1I* Mult_Hist[7];


  
  for(Int_t i=0;i<7;i++)
    {
      NetCharge_Hist[i]=(TH1I*)file->Get(Form("NetHist_%d",i));
      Mult_Hist[i]=(TH1I*)file->Get(Form("MultHist_%d",i));
      
    }


  Double_t Y[7];
  Double_t X[7];

  for(Int_t j=0;j<7;j++)
    {
      Y[j]=NetCharge_Hist[j]->GetMean();
      X[j]=Mult_Hist[j]->GetMean();
      
    }

  TFile* file2=new TFile("plot.root","recreate");
  TGraph *g1=new TGraph(7,X,Y);
  g1->SetMarkerStyle(21);
  g1->SetMarkerColor(4);
  g1->Write();
  file2->Close();

  file->Close();  

  return 0;
}
