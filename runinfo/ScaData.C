//int coin=15;

long long ScaData(int runnum,int colmun){
  
  TString filepath="runinfo/onokoro_2024apr_RunSummary.txt";
  ifstream scafile(filepath);
  std::string line_scafile;
  
  //Skip Header
  getline(scafile,line_scafile);
  
  //Read Lines
  while(getline(scafile,line_scafile)){
    std::istringstream line(line_scafile);
    
    //check runnumber
    std::string str_runnum;   
    line >> str_runnum;
    if(std::stoi(str_runnum)  == runnum){    
            
      const int max_colmun=83;
      std::string str[max_colmun];
      
      for(int i= 0;i<max_colmun;i++){
	line >> str[i];
      }
      
      //return value      
      if(colmun > 3 && colmun < max_colmun ){
	return stoll(str[colmun-1]);
      }
      if(colmun == 1){

	//BLP1
	if(str[0] == "OUT"){
	  return 0;
	}else if(str[0] == "IN" ){
	  return 1;
	}else{
	  return -1;
	}
      }if(colmun == 2){	
	//BLP2
	if(str[1] == "OUT"){
	  return 0;
	}else if(str[1] == "IN" ){
	  return 1;
	}else{
	  return -1;
	}
	
      }if(colmun ==3){
	
	//SPIN
	if(str[2] == "UNPOL"){
	  return 0;
	}else if(str[2] == "POL" ){
	  return 1;
	}else{
	  return -1;
	}
	
      }else{	
	std::cout << "Invalid colmun :" << colmun << std::endl;
	return -1;	
      }      
      break;
    }    
  }
  return -1;
}

  
