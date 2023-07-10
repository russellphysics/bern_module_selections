
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
  
  TTree *cds_Evtr_out;
  
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
char CRStr_cut[256];

void BuildIndex(TTree *cds_Evtr, const char *major,const char *minor)
{
  cds_Evtr->BuildIndex(major, minor);
  if(cds_Evtr->GetTreeIndex()) trindex=((TTreeIndex*)cds_Evtr->GetTreeIndex())->GetIndex();
  else trindex=0;
} 

void selectHMIPS_newformat(const char * CRSfname, const char * CRScut_str="", bool selMIP=0, bool selHIP=1 )
{

  sprintf(CRS_cut,"%s",CRScut_str);
  printf("Usage:\n");
  printf("selectHMIPS_newformat(CRSfname, cds_Evtr_cut, selectMIPs, selectHIPs)\n");
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

//if(MIP_HIP_SELECTOR==0) sprintf(fn_string,"HIPs_%s",CRSfname);
if(selHIP && !selMIP) sprintf(fn_string,"HIPs_%s",CRSfname);
if(selMIP && !selHIP) sprintf(fn_string,"MIPs_%s",CRSfname);
if(selMIP && selHIP) sprintf(fn_string,"AIPs_%s",CRSfname);
if(!selMIP && !selHIP) {printf("Neither MIPs nor HIPs selector is set, exiting.\n"); return;}

g_selMIP=selMIP;
g_selHIP=selHIP;

//outfile= new TFile("sub_selected_events.root", "recreate");
printf("Creating output file %s\n",fn_string);
outfile= new TFile(fn_string, "recreate","",9);
cds_Evtr_out = cds_Evtr->CloneTree(0);

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

  
int display_event(int ev)
{
   int retval=0;
   int selval=0;
   //event_photons=0; 
   cout<<"Plotting event "<<ev<<endl;
   selval=new_select(ev);
   if(selval<=0) return selval;
 
   int zbin;
   if(c==0)
   {
   

   xyz = new TH3D("3D_view","3D_view", 140,-PIXPITCH*70,PIXPITCH*70 ,140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140);
//   xyz = new TH3D("3D_view","3D_view", 35,-PIXPITCH*70,PIXPITCH*70 ,35,-PIXPITCH*70,PIXPITCH*70, 70,-PIXPITCH*140,PIXPITCH*140);
   xyz->GetXaxis()->SetTitle("z [mm]");
   xyz->GetYaxis()->SetTitle("x [mm]");
   xyz->GetZaxis()->SetTitle("y [mm]");
   xyz->SetLineWidth(0);

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
     xy->Reset();
     zy->Reset();
   }

   //3D view
   c->cd(1);
  
      for(int i=0; i< event_nhits; i++){
       //geometry correction
    //    ev_h_y[i]=ev_h_y[i]*((ev_h_y[i]<-310)*-2+1)-3*310*(ev_h_y[i]<-310);
    //    ev_h_x[i]=ev_h_x[i]*((ev_h_y[i]<-310)*-2+1);
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
        
        
    float max_light;
    float min_light=0;
    max_light=max(lnegx320->GetBinContent(lnegx320->GetMaximumBin()),lposx320->GetBinContent(lposx320->GetMaximumBin()) );    
 //   min_light=min(lnegx320->GetBinContent(lnegx320->GetMinimumBin()),lposx320->GetBinContent(lposx320->GetMinimumBin()) );    
//	float max_light = max(lnegx320->GetMaximum() , lposx320->GetMaximum()); 
	//max_light = min(4000.00 , max_light);
   	lnegx320->SetMaximum(max_light);
	lnegx320->SetMinimum(min_light);
        lnegx320->GetXaxis()->SetTitle("z [mm]");
        lnegx320->GetYaxis()->SetTitle("y [mm]");
	lnegx320->SetStats(0);
   	lnegx320->Draw("colz");

   	c->cd(6);
   	lposx320->SetMaximum(max_light);
    lposx320->SetMinimum(min_light);
        lposx320->GetXaxis()->SetTitle("z [mm]");
        lposx320->GetYaxis()->SetTitle("y [mm]");
    lposx320->SetStats(0);
   	lposx320->Draw("colz");
        	
 retval=1;

 printf("xyz->GetMaximumBin()=%f\n",xyz->GetBinContent(xyz->GetMaximumBin()));
 //if(MIP_HIP_SELECTOR==0) {if(xyz->GetBinContent(xyz->GetMaximumBin())<THRESHOLD_ON_MAX_BIN) return retval;} //Write to file only HIPs
 //else {if(xyz->GetBinContent(xyz->GetMaximumBin())>THRESHOLD_ON_MAX_BIN) return retval;} //Write to file only MIPs
 if(!g_selMIP) if(xyz->GetBinContent(xyz->GetMaximumBin())<THRESHOLD_ON_MAX_BIN) return retval; //skip MIPs
 if(!g_selHIP) if(xyz->GetBinContent(xyz->GetMaximumBin())>THRESHOLD_ON_MAX_BIN) return retval; //skip HIPs
 
 c->Update();
 printf("**** Passed the cut, therefore saving the event to output file..\n");
 cds_Evtr_out->Fill();  
 outfile->Write("",TObject::kOverwrite);  
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




