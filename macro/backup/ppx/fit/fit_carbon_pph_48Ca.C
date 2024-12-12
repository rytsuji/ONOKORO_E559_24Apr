{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("pph_48Ca","carbon");
  //gApplication->ProcessLine("gcom 42Ca(p,ph)");

  /*
  gROOT->LoadMacro("macro/function/def_2gaus.C");
  f->SetParameters(0.3,21.8,
		   0.8,22.7,
		   0.5);
  sx->Fit("f","","",21.0,23.5)
  */



}
