{

  TFile *file_carbon = TFile::Open("output/calib_pid/hist_sx/pph_carbon.root ");
      
  TH1F *h_carbon = (TH1F*)file_carbon->Get("sx")->Clone("h_carbon");
  TH1F *h_carbon0 = (TH1F*)file_carbon->Get("sx0")->Clone("h_carbon0");
  h_carbon->SetMinimum(-0.02);
  h_carbon->SetMaximum(0.20);  
  h_carbon->SetTitle("");
  h_carbon->SetStats(0);
  TCanvas *c1=new TCanvas("c1","c1",800,600);
  h_carbon->Draw();
  h_carbon0->Draw("same");
  TF1 *f=new TF1("f","gausn",-100,100);
  h_carbon->Fit("f","","",20,27);

  int nBin=h_carbon->GetXaxis()->GetNbins();
  double xMin=h_carbon->GetXaxis()->GetXmin();
  double xMax=h_carbon->GetXaxis()->GetXmax();

  double TDX=f->GetParameter(0)/( (xMax-xMin)/(double) nBin);
  double res=f->GetParameter(2);
  
  double scale=1.0;
  TLatex title;
  title.SetTextAlign(11);
  title.SetNDC(1);
  title.DrawLatex(.60,.8,Form("#scale[%f]{^{12}C(#it{p,p}^{3}He)}",1.0*scale));
  title.DrawLatex(.55,.65,Form("#scale[%f]{TDX: %8.3f (#mu b/MeV#upoint sr^{2})}",0.75*scale,TDX));                                                             
  title.DrawLatex(.55,.575,Form("#scale[%f]{#sigma: %8.3f (MeV)}",0.75*scale,res)); 
}
