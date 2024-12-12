const int nFile=5;
std::vector<std::vector<double>> x;
std::vector<std::vector<double>> a;
std::vector<std::vector<double>> y;
std::vector<std::vector<double>> b;
std::vector<std::vector<double>> a_tgt;
std::vector<std::vector<double>> b_tgt;
std::vector<std::vector<double>> bc;

std::vector<std::vector<double>> py0;
std::vector<std::vector<double>> py1;
std::vector<std::vector<double>> py3;
std::vector<std::vector<double>> ac;
std::vector<std::vector<double>> xc;

void read_data();

int b_gr_fit(){

  read_data();

  py0.resize(5);
  py1.resize(5);
  py3.resize(5);
  ac.resize(5);
  xc.resize(5);
  bc.resize(5);    
  
  TTree *tree = new TTree("tree","tree");
  tree->Branch("x",&x);
  tree->Branch("y",&y);
  tree->Branch("a",&a);
  tree->Branch("b",&b);  
  tree->Branch("a_tgt",&a_tgt);
  tree->Branch("b_tgt",&b_tgt);
  tree->Branch("bc",&bc);  
  tree->Fill();
  
  //tree->Branch("bc",&bc);
  //bc.resize(5);
  TTree *tree1 = new TTree("tree1","tree1");
  tree1->Branch("py0",&py0);
  tree1->Branch("py1",&py1);
  tree1->Branch("py3",&py3);
  tree1->Branch("ac",&ac);
  tree1->Branch("xc",&xc);
  
  TH2F *h_yb[5][4];
  for(int i=0;i<5;i++){
    for(int j=0;j<4;j++){    
      h_yb[i][j]= new TH2F(Form("h_yb[%d][%d]",i,j),Form("h_yb[%d][%d]",i,j),1000,-200,200,1000,-0.05,0.05);
      h_yb[i][j]->SetMarkerStyle(8);
      TString draw_yb=Form("b_tgt[%d]:y[%d]>>h_yb[%d][%d]",i,i,i,j);
      TCut acut=Form("abs(a_tgt[%d]-((2-%e)*0.007792))<0.001",i,(double) j);
      tree->Draw(draw_yb,acut,"");
      //TF1 *p3=new TF1("p3","[0]+[1]*x+[2]*x*x*x",-200,200);
      TF1 *p3=new TF1("p3","[0]+[1]*x",-200,200);
      h_yb[i][j]->Fit("p3");

      int nA=0;
      double valA=0.0;
      for(int k=0;k<x[i].size();k++){
	if(abs(a_tgt[i][k]-((double)(2-j)*0.007792))<0.001){
	  valA += a_tgt[i][k];
	  nA++;
	}
      }
      
      py0[i].push_back(p3->GetParameter(0));
      py1[i].push_back(p3->GetParameter(1));
      //py3[i].push_back(p3->GetParameter(2));      
      ac[i].push_back(valA/(double)nA);
      xc[i].push_back(x[i][0]);      
    }
  }

  tree1->Fill();


  TString oname="work/ang_gr/dat/b_gr.dat";
  ofstream ofile((std::string) oname);
  for(int i=0;i<5;i++){
    for(int j=0;j<4;j++){
      //ofile << xc[i][j] << " " << ac[i][j] << " " << py0[i][j] << " " << py1[i][j] << " " << py3[i][j] << std::endl;
      ofile << xc[i][j] << " " << ac[i][j] << " " << py0[i][j] << " " << py1[i][j] << std::endl;
    }
  }
  ofile.close();
  return 0;
}

void read_data(){
  x.resize(nFile);
  y.resize(nFile);
  a.resize(nFile);      
  b.resize(nFile);
  a_tgt.resize(nFile);
  b_tgt.resize(nFile);      
  std::string dir="work/ang_gr/dat/";
  std::string file[nFile]={"delta98.dat","delta99.dat","delta100.dat","delta101.dat","delta102.dat"};

   
  for(int iFile=0;iFile<nFile;iFile++){
    
    std::ifstream InFile(dir+file[iFile]);
    std::string InLine;
    while(getline(InFile,InLine)){
      std::string Str;
      std::vector<double> Val;
      stringstream SS(InLine);
      while(getline(SS, Str, ' ')){
	Val.push_back(std::stod(Str));
      }
      //std::cout << Val[0] << std::endl;
      x[iFile].push_back(Val[0]);
      a[iFile].push_back(Val[1]);
      y[iFile].push_back(Val[2]);      
      b[iFile].push_back(Val[3]);
      a_tgt[iFile].push_back(Val[4]);
      b_tgt[iFile].push_back(Val[5]);                        
    }    
  }



}
  
