void eff_gr(Int_t runnum,TString setup){
    gROOT->ProcessLine(Form(
                          "add steering/chk_eff_gr.yaml NUM=%d SETUP=%s",
                          runnum,setup.Data()
                          ));
    art::TLoopManager::Instance()->GetLoop(0)->Resume();
}
