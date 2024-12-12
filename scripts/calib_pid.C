void calib_pid(Int_t runnum,TString setup){
    gROOT->ProcessLine(Form(
                          "add steering/calib_pid.yaml NUM=%d SETUP=%s",
                          runnum,setup.Data()
                          ));
    art::TLoopManager::Instance()->GetLoop(0)->Resume();
    gApplication->Terminate();
}
