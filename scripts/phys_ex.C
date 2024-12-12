void phys_ex(Int_t runnum,TString setup,TString tgt){
  gROOT->ProcessLine(Form(
                          //"add steering/phys_ex.yaml NUM=%d SETUP=%s TGT=%s",
			  "add steering/phys_ex_nogate.yaml NUM=%d SETUP=%s TGT=%s",
                          runnum,setup.Data(),tgt.Data()
                          ));
  art::TLoopManager::Instance()->GetLoop(0)->Resume();
}
