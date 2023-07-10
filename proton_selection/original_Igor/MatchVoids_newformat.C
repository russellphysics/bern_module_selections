
#define PIXPITCH 4.434

//#include <TSystem.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"
int i=0;
  TCanvas *c1;
  TFile *cdsf;
  TFile *vdsf;
  TFile *outfile;

  TTree *cds_EvHough;
  TTree *VoidsTree;
  TTree *cds_EvHough_out;
   char fn_string[256];
 
 #define DistToVoid  PIXPITCH*0
 Int_t endnearvoid[10]; //flag showing that track touchs the void at one of its ends
 Int_t crossvoid[10]; //flag showing that track has hits near the void

   // Declaration of leaf types
   Int_t           eventID;
   Int_t           event_start_t;
   Int_t           event_end_t;
   Int_t           event_duration;
   Int_t           event_unix_ts;
   Int_t           event_nhits;
   Float_t         event_q;
   Int_t           event_ntracks;
   Int_t           event_n_ext_trigs;
   Int_t           trigID;
   Int_t           trig_type;
   Int_t           trig_ts;
   Int_t           trig_eventID;
   TH2F            *lnegx320;
   TH2F            *lposx320;
   Int_t           event_photons;
   Int_t           nhtracks;
   Double_t        htracks_ax[10];   //[nhtracks]
   Double_t        htracks_ay[10];   //[nhtracks]
   Double_t        htracks_az[10];   //[nhtracks]
   Double_t        htracks_nx[10];   //[nhtracks]
   Double_t        htracks_ny[10];   //[nhtracks]
   Double_t        htracks_nz[10];   //[nhtracks]
   Float_t         htracks_start_x[10];   //[nhtracks]
   Float_t         htracks_start_y[10];   //[nhtracks]
   Float_t         htracks_start_z[10];   //[nhtracks]
   Float_t         htracks_end_x[10];   //[nhtracks]
   Float_t         htracks_end_y[10];   //[nhtracks]
   Float_t         htracks_end_z[10];   //[nhtracks]
   Int_t           htracks_ID[10];   //[nhtracks]
   Int_t           htracks_npts[10];   //[nhtracks]
   Double_t        htracks_qhts[10];   //[nhtracks]
   Double_t        htracks_rhits[10];   //[nhtracks]
   Int_t           htracks_nhts[10];   //[nhtracks]
   Double_t        htracks_tl[10];   //[nhtracks]
   Double_t        htracks_pE[10];   //[nhtracks]
   Float_t         htrack_hits_x[10][10000];
   Float_t         htrack_hits_y[10][10000];
   Float_t         htrack_hits_z[10][10000];
   Float_t         htrack_hits_q[10][10000];
   Int_t           htracks_nvox[10];
   Float_t         htrack_vox_x[10][10000];
   Float_t         htrack_vox_y[10][10000];
   Float_t         htrack_vox_z[10][10000];
   Float_t         htrack_vox_q[10][10000];
   Float_t         pida_A[10];
   Float_t         pida_B[10];
   Float_t         pida_C[10];
   Float_t         vpida_A[10];
   Float_t         vpida_B[10];
   Float_t         vpida_C[10];
   Int_t           upward[10];

   // List of branches
   TBranch        *b_eventID;   //!
   TBranch        *b_event_start_t;   //!
   TBranch        *b_event_end_t;   //!
   TBranch        *b_event_duration;   //!
   TBranch        *b_event_unix_ts;   //!
   TBranch        *b_event_nhits;   //!
   TBranch        *b_event_q;   //!
   TBranch        *b_event_ntracks;   //!
   TBranch        *b_event_n_ext_trigs;   //!
   TBranch        *b_trigID;   //!
   TBranch        *b_trig_type;   //!
   TBranch        *b_trig_ts;   //!
   TBranch        *b_trig_eventID;   //!
   TBranch        *b_lnegx320;   //!
   TBranch        *b_lposx320;   //!
   TBranch        *b_event_photons;   //!
   TBranch        *b_nhtracks;   //!
   TBranch        *b_htracks_ax;   //!
   TBranch        *b_htracks_ay;   //!
   TBranch        *b_htracks_az;   //!
   TBranch        *b_htracks_nx;   //!
   TBranch        *b_htracks_ny;   //!
   TBranch        *b_htracks_nz;   //!
   TBranch        *b_htracks_start_x;   //!
   TBranch        *b_htracks_start_y;   //!
   TBranch        *b_htracks_start_z;   //!
   TBranch        *b_htracks_end_x;   //!
   TBranch        *b_htracks_end_y;   //!
   TBranch        *b_htracks_end_z;   //!
   TBranch        *b_htracks_ID;   //!
   TBranch        *b_htracks_npts;   //!
   TBranch        *b_htracks_qhts;   //!
   TBranch        *b_htracks_rhits;   //!
   TBranch        *b_htracks_nhts;   //!
   TBranch        *b_htracks_tl;   //!
   TBranch        *b_htracks_pE;   //!
   TBranch        *b_htr_h_x;   //!
   TBranch        *b_htr_h_y;   //!
   TBranch        *b_htr_h_z;   //!
   TBranch        *b_htr_h_q;   //!
   TBranch        *b_htracks_nvox;   //!
   TBranch        *b_htr_vox_x;   //!
   TBranch        *b_htr_vox_y;   //!
   TBranch        *b_htr_vox_z;   //!
   TBranch        *b_htr_vox_q;   //!
   TBranch        *b_pida_A;   //!
   TBranch        *b_pida_B;   //!
   TBranch        *b_pida_C;   //!
   TBranch        *b_vpida_A;   //!
   TBranch        *b_vpida_B;   //!
   TBranch        *b_vpida_C;   //!
   TBranch        *b_upward;   //!  
 
   // Declaration of leaf types
   Float_t         vcx;
   Float_t         vcy;
   Int_t         vcz;
   Float_t         vdx;
   Float_t         vdy;

   // List of branches
   TBranch        *b_vcx;   //!
   TBranch        *b_vcy;   //!
   TBranch        *b_vcz;   //!
   TBranch        *b_vdx;   //!
   TBranch        *b_vdy;   //!

  
void MatchVoids_newformat(const char * PIDAfname, const char * VoidsTreefname)
{

  cdsf= new TFile(PIDAfname , "READ" );
  cout<<"Open PIDA file:" << PIDAfname <<endl;

  cdsf->GetObject("Hevents",cds_EvHough);  
  if(!cds_EvHough) {printf("Cant find HEvents tree! Exiting.\n"); return;}
  printf("Events and Tracks tree loaded...\n");
 
 
  vdsf= new TFile(VoidsTreefname , "READ" );
  cout<<"Open Voids file:" << VoidsTreefname <<endl;

  vdsf->GetObject("voids",VoidsTree);  
  if(!VoidsTree) {printf("Cant find voids tree! Exiting.\n"); return;}
  printf("Voids tree loaded...\n");

   cds_EvHough->SetBranchAddress("eventID", &eventID, &b_eventID);
   cds_EvHough->SetBranchAddress("event_start_t", &event_start_t, &b_event_start_t);
   cds_EvHough->SetBranchAddress("event_end_t", &event_end_t, &b_event_end_t);
   cds_EvHough->SetBranchAddress("event_duration", &event_duration, &b_event_duration);
   cds_EvHough->SetBranchAddress("event_unix_ts", &event_unix_ts, &b_event_unix_ts);
   cds_EvHough->SetBranchAddress("event_nhits", &event_nhits, &b_event_nhits);
   cds_EvHough->SetBranchAddress("event_q", &event_q, &b_event_q);
   cds_EvHough->SetBranchAddress("event_ntracks", &event_ntracks, &b_event_ntracks);
   cds_EvHough->SetBranchAddress("event_n_ext_trigs", &event_n_ext_trigs, &b_event_n_ext_trigs);
   cds_EvHough->SetBranchAddress("trigID", &trigID, &b_trigID);
   cds_EvHough->SetBranchAddress("trig_type", &trig_type, &b_trig_type);
   cds_EvHough->SetBranchAddress("trig_ts", &trig_ts, &b_trig_ts);
   cds_EvHough->SetBranchAddress("trig_eventID", &trig_eventID, &b_trig_eventID);
   cds_EvHough->SetBranchAddress("lnegx320", &lnegx320, &b_lnegx320);
   cds_EvHough->SetBranchAddress("lposx320", &lposx320, &b_lposx320);
   cds_EvHough->SetBranchAddress("event_photons", &event_photons, &b_event_photons);
   cds_EvHough->SetBranchAddress("nhtracks", &nhtracks, &b_nhtracks);
   cds_EvHough->SetBranchAddress("htracks_ax", htracks_ax, &b_htracks_ax);
   cds_EvHough->SetBranchAddress("htracks_ay", htracks_ay, &b_htracks_ay);
   cds_EvHough->SetBranchAddress("htracks_az", htracks_az, &b_htracks_az);
   cds_EvHough->SetBranchAddress("htracks_nx", htracks_nx, &b_htracks_nx);
   cds_EvHough->SetBranchAddress("htracks_ny", htracks_ny, &b_htracks_ny);
   cds_EvHough->SetBranchAddress("htracks_nz", htracks_nz, &b_htracks_nz);
   cds_EvHough->SetBranchAddress("htracks_start_x", htracks_start_x, &b_htracks_start_x);
   cds_EvHough->SetBranchAddress("htracks_start_y", htracks_start_y, &b_htracks_start_y);
   cds_EvHough->SetBranchAddress("htracks_start_z", htracks_start_z, &b_htracks_start_z);
   cds_EvHough->SetBranchAddress("htracks_end_x", htracks_end_x, &b_htracks_end_x);
   cds_EvHough->SetBranchAddress("htracks_end_y", htracks_end_y, &b_htracks_end_y);
   cds_EvHough->SetBranchAddress("htracks_end_z", htracks_end_z, &b_htracks_end_z);
   cds_EvHough->SetBranchAddress("htracks_ID", htracks_ID, &b_htracks_ID);
   cds_EvHough->SetBranchAddress("htracks_npts", htracks_npts, &b_htracks_npts);
   cds_EvHough->SetBranchAddress("htracks_qhts", htracks_qhts, &b_htracks_qhts);
   cds_EvHough->SetBranchAddress("htracks_rhits", htracks_rhits, &b_htracks_rhits);
   cds_EvHough->SetBranchAddress("htracks_nhts", htracks_nhts, &b_htracks_nhts);
   cds_EvHough->SetBranchAddress("htracks_tl", htracks_tl, &b_htracks_tl);
   cds_EvHough->SetBranchAddress("htracks_pE", htracks_pE, &b_htracks_pE);
   cds_EvHough->SetBranchAddress("htrack_hits_x", htrack_hits_x, &b_htr_h_x);
   cds_EvHough->SetBranchAddress("htrack_hits_y", htrack_hits_y, &b_htr_h_y);
   cds_EvHough->SetBranchAddress("htrack_hits_z", htrack_hits_z, &b_htr_h_z);
   cds_EvHough->SetBranchAddress("htrack_hits_q", htrack_hits_q, &b_htr_h_q);
   cds_EvHough->SetBranchAddress("htracks_nvox", htracks_nvox, &b_htracks_nvox);
   cds_EvHough->SetBranchAddress("htrack_vox_x", htrack_vox_x, &b_htr_vox_x);
   cds_EvHough->SetBranchAddress("htrack_vox_y", htrack_vox_y, &b_htr_vox_y);
   cds_EvHough->SetBranchAddress("htrack_vox_z", htrack_vox_z, &b_htr_vox_z);
   cds_EvHough->SetBranchAddress("htrack_vox_q", htrack_vox_q, &b_htr_vox_q);
   cds_EvHough->SetBranchAddress("pida_A", pida_A, &b_pida_A);
   cds_EvHough->SetBranchAddress("pida_B", pida_B, &b_pida_B);
   cds_EvHough->SetBranchAddress("pida_C", pida_C, &b_pida_C);
   cds_EvHough->SetBranchAddress("vpida_A", vpida_A, &b_vpida_A);
   cds_EvHough->SetBranchAddress("vpida_B", vpida_B, &b_vpida_B);
   cds_EvHough->SetBranchAddress("vpida_C", vpida_C, &b_vpida_C);
   cds_EvHough->SetBranchAddress("upward", upward, &b_upward);
  

  VoidsTree->SetBranchAddress("vcx", &vcx, &b_vcx);
   VoidsTree->SetBranchAddress("vcy", &vcy, &b_vcy);
   VoidsTree->SetBranchAddress("vdx", &vdx, &b_vdx);
   VoidsTree->SetBranchAddress("vdy", &vdy, &b_vdy);
   VoidsTree->SetBranchAddress("vcz", &vcz, &b_vcz);

  
  sprintf(fn_string,"Voids_%s",PIDAfname);
printf("Creating output file %s\n",fn_string);
outfile= new TFile(fn_string, "recreate");
outfile->cd();
cds_EvHough_out=cds_EvHough->CloneTree(0);
cds_EvHough_out->Branch("crossvoid", crossvoid,"crossvoid[10]/I");
cds_EvHough_out->Branch("endnearvoid", endnearvoid,"endnearvoid[10]/I");



c1 = new TCanvas("c1","Voids",900,450);

Int_t nvoids=VoidsTree->GetEntries();
printf("Done. Looping over TrHough tree and checking if track touchs any of %d voids..\n",nvoids);

for(int e=0; e<cds_EvHough->GetEntries(); e++)
 {
  cds_EvHough->GetEntry(e);
  for(int t=0; t<nhtracks; t++) 
  {
  endnearvoid[t]=0;
  crossvoid[t]=0;

  
  

  for(int j=0; j<nvoids; j++)
   {
     VoidsTree->GetEntry(j);
     for(int h=0; h<htracks_nhts[t]; h++)
        if( htrack_hits_z[t][h] * vcz >=0 ) //hit and void in the same same TPC 
        {
        if( abs(htrack_hits_x[t][h]-vcx)<vdx+DistToVoid  && abs(htrack_hits_y[t][h]-vcy)<vdy+DistToVoid ) { crossvoid[t]=1; break;} 
        } 
     if( abs(htracks_start_x[t]-vcx)<vdx+DistToVoid  && abs(htracks_start_y[t]-vcy)<vdy+DistToVoid ) { endnearvoid[t]=1;} 
     if( abs(htracks_end_x[t]-vcx)<vdx+DistToVoid  && abs(htracks_end_y[t]-vcy)<vdy+DistToVoid ) { endnearvoid[t]=1;} 
     if( crossvoid[t]==1 && endnearvoid[t]==1) break; //no need to proceed, both flags are true
   }
  
  } 
  cds_EvHough_out->Fill();
 }



printf("Done. Saving output trees.\n");
 outfile->cd();  
 cds_EvHough_out->Write("Hevents",TObject::kOverwrite);  
 outfile->Write("",TObject::kOverwrite);  
 c1->cd();
 cds_EvHough_out->Draw("endnearvoid","","");
}


/*
Htracks->Draw("4.7*(log(tr_vox_q)-3.2)+log(vrange):qhts/tl>>hh(45,0,180,50,-5,25)","nhtracks==1&&trackID==0","colz");
Htracks->SetAlias("v1","4.7*(log(tr_vox_q)-3.2)+log(vrange)");
Htracks->SetAlias("v2","qhts/tl");
Htracks->SetAlias("cut0","abs(v2-30)<10&&abs(v1-8)<9");
Htracks->SetAlias("cut1","abs(v2-85)<25&&abs(v1-3)<5");
Htracks->SetAlias("cut2","abs(v2-85)<25&&abs(v1-10)<3");
Htracks->SetAlias("cut3","abs(v2-85)<25&&abs(v1-17)<4");

 Htracks->Draw("tr_vox_y:tr_vox_x:tr_vox_z","nhtracks==1&&trackID==0&&cut3","");
 
Htracks->Draw("tr_vox_y:tr_vox_x:tr_vox_z","endnearvoid==0&&nhtracks==1&&trackID==0","")

*/
