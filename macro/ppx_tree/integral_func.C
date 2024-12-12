double calc_integral(TH1F *h,double min, double max);
double calc_err(TH1F *h,double min, double max);
  
double calc_integral(TH1F *h,double min, double max){

  double val_integral=0.0;
  int MinBin=h->FindBin(min);
  int MaxBin=h->FindBin(max);
  for(int i=MinBin;i<MaxBin+1;i++){
      val_integral +=h->GetBinContent(i);
  }  
  return val_integral;
}


double calc_err(TH1F *h,double min, double max){

  double val_err=0.0;
  
  int MinBin=h->FindBin(min);
  int MaxBin=h->FindBin(max);
  for(int i=MinBin;i<MaxBin+1;i++){
    double bin_err=h->GetBinError(i);
    val_err += pow(bin_err,2.0);
  }  
  return sqrt(val_err);
}
