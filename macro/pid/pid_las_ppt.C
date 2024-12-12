{

  TFile *file= TFile::Open("output/calib/run2070.root");

  TCut rf="abs(fmod(pid_las.fTiming -plas.GetTOF()- rf1.fTiming + 1420.6750, 71.033750)  - (25.0+55.0)/2.0 ) < abs(55.0-25.0)/2.0";
  TCut charge="pid_las.fCharge> 100.0 && pid_las.fCharge < 100000.0";

  TLatex t1;
  t1.SetNDC(1);
  t1.SetTextAlign(12);
  
  TH1F *h_rf=new TH1F("h_rf","",300,-5,145);
  TH1F *h_charge=new TH1F("h_charge","",300,0,300);
  TCanvas *c1 =new TCanvas("c1","",800,300);
  c1->Divide(2,1);

  c1->cd(1);
  h_rf->GetXaxis()->SetTitle("TOF_{LAS} (ns)");
  h_rf->GetYaxis()->SetTitle("count");
  h_rf->SetStats(0);
  tree->Draw("fmod(pid_las.fTiming -plas.GetTOF()- rf1.fTiming + 1420.6750, 71.033750)>>h_rf",charge,"");
  t1.DrawLatex(0.8,0.8,"(a)");
  
  c1->cd(2);
  h_charge->GetXaxis()->SetTitle("Q_{LAS} (ch)");
  h_charge->GetYaxis()->SetTitle("count");
  h_charge->SetStats(0);
  tree->Draw("pid_las.fCharge>>h_charge",rf,"");
  t1.DrawLatex(0.8,0.8,"(b)");
    
}
