{

  Double_t constant=10000;
  Double_t mean=-80;
  Double_t sigma=7.0;
  Double_t slope=0.0;
  Double_t offset=0.0;

  Double xmin=-140.0;
  Double xmax=-50.0;
  
  TF1 *f=new TF1("f","gausn+[3]+[4]*x",-1000,1000);
  f->SetParaneters(constant,mean,sigma,slope,offset);

  x_gr->Fit("f","","",xmin,xmax);
  

  std::cout << "Count is " << f->GetParameter(0) << std::endl;



}
