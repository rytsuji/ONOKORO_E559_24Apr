void rawdata(Int_t runnum,TString setup){
    gROOT->ProcessLine(Form(
                          "add steering/rawdata.yaml NUM=%d SETUP=%s",
                          runnum,setup.Data()
                          ));
    art::TLoopManager::Instance()->GetLoop(0)->Resume();
}
