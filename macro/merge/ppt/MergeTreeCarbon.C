{

  TChain *tree= new TChain("tree", "");

  tree->Add("output/calib_pid/run2070.root");
  tree->Add("output/calib_pid/run2079.root");
  tree->Add("output/calib_pid/run2117.root");  


  TFile *chain = new TFile("output/merge_calib/ppt_carbon.root","RECREATE");
  tree->Write();
  chain->Close();
  
}

