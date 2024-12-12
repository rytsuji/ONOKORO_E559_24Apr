{
  gROOT->LoadMacro("macro/fucn/def_3gaus.C");
  f->SetParameters(67.518518,20.516256,81.949722,21.635125,47.074313,22.221199,0.3);
  sx->Fit("f","","",18.0,22.6);
}
