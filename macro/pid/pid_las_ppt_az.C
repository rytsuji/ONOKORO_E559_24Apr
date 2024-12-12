{

  TFile *file= TFile::Open("output/calib/run2070.root");

  TCut rf="abs(fmod(pid_las.fTiming -plas.GetTOF()- rf1.fTiming + 1420.6750, 71.033750)  - (25.0+55.0)/2.0 ) < abs(55.0-25.0)/2.0";
  TCut charge="pid_las.fCharge> 100.0 && pid_las.fCharge < 100000.0";

  TLatex t1;
  t1.SetNDC(1);
  t1.SetTextAlign(12);
  
  TH2F *h=new TH2F("h","",300,-5,145,500,0,5);
  TCanvas *c1 =new TCanvas("c1","",800,600);

  h->GetXaxis()->SetTitle("TOF_{LAS} (ns)");
  h->GetYaxis()->SetTitle("A_{LAS}");
  h->SetStats(0);
  tree->Draw("3.0*sqrt(pid_las.fCharge/1.46928e+02):fmod(pid_las.fTiming -plas.GetTOF()- rf1.fTiming + 1420.6750, 71.033750)>>h","","colz");

    
}
