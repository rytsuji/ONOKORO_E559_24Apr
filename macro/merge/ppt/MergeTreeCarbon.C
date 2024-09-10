{

  TChain *tree= new TChain("tree", "");

  tree->Add("output/calib/run2070.root");
  tree->Add("output/calib/run2079.root");
  tree->Add("output/calib/run2117.root");  


  TFile *chain = new TFile("output/merge_calib/ppt_carbon.root","RECREATE");
  tree->Write();
  chain->Close();
  
}

