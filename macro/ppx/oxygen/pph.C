#include <TFile.h>
#include <TH1.h>
void pph(void){


  TFile *file_mylar = TFile::Open("macro/ppx/output_sx/pph_mylar.root");
  TFile *file_carbon = TFile::Open("macro/ppx/output_sx/pph_carbon.root");
  Double_t scale=0.66348429*(48.0080/10.47)/(12.0/10.65);
  TFile *fout = new TFile("macro/ppx/output_sx/pph_oxygen.root","RECREATE");

 
  TH1F* h_mylar0= (TH1F*) file_mylar->Get("sx0")->Clone();
  h_mylar0->SetName("h_mylar0");
  TH1F* h_carbon0= (TH1F*) file_carbon->Get("sx0")->Clone();
  h_carbon0->SetName("h_carbon0");
  TH1F* h_oxygen0= (TH1F*) file_mylar->Get("sx0")->Clone();
  h_oxygen0->SetName("h_oxygen0");

  TH1F* h_mylar= (TH1F*) file_mylar->Get("sx")->Clone();
  h_mylar->SetName("h_mylar");
  TH1F* h_carbon= (TH1F*) file_carbon->Get("sx")->Clone();
  h_carbon->SetName("h_carbon");
  TH1F* h_oxygen= (TH1F*) file_mylar->Get("sx")->Clone();
  h_oxygen->SetName("h_oxygen");
  
  h_mylar->Sumw2();
  h_oxygen->Sumw2();
  h_carbon->Sumw2();

  h_carbon0->Scale(scale);
  h_carbon->Scale(scale);
  
  h_oxygen0->Add(h_carbon0,-1.0);
  h_oxygen->Add(h_carbon,-1.0);  
  
  h_mylar0->Sumw2(0);
  h_oxygen0->Sumw2(0);
  h_carbon0->Sumw2(0);

  h_mylar0->Write();
  h_oxygen0->Write(); 
  h_carbon0->Write();

  h_mylar->Write();
  h_oxygen->Write(); 
  h_carbon->Write();

  fout->Close();

  TFile *file = new TFile("macro/ppx/output_sx/pph_oxygen.root"); 

  gApplication->ProcessLine("zon");
  gApplication->ProcessLine("gcom Mylar(p,ph)");
  gApplication->ProcessLine("h_mylar0->GetXaxis()->ZoomOut(0.6,0.5)");                                                                                       
  gApplication->ProcessLine("ht h_mylar0");
  gApplication->ProcessLine("h_mylar->Draw(\"same\")");                                                                                                     
  gApplication->ProcessLine("h_carbon0->SetLineColor(2)");
  gApplication->ProcessLine("h_carbon->SetLineColor(2)");
  gApplication->ProcessLine("h_carbon->SetMarkerColor(2)");                                                                                                  
  gApplication->ProcessLine("h_carbon0->Draw(\"same\")");                                                                                                    
  gApplication->ProcessLine("h_carbon->Draw(\"same\")");
  
  return;

  
}
