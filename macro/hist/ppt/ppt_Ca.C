{
  TCanvas *c1=new TCanvas("c1","",400,1200);
  c1->Divide(1,4);
  c1->cd(1);
  gApplication->ProcessLine(".x macro/hist/ppt_40Ca.C");
  c1->cd(2);
  //gApplication->ProcessLine(".x macro/hist/ppt_42Ca.C"); 
  c1->cd(3);
  //gApplication->ProcessLine(".x macro/hist/ppt_44Ca.C");
  c1->cd(4);
  //gApplication->ProcessLine(".x macro/hist/ppt_48Ca.C"); 


}
