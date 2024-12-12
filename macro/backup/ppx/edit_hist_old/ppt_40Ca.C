{

  TFile *_file0 = TFile::Open("macro/ppx/output_sx/ppt_40Ca.root");

  Double_t ymin=-0.05;
  Double_t ymax=0.5;
  
  sx->SetMinimum(ymin);
  sx->SetMaximum(ymax);

  sx->GetXaxis()->SetRange(sx->FindBin(20),sx->FindBin(45));


  sx->Draw("");
  sx0->Draw("same");
  Double_t St=24.996; // 3/2+
  Double_t E1=1370.85/1000.0; //1/2+
  Double_t E2=2285.24/1000.0; //5/2+, 7/2+
  Double_t E3=2750.22/1000.0; //5/2+
  Double_t E4=3239.5/1000.0; //5/2+

  TLine *z0=new TLine(St,ymin, St,ymax);
  z0->SetLineStyle(2);
  z0->SetLineColor(2);
  z0->Draw("same");

  TLine *z1=new TLine(St+E1,ymin, St+E1,ymax);
  z1->SetLineStyle(1);  
  z1->SetLineColor(2);
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

  /*
  TLine *z5=new TLine(St+E5,ymin, St+E5,ymax);
  z5->SetLineStyle(9);
  z5->Draw("same");

  TLine *z6=new TLine(St+E6,ymin, St+E6,ymax);
  z6->SetLineStyle(9);
  z6->Draw("same");

  TLine *z7=new TLine(St+E7,ymin, St+E7,ymax);
  z7->SetLineStyle(9);
  z7->Draw("same");
  */

  Double_t St_oxygen = 25.032;// 1/2-
  Double_t E1_oxygen = 3.502; // 3/2-
  Double_t E2_oxygen = 7.376; // 5/2-
  Double_t E3_oxygen = 8.918; // 1/2-
  
  TLine *zo0=new TLine(St_oxygen,ymin, St_oxygen,ymax);
  zo0->SetLineStyle(2);
  zo0->Draw("same");

  TLine *zo1=new TLine(St_oxygen+E1_oxygen,ymin, St_oxygen+E1_oxygen,ymax);
  zo1->SetLineStyle(2);
  zo1->Draw("same");

  TLine *zo2=new TLine(St_oxygen+E2_oxygen,ymin, St_oxygen+E2_oxygen,ymax);
  zo2->SetLineStyle(2);
  zo2->Draw("same");

  /*
  TLine *zo3=new TLine(St_oxygen+E3_oxygen,ymin, St_oxygen+E3_oxygen,ymax);
  zo3->SetLineStyle(3);
  zo3->Draw("same");
  */
  
  //gApplication->ProcessLine("gcom 40Ca(p,pt)");
  gROOT->LoadMacro("macro/function/def_4gaus.C");
  f->SetParameters(0.1,St,
                   0.2,St+E1,
		   0.05,St+E2,
                   0.1,St+E3,
                   0.1);
  sx->Fit("f","","",15.0,28.0)

}
