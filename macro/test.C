{
   gROOT->Reset();


   TCanvas c1("c1","multipads",600,1200);
   gStyle->SetPadBorderMode(0);   
   gStyle->SetFrameBorderMode(0);
   Float_t small = 1e-5;
   //c1.Divide(1,4,small,small);
   c1.Divide(1,4);
   TH1F h1("h1","",40,-4,4);
   TH1F h2("h2","",40,-4,4);
   TH1F h3("h3","",40,-4,4);
   TH1F h4("h4","",40,-4,4);
   h1.FillRandom("gaus",1000);
   h2.FillRandom("gaus",1000);
   h3.FillRandom("gaus",1000);
   h4.FillRandom("gaus",1000);
   c1.cd(0);
   //gPad->SetTopMargin(0.1);
   //gPad->SetBottomMargin(0.1);

   c1.cd(1);
   //gPad->SetTopMargin(small);   
   //gPad->SetBottomMargin(small);
   h1.Draw();

   c1.cd(2);
   //gPad->SetTopMargin(small);   
   //gPad->SetBottomMargin(small);   
   //gPad->SetTickx();
   h2.Draw();

   c1.cd(3);
   //gPad->SetTopMargin(small);   
   //gPad->SetBottomMargin(small);
   //gPad->SetTickx();
   h3.Draw();

   c1.cd(4);   
   //gPad->SetTopMargin(small);
   //gPad->SetBottomMargin(small);   
   //gPad->SetTickx();
   h4.Draw();
} 
