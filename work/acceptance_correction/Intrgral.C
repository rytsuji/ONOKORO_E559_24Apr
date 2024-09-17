{
  //std::ifstream InFile("pph_40Ca.dat");
  //ofstream ofile("pph_40Ca_Int.dat");

  std::ifstream InFile("ppt_40Ca.dat");
  ofstream ofile("ppt_40Ca_Int.dat");

  std::string InLine;

  int count=0;
  double ratio_norm=0.0;  
  
  double kf_pre=-9999;
  double theta_pre=0.0;
  double ratio_pre=0.0;  
  //double acc_pre=0.0;
  //double req_pre=0.0;  

  double kf;
  double theta;
  double ratio;  
  double acc;
  double req;      

  double ratio_int=0.0;  
  double acc_int=0.0;
  double req_int=0.0;    
  
  while(getline(InFile,InLine)){
    std::string Str;
    std::vector<double> Val;
    stringstream SS(InLine);
    while(getline(SS, Str, ' ')){
      Val.push_back(std::stod(Str));
    }
    
    if(Val.size()==5){
      kf=Val[0];
      theta=Val[1];
      ratio=Val[3];
      acc=Val[3];
      req=Val[4];                  
      
      if(Val[0]==kf_pre){
	ratio_int += (ratio+ratio_pre)/2.0*(theta-theta_pre);
	acc_int += acc;
	req_int += req;
      }
      
      kf_pre=kf;
      theta_pre=theta;
      ratio_pre=ratio;      
      
    }else if(Val.size()==0){ 
      if(count == 0) ratio_norm = ratio_int;
      
      ofile << kf << " " << ratio_int/ratio_norm  << std::endl;
      //ofile << kf << " " << ratio_int << std::endl;
      ratio_int = 0.0;
      acc_int = 0.0;
      req_int = 0.0;
      
      count ++;
    }    
  }
  ofile.close();
}







