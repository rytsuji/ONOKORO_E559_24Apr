{

  TChain *tree= new TChain("tree", "");

  tree->Add("output/calib/run2087.root");
  tree->Add("output/calib/run2088.root");
  tree->Add("output/calib/run2093.root");
  tree->Add("output/calib/run2137.root");    


  TFile *chain = new TFile("output/merge_calib/pph_carbon.root","RECREATE");
  tree->Write();
  chain->Close();
  
}

