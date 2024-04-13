{

  TChain *tree= new TChain("tree", "");

  tree->Add("InputFile1.root");
  tree->Add("InputFile2.root");


  TFile *chain = new TFile("OutputFile.root","RECREATE");
  tree->Write();
  chain->Close();
  
}
