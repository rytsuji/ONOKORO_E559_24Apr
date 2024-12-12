{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("ppt","48Ca");
  gApplication->ProcessLine("gcom 48Ca(p,pt)");
  
  gROOT->LoadMacro("macro/function/def_5gaus.C");
  f->SetParameters(0.1,22.559,
		   0.2,22.559+0.474,
		   0.1,22.559+1.020,
		   0.1,22.559+1.424,
		   0.2,25.0,
		   0.25);
  sx->Fit("f","","",21.5,25.2);
  



}
