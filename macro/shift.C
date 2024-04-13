Int_t runnumber;
const char* shift_figs_file;


void shift(Int_t InputRunnumber) {
  
  runnumber=InputRunnumber;

  // Add steering file
  gROOT->ProcessLine(Form(
			  "add steering/chk_shift.yaml NUM=%d",
			  runnumber
			  ));
  // Resume analysis
  
  
  
  //art::TLoopManager::Instance()->GetLoop(0)->Resume();
  gApplication->ProcessLine("res");
  //genHisto();
  
  
  
}

  





void genHisto(){
  shift_figs_file = Form("figs/shift/shift_run%d.pdf",runnumber);
  
  // Make histograms
  //shift_figs_file = Form("figs/shift/shift_run%d.pdf",runnumber);
  //TString  shift_figs_file = Form("figs/shift/shit_run%d.pdf",runnumber);
  //const char*  shift_figs_file = Form("figs/shift/shift_run%d.pdf",9999);

  
 TString PL[6]={"x1","x2","u1","u2","v1","v2"};

  TString back="cd";
  
  // GR VDC ID
  gApplication->ProcessLine("zon 2 2 ");
    gApplication->ProcessLine(Form(
    "gcom run %d GR VDC ID",
    runnumber
  ));
  
  for(int i=0;i<4;i++){
    gApplication->ProcessLine(back);
    gApplication->ProcessLine("cd vdc_gr_"+PL[i]);
    gApplication->ProcessLine("ht vdc_gr_"+PL[i]+"_id");
  }
  //Print 1st canvas
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s(\")",shift_figs_file));


  // VDC GR ID vs Charge
  gApplication->ProcessLine("zon 2 2 ");
  gApplication->ProcessLine(Form(
    "gcom run %d GR VDC ID vs Charge ",
    runnumber
  ));
  for(int i=0;i<4;i++){
    gApplication->ProcessLine(back);
    gApplication->ProcessLine("cd vdc_gr_"+PL[i]);
    gApplication->ProcessLine("ht vdc_gr_"+PL[i]+"_idq colz");
  }
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));


  // VDC GR ID vs Timing
  gApplication->ProcessLine("zon 2 2 ");
  gApplication->ProcessLine(Form(
    "gcom run %d GR VDC ID vs Timing ",
    runnumber
  ));
  for(int i=0;i<4;i++){
    gApplication->ProcessLine(back);
    gApplication->ProcessLine("cd vdc_gr_"+PL[i]);
    gApplication->ProcessLine("ht vdc_gr_"+PL[i]+"_idt colz");
  }
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));

  // VDC LAS ID
  gApplication->ProcessLine("zon 3 2 ");
  gApplication->ProcessLine(Form(
    "gcom run %d LAS VDC ID ",
    runnumber
  ));
  for(int i=0;i<6;i++){
    gApplication->ProcessLine(back);
    gApplication->ProcessLine("cd vdc_las_"+PL[i]);
    gApplication->ProcessLine("ht vdc_las_"+PL[i]+"_id");
  }
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));

  // VDC LAS ID vs Charge
  gApplication->ProcessLine("zon 3 2 ");
  gApplication->ProcessLine(Form(
    "gcom run %d LAS VDC ID vs Charge ",
    runnumber
  ));
  for(int i=0;i<6;i++){
    gApplication->ProcessLine(back);
    gApplication->ProcessLine("cd vdc_las_"+PL[i]);
    gApplication->ProcessLine("ht vdc_las_"+PL[i]+"_idq colz");
  }
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));

  // VDC LAS ID vs Timing
  gApplication->ProcessLine("zon 3 2 ");
  gApplication->ProcessLine(Form(
    "gcom run %d LAS VDC ID vs Timing ",
    runnumber
  ));
  for(int i=0;i<6;i++){
    gApplication->ProcessLine(back);
    gApplication->ProcessLine("cd vdc_las_"+PL[i]);
    gApplication->ProcessLine("ht vdc_las_"+PL[i]+"_idt colz");
  }
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));
  //gApplication->ProcessLine(Form("artcanvas->Print(\"%s)\")",shift_figs_file));

  // GR plastic 
  for(int i=1;i<3;i++){
    gApplication->ProcessLine("zon 2 2 ");
    gApplication->ProcessLine(Form(
     "gcom run %d GR %d plastic ",
     i,
     runnumber
   ));

    gApplication->ProcessLine(back);
    gApplication->ProcessLine(Form("cd plastic_gr_%d",i));
    gApplication->ProcessLine(Form("ht qlx_gr_%d colz",i));
    gApplication->ProcessLine(Form("ht qrx_gr_%d colz",i));
    gApplication->ProcessLine(Form("ht q_gr_%d_lr colz",i));

    gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));
  }
  
  // LAS plastic 
  for(int i=3;i<7;i++){
    gApplication->ProcessLine("zon 2 2 ");
    gApplication->ProcessLine(Form(
     "gcom run %d LAS  %d plastic ",
     i,
     runnumber
     ));

    gApplication->ProcessLine(back);
    gApplication->ProcessLine(Form("cd plastic_las_%d",i));
    gApplication->ProcessLine(Form("ht qlx_las_%d colz",i));
    gApplication->ProcessLine(Form("ht qrx_las_%d colz",i));
    gApplication->ProcessLine(Form("ht q_las_%d_lr colz",i));
    gApplication->ProcessLine(Form("artcanvas->Print(\"%s\")",shift_figs_file));
  }

  shift_figs_file = Form("figs/shift/shift_run%d.pdf",runnumber);
  gApplication->ProcessLine("zon 2 2 ");
  gApplication->ProcessLine(Form(
    "gcom run %d ",    
     runnumber
   ));
  gApplication->ProcessLine(back);
  gApplication->ProcessLine("cd tc");
  gApplication->ProcessLine("ht tc");
  //Print last canvas
  gApplication->ProcessLine(Form("artcanvas->Print(\"%s)\")",shift_figs_file));
  
  //Open pdf
  std::cout << Form("%s was generated!" ,shift_figs_file) << std::endl;
  gApplication->ProcessLine(Form(".! xdg-open %s",shift_figs_file));
  

  
  
}

void priHisto(){
  shift_figs_file = Form("figs/shift/shift_run%d.pdf",runnumber);
  const char* current_dir=get_current_dir_name();
  gApplication->ProcessLine(Form(".! ssh aino-2 lpr -P rcc4000a %s/%s",current_dir,shift_figs_file));
}

void openHisto(){
  shift_figs_file = Form("figs/shift/shift_run%d.pdf",runnumber);
  gApplication->ProcessLine(Form(".! xdg-open %s",shift_figs_file));

}


