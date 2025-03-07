{

  double theta_las[2]={TMath::DegToRad()*46.0,
		       TMath::DegToRad()*52.0};
  
  double phi_las[2]={TMath::DegToRad()*(-3.5),
		     TMath::DegToRad()*(3.5)};
  
  double theta_gr[4]={TMath::DegToRad()*49.7,
		      TMath::DegToRad()*50.2,
		      TMath::DegToRad()*51.3,
		      TMath::DegToRad()*51.7};
  double phi_gr[4]={TMath::DegToRad()*1.5,
		    TMath::DegToRad()*3.5,
		    TMath::DegToRad()*3.5,
		    TMath::DegToRad()*1.5};

  double f=1.0;

  double err_theta_gr=abs(0.072*(1-pow(tan(TMath::DegToRad()*50.7),2.0))*pow(cos(TMath::DegToRad()*50.7),2.0));
  double err_phi_gr=abs(0.6988/sin(TMath::DegToRad()*50.7));
  double err_theta_las=abs(0.4491*(1-pow(tan(TMath::DegToRad()*49.25),2.0))*pow(cos(TMath::DegToRad()*49.25),2.0));
  double err_phi_las=abs(1.218/sin(TMath::DegToRad()*49.25));

  
  for(int i=0;i<4;i++){
    theta_gr[i] += 1.0/1000.*f*( (double)( (theta_gr[i]>0)-(theta_gr[i]<0) ))*err_theta_gr;
    phi_gr[i]   += 1.0/1000.*f*( (double)( (phi_gr[i]>0)-(phi_gr[i]<0) ))*err_phi_gr;
  }

  for(int i=0;i<2;i++){
    theta_las[i] += 1.0/1000.*f*( (double)( (theta_las[i]>0)-(theta_las[i]<0) ))*err_theta_las;
    phi_las[i]   += 1.0/1000.*f*( (double)( (phi_las[i]>0)-(phi_las[i]<0) ))*err_phi_las;
  }
  
  double domega_gr=2*phi_gr[1]*(-cos(theta_gr[2])+cos(theta_gr[1]));


  double a1=(phi_gr[1]-phi_gr[0])/(theta_gr[1]-theta_gr[0]);
  double b1=(a1*(-theta_gr[0])+phi_gr[0]);    
  domega_gr += 2*b1*(-cos(theta_gr[1])+cos(theta_gr[0]));
  domega_gr += 2*a1*(sin(theta_gr[1])-sin(theta_gr[0]));
  domega_gr += 2*a1*(-theta_gr[1]*cos(theta_gr[1])+theta_gr[0]*cos(theta_gr[0]));

  double a2=(phi_gr[3]-phi_gr[2])/(theta_gr[3]-theta_gr[2]);
  double b2=(a2*(-theta_gr[2])+phi_gr[2]);   
  domega_gr += 2*b2*(-cos(theta_gr[3])+cos(theta_gr[2]));
  domega_gr += 2*a2*(sin(theta_gr[3])-sin(theta_gr[2]));
  domega_gr += 2*a2*(-theta_gr[3]*cos(theta_gr[3])+theta_gr[2]*cos(theta_gr[2]));


  std::cout << "dOmega_GR (str^2) :" << domega_gr << std::endl;
    
  
  double domega_las=(phi_las[1]-phi_las[0])*(-cos(theta_las[1])+cos(theta_las[0]));
  std::cout << "dOmega_LAS (str^2) :" << domega_las << std::endl;
  
}
