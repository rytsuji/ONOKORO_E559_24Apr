void phys_40Ca(Int_t runnum,TString setup){
    gROOT->ProcessLine(Form(
                          "add steering/phys_40Ca.yaml NUM=%d SETUP=%s",
                          runnum,setup.Data()
                          ));
    art::TLoopManager::Instance()->GetLoop(0)->Resume();
}
