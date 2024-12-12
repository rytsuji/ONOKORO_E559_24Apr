{

  double theta_las[2]={TMath::DegToRad()*48.0,
		       TMath::DegToRad()*55.0};
  
  double phi_las[2]={TMath::DegToRad()*(-3.0),
		     TMath::DegToRad()*(3.0)};

  double theta_gr[2]={TMath::DegToRad()*51.0,
		       TMath::DegToRad()*52.0};
  
  double phi_gr[2]={TMath::DegToRad()*(-3.0),
		     TMath::DegToRad()*(3.0)};
  

  double domega_gr=(phi_gr[1]-phi_gr[0])*(-cos(theta_gr[1])+cos(theta_gr[0]));
  std::cout << "dOmega_GR (str^2) :" << domega_gr << std::endl;
    
  double domega_las=(phi_las[1]-phi_las[0])*(-cos(theta_las[1])+cos(theta_las[0]));
  std::cout << "dOmega_LAS (str^2) :" << domega_las << std::endl;
  
}
