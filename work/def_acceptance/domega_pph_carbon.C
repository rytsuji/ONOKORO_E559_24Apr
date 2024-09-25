{

  double theta_las[2]={TMath::DegToRad()*47.5,
		       TMath::DegToRad()*54.3};
  
  double phi_las[2]={TMath::DegToRad()*(-3.5),
		     TMath::DegToRad()*(3.5)};
  
  double theta_gr[4]={TMath::DegToRad()*50.2,
		      TMath::DegToRad()*50.7,
		      //TMath::DegToRad()*51.8,
		      TMath::DegToRad()*51.5,
		      TMath::DegToRad()*52.2};
  double phi_gr[4]={TMath::DegToRad()*1.5,
		    TMath::DegToRad()*3.5,
		    TMath::DegToRad()*3.5,
		    TMath::DegToRad()*1.5};

  double domega_gr=2*phi_gr[1]*(-cos(theta_gr[2])+cos(theta_gr[1]));


  double a1=(phi_gr[1]-phi_gr[0])/(theta_gr[1]-theta_gr[0]);
  double b1=(a1*(-theta_gr[0])+phi_gr[0]);    
  domega_gr += 2*b1*(-cos(theta_gr[1])+cos(theta_gr[0]));
  domega_gr += 2*a1*(sin(theta_gr[1])-sin(theta_gr[0]));
  domega_gr += 2*a1*(-theta_gr[1]*cos(theta_gr[1])+theta_gr[0]*cos(theta_gr[0]));

  //double a2=(phi_gr[3]-phi_gr[2])/(theta_gr[3]-theta_gr[2]);
  //double b2=(a2*(-theta_gr[2])+phi_gr[2]);   
  //domega_gr += 2*b2*(-cos(theta_gr[3])+cos(theta_gr[2]));
  //domega_gr += 2*a2*(sin(theta_gr[3])-sin(theta_gr[2]));
  //domega_gr += 2*a2*(-theta_gr[3]*cos(theta_gr[3])+theta_gr[2]*cos(theta_gr[2]));


  std::cout << "dOmega_GR (str^2) :" << domega_gr << std::endl;
    
  
  double domega_las=(phi_las[1]-phi_las[0])*(-cos(theta_las[1])+cos(theta_las[0]));
  std::cout << "dOmega_LAS (str^2) :" << domega_las << std::endl;
  
}
