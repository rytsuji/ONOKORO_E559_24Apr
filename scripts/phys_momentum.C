void phys_momentum(Int_t runnum,TString setup,TString target){
    gROOT->ProcessLine(Form(
                          "add steering/phys_momentum.yaml NUM=%d SETUP=%s TGT=%s",
                          runnum,setup.Data(),target.Data()
                          ));
    art::TLoopManager::Instance()->GetLoop(0)->Resume();
}
