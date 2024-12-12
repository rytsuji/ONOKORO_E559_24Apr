void phys_nogate(Int_t runnum,TString setup){
    gROOT->ProcessLine(Form(
                          "add steering/phys_nogate.yaml NUM=%d SETUP=%s",
                          runnum,setup.Data()
                          ));
    art::TLoopManager::Instance()->GetLoop(0)->Resume();
}
