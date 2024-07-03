{

  TFile *_file0 = TFile::Open("macro/ppx/output_sx/ppt_48Ca.root");

  Double_t ymin=-0.05;
  Double_t ymax=0.6;

  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);
  sx->Draw("");
  sx0->Draw("same");

  Double_t dE=-0.2;  
  Double_t St=22.559+dE;
  Double_t E1=474.45/1000.0;
  Double_t E2=980.476/1000.0;
  Double_t E3=1424.3/1000.0;
  Double_t E4=1639.15/1000.0;
  Double_t E5=2188.22/1000.0;
  Double_t E6=2747.9/1000.0;

  Double_t St_oxygen = 25.032;// 1/2-                                                                                                                        
  Double_t E1_oxygen = 3.502; // 3/2-                                                                                                                        
  Double_t E2_oxygen = 7.376; // 5/2-                                                                                                                        
  Double_t E3_oxygen = 8.918; // 1/2-  
  
  TLine *z0=new TLine(St,ymin, St,ymax);
  z0->SetLineStyle(2);
  z0->SetLineColor(2);
  z0->Draw("same");

  TLine *z1=new TLine(St+E1,ymin, St+E1,ymax);
  z1->SetLineColor(1);
  z1->SetLineStyle(2);
  z1->Draw("same");

  TLine *z2=new TLine(St+E2,ymin, St+E2,ymax);
  z2->SetLineColor(2);
  z2->SetLineStyle(2);
  z2->Draw("same");

  TLine *z3=new TLine(St+E3,ymin, St+E3,ymax);
  z3->SetLineColor(2);
  z3->SetLineStyle(2);
  z3->Draw("same");


  TLine *z4=new TLine(St+E4,ymin, St+E4,ymax);
  z4->SetLineColor(2);
  z4->SetLineStyle(2);
  z4->Draw("same");


  TLine *z5=new TLine(St+E5,ymin, St+E5,ymax);
  z5->SetLineColor(2);
  z5->SetLineStyle(2);
  z5->Draw("same");

  TLine *z6=new TLine(St+E6,ymin, St+E6,ymax);
  z6->SetLineColor(2);
  z6->SetLineStyle(2);
  z6->Draw("same");




  TLine *zo0=new TLine(St_oxygen,ymin, St_oxygen,ymax);
  zo0->SetLineStyle(3);
  zo0->Draw("same");

  TLine *zo1=new TLine(St_oxygen+E1_oxygen,ymin, St_oxygen+E1_oxygen,ymax);
  zo1->SetLineStyle(3);
  zo1->Draw("same");
  
  TLine *zo2=new TLine(St_oxygen+E2_oxygen,ymin, St_oxygen+E2_oxygen,ymax);
  zo2->SetLineStyle(3);
  zo2->Draw("same");
  
  gROOT->LoadMacro("macro/function/def_5gaus.C");
  f->SetParameters(0.1,St,
                   0.2,St+E1,
                   0.1,St+E2,
                   0.1,St+E3,
                   0.2,St_oxygen,
                   0.25);
  sx->Fit("f","","",21.8,25.2);

}
