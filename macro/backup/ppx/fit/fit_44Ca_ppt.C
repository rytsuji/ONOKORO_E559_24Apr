{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("ppt","44Ca");
  gApplication->ProcessLine("gcom 44Ca(p,pt)");
  
  gROOT->LoadMacro("macro/function/def_3gaus.C");
  f->SetParameters(0.3,20.5,
		   0.4,21.75,
		   0.2,22.35,
		   0.3);
  sx->Fit("f","","",15.0,22.8)
  



}
