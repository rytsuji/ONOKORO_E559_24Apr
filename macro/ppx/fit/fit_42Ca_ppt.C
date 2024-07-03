{
  gROOT->LoadMacro("macro/ppx/hist_sx.C");
  hist_sx("ppt","42Ca");
  gApplication->ProcessLine("gcom 42Ca(p,pt)");
  /*
  gROOT->LoadMacro("macro/function/def_3gaus.C");
  f->SetParameters(0.2,25.0,
		   0.9,26.4,
		   0.5,27.2,
		   0.3);
  sx->Fit("f","","",15.0,28.0)
  */

  sx->Fit("gausn","","",21.0,23.0);
    

}
