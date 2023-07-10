
#define CRS_PATH "./"

#define offset_ns_nmax 128*10

#define PIXPITCH 4.434


//#define MIP_HIP_SELECTOR 0  //HIP selector
//#define MIP_HIP_SELECTOR 1  //MIP selector
#define THRESHOLD_ON_MAX_BIN 300 //for HIPS selection
//#define THRESHOLD_ON_MAX_BIN 0 //No selection

//#include <TSystem.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"
int i=0;
  TFile *comf;
  TFile *cdsf;
  TFile *outfile;
  TObjString *cds_os;
  TTree *comb_tr;
  TTree *cds_Evtr;
  TTree *cds_EvHough;
  TObjArray * larr;
#define ROAD 20
TH1F h_residuals("h_residuals","h_residuals",ROAD,0,ROAD); //ROAD here defines track road in mm for hit assignment and integration
  
  
     Long64_t * trindex; //! transient Tree index array, where entries are sorted by time


  char cut_string[256];
  char fn_string[256];

  
      // Declaration of leaf types
      
      
        // Declaration of leaf types
   Int_t           eventID;
   Int_t           event_start_t;
   Int_t           event_end_t;
   Int_t           event_duration;
   Int_t           event_unix_ts;
   Int_t           event_nhits;
   Float_t         event_q;
   Float_t         event_q_raw;
   Int_t           event_ntracks;
   Int_t           event_n_ext_trigs;
   Float_t         event_hits_x[100000];   //[event_nhits]
   Float_t         event_hits_y[100000];   //[event_nhits]
   Float_t         event_hits_z[100000];   //[event_nhits]
   Int_t           event_hits_ts[100000];   //[event_nhits]
   Float_t         event_hits_q[100000];   //[event_nhits]
   Float_t         event_hits_q_raw[100000];   //[event_nhits]
   Int_t           event_hits_Dt[100000];   //[event_nhits]
   Int_t           event_hits_io_group[100000];   //[event_nhits]
   Int_t           event_hits_chipid[100000];   //[event_nhits]
   Int_t           event_hits_channelid[100000];   //[event_nhits]
   Int_t           event_hits_io_channel[100000];   //[event_nhits]
   Int_t           trigID[10];   //[event_n_ext_trigs]
   Int_t           trig_type[10];   //[event_n_ext_trigs]
   Int_t           trig_ts[10];   //[event_n_ext_trigs]
   Int_t           trig_eventID[10];   //[event_n_ext_trigs]
   Int_t           etrack_nhits[10];
   Int_t           etrackID[10];
   Float_t         etrack_theta[10];
   Float_t         etrack_phi[10];
   Float_t         etrack_length[10];
   Float_t         etrack_q[10];
   Float_t         etrack_dx[10];
   Float_t         etrack_dy[10];
   Float_t         etrack_dz[10];
   Float_t         etrack_hits_x[10][20000];
   Float_t         etrack_hits_y[10][20000];
   Float_t         etrack_hits_z[10][20000];
   Int_t           etrack_hits_Dt[10][20000];
   Float_t         etrack_hits_q[10][20000];
   Float_t         etrack_hits_dr[10][20000];
   Int_t           etrack_hits_ts[10][20000];
   Float_t         etrack_residual_x[10];
   Float_t         etrack_residual_y[10];
   Float_t         etrack_residual_z[10];
   TH2F            *lnegx320;
   TH2F            *lposx320;
   Float_t         event_photons;
   
   
     Int_t nvox;
  Float_t vox_x[100000], vox_y[100000], vox_z[100000], vox_q[100000]; //voxels after unfolding
  Int_t track_nvox;
  Float_t htr_vox_x[10][20000], htr_vox_y[10][20000], htr_vox_z[10][20000], htr_vox_q[10][20000]; //voxels after unfolding


   // List of branches
   TBranch        *b_eventID;   //!
   TBranch        *b_event_start_t;   //!
   TBranch        *b_event_end_t;   //!
   TBranch        *b_event_duration;   //!
   TBranch        *b_event_unix_ts;   //!
   TBranch        *b_event_nhits;   //!
   TBranch        *b_event_q;   //!
   TBranch        *b_event_q_raw;   //!
   TBranch        *b_event_ntracks;   //!
   TBranch        *b_event_n_ext_trigs;   //!
   TBranch        *b_event_hits_x;   //!
   TBranch        *b_event_hits_y;   //!
   TBranch        *b_event_hits_z;   //!
   TBranch        *b_event_hits_ts;   //!
   TBranch        *b_event_hits_q;   //!
   TBranch        *b_event_hits_q_raw;   //!
   TBranch        *b_event_hits_Dt;   //!
   TBranch        *b_event_hits_io_group;   //!
   TBranch        *b_event_hits_chipid;   //!
   TBranch        *b_event_hits_channelid;   //!
   TBranch        *b_event_hits_io_channel;   //!
   TBranch        *b_trigID;   //!
   TBranch        *b_trig_type;   //!
   TBranch        *b_trig_ts;   //!
   TBranch        *b_trig_eventID;   //!
   TBranch        *b_etrack_nhits;   //!
   TBranch        *b_etrack_ID;   //!
   TBranch        *b_etrack_theta;   //!
   TBranch        *b_etrack_phi;   //!
   TBranch        *b_etrack_length;   //!
   TBranch        *b_etrack_q;   //!
   TBranch        *b_etrack_dx;   //!
   TBranch        *b_etrack_dy;   //!
   TBranch        *b_etrack_dz;   //!
   TBranch        *b_etrack_hits_x;   //!
   TBranch        *b_etrack_hits_y;   //!
   TBranch        *b_etrack_hits_z;   //!
   TBranch        *b_etrack_hits_Dt;   //!
   TBranch        *b_etrack_hits_q;   //!
   TBranch        *b_etrack_hits_dr;   //!
   TBranch        *b_etrack_hits_ts;   //!
   TBranch        *b_etrack_residual_x;   //!
   TBranch        *b_etrack_residual_y;   //!
   TBranch        *b_etrack_residual_z;   //!
   TBranch        *b_lnegx320;   //!
   TBranch        *b_lposx320;   //!
   TBranch        *b_event_photons;   //!
   
   
   
   UInt_t          event =0;
   UInt_t          sn =0;
   UInt_t          ch =0;
   ULong64_t       ntp_ms =0;
   ULong64_t       tai_ns =0;
   ULong64_t       pps_ns =0;
   Int_t offset_ns[offset_ns_nmax] ={0};
   Int_t offset_ns_n=0;
   Int_t wf =0;
   Int_t t_window =300;
   

  Int_t dev=0;
  EColor color=kBlack;


TEventList *cds_elist; //list of associated entries in Events tree in CDS file

Int_t g_eventID;
Int_t Dt_unix_ms;
Int_t Dt_ns;
bool g_selMIP=0;
bool g_selHIP=0;
int new_select(int ev);
int display_event(int ev);

  char st[256];
  const char *sptr;
   TH1F *kernel;
   TH3D *xyz0;
   TH3D *xyz_out;

   TH3D *xyz=0;
   TH2D *xy=0, *zy=0;
   TH1S *temp=0, *hsum1[9], *hsum2[9];
   TCanvas *c=0;
   TVirtualPad *c_4=0;
   TH1S *tpc1_sum[9], *tpc2_sum[9];



char fname1[256];
char fname2[256];
char LDS_cut[256];
char CRS_cut[256];


//Hough-reco tracks
#define MAXTRACKS 10
Double_t ax[MAXTRACKS],ay[MAXTRACKS],az[MAXTRACKS],nx[MAXTRACKS],ny[MAXTRACKS],nz[MAXTRACKS];
Int_t npts[MAXTRACKS]; //number of XYZ voxels in track
Int_t nhtracks; 
Double_t qhts[MAXTRACKS]; //total summed charge hits around the track path
Double_t rhits[MAXTRACKS]; //hit-track residual RMS
Int_t nhts[MAXTRACKS]; //number of raw hits in track
Double_t tl[MAXTRACKS]; //track length
Double_t pE[MAXTRACKS]; //proton energy corresponding to tl (from CSDA data)

   Float_t         htracks_start_x[MAXTRACKS];
   Float_t         htracks_start_y[MAXTRACKS];
   Float_t         htracks_start_z[MAXTRACKS];
   Float_t         htracks_end_x[MAXTRACKS];
   Float_t         htracks_end_y[MAXTRACKS];
   Float_t         htracks_end_z[MAXTRACKS];
   Int_t htracks_ID[10];
   Int_t htracks_nvox[10];
   Float_t   htr_h_x[10][20000], htr_h_y[10][20000], htr_h_z[10][20000], htr_h_q[10][20000] ;

int new_select(int ev);
int display_event(int ev);
void UnfoldResponse();

TGraph *pEfromRange;

void ReadProton_Range() //Fill E(MeV)  vs Range(mm) from CSDA data. Usage:   pEfromRange->Eval(Float_t range)
{
TTree *tprange;
tprange=new TTree();
tprange->ReadFile("Proton_CSDA_RANGE_in_Ar.txt","E/F:R/F");
int n=tprange->Draw("R*10/1.4:E","E>20&&E<600","goff");
//int n = tree->Draw("x","","",3950,0);
pEfromRange = new TGraph(n, tprange->GetV1(), tprange->GetV2());
//pEfromRange->Draw("APL");
}



void BuildIndex(TTree *cds_Evtr, const char *major,const char *minor)
{
  cds_Evtr->BuildIndex(major, minor);
  if(cds_Evtr->GetTreeIndex()) trindex=((TTreeIndex*)cds_Evtr->GetTreeIndex())->GetIndex();
  else trindex=0;
} 

void RecoHough_newformat(const char * CRSfname, const char * CRScut_str="")
{
ReadProton_Range();

  sprintf(CRS_cut,"%s",CRScut_str);
  printf("Usage:\n");
  printf("RecoHough_newformat(CRSfname, cds_Evtr_cut)\n");
  sprintf(fname1, "%s%s",CRS_PATH,CRSfname);
  cdsf= new TFile(fname1 , "READ" );
  cout<<"Open CRS file:" << fname1 <<endl;

  cdsf->GetObject("events",cds_Evtr);  //Get event tree
  if(!cds_Evtr) {printf("Cant find Events tree! Exiting.\n"); return;}
  printf("Events tree loaded...\n");



   cds_Evtr->SetBranchAddress("eventID", &eventID, &b_eventID);
   cds_Evtr->SetBranchAddress("event_start_t", &event_start_t, &b_event_start_t);
   cds_Evtr->SetBranchAddress("event_end_t", &event_end_t, &b_event_end_t);
   cds_Evtr->SetBranchAddress("event_duration", &event_duration, &b_event_duration);
   cds_Evtr->SetBranchAddress("event_unix_ts", &event_unix_ts, &b_event_unix_ts);
   cds_Evtr->SetBranchAddress("event_nhits", &event_nhits, &b_event_nhits);
   cds_Evtr->SetBranchAddress("event_q", &event_q, &b_event_q);
   cds_Evtr->SetBranchAddress("event_q_raw", &event_q_raw, &b_event_q_raw);
   cds_Evtr->SetBranchAddress("event_ntracks", &event_ntracks, &b_event_ntracks);
   cds_Evtr->SetBranchAddress("event_n_ext_trigs", &event_n_ext_trigs, &b_event_n_ext_trigs);
   cds_Evtr->SetBranchAddress("event_hits_x", event_hits_x, &b_event_hits_x);
   cds_Evtr->SetBranchAddress("event_hits_y", event_hits_y, &b_event_hits_y);
   cds_Evtr->SetBranchAddress("event_hits_z", event_hits_z, &b_event_hits_z);
   cds_Evtr->SetBranchAddress("event_hits_ts", event_hits_ts, &b_event_hits_ts);
   cds_Evtr->SetBranchAddress("event_hits_q", event_hits_q, &b_event_hits_q);
   cds_Evtr->SetBranchAddress("event_hits_q_raw", event_hits_q_raw, &b_event_hits_q_raw);
   cds_Evtr->SetBranchAddress("event_hits_Dt", event_hits_Dt, &b_event_hits_Dt);
   cds_Evtr->SetBranchAddress("event_hits_io_group", event_hits_io_group, &b_event_hits_io_group);
   cds_Evtr->SetBranchAddress("event_hits_chipid", event_hits_chipid, &b_event_hits_chipid);
   cds_Evtr->SetBranchAddress("event_hits_channelid", event_hits_channelid, &b_event_hits_channelid);
   cds_Evtr->SetBranchAddress("event_hits_io_channel", event_hits_io_channel, &b_event_hits_io_channel);
   cds_Evtr->SetBranchAddress("trigID", trigID, &b_trigID);
   cds_Evtr->SetBranchAddress("trig_type", trig_type, &b_trig_type);
   cds_Evtr->SetBranchAddress("trig_ts", trig_ts, &b_trig_ts);
   cds_Evtr->SetBranchAddress("trig_eventID", trig_eventID, &b_trig_eventID);
   cds_Evtr->SetBranchAddress("etrack_nhits", etrack_nhits, &b_etrack_nhits);
   cds_Evtr->SetBranchAddress("etrackID", etrackID, &b_etrack_ID);
   cds_Evtr->SetBranchAddress("etrack_theta", etrack_theta, &b_etrack_theta);
   cds_Evtr->SetBranchAddress("etrack_phi", etrack_phi, &b_etrack_phi);
   cds_Evtr->SetBranchAddress("etrack_length", etrack_length, &b_etrack_length);
   cds_Evtr->SetBranchAddress("etrack_q", etrack_q, &b_etrack_q);
   cds_Evtr->SetBranchAddress("etrack_dx", etrack_dx, &b_etrack_dx);
   cds_Evtr->SetBranchAddress("etrack_dy", etrack_dy, &b_etrack_dy);
   cds_Evtr->SetBranchAddress("etrack_dz", etrack_dz, &b_etrack_dz);
   cds_Evtr->SetBranchAddress("etrack_hits_x", etrack_hits_x, &b_etrack_hits_x);
   cds_Evtr->SetBranchAddress("etrack_hits_y", etrack_hits_y, &b_etrack_hits_y);
   cds_Evtr->SetBranchAddress("etrack_hits_z", etrack_hits_z, &b_etrack_hits_z);
   cds_Evtr->SetBranchAddress("etrack_hits_Dt", etrack_hits_Dt, &b_etrack_hits_Dt);
   cds_Evtr->SetBranchAddress("etrack_hits_q", etrack_hits_q, &b_etrack_hits_q);
   cds_Evtr->SetBranchAddress("etrack_hits_dr", etrack_hits_dr, &b_etrack_hits_dr);
   cds_Evtr->SetBranchAddress("etrack_hits_ts", etrack_hits_ts, &b_etrack_hits_ts);
   cds_Evtr->SetBranchAddress("etrack_residual_x", etrack_residual_x, &b_etrack_residual_x);
   cds_Evtr->SetBranchAddress("etrack_residual_y", etrack_residual_y, &b_etrack_residual_y);
   cds_Evtr->SetBranchAddress("etrack_residual_z", etrack_residual_z, &b_etrack_residual_z);
   cds_Evtr->SetBranchAddress("lnegx320", &lnegx320, &b_lnegx320);
   cds_Evtr->SetBranchAddress("lposx320", &lposx320, &b_lposx320);
   cds_Evtr->SetBranchAddress("event_photons", &event_photons, &b_event_photons);

   cds_Evtr->SetEventList(0); //This line solved the bug. it will clear the event list 
   cds_Evtr->Draw(">>elist_charge", CRS_cut,"*");
   printf("Selecting charge events with cut:\n%s\n",CRS_cut);
   cds_elist=(TEventList*)gDirectory->Get("elist_charge");
   cds_Evtr->SetEventList(cds_elist);

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

sprintf(fn_string,"HoughReco_%s",CRSfname);
printf("Creating output file %s\n",fn_string);
outfile= new TFile(fn_string, "recreate","",9);
//outfile->cd();
//cds_EvHough=cds_Evtr->CloneTree(0);
//cds_Vtx=new TTree();
cds_EvHough=new TTree();


   cds_EvHough->Branch("eventID", &eventID, "eventID/I");
   cds_EvHough->Branch("event_start_t", &event_start_t, "event_start_t/I");
   cds_EvHough->Branch("event_end_t", &event_end_t, "event_end_t/I");
   cds_EvHough->Branch("event_duration", &event_duration, "event_duration/I");
   cds_EvHough->Branch("event_unix_ts", &event_unix_ts, "event_unix_ts/I");
   cds_EvHough->Branch("event_nhits", &event_nhits, "event_nhits/I");
   cds_EvHough->Branch("event_q", &event_q, "event_q/F");
   cds_EvHough->Branch("event_ntracks", &event_ntracks, "event_ntracks/I");
   cds_EvHough->Branch("event_n_ext_trigs", &event_n_ext_trigs, "event_n_ext_trigs/I");
   cds_EvHough->Branch("trigID", trigID, "trigID/I");
   cds_EvHough->Branch("trig_type", trig_type, "trig_type/I");
   cds_EvHough->Branch("trig_ts", trig_ts, "trig_ts/I");
   cds_EvHough->Branch("trig_eventID", trig_eventID, "trig_eventID/I");
   cds_EvHough->Branch("lnegx320", &lnegx320);
   cds_EvHough->Branch("lposx320", &lposx320);
   cds_EvHough->Branch("event_photons", &event_photons, "event_photons/I");



cds_EvHough->Branch("nhtracks",&nhtracks,"nhtracks/I");
cds_EvHough->Branch("htracks_ax",ax,"ax[nhtracks]/D");
cds_EvHough->Branch("htracks_ay",ay,"ay[nhtracks]/D");
cds_EvHough->Branch("htracks_az",az,"az[nhtracks]/D");
cds_EvHough->Branch("htracks_nx",nx,"nx[nhtracks]/D");
cds_EvHough->Branch("htracks_ny",ny,"ny[nhtracks]/D");
cds_EvHough->Branch("htracks_nz",nz,"nz[nhtracks]/D");

cds_EvHough->Branch("htracks_start_x", htracks_start_x,"htracks_start_x[nhtracks]/F");
cds_EvHough->Branch("htracks_start_y", htracks_start_y,"htracks_start_y[nhtracks]/F");
cds_EvHough->Branch("htracks_start_z", htracks_start_z,"htracks_start_z[nhtracks]/F");

cds_EvHough->Branch("htracks_end_x", htracks_end_x,"htracks_end_x[nhtracks]/F");
cds_EvHough->Branch("htracks_end_y", htracks_end_y,"htracks_end_y[nhtracks]/F");
cds_EvHough->Branch("htracks_end_z", htracks_end_z,"htracks_end_z[nhtracks]/F");


cds_EvHough->Branch("htracks_ID",htracks_ID,"htracks_ID[nhtracks]/I");
cds_EvHough->Branch("htracks_npts",npts,"npts[nhtracks]/I");
cds_EvHough->Branch("htracks_qhts",qhts,"qhts[nhtracks]/D");
cds_EvHough->Branch("htracks_rhits",rhits,"rhits[nhtracks]/D");
cds_EvHough->Branch("htracks_nhts",nhts,"nhts[nhtracks]/I");
cds_EvHough->Branch("htracks_tl",tl,"htl[nhtracks]/D");
cds_EvHough->Branch("htracks_pE",pE,"pE[nhtracks]/D");

//tracks

//cds_EvHough->Branch("htrack_nhits",htrack_nhits,"htrack_nhits[10]/I");
cds_EvHough->Branch("htrack_hits_x", htr_h_x,"htr_h_x[10][10000]/F");
cds_EvHough->Branch("htrack_hits_y", htr_h_y,"htr_h_y[10][10000]/F");
cds_EvHough->Branch("htrack_hits_z", htr_h_z,"htr_h_z[10][10000]/F");
cds_EvHough->Branch("htrack_hits_q", htr_h_q,"htr_h_q[10][10000]/F");


cds_EvHough->Branch("htracks_nvox",htracks_nvox,"htracks_nvox[10]/I");
cds_EvHough->Branch("htrack_vox_x", htr_vox_x,"htr_vox_x[10][10000]/F");
cds_EvHough->Branch("htrack_vox_y", htr_vox_y,"htr_vox_y[10][10000]/F");
cds_EvHough->Branch("htrack_vox_z", htr_vox_z,"htr_vox_z[10][10000]/F");
cds_EvHough->Branch("htrack_vox_q", htr_vox_q,"htr_vox_q[10][10000]/F");

/*

cds_Vtx->Branch("eventID",&eventID,"eventID/I");
cds_Vtx->Branch("event_unix_ts",&event_unix_ts,"event_unix_ts/I");

cds_Vtx->Branch("vertex_x",&vertex_x,"vertex_x/F");
cds_Vtx->Branch("vertex_y",&vertex_y,"vertex_y/F");
cds_Vtx->Branch("vertex_z",&vertex_z,"vertex_z/F");
cds_Vtx->Branch("vertex_ID",&vertex_ID,"vertex_ID/I");
cds_Vtx->Branch("vertex_mult",&vertex_mult,"vertex_mult/I");
cds_Vtx->Branch("vertex_tracksID",vertex_tracksID,"vertex_tracksID[vertex_mult]/I");
*/

   kernel=new TH1F("kernel","kernel",100,0,100);
   for(int i=0;i<100;i++) kernel->Fill(i,1./(i*7.+1));

}

Int_t bins;
Int_t trel;


int new_select(int ev){
  char trcut[256];
  if(ev>cds_elist->GetN()) {printf("No event with this number!\n"); return -1;} 
   
  cds_Evtr->GetEntry(cds_elist->GetEntry(ev));
  g_eventID=eventID;

 
   cout<<"calling event "<<ev<<endl;
   cout<<"charge event time [us]: "<< (long long)event_unix_ts*1000000 + event_start_t /10 <<endl;
   cout<<event_unix_ts << " , " <<event_start_t <<endl; 
   
   return 1;
}


   TString s;

  
int display_event(int ev)
{
   char line[128];
   int retval=0;
   int selval=0;
   //event_photons=0; 
   cout<<"Plotting event "<<ev<<endl;
   selval=new_select(ev);
   if(selval<=0) return selval;
 
 
 memset(htr_h_x, 0, sizeof htr_h_x);
 memset(htr_h_y, 0, sizeof htr_h_y);
 memset(htr_h_z, 0, sizeof htr_h_z);
 memset(htr_h_q, 0, sizeof htr_h_q);
 memset(htr_vox_x, 0, sizeof htr_vox_x);
 memset(htr_vox_y, 0, sizeof htr_vox_y);
 memset(htr_vox_z, 0, sizeof htr_vox_z);
 memset(htr_vox_q, 0, sizeof htr_vox_q);

 
   int zbin;
   if(c==0)
   {
   

   xyz = new TH3D("3D_view","3D_view", 140,-PIXPITCH*70,PIXPITCH*70 ,140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140);
//   xyz = new TH3D("3D_view","3D_view", 35,-PIXPITCH*70,PIXPITCH*70 ,35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140);
   xyz->GetXaxis()->SetTitle("z [mm]");
   xyz->GetYaxis()->SetTitle("x [mm]");
   xyz->GetZaxis()->SetTitle("y [mm]");
   xyz->SetLineWidth(0);

   xyz0=(TH3D*)(xyz->Clone());
   xyz_out=(TH3D*)(xyz->Clone());

//   TH2D *xy, *zy;
   xy= new TH2D("xy","front",140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140); 
   zy= new TH2D("zy","side",140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140); 
//   xy= new TH2D("xy","front",35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140); 
//   zy= new TH2D("zy","side",35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140); 
   xy->GetXaxis()->SetTitle("x [mm]");
   xy->GetYaxis()->SetTitle("y [mm]");
//   xy->GetZaxis()->SetRangeUser(0,1200);
   xy->GetZaxis()->SetRangeUser(0,500);
   zy->GetXaxis()->SetTitle("z [mm]");
   zy->GetYaxis()->SetTitle("y [mm]");
//   zy->GetZaxis()->SetRangeUser(0,1200);
   zy->GetZaxis()->SetRangeUser(0,500);
   
   //c->Clear();
   c = new TCanvas("c","display",900,1000);
   c->Divide(3,2);
   c_4 = c->cd(4); 
   c_4->Divide(2,4);

   }
   else
   {
     xyz->Reset();
     xyz0->Reset();
     xyz_out->Reset();
     xy->Reset();
     zy->Reset();
   }

   //3D view
   c->cd(1);
  
      for(int i=0; i< event_nhits; i++){
       //geometry correction
    //    event_hits_y[i]=event_hits_y[i]*((event_hits_y[i]<-310)*-2+1)-3*310*(event_hits_y[i]<-310);
    //    event_hits_x[i]=event_hits_x[i]*((event_hits_y[i]<-310)*-2+1);
        //filling plots
	xyz->Fill(event_hits_z[i], event_hits_x[i], event_hits_y[i], event_hits_q[i]);
	xy->Fill(event_hits_x[i], event_hits_y[i], event_hits_q[i]);
	zy->Fill(event_hits_z[i], event_hits_y[i], event_hits_q[i]);
   }

   
   //xyz->GetZaxis()->SetRangeUser(0,1200);
//   xyz->SetMaximum(400);
   xyz->SetMaximum(300);
   xyz->Draw("BOX2 Z");
   
 //  xyz->Draw("GLBOX1 Z");

   gPad->SetTheta(5);
   gPad->SetPhi(30);
   c->cd(2);

   xy->SetTitle(Form("event %d xy view",g_eventID));
   xy->SetStats(0);
   xy->Draw("colz");
   c->cd(3);
   
   zy->SetTitle(Form("Event %d zy view",g_eventID));
   zy->SetStats(0);
   zy->Draw("colz");


        c->cd(5);
	double max_light = max(lnegx320->GetMaximum() , lposx320->GetMaximum()); 
	//max_light = min(4000.00 , max_light);
   	lnegx320->SetMaximum(max_light);
	lnegx320->SetMinimum(min(lnegx320->GetMinimum() , lposx320->GetMinimum()));
        lnegx320->GetXaxis()->SetTitle("z [mm]");
        lnegx320->GetYaxis()->SetTitle("y [mm]");
	lnegx320->SetStats(0);
   	lnegx320->Draw("colz");

   	c->cd(6);
   	lposx320->SetMaximum(max_light);
        lposx320->SetMinimum(min(lnegx320->GetMinimum() , lposx320->GetMinimum()));
        lposx320->GetXaxis()->SetTitle("z [mm]");
        lposx320->GetYaxis()->SetTitle("y [mm]");
        lposx320->SetStats(0);
   	lposx320->Draw("colz");
        	
 retval=1;

 printf("xyz->GetMaximumBin()=%f\n",xyz->GetBinContent(xyz->GetMaximumBin()));
 
  for(int ti=0; ti<event_ntracks;ti++)
 {  
   printf("Track #%d length=%f q=%f dq/dL=%f theta=%f phi=%f\n",ti,etrack_length[ti],etrack_q[ti],etrack_q[ti]/etrack_length[ti],etrack_theta[ti],etrack_phi[ti]);
   printf("Residuals: %f %f %f\n",etrack_residual_x[ti],etrack_residual_y[ti],etrack_residual_z[ti]);
printf("event_photons/event_q=%f  track_q/track_nhits=%f, qh+pq*100-210=%f \n",event_photons/event_q,etrack_q[ti]/etrack_nhits[ti],etrack_q[ti]/etrack_nhits[ti]+event_photons/event_q*100.-210.);
      c->cd(2);
    //  gPad.Range( 0., -10., 1., 10. )
    //  line = TLine(track_start_x);
    //  line.SetLineColor(kYellow)
    //  line.SetLineWidth(2)
    //  line.Draw()
  // xy->Draw("colz");
   c->cd(3);
  //  zy->Draw("colz");

//   cds_Trtr_out->Fill(); 
 }
// outfile->Write("",TObject::kOverwrite);  


 
int binsx,binsy,binsz;
Double_t x,y,z,q;

c->Update();

binsx=xyz->GetNbinsX();
binsy=xyz->GetNbinsY();
binsz=xyz->GetNbinsZ();

printf("Input space %dx%dx%d bins for Hough transform..\n",binsx,binsy,binsz);

gSystem->Exec("rm testdata.dat");
for(int xb=1; xb<binsx-1; xb++)
for(int yb=1; yb<binsy-1; yb++)
for(int zb=1; zb<binsz-1; zb++)
 {
   q=xyz->GetBinContent(xb,yb,zb);
   if(q==0) continue;
   x=((TAxis*)xyz->GetXaxis())->GetBinCenter(xb);
   y=((TAxis*)xyz->GetYaxis())->GetBinCenter(yb);
   z=((TAxis*)xyz->GetZaxis())->GetBinCenter(zb);
   sprintf(line,"echo %f,%f,%f >>testdata.dat",x,y,z);
   gSystem->Exec(line);
 }
printf("Hough transform is in progress..\n");

    s=gSystem->GetFromPipe("./hough3dlines testdata.dat -dx 16 -raw -minvotes 10"); //good
//    s=gSystem->GetFromPipe("./hough3dlines testdata.dat -dx 5 -raw -minvotes 20"); //test
    printf("Hough transform output (az,ax,ay,nz,nx,ny):\n%s\n",s.Data());
    larr=s.Tokenize(10);
    nhtracks=larr->GetEntries();
    if(nhtracks>MAXTRACKS) nhtracks=MAXTRACKS;
    
    for(int il=0; il<nhtracks; il++)
    { 
     npts[il]=0;

     sscanf(((TObjString*)(larr->At(il)))->String().Data(),"%lf %lf %lf %lf %lf %lf %d", &az[il], &ax[il], &ay[il], &nz[il], &nx[il], &ny[il], &npts[il] );
     printf("Track %d: a(%f,%f,%f) n(%f %f %f) number of hits on track: %d\n",il,ax[il],ay[il],az[il],nx[il],ny[il],nz[il],npts[il]);
    }
printf("Done. \n");
Double_t dr,dn, min_dn, max_dn;
 TVector3 vec_a;
 TVector3 vec_n;
 TVector3 vec_a0;
 TVector3 vec_n0;
 TVector3 vec_p;  //point radius vector
 Double_t tr_dist;
 
  TVector3 cn;
 TVector3 proj;
 TVector3 rej;
 TVector3 clapp;
 TVector3 vtx;


 //printf("Call Unfold \n");
     UnfoldResponse();
// printf("Ret from Unfold \n");
      xyz->Draw("BOX2 Z");
      c->Update();

    for(int il=0; il<nhtracks; il++)
 //   for(int il=0; il<1; il++)
    { 
     qhts[il]=0; //total summed charge hits around the track path
     rhits[il]=0; //hit-track residual mean
     nhts[il]=0; //number of raw hits in track
     min_dn=9999;
     max_dn=-9999;
	 vec_a.SetXYZ(ax[il],ay[il],az[il]);
	 vec_n.SetXYZ(nx[il],ny[il],nz[il]);
 printf("TP1 \n");
	 h_residuals.Reset();
     for(int i=0; i< event_nhits && nhts[il]<10000; i++)
       {
	     vec_p.SetXYZ(event_hits_x[i], event_hits_y[i], event_hits_z[i]);
	     dr=((vec_p-vec_a).Cross(vec_n)).Mag() / vec_n.Mag();
	     h_residuals.Fill(dr,event_hits_q[i]);
	     if(dr<ROAD) 
	       { 
	         qhts[il]=qhts[il]+event_hits_q[i];
	         dn=((vec_p-vec_a).Dot(vec_n)) / vec_n.Mag(); //distance from track ceter to a hit along the track, signed
	         if(dn>max_dn) max_dn=dn; //finding track ends - furthest hits from the center
	         if(dn<min_dn) min_dn=dn;
	         htr_h_x[il][nhts[il]]=event_hits_x[i];
	         htr_h_y[il][nhts[il]]=event_hits_y[i];
	         htr_h_z[il][nhts[il]]=event_hits_z[i];
	         htr_h_q[il][nhts[il]]=event_hits_q[i];
	         nhts[il]++;
	       }
	   }
	 rhits[il]=h_residuals.GetMean();
	 tl[il]=max_dn-min_dn;
	 pE[il]=pEfromRange->Eval(tl[il]);
	//   printf("Track %d: min_dn=%f max_dn=%f track_q=%f ke,  track_l=%f mm,  dQ/dx=%f\n",il,min_dn, max_dn,qhts[il],tl[il],qhts[il]/tl[il]);
	   printf("Track %d:  track_q=%f ke,  track_l=%f mm,  dQ/dx=%f  hits residual %f\n",il,qhts[il],tl[il],qhts[il]/tl[il],rhits[il]);
	   printf("Hypotetic recoil prototn energy: %lf\n",pE[il]);
	   
	   htracks_start_x[il]=ax[il]+nx[il]*max_dn;
	   htracks_start_y[il]=ay[il]+ny[il]*max_dn;
	   htracks_start_z[il]=az[il]+nz[il]*max_dn;
	   htracks_end_x[il]=ax[il]+nx[il]*min_dn;
	   htracks_end_y[il]=ay[il]+ny[il]*min_dn;
	   htracks_end_z[il]=az[il]+nz[il]*min_dn;
	   
         c->cd(1);
         
/* 
    TGraph2D *g=new TGraph2D(2);
   g->SetPoint(0,htracks_end_z[il],htracks_end_x[il],htracks_end_y[il]);
   g->SetPoint(1,htracks_start_z[il],htracks_start_x[il],htracks_start_y[il]);
   g->SetLineWidth(2);
   if(npts[il]>50) g->SetLineColor(kBlack);
   else g->SetLineColor(kMagenta);
   g->Draw("LINEsame");

    c->cd(2);
    TGraph *gxy=new TGraph(2);
   gxy->SetPoint(0,htracks_end_x[il],htracks_end_y[il]);
   gxy->SetPoint(1,htracks_start_x[il],htracks_start_y[il]);
   gxy->SetLineWidth(1);
   if(npts[il]>50) gxy->SetLineColor(kBlack);
   else gxy->SetLineColor(kMagenta);
   gxy->Draw("LINEsame");

    c->cd(3);
    TGraph *gzy=new TGraph(2);
   gzy->SetPoint(0,htracks_end_z[il],htracks_end_y[il]);
   gzy->SetPoint(1,htracks_start_z[il],htracks_start_y[il]);
   gzy->SetLineWidth(1);
   if(npts[il]>50) gzy->SetLineColor(kBlack);
   else gzy->SetLineColor(kMagenta);
   gzy->Draw("LINEsame");
   c->Update();
*/   
   
   htracks_ID[il]=il;

   // filling voxels near the track
     htracks_nvox[il]=0;
     for(int i=0; i<nvox && htracks_nvox[il]<10000; i++)
       {
	     vec_p.SetXYZ(vox_x[i], vox_y[i], vox_z[i]);
	     dr=((vec_p-vec_a).Cross(vec_n)).Mag() / vec_n.Mag();
	     if(dr<ROAD) 
	       { 
	         htr_vox_x[il][htracks_nvox[il]]=vox_x[i];
	         htr_vox_y[il][htracks_nvox[il]]=vox_y[i];
	         htr_vox_z[il][htracks_nvox[il]]=vox_z[i];
	         htr_vox_q[il][htracks_nvox[il]]=vox_q[i];
	         htracks_nvox[il]++;
	       }
	   }
    
    } //end loop on tracks in event

 c->Update();
 cds_EvHough->Fill();
 /*
 // Find vertices
 vertex_ID=0;
 for(int il0=0; il0<nhtracks; il0++)  for(int il=il0+1; il<nhtracks; il++)
  {
    vec_a.SetXYZ(ax[il],ay[il],az[il]);
	vec_n.SetXYZ(nx[il],ny[il],nz[il]);
    vec_a0.SetXYZ(ax[il0],ay[il0],az[il0]);
	vec_n0.SetXYZ(nx[il0],ny[il0],nz[il0]);

    tr_dist = abs( (vec_a-vec_a0)*(vec_n0.Cross(vec_n)) )   /  (vec_n0.Cross(vec_n)).Mag() ; 
    printf("Tracks %d and %d: distance %f\n",il0,il,tr_dist);
    
    if(tr_dist > rhits[il] + rhits[il0] ) continue;
    //find nearest point = vertex
  //  Double_t f=(vec_n.Cross(vec_n0)).Mag();
  //  f=1/f;
    cn=(vec_n.Cross(vec_n0)).Unit(); ///(vec_n.Cross(vec_n0)).Mag();
    proj = (vec_a-vec_a0).Dot(vec_n0) * vec_n0;
    rej  = vec_a-vec_a0 - proj - (vec_a-vec_a0).Dot(cn) * cn;
    clapp = vec_a-vec_n*rej.Mag()*(1./vec_n.Dot(rej.Unit()));
//    printf("Clapp:"); clapp.Print();
//    vtx=vec_a+clapp*0.5;
    vtx=clapp;
    vertex_x=vtx.X();
    vertex_y=vtx.Y();
    vertex_z=vtx.Z();
    vertex_mult=2; //(for the moment find pairs only)
    vertex_tracksID[0]=il0;
    vertex_tracksID[1]=il;
    printf("Found vertex at %f,%f,%f\n",vertex_x,vertex_y,vertex_z);
//     TPolyMarker3D *pm3d2 = new TPolyMarker3D(1);
//     pm3d2->SetPoint(0,vertex_x,vertex_y,vertex_z);
//     c->cd(1);
//     pm3d2->Draw("same");
//
    cds_Vtx->Fill();
    vertex_ID++;
  }
  
 // End find vertices

*/
  
//c->Update();
 /*
cds_EvHough->SetAlias("t_d1x","track_hits_x-track_end_x");
cds_EvHough->SetAlias("t_d1z","track_hits_z-track_end_z");
cds_EvHough->SetAlias("t_d1y","track_hits_y-track_end_y");

cds_EvHough->SetAlias("t_d2x","track_hits_x-track_start_x");
cds_EvHough->SetAlias("t_d2y","track_hits_y-track_start_y");
cds_EvHough->SetAlias("t_d2z","track_hits_z-track_start_z");

cds_EvHough->SetAlias("range1","sqrt(t_d1x*t_d1x+t_d1y*t_d1y+t_d1z*t_d1z)");
cds_EvHough->SetAlias("range2","sqrt(t_d2x*t_d2x+t_d2y*t_d2y+t_d2z*t_d2z)");
cds_EvHough->SetAlias("range","range1*(track_start_y>track_end_y)+range2*(track_start_y<=track_end_y)");
cds_EvHough->SetAlias("pida","(log(track_hits_q)-3.15)/(11-log(range))");



cds_EvHough->SetAlias("vt_d1x","track_vox_x-track_end_x");
cds_EvHough->SetAlias("vt_d1z","track_vox_z-track_end_z");
cds_EvHough->SetAlias("vt_d1y","track_vox_y-track_end_y");

cds_EvHough->SetAlias("vt_d2x","track_vox_x-track_start_x");
cds_EvHough->SetAlias("vt_d2y","track_vox_y-track_start_y");
cds_EvHough->SetAlias("vt_d2z","track_vox_z-track_start_z");

cds_EvHough->SetAlias("vrange1","sqrt(vt_d1x*vt_d1x+vt_d1y*vt_d1y+vt_d1z*vt_d1z)");
cds_EvHough->SetAlias("vrange2","sqrt(vt_d2x*vt_d2x+vt_d2y*vt_d2y+vt_d2z*vt_d2z)");
cds_EvHough->SetAlias("vrange","vrange1*(track_start_y>track_end_y)+vrange2*(track_start_y<=track_end_y)");
cds_EvHough->SetAlias("vpida","(log(track_vox_q)-3.15)/(11-log(vrange))");
*/
 
// outfile->cd();  
 cds_EvHough->Write("Hevents",TObject::kOverwrite);  
// cds_TrHough->Write("Htracks",TObject::kOverwrite);  
// cds_Vtx->Write("Vtx",TObject::kOverwrite);  
 outfile->Write("",TObject::kOverwrite);  

 return retval;
}



void UnfoldResponse()
{
printf("Unfolding field response...\n");
Float_t resval;
Float_t fracq;

   xyz_out->Clear();
    for(int iz=xyz->GetNbinsZ();iz>0;iz--)
    for(int iy=xyz->GetNbinsY();iy>0;iy--)
    for(int i=xyz->GetNbinsX();i>0;i--)
   {
      xyz0->SetBinContent(i,iy,iz,xyz->GetBinContent(i,iy,iz)); //copy
   }

 /*
  TPC z(drift) is X axis of TH3D
  TPC x is Y axis
  TPC y is Z axis
 */
  for(int iz=xyz->GetNbinsZ();iz>0;iz--)
  for(int iy=xyz->GetNbinsY();iy>0;iy--)
  {
// Part for Z<0
    for(int i=xyz->GetNbinsX()/2;i>0;i--)
   {
     if(xyz->GetBinContent(i,iy,iz)<=0) continue;
     xyz_out->SetBinContent(i,iy,iz,xyz->GetBinContent(i,iy,iz));
     for(int j=i;j>=i-5;j--) for(int k=-(i-j); k<=(i-j); k++) for(int l=-(i-j); l<=(i-j); l++) 
     {
     //sanity checks
     if(i-j+1<0 || i-j+1>kernel->GetNbinsX()) continue;
     if(iy+k<0 || iy+k>xyz->GetNbinsY()) continue;
     if(iz+l<0 || iz+l>xyz->GetNbinsZ()) continue;
     //
     fracq=xyz_out->GetBinContent(i,iy,iz)*kernel->GetBinContent(i-j+1);
     resval=xyz->GetBinContent(j,iy+k,iz+l)-fracq;
     if(resval<=0) 
      {
       resval=0;
       if(i!=j)   xyz_out->SetBinContent(i,iy,iz,xyz_out->GetBinContent(i,iy,iz)+xyz->GetBinContent(j,iy+k,iz+l));
      }
      else 
      {
       if(i!=j)  xyz_out->SetBinContent(i,iy,iz,xyz_out->GetBinContent(i,iy,iz)+fracq);
      } 
     xyz->SetBinContent(j,iy+k,iz+l,resval);
     }
   }
// Part for Z>0
    for(int i=xyz->GetNbinsX()/2+1;i<xyz->GetNbinsX();i++)
   {
     if(xyz->GetBinContent(i,iy,iz)<=0) continue;
     xyz_out->SetBinContent(i,iy,iz,xyz->GetBinContent(i,iy,iz));
     for(int j=i;j<=i+5;j++) for(int k=-(j-i); k<=(j-i); k++) for(int l=-(j-i); l<=(j-i); l++) 
     {
     //sanity checks
     if(j-i+1<0 || j-i+1>kernel->GetNbinsX()) continue;
     if(iy+k<0 || iy+k>xyz->GetNbinsY()) continue;
     if(iz+l<0 || iz+l>xyz->GetNbinsZ()) continue;
     //
     fracq=xyz_out->GetBinContent(i,iy,iz)*kernel->GetBinContent(j-i+1);
     resval=xyz->GetBinContent(j,iy+k,iz+l)-fracq;
     if(resval<=0) 
      {
       resval=0;
       if(i!=j)   xyz_out->SetBinContent(i,iy,iz,xyz_out->GetBinContent(i,iy,iz)+xyz->GetBinContent(j,iy+k,iz+l));
      }
      else 
      {
       if(i!=j)  xyz_out->SetBinContent(i,iy,iz,xyz_out->GetBinContent(i,iy,iz)+fracq);
      } 
     xyz->SetBinContent(j,iy+k,iz+l,resval);
     //printf("*");
     }
   }
  } 
 /*
  TPC z(drift) is X axis of TH3D
  TPC x is Y axis
  TPC y is Z axis
 */

    nvox=0;
    for(int iz=xyz->GetNbinsZ();iz>0;iz--)
    for(int iy=xyz->GetNbinsY();iy>0;iy--)
    for(int i=xyz->GetNbinsX();i>0;i--)
   {
  //   if(xyz_out->GetBinContent(i,iy,iz)<=50) xyz->SetBinContent(i,iy,iz,0); //apply threshold
     if(xyz_out->GetBinContent(i,iy,iz)<=0) xyz->SetBinContent(i,iy,iz,0); //apply threshold
     else 
     { 
      xyz->SetBinContent(i,iy,iz,xyz_out->GetBinContent(i,iy,iz)); //copy back
      //Filling voxel info in the tree
      vox_q[nvox]=xyz->GetBinContent(i,iy,iz);
      vox_z[nvox]=((TAxis*)xyz->GetXaxis())->GetBinCenter(i);
      vox_x[nvox]=((TAxis*)xyz->GetYaxis())->GetBinCenter(iy);
      vox_y[nvox]=((TAxis*)xyz->GetZaxis())->GetBinCenter(iz);
      nvox++;
     }

   }
   
  xyz->Scale(xyz0->Integral()/xyz->Integral()); 
  printf("Done.\n");

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


 /*
Hevents->SetAlias("t_d1x","htrack_hits_x-htracks_end_x");
Hevents->SetAlias("t_d1z","htrack_hits_z-htracks_end_z");
Hevents->SetAlias("t_d1y","htrack_hits_y-htracks_end_y");

Hevents->SetAlias("t_d2x","htrack_hits_x-htracks_start_x");
Hevents->SetAlias("t_d2y","htrack_hits_y-htracks_start_y");
Hevents->SetAlias("t_d2z","htrack_hits_z-htracks_start_z");

Hevents->SetAlias("range1","sqrt(t_d1x*t_d1x+t_d1y*t_d1y+t_d1z*t_d1z)");
Hevents->SetAlias("range2","sqrt(t_d2x*t_d2x+t_d2y*t_d2y+t_d2z*t_d2z)");
Hevents->SetAlias("range","range1*(htracks_start_y>htracks_end_y)+range2*(htracks_start_y<=htracks_end_y)");
Hevents->SetAlias("pida","(log(htrack_hits_q)-3.15)/(11-log(range))");



Hevents->SetAlias("vt_d1x","htrack_vox_x-htracks_end_x");
Hevents->SetAlias("vt_d1z","htrack_vox_z-htracks_end_z");
Hevents->SetAlias("vt_d1y","htrack_vox_y-htracks_end_y");

Hevents->SetAlias("vt_d2x","htrack_vox_x-htracks_start_x");
Hevents->SetAlias("vt_d2y","htrack_vox_y-htracks_start_y");
Hevents->SetAlias("vt_d2z","htrack_vox_z-htracks_start_z");

Hevents->SetAlias("vrange1","sqrt(vt_d1x*vt_d1x+vt_d1y*vt_d1y+vt_d1z*vt_d1z)");
Hevents->SetAlias("vrange2","sqrt(vt_d2x*vt_d2x+vt_d2y*vt_d2y+vt_d2z*vt_d2z)");
Hevents->SetAlias("vrange","vrange1*(htracks_start_y>htracks_end_y)+vrange2*(htracks_start_y<=htracks_end_y)");
Hevents->SetAlias("vpida","(log(htrack_vox_q)-3.15)/(11-log(vrange))");



Hevents->Draw("4.7*(log(htrack_vox_q)-3.2)+log(vrange):htracks_qhts/htracks_tl>>hh(45,0,180,50,-5,25)","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1","colz")
*/


