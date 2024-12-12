{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("pph","44Ca");
  gApplication->ProcessLine("gcom 44Ca(p,ph)");

  
  gROOT->LoadMacro("macro/function/def_2gaus.C");
  f->SetParameters(0.3,25.3,
		   0.4,26.5,
		   0.5);
  sx->Fit("f","","",24.5,27.1);



}
