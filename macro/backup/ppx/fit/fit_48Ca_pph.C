{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("pph_48Ca","48Ca");
  gApplication->ProcessLine("gcom 48Ca(p,ph)");

  

  gROOT->LoadMacro("macro/function/def_2gaus.C");
  f->SetParameters(0.1,30.5,
		   0.1,31.5,
		   0.5);
  sx->Fit("f","","",29.7,32.2);
  


}
