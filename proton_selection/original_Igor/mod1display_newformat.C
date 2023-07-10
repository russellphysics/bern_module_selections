//For module 0
//#define LDS_PATH "/data/LRS/SingleModule_2021/Converted/rwf_20210405_203834.data.root"
//#define CRS_PATH "/media/daq/My Book Duo/SingleModule_March21/TPC12/dataRuns/evdData/good_michel/michel_datalog_2021_04_05_20_38_29_CEST_evd.root"

//Path for module 1
//#define LDS_PATH "/data/LRS/SingleModule_Jan22/Converted/rwf_0cd913fb_20220209_021728.data.root"
//#define CRS_PATH "/data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/new/packet_2022_02_09_02_17_27_CETevd.root "

#define LDS_PATH "/data/LRS/SingleModule_Jan22/Converted/"
//#define CRS_PATH "/data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/"
#define CRS_PATH "/data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/fixed_hit_charge/"
//#define CRS_PATH "./"


//#define OUT_PATH  "/data/LArPix/SingleModule_March2021/TPC12/dataRuns/evdData/with_lightreco/integrated_light_oct27/michel_datalog_2021_04_04_16_19_13_CEST_evd_with_integration.root"

//{while(i<=cds_elist->GetN()) {while(display_event(i++)==0) {}}}

#define MAXTRACKS 10
#define MAXHITSINTRACK 20000

#define offset_ns_nmax 128*10

#define ADC1 215553019 //sn ADC1
#define ADC2 215563696 //sn ADC2
#define ADC3 215564636 //sn ADC3

#define PIXPITCH 4.434

//#include <TSystem.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"

  TFile *comf;
  TFile *cdsf;
  TFile *ldsf;
  TFile *outfile;
  TObjString *lds_os;
  TObjString *cds_os;
  TTree *comb_tr;
  TTree *cds_Evtr;
  TTree *cds_Trtr;
  TTree *lds_rwftr;
 // TTree *output_Evtr;
  
  TTree *cds_Evtr_out;
 // TTree *cds_Trtr_out;
  
     Long64_t * trindex; //! transient Tree index array, where entries are sorted by time
int i=0;

  char cut_string[256];
  char fn_string[256];

  
      // Declaration of leaf types
   UInt_t          event =0;
   UInt_t          sn =0;
   UInt_t          ch =0;
   ULong64_t       ntp_ms =0;
   ULong64_t       tai_ns =0;
   ULong64_t       pps_ns =0;
   TH1S            *th1s_ptr;
   Int_t offset_ns[offset_ns_nmax] ={0};
   Int_t offset_ns_n=0;
   Int_t wf =0;
   Int_t t_window =300;
   Float_t integral_temp = 0;

   
   Float_t event_photons=0;

  //Decleration of charge data leaf types
  Int_t track_ID =0, track_nhits=0, event_ID=0, event_ntracks=0, event_nhits=0, event_unix_ts=0, event_start_t=0,
	        track_eventID =0, track_no_in_event=0;
  Float_t theta=0.0, phi=0.0, dl=0.0, track_q=0.0, event_q=0.0, dx=0.0, dy=0.0, dz=0.0;

  //tracks hit properties
  Float_t tr_h_x[MAXHITSINTRACK] ={0.0}, tr_h_y[MAXHITSINTRACK] ={0.0},tr_h_z[MAXHITSINTRACK] ={0.0}, tr_h_q[MAXHITSINTRACK] ={0.0}, tr_h_dr[MAXHITSINTRACK] ={0.0}; //, tr_h_Dt[MAXHITSINTRACK];
 // <vector>float tr_h_x[MAXHITSINTRACK] ={0.0}, tr_h_y[MAXHITSINTRACK] ={0.0},tr_h_z[MAXHITSINTRACK] ={0.0}, tr_h_q[MAXHITSINTRACK] ={0.0}, tr_h_dr[MAXHITSINTRACK] ={0.0}; //, tr_h_Dt[MAXHITSINTRACK];
  Int_t  tr_h_Dt[MAXHITSINTRACK];
  Int_t tr_h_ts[MAXHITSINTRACK];
  

   Float_t         track_residual_x;
   Float_t         track_residual_y;
   Float_t         track_residual_z;

  //events hit properties
  Float_t ev_h_x[MAXHITSINTRACK] ={0.0}, ev_h_y[MAXHITSINTRACK]={0.0},ev_h_z[MAXHITSINTRACK]={0.0}, ev_h_q[MAXHITSINTRACK]={0.0};
  Int_t ev_h_ts[MAXHITSINTRACK] ={0};



  //Decleration of charge data leaf types
  Int_t etrack_ID[MAXTRACKS], etrack_nhits[MAXTRACKS]; 
  Float_t etheta[MAXTRACKS], ephi[MAXTRACKS], edl[MAXTRACKS], etrack_q[MAXTRACKS], edx[MAXTRACKS], edy[MAXTRACKS], edz[MAXTRACKS];

  //tracks hit properties
  Float_t etr_h_x[MAXTRACKS][MAXHITSINTRACK] ={0.0}, etr_h_y[MAXTRACKS][MAXHITSINTRACK] ={0.0},etr_h_z[MAXTRACKS][MAXHITSINTRACK] ={0.0}, etr_h_q[MAXTRACKS][MAXHITSINTRACK] ={0.0}, etr_h_dr[MAXTRACKS][MAXHITSINTRACK] ={0.0}; 
  Int_t  etr_h_Dt[MAXTRACKS][MAXHITSINTRACK];
  Int_t etr_h_ts[MAXTRACKS][MAXHITSINTRACK];
  

   Float_t         etrack_residual_x[MAXTRACKS];
   Float_t         etrack_residual_y[MAXTRACKS];
   Float_t         etrack_residual_z[MAXTRACKS];




  Int_t dev=0;
  EColor color=kBlack;

//TCanvas *c;
//TCanvas *ct;
//TCanvas *cc;

TEventList *cds_elist; //list of associated entries in Events tree in CDS file
TEventList *cdstr_elist; //list of associated entries in Events tree in CDS file
TEventList *rwf_elist; //list of associated entries (by time) in Hits tree in LDS file

Int_t g_eventID;
Int_t Dt_unix_ms;
Int_t Dt_ns;

int new_select(int ev);
int display_event(int ev);
int GetNWaveforms();
TH1S* GetWaveform(int wf);

Float_t gain[2][64] =  {{-1,-1,-1,-1, 207.93, 199.9 , 200.26, 201.94, 198.42, 197.55, 196.46, 206.72, 200.72, 198.26, 196.08, 202.65,
                         -1,-1,-1,-1, 202.69, 203.13, 205.08, 198.69, 202.75, 198.38, 195.29, 201.35, 209.5 , 193.48, 197.86, 203.79,
			 -1,-1,-1,-1, 191.02, 198.2 , 199.18, 191.37, 200.29, 202.07, 193.05, 200.07, 193.33, -1    , 188.39, 189.92,
			 -1,-1,-1,-1, 235.45 ,-124.42, -1   , 211.01, 194.2 , 206.21, 194.45, 192.42, 192.8 , 188.43, 183.18, 194.38},
                        {-1,-1,-1,-1, 199.36, 191.14, 190.03, 197.02, 201.71, 198.16, 188.2 , 192.39, 198.73, 201.79, 183.6 , 197.97,
			 -1,-1,-1,-1, 202.19, 197.61, 198.76, 197.67, 198.18, 190.92, 186.68, 200.38, 189.24, 191.16, 191.96, 186.65,
			 -1,-1,-1,-1, 196.84, 194.07, 195.51, 198.24, 200.72, 198.67, 187.2 , 188.82, 190.32, 196.59, 186.74, 200.24,
			 -1,-1,-1,-1, 191.8 , 199.77, 199.64, 250.9 , 200.79, 200.32, 191.09, 195.39, 203.04, 190.65, 225.22, 217.97}};

  char st[256];
  const char *sptr;

   TH3D *xyz=0;
   TH2D *xy=0, *zy=0;
   TH2F *l_display_1=0;
   TH2F *l_display_2=0;
   TH1S *temp=0, *hsum1[9], *hsum2[9];
   TCanvas *c=0;
   TVirtualPad *c_4=0;
   TH1S *tpc1_sum[9], *tpc2_sum[9];


void RestoreBL(TH1S * h)
{
 Double_t bl;
 Int_t nbl=60;
 bl=0;
 for(int i=0;i<nbl;i++) bl=bl+h->GetBinContent(i+1);
 bl=bl/nbl;
 for(int i=0;i<h->GetXaxis()->GetNbins()-1;i++) 
   { 
     if(h->GetBinContent(i+1)-bl<-65535) h->SetBinContent(i+1,-65535); //32767
     else if(h->GetBinContent(i+1)-bl>65535) h->SetBinContent(i+1,65535);
     else h->SetBinContent(i+1, h->GetBinContent(i+1)-bl);
   }   
}


char fname1[256];
char fname2[256];
char LDS_cut[256];
char CRS_cut[256];
char CRStr_cut[256];

void BuildIndex(TTree *fChain, const char *major,const char *minor)
{
  fChain->BuildIndex(major, minor);
  if(fChain->GetTreeIndex()) trindex=((TTreeIndex*)fChain->GetTreeIndex())->GetIndex();
  else trindex=0;
} 

void mod1display_newformat(const char * CRSfname, const char * LDSfname, const char * CRScut_str="",const char * CRStrcut_str="", const char * LDScut_str="" )
{

  sprintf(LDS_cut,"%s",LDScut_str);
  sprintf(CRS_cut,"%s",CRScut_str);
  sprintf(CRStr_cut,"%s",CRStrcut_str);
  printf("Usage:\n");
  printf("mod1display_newformat(CRSfname, LDSfname, cds_Evtr_cut, cds_Trtr_cut, lds_rwftr_cut )\n");
  sprintf(fname1, "%s%s",CRS_PATH,CRSfname);
  cdsf= new TFile(fname1 , "READ" );
  cout<<"Open CRS file:" << fname1 <<endl;

  cdsf->GetObject("events",cds_Evtr);  //Get event tree
  cdsf->GetObject("tracks",cds_Trtr);
  if(!cds_Evtr) {printf("Cant find Events tree! Exiting.\n"); return;}
  if(!cds_Trtr) {printf("Cant find Tracks tree! Exiting.\n"); return;}
  printf("Events and Tracks tree loaded...\n");

   cds_Trtr->SetBranchAddress("track_nhits",&track_nhits);
   cds_Trtr->SetBranchAddress("trackID", &track_ID);
 //  cds_Trtr->SetBranchAddress("track_eventID",&track_eventID);
   cds_Trtr->SetBranchAddress("eventID",&track_eventID);
   cds_Trtr->SetBranchAddress("track_no_in_event",&track_no_in_event);

   cds_Trtr->SetBranchAddress("track_theta", &theta);
   cds_Trtr->SetBranchAddress("track_phi", &phi);
   cds_Trtr->SetBranchAddress("track_length", &dl);
   cds_Trtr->SetBranchAddress("track_q", &track_q);
   cds_Trtr->SetBranchAddress("track_dx",&dx);
   cds_Trtr->SetBranchAddress("track_dy",&dy);
   cds_Trtr->SetBranchAddress("track_dz",&dz);

   cds_Trtr->SetBranchAddress("track_hits_x", tr_h_x);
   cds_Trtr->SetBranchAddress("track_hits_y", tr_h_y);
   cds_Trtr->SetBranchAddress("track_hits_z", tr_h_z);
   cds_Trtr->SetBranchAddress("track_hits_Dt", tr_h_Dt);
   cds_Trtr->SetBranchAddress("track_hits_q", tr_h_q);
   cds_Trtr->SetBranchAddress("track_hits_dr", tr_h_dr);
   cds_Trtr->SetBranchAddress("track_hits_ts", tr_h_ts);
   
   cds_Trtr->SetBranchAddress("track_residual_x", &track_residual_x);
   cds_Trtr->SetBranchAddress("track_residual_y", &track_residual_y);
   cds_Trtr->SetBranchAddress("track_residual_z", &track_residual_z);

   cds_Trtr->BuildIndex("eventID","track_no_in_event");
   cds_Trtr->SetAlias("contained","track_start_pos_y>-500&&track_start_pos_y<500&&track_start_pos_x>-250&&track_start_pos_x<250&&track_start_pos_z>-250&&track_start_pos_z<250&&track_end_pos_y>-500&&track_end_pos_y<500&&track_end_pos_x>-250&&track_end_pos_x<250&&track_end_pos_z>-250&&track_end_pos_z<250");
cds_Trtr->SetAlias("edge","track_start_pos_y<-500||track_start_pos_y>500||track_start_pos_x<-250||track_start_pos_x>250||track_start_pos_z<-250||track_start_pos_z>250||track_end_pos_y<-500||track_end_pos_y>500||track_end_pos_x<-250||track_end_pos_x>250||track_end_pos_z<-250||track_end_pos_z>250");

cds_Trtr->SetAlias("enterstop","(track_start_pos_y>500 && track_start_pos_x>-250&&track_start_pos_x<250&&track_start_pos_z>-250&&track_start_pos_z<250&&track_end_pos_y>-500&&track_end_pos_y<400&&track_end_pos_x>-250 && track_end_pos_x<250&&track_end_pos_z>-250&&track_end_pos_z<250) || (track_end_pos_y>500 && track_start_pos_x>-250&&track_start_pos_x<250&&track_start_pos_z>-250&&track_start_pos_z<250&&track_start_pos_y>-500&&track_start_pos_y<400&&track_end_pos_x>-250 && track_end_pos_x<250&&track_end_pos_z>-250&&track_end_pos_z<250)");

   cds_Evtr->SetBranchAddress("eventID",&event_ID);
   cds_Evtr->SetBranchAddress("event_unix_ts",&event_unix_ts);
   cds_Evtr->SetBranchAddress("event_start_t",&event_start_t);
   cds_Evtr->SetBranchAddress("event_ntracks",&event_ntracks);
   cds_Evtr->SetBranchAddress("event_nhits",&event_nhits);
   cds_Evtr->SetBranchAddress("event_q",&event_q);
   cds_Evtr->SetBranchAddress("event_hits_x", ev_h_x);
   cds_Evtr->SetBranchAddress("event_hits_y", ev_h_y);
   cds_Evtr->SetBranchAddress("event_hits_z", ev_h_z);
   cds_Evtr->SetBranchAddress("event_hits_q", ev_h_q);
   cds_Evtr->SetBranchAddress("event_hits_ts", ev_h_ts);


   cds_Evtr->SetEventList(0); //This line solved the bug. it will clear the event list 
   cds_Evtr->Draw(">>elist_charge", CRS_cut,"*");
   printf("Selecting charge events with cut:\n%s\n",CRS_cut);
   cds_elist=(TEventList*)gDirectory->Get("elist_charge");
   cds_Evtr->SetEventList(cds_elist);


   //ldsf=new TFile(lds_os->GetString().Data());
  sprintf(fname2, "%s%s",LDS_PATH,LDSfname);
  ldsf= new TFile(fname2);
  cout<<"Open LDS file:" << fname2 <<endl;

   ldsf->GetObject("rwf",lds_rwftr);  //Get light tree
  if(!lds_rwftr) {printf("Cant find Waveforms tree! Exiting.\n"); return;}
  printf("Waveforms tree loaded...\n");          

   lds_rwftr->SetBranchAddress("event", &event);
   lds_rwftr->SetBranchAddress("sn", &sn);
   lds_rwftr->SetBranchAddress("ch", &ch);
   lds_rwftr->SetBranchAddress("ntp_ms", &ntp_ms);
   lds_rwftr->SetBranchAddress("tai_ns", &tai_ns);
   lds_rwftr->SetBranchAddress("tslpps_ns", &pps_ns);
   lds_rwftr->SetBranchAddress("th1s_ptr", &th1s_ptr);
   BuildIndex(lds_rwftr,"ntp_ms","tai_ns");
   



    const Int_t NRGBs = 5;
    const Int_t NCont = 255;

    Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 };
    Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 };
    Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 };
    Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };
    TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
    gStyle->SetNumberContours(NCont);
    gStyle->SetOptStat(0);
TColor(255,0,0,0.5);
//gStyle->SetCanvasPreferGL(true);

// Open output file

sprintf(fn_string,"newformat_%s_%s",CRStr_cut,CRSfname);
printf("Creating output file %s\n",fn_string);
outfile= new TFile(fn_string, "recreate","",9);

//outfile= new TFile("selected_events.root", "recreate");
cds_Evtr_out = cds_Evtr->CloneTree(0);
//cds_Evtr_out = new TTree();

   cds_Evtr_out->Branch("etrack_nhits",etrack_nhits,"etrack_nhits[10]/I");
   cds_Evtr_out->Branch("etrackID", etrack_ID,"etrack_ID[10]/I");
   cds_Evtr_out->Branch("etrack_theta", etheta,"etrack_theta[10]/F");
   cds_Evtr_out->Branch("etrack_phi", ephi,"etrack_phi[10]/F");
   cds_Evtr_out->Branch("etrack_length", edl,"etrack_length[10]/F");
   cds_Evtr_out->Branch("etrack_q", etrack_q,"etrack_q[10]/F");
   cds_Evtr_out->Branch("etrack_dx",edx,"etrack_dx[10]/F");
   cds_Evtr_out->Branch("etrack_dy",edy,"etrack_dy[10]/F");
   cds_Evtr_out->Branch("etrack_dz",edz,"etrack_dz[10]/F");
   cds_Evtr_out->Branch("etrack_hits_x", etr_h_x,"etrack_hits_x[10][20000]/F");
   cds_Evtr_out->Branch("etrack_hits_y", etr_h_y,"etrack_hits_y[10][20000]/F");
   cds_Evtr_out->Branch("etrack_hits_z", etr_h_z,"etrack_hits_z[10][20000]/F");
   cds_Evtr_out->Branch("etrack_hits_Dt",etr_h_Dt,"etrack_hits_Dt[10][20000]/I");
   cds_Evtr_out->Branch("etrack_hits_q", etr_h_q,"etrack_hits_q[10][20000]/F");
   cds_Evtr_out->Branch("etrack_hits_dr", etr_h_dr,"etrack_hits_dr[10][20000]/F");
   cds_Evtr_out->Branch("etrack_hits_ts", etr_h_ts,"etrack_hits_ts[10][20000]/I");
   cds_Evtr_out->Branch("etrack_residual_x", etrack_residual_x,"etrack_residual_x[10]/F");
   cds_Evtr_out->Branch("etrack_residual_y", etrack_residual_y,"etrack_residual_y[10]/F");
   cds_Evtr_out->Branch("etrack_residual_z", etrack_residual_z,"etrack_residual_z[10]/F");

   cds_Evtr_out->Branch("lnegx320", &l_display_1);
   cds_Evtr_out->Branch("lposx320", &l_display_2);

cds_Evtr_out->Branch("event_photons",&event_photons,"event_photons/F");

//cds_Trtr_out = cds_Trtr->CloneTree(0);

}

Int_t bins;
Int_t trel;

int GetNWaveforms()
{
  return rwf_elist->GetN();
 //return my_list->GetN();
}

TH1S* GetWaveform(int wf)
{
  lds_rwftr->GetEntry(rwf_elist->GetEntry(wf));
  //lds_rwftr->GetEntry(my_list->GetEntry(wf));

  RestoreBL(th1s_ptr);
  //trel=offset_ns[wf];
  trel=(tai_ns-36000000000)-1000*(event_unix_ts*1000000+event_start_t/10);
  bins=th1s_ptr->GetXaxis()->GetNbins();
  //cout<<"number of bins: "<<bins<<endl;
//  th1s_ptr->SetLineColor(kRed);
//  th1s_ptr->GetXaxis()->Set(bins,0,998);
  //th1s_ptr->GetXaxis()->Set(bins,trel,trel+bins*16);
  
  //th1s_ptr->SetMinimum( min(-5000.0, th1s_ptr->GetMinimum() ));
  //th1s_ptr->SetMaximum( max(1000.0, th1s_ptr->GetMaximum() ));
  //th1s_ptr->Draw("");
  return th1s_ptr;
}


int new_select(int ev){
  char trcut[256];
   
  cds_Evtr->GetEntry(cds_elist->GetEntry(ev));
  g_eventID=event_ID;

   cds_Trtr->SetEventList(0); //This line solved the bug. it will clear the event list 
   sprintf(trcut,"track_eventID==%d&&!(%s)",event_ID,CRStr_cut);
   cds_Trtr->Draw(">>elist_chargetr",trcut ,"*");
   cdstr_elist=(TEventList*)gDirectory->Get("elist_chargetr");
   if(cdstr_elist->GetN()>0) {printf("There are tracks, satisfying %s. Skipping event.\n",trcut);return 0;} //there are non-contained tracks, for instance
   
   sprintf(trcut,"track_eventID==%d&&%s",event_ID,CRStr_cut);
   cds_Trtr->Draw(">>elist_chargetr",trcut ,"*");
   cdstr_elist=(TEventList*)gDirectory->Get("elist_chargetr");
  
   cds_Trtr->SetEventList(cdstr_elist);
   printf("Sub-Selecting charge events with cut:\n%s\n",trcut);
    printf("%d tracks found for the event, with cut:\n%s\n",cdstr_elist->GetN(),trcut);
   if(cdstr_elist->GetN()==0) {printf("Skipping event.\n");return 0;} 

  printf("Selected charge event with selection index %d, resulting eventID=%d\n",ev, g_eventID);
 
  // I have to open the file again. otherwise the elist is not filled correctly !! I dont know why. 
   cout<<"calling event "<<ev<<endl;
   cout<<"charge event time [us]: "<< (long long)event_unix_ts*1000000 + event_start_t /10 <<endl;
   cout<<event_unix_ts << " , " <<event_start_t <<endl; 

   sprintf(cut_string, "abs(tai_ns/1000-36000000-%lld)< %d ",(long long)event_unix_ts*1000000 + event_start_t /10 , t_window);
   if(strlen(LDS_cut)>0) sprintf(cut_string,"%s && %s", cut_string,LDS_cut);
   printf("Selecting waveforms with cut:\n%s\n",cut_string);
   ldsf->cd();
   lds_rwftr->SetEventList(0); //This line solved the bug. it will clear the event list 
   lds_rwftr->Draw(">>elist_light", cut_string,"*");
   rwf_elist=(TEventList*)gDirectory->Get("elist_light");
   lds_rwftr->SetEventList(rwf_elist);
   cout<<"Found waveforms: "<<rwf_elist->GetN()<<endl;
   lds_rwftr->GetEntry(rwf_elist->GetEntry(0));
   cout<<"light event time [us]: "<< (long long)tai_ns/1000 -36000000 <<endl;
   
   
   
   return 1;
}


  
int display_event(int ev)
{
   int retval=0;
   event_photons=0; 
   cout<<"Plotting event "<<ev<<endl;
   if(new_select(ev)==0) return 0;
 
   int map_sn_ch_to_ybin[2][64]  =  {{-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17,-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17,-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17,-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17},
				    {-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23,-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23,-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23,-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23}};

   int map_sn_ch_to_xbin[2][64]  =  {{-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1},
                                     {-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1}};

   int map_sn_ch_to_tpc[2][64]  =  {{-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2},
				    {-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2}}; 

   int map_sn_ch_to_display[2][64]  =  {{-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1},
                                        {-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1}}; 

//   int map_ch_to_bin[32] ={-1,-1,0,1,2,3,4,5,-1,6,7,8,9,10,11,-1,-1,-1,12,13,14,15,16,17,-1,18,19,20,21,22,23,-1};


   int zbin;
   if(c==0)
   {
   
   for(int i=1;i<=8;i++) 
     { 	
       tpc1_sum[i]=new TH1S(Form("tpc1wf%d",i),"",1000,0,1000); 
       tpc2_sum[i]=new TH1S(Form("tpc2wf%d",i),"",1000,0,1000); 
     }   

//   xyz = new TH3D("3D_view","3D_view", 140,-PIXPITCH*70,PIXPITCH*70 ,140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140);
   xyz = new TH3D("3D_view","3D_view", 35,-PIXPITCH*70,PIXPITCH*70 ,35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140);
   xyz->GetXaxis()->SetTitle("z [mm]");
   xyz->GetYaxis()->SetTitle("x [mm]");
   xyz->GetZaxis()->SetTitle("y [mm]");
   xyz->SetLineWidth(0);

//   TH2D *xy, *zy;
//   xy= new TH2D("xy","front",140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140); 
//   zy= new TH2D("zy","side",140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140); 
   xy= new TH2D("xy","front",35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140); 
   zy= new TH2D("zy","side",35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140); 
   l_display_1 = new TH2F("light_x_-320","light readout x=-320",2,-310,310,24,-620,620);
   l_display_2 = new TH2F("light_x_+320","light readout x=320",2,-310,310,24,-620,620);
//   TH1S *temp, *hsum1[9], *hsum2[9];
   xy->GetXaxis()->SetTitle("x [mm]");
   xy->GetYaxis()->SetTitle("y [mm]");
//   xy->GetZaxis()->SetRangeUser(0,1200);
   xy->GetZaxis()->SetRangeUser(0,4000);
   zy->GetXaxis()->SetTitle("z [mm]");
   zy->GetYaxis()->SetTitle("y [mm]");
//   zy->GetZaxis()->SetRangeUser(0,1200);
   zy->GetZaxis()->SetRangeUser(0,4000);
   
   //c->Clear();
   c = new TCanvas("c","display",900,1000);
   c->Divide(3,2);
   c_4 = c->cd(4); 
   c_4->Divide(2,4);

   }
   else
   {
     xyz->Reset();
     xy->Reset();
     zy->Reset();
     l_display_1->Reset();
     l_display_2->Reset();
        for(int i=1;i<=8;i++) 
     { 	
       tpc1_sum[i]->Reset();
       tpc2_sum[i]->Reset(); 
     }   

   }

   //3D view
   c->cd(1);
/*
   for(int i=0; i< track_nhits; i++){
       //geometry correction
    //    tr_h_y[i]=tr_h_y[i]*((tr_h_y[i]<-310)*-2+1)-3*310*(tr_h_y[i]<-310);
    //    tr_h_x[i]=tr_h_x[i]*((tr_h_y[i]<-310)*-2+1);
        //filling plots
	xyz->Fill(tr_h_z[i], tr_h_x[i], tr_h_y[i], tr_h_q[i]);
	xy->Fill(tr_h_x[i], tr_h_y[i], tr_h_q[i]);
	zy->Fill(tr_h_z[i], tr_h_y[i], tr_h_q[i]);
   }
*/   
      for(int i=0; i< event_nhits && i<MAXHITSINTRACK; i++){
       //geometry correction
    //    ev_h_y[i]=ev_h_y[i]*((ev_h_y[i]<-310)*-2+1)-3*310*(ev_h_y[i]<-310);
    //    ev_h_x[i]=ev_h_x[i]*((ev_h_y[i]<-310)*-2+1);
        //filling plots
	xyz->Fill(ev_h_z[i], ev_h_x[i], ev_h_y[i], ev_h_q[i]);
	xy->Fill(ev_h_x[i], ev_h_y[i], ev_h_q[i]);
	zy->Fill(ev_h_z[i], ev_h_y[i], ev_h_q[i]);
   }

   
   //xyz->GetZaxis()->SetRangeUser(0,1200);
//   xyz->SetMaximum(400);
   xyz->SetMaximum(6000);
   xyz->Draw("BOX2 Z");
   
 //  xyz->Draw("GLBOX1 Z");

   gPad->SetTheta(5);
   gPad->SetPhi(30);
   c->cd(2);

  // cds_Evtr->Draw("event_hits_y*((event_hits_y<-310)*-2+1)-3*310*(event_hits_y<-310):\
//                   event_hits_x*((event_hits_y<-310)*-2+1):\
//                   event_hits_q>>xy_view(155,-310,310,310,-620,620)",Form("eventID == %d",g_eventID),"colz");

   //cds_Evtr->Draw("event_hits_y:event_hits_x:event_hits_q>>xy_view(50,0,1000,320,-320,320,640,-640,640)",Form("eventID == %d",ev),"colz");
   //xy = (TH2D*)gDirectory->Get("xy_view");
   xy->SetTitle(Form("event %d xy view",g_eventID));
   xy->SetStats(0);
   xy->Draw("colz");
   c->cd(3);
   
  // cds_Evtr->Draw("event_hits_y*((event_hits_y<-310)*-2+1)-3*310*(event_hits_y<-310):\
//                   event_hits_z:\
//                   event_hits_q>>zy_view(155,-310,310,310,-620,620)",Form("eventID == %d",g_eventID),"colz");

   //cds_Evtr->Draw("event_hits_y:event_hits_z:event_hits_q>>zy_view(50,0,1000,320,-320,320,640,-640,640)",Form("eventID == %d",ev),"colz");
   //zy =(TH2D*)gDirectory->Get("zy_view");
   zy->SetTitle(Form("Event %d zy view",g_eventID));
   zy->SetStats(0);
   zy->Draw("colz");

   //c->cd(4);
   cout<<" N waveforms: "<< GetNWaveforms()<<endl;
   //if(GetNWaveforms() == 0) continue;

	  integral_temp = 0;

   try{
   	for(int i =0; i < GetNWaveforms(); i++){
	    int adc = -1;
	    integral_temp = 0;
	    temp = GetWaveform(i);
 	    if(sn == ADC1 && gain[0][ch]!=-1){ cout<<"waveform " <<i <<" form ADC1 sn: "<< sn <<" ch: "<<ch << " y bin: " << map_sn_ch_to_ybin[0][ch] \
				<<" x bin: " << map_sn_ch_to_xbin[0][ch] << " tpc " << map_sn_ch_to_tpc[0][ch]  <<" Integral: "<<-1*temp->Integral(61,92)/gain[0][ch] << endl;
			integral_temp = -1*temp->Integral(61,92)/gain[0][ch];
			integral_temp=integral_temp*4; // to bring ACL to the same visual range as LCM
			event_photons=event_photons+integral_temp;
			
	    }
        if(sn == ADC2 && gain[1][ch]!=-1){ cout<<"waveform " <<i <<" form ADC2 sn: "<< sn <<" ch: "<<ch << " y bin: " << map_sn_ch_to_ybin[1][ch] \
				<<" x bin: " << map_sn_ch_to_xbin[1][ch] << " tpc " << map_sn_ch_to_tpc[1][ch] <<" Integral: "<<-1*temp->Integral(61,92)/gain[1][ch] << endl;
            integral_temp = -1*temp->Integral(61,92)/gain[1][ch];
			event_photons=event_photons+integral_temp;
	    }
            if(sn == ADC3 ) cout<<"waveform " <<i <<" form ADC3 sn: "<< sn <<" ch: "<<ch <<" SUM Integral: "<<-1*temp->Integral(61,92)/200 << endl;


	    if (sn == ADC1) adc = 0;
        if (sn == ADC2) adc = 1;

        if(map_sn_ch_to_display[adc][ch] == 1)
		l_display_1->Fill(-150.0 + 300*map_sn_ch_to_xbin[adc][ch] ,-610 + (640+640)/24 *map_sn_ch_to_ybin[adc][ch], integral_temp);

        if(map_sn_ch_to_display[adc][ch] == 2)
        l_display_2->Fill(-150.0 + 300*map_sn_ch_to_xbin[adc][ch] ,-610 + (640+640)/24 *map_sn_ch_to_ybin[adc][ch], integral_temp);

   	 }


	for(int i =0; i < GetNWaveforms(); i++){

     		temp = GetWaveform(i);
                if (sn != ADC3) continue;
      		if(ch == 15){ tpc1_sum[7]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[7]"<<endl;} 
      		if(ch == 47){ tpc1_sum[5]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[5]"<<endl;}
      		if(ch == 14){ tpc1_sum[3]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[3]"<<endl;}
      		if(ch == 46){ tpc1_sum[1]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[1]"<<endl;}

      		if(ch == 13){ tpc1_sum[8]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[8]"<<endl;}
      		if(ch == 45){ tpc1_sum[6]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[6]"<<endl;}
      		if(ch == 12){ tpc1_sum[4]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[4]"<<endl;}
      		if(ch == 44){ tpc1_sum[2]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[2]"<<endl;} 

      		if(ch == 31){ tpc2_sum[8]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[7]"<<endl;} 
      		if(ch == 63){ tpc2_sum[6]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[5]"<<endl;} 
      		if(ch == 30){ tpc2_sum[4]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[3]"<<endl;} 
      		if(ch == 62){ tpc2_sum[2]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[1]"<<endl;} 

      		if(ch == 29){ tpc2_sum[7]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[8]"<<endl;} 
      		if(ch == 61){ tpc2_sum[5]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[6]"<<endl;} 
      		if(ch == 28){ tpc2_sum[3]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[4]"<<endl;} 
      		if(ch == 60){ tpc2_sum[1]->Add(temp); } // = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[2]"<<endl;}
	 
   	}
        cout<<"Sum waveforms filled"<<endl;

	for(Int_t j=1; j<9; j++){
      		c_4->cd(j);
		//cout<<"filling c pad "<< j <<endl;

      		tpc1_sum[j]->SetLineColor(kBlue);
      		tpc1_sum[j]->GetYaxis()->SetRangeUser(-30000,5000);
      		tpc1_sum[j]->Draw("hist");
		//cout<<"draw h "<<j<<endl;

      		tpc2_sum[j]->SetLineColor(kRed);
      		tpc2_sum[j]->GetYaxis()->SetRangeUser(-30000,5000);
      		tpc2_sum[j]->Draw("histsame");
   	}
	
	cout<<"done"<<endl;
   //end of try
   } catch (int i ){
       if(i==1) cout<<"There is no waveforms.";
	if(i==2) cout<<"Half of the waveforms are missing.";
   }
// Fillall arrays with zeros


memset(etrack_nhits, 0, sizeof etrack_nhits);
memset(etrack_ID, 0, sizeof etrack_ID);
memset(etrack_residual_x, 0, sizeof etrack_residual_x);
memset(etrack_residual_y, 0, sizeof etrack_residual_y);
memset(etrack_residual_z, 0, sizeof etrack_residual_z);
memset(etheta, 0, sizeof etheta);
memset(ephi, 0, sizeof ephi);
memset(edl, 0, sizeof edl);
memset(etrack_q, 0, sizeof etrack_q);
memset(edx, 0, sizeof edx);
memset(edy, 0, sizeof edy);
memset(edz, 0, sizeof edz);
memset(etr_h_x, 0, sizeof etr_h_x);
memset(etr_h_y, 0, sizeof etr_h_y);
memset(etr_h_z, 0, sizeof etr_h_z);
memset(etr_h_q, 0, sizeof etr_h_q);
memset(etr_h_Dt, 0, sizeof etr_h_Dt);
memset(etr_h_dr, 0, sizeof etr_h_dr);
memset(etr_h_ts, 0, sizeof etr_h_ts);


 for(int ti=0; ti<cdstr_elist->GetN() && ti<10;ti++)
 {  
   cds_Trtr->GetEntry(cdstr_elist->GetEntry(ti));
   printf("Track #%d length=%f q=%f dq/dL=%f theta=%f phi=%f\n",ti,dl,track_q,track_q/dl,theta,phi);
   printf("Residuals: %f %f %f\n",track_residual_x,track_residual_y,track_residual_z);
   
   etrack_nhits[ti]=track_nhits;  //  "etrack_nhits[MAXTRACKS]/I");
   etrack_ID[ti]=track_ID;  //  "etrack_ID[MAXTRACKS]/I");
   etheta[ti]=theta;  //  "etrack_theta[MAXTRACKS]/F");
   ephi[ti]= phi; //  "etrack_phi[MAXTRACKS]/F");
   edl[ti]=dl;  //  "etrack_length[MAXTRACKS]/F");
   etrack_q[ti]=track_q;  //  "etrack_q[MAXTRACKS]/F");
   edx[ti]=dx;  //  "etrack_dx[MAXTRACKS]/F");
   edy[ti]=dy;  //  "etrack_dy[MAXTRACKS]/F");
   edz[ti]=dy;  //  "etrack_dz[MAXTRACKS]/F");
   etrack_residual_x[ti]=track_residual_x;  //  "etrack_residual_x[MAXTRACKS]/F");
   etrack_residual_y[ti]=track_residual_y;  //  "etrack_residual_y[MAXTRACKS]/F");
   etrack_residual_z[ti]=track_residual_z;  //  "etrack_residual_z[MAXTRACKS]/F");
   for(int hi=0; hi<track_nhits && hi<MAXHITSINTRACK;hi++)
   {
    etr_h_x[ti][hi]=tr_h_x[hi];  //  "etrack_hits_x[MAXTRACKS][MAXHITSINTRACK]/F");
    etr_h_y[ti][hi]=tr_h_y[hi];  //  "etrack_hits_y[MAXTRACKS][MAXHITSINTRACK]/F");
    etr_h_z[ti][hi]=tr_h_z[hi];  //  "etrack_hits_z[MAXTRACKS][MAXHITSINTRACK]/F");
    etr_h_Dt[ti][hi]=tr_h_Dt[hi];  //  "etrack_hits_Dt[MAXTRACKS][MAXHITSINTRACK]/I");
    etr_h_q[ti][hi]=tr_h_q[hi];  //  "etrack_hits_q[MAXTRACKS][MAXHITSINTRACK]/F");
    etr_h_dr[ti][hi]=tr_h_dr[hi];  //  "etrack_hits_dr[MAXTRACKS][MAXHITSINTRACK]/F");
    etr_h_ts[ti][hi]=tr_h_ts[hi];  //  "etrack_hits_ts[MAXTRACKS][MAXHITSINTRACK]/I");   
   }
 //  cds_Trtr_out->Fill(); 
 }

 cds_Evtr_out->Fill(); 

 outfile->Write("",TObject::kOverwrite);  
 retval=GetNWaveforms();
 
         c->cd(5);
	float max_light = max(l_display_1->GetMaximum() , l_display_2->GetMaximum()); 
	//max_light = min(4000.00 , max_light);
   	l_display_1->SetMaximum(max_light);
	l_display_1->SetMinimum(min(l_display_1->GetMinimum() , l_display_2->GetMinimum()));
        l_display_1->GetXaxis()->SetTitle("z [mm]");
        l_display_1->GetYaxis()->SetTitle("y [mm]");
	l_display_1->SetStats(0);
   	l_display_1->Draw("colz");

   	c->cd(6);
   	l_display_2->SetMaximum(max_light);
    l_display_2->SetMinimum(min(l_display_1->GetMinimum() , l_display_2->GetMinimum()));
        l_display_2->GetXaxis()->SetTitle("z [mm]");
        l_display_2->GetYaxis()->SetTitle("y [mm]");
    l_display_2->SetStats(0);
   	l_display_2->Draw("colz");

 c->Update();

 return retval;
}

/*
packet_2022_02_11_06_20_17_CETevd.root

HIPs:
8223
8869 (2 HIPs)
19361
26514

Broken MIPS:
20992
23597



root_files_with_swapped_tiles_geometry_before_18_March_2022/packet_2022_02_11_05_00_12_CETevd.root

HIPs:
3037
7814
11317
11724
12321
13300
14853
15325
18611
23314


Broken MIPS:


HIP like MIPs?
3137
3643
3645
4676
6001
8608


 
NuMu-like
4263
9967
_2022_02_11_05_00_12_CETevd.root
*/




