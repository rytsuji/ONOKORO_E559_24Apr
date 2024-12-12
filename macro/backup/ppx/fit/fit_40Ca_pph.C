{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("pph","40Ca");
  gApplication->ProcessLine("gcom 40Ca(p,ph)");
  
  gROOT->LoadMacro("macro/function/def_3gaus.C");
  f->SetParameters(0.3,19.0,
		   0.8,20.5,
		   0.3,21.7,
		   0.5);
  sx->Fit("f","","",18.0,22.2)
  



}
