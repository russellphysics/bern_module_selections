
#define PIXPITCH 4.434

//#include <TSystem.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"
int i=0;
  TCanvas *c1;
  TFile *cdsf;
  TFile *outfile;
  TH1F *ph1;
  TH1F *ph2;

  TTree *cds_EvHough;
//  TTree *cds_TrHough;
//  TTree *cds_Vtx;
  TTree *cds_EvHough_out;
//  TTree *cds_TrHough_out;
//  TTree *cds_Vtx_out;
  
  Float_t pida_A[10], pida_B[10], pida_C[10], vpida_A[10], vpida_B[10], vpida_C[10]; //PIDA fit parameters for raw hits and voxelized unfolded hits
  Int_t upward[10];
TH2F h_pida("h_pida","h_pida",100,0,100,100,0,100); 
//TH2F h_vpida("h_vpida","h_vpida",100,0,100,100,0,100); 

  char fn_string[256];

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


TProfile *ph;
TProfile *pv;
TGraph *gh;
TGraph *gv;
TF1 *fpida1;
TF1 *fpida2;

void CalcPIDA(int e)
{
   int n,nv;
   Float_t av_c=0;
   Float_t av_vc=0;
   char str[128];
   int ntr=0;
//   gh=new TGraph(2);
//   gv=new TGraph(2);
cds_EvHough->GetEntry(e);
ntr=nhtracks;
printf("****************************===================================>      Event %d with %d tracks\n",e,ntr);

for(int t=0; t<ntr; t++)
  {
   pida_A[t]=0;
   pida_B[t]=0;
   pida_C[t]=0;
   int bins=3;
   bool normal_dir=1;
   float tr_len=htracks_tl[t]; 
  fpida1->SetParameter(0, 100.);
  fpida1->SetParameter(1, -0.7);
  fpida2->SetParameter(0, 100.);
  fpida2->SetParameter(1, -0.7);
   printf("Event %d htrack %d : nvox=%d nhts=%d",e,t,htracks_nhts[t],htracks_nvox[t]);
   TH1F ht("ht","Q vs residual range",3,0,tr_len);
   if(int(tr_len/10.) > 3) bins = int(tr_len/10.);
   TH1F htd("htd","Q vs residual range",bins,0,tr_len);
   sprintf(str,"htrack_vox_q*(htrack_vox_q>0 && htracks_ID==%d)",t);
   nv=cds_EvHough->Draw("vrange_proj1>>ht",str,"hist",1,e); //draw one track at entry t
   normal_dir=(ht.GetBinContent(1) > ht.GetBinContent(3));
   if(normal_dir) upward[t]=0; else upward[t]=1;
   if(normal_dir) //normal track direction
         nv=cds_EvHough->Draw("vrange_proj1>>htd",str,"histgoff",1,e); //draw one track at entry t    
   else  //reverse track direction
         nv=cds_EvHough->Draw("vrange_proj2>>htd",str,"histgoff",1,e); //draw one track at entry t
   htd.Fit(fpida2,"","",0,tr_len);    
 
   sprintf(str,"htrack_hits_q*(htrack_hits_q>0 && htracks_ID==%d)",t);
   if(normal_dir) //normal track direction
         nv=cds_EvHough->Draw("range_proj1>>htd",str,"histgoff",1,e); //draw one track at entry t    
   else  //reverse track direction
         nv=cds_EvHough->Draw("range_proj2>>htd",str,"histgoff",1,e); //draw one track at entry t
   htd.Fit(fpida1,"","",0,tr_len);    
   
/*
   sprintf(str,"htrack_hits_q>50 && htracks_ID==%d",t);
   n=cds_EvHough->Draw("htrack_hits_q:range_proj",str,"goff",1,e); //draw one track at entry t
   gh=new TGraph(n,cds_EvHough->GetV2(),cds_EvHough->GetV1()); 
   sprintf(str,"htrack_vox_q>50 && htracks_ID==%d",t);
   nv=cds_EvHough->Draw("htrack_vox_q:vrange_proj",str,"goff",1,e); //draw one track at entry t
   gv=new TGraph(nv,cds_EvHough->GetV2(),cds_EvHough->GetV1()); 
    printf("; after cut on q %d hits, %d voxels\n",n,nv);
  if(n==0 || nv==0)
  fpida1->SetParameter(0, 100.);
  fpida1->SetParameter(1, -0.7);
  fpida2->SetParameter(0, 100.);
  fpida2->SetParameter(1, -0.7);
  gh->Fit(fpida1);
  gv->Fit(fpida2);
  */
  pida_A[t]=fpida1->GetParameter(0);
  pida_B[t]=fpida1->GetParameter(1);
  vpida_A[t]=fpida2->GetParameter(0);
  vpida_B[t]=fpida2->GetParameter(1);
  c1->cd(1);
  ht.Draw("hist");
//  gh->Draw("AP*");
  c1->cd(2);
  htd.Draw("hist");
//  gv->Draw("AP*");
   sprintf(str,"htrack_hits_q>50 && htracks_ID==%d",t);
  if(normal_dir) //normal track direction
       cds_EvHough->Draw("4.7*(log(htrack_hits_q)-3.2)+log(range_proj1)>>hh",str,"goff",1,e);
  else 
       cds_EvHough->Draw("4.7*(log(htrack_hits_q)-3.2)+log(range_proj2)>>hh",str,"goff",1,e);
  pida_C[t]=((TH1F*)(gDirectory->FindObject("hh")))->GetMean();
   sprintf(str,"htrack_vox_q>50 && htracks_ID==%d",t);
  if(normal_dir) //normal track direction
       cds_EvHough->Draw("4.7*(log(htrack_vox_q)-3.2)+log(vrange_proj1)>>hh",str,"goff",1,e);
  else 
       cds_EvHough->Draw("4.7*(log(htrack_vox_q)-3.2)+log(vrange_proj2)>>hh",str,"goff",1,e);
  vpida_C[t]=((TH1F*)(gDirectory->FindObject("hh")))->GetMean();
  c1->Update();
  }
}
  
void pida_newformat(const char * CRSfname)
{
 // ph=new TProfile("ph","Hit q vs Range",50,0.,1000.); //20mm bin
 // pv=new TProfile("pv","Voxel q vs Range",50,0.,1000.); //20mm bin
    fpida1 = new TF1( "fpida1", "[0]*pow(x,[1])", 0, 1000.);
    fpida2 = new TF1( "fpida2", "[0]*pow(x,[1])", 0, 1000.);

  cdsf= new TFile(CRSfname , "READ" );
  cout<<"Open CRS file:" << CRSfname <<endl;

  cdsf->GetObject("Hevents",cds_EvHough);  
//  cdsf->GetObject("Htracks",cds_TrHough);
//  cdsf->GetObject("Vtx",cds_Vtx);
  if(!cds_EvHough) {printf("Cant find HEvents tree! Exiting.\n"); return;}
//  if(!cds_TrHough) {printf("Cant find HTracks tree! Exiting.\n"); return;}
//  if(!cds_Vtx) {printf("Cant find Vtx tree! Exiting.\n"); return;}
  printf("Events and Tracks tree loaded...\n");
  

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

cds_EvHough->SetAlias("t_d1x","htrack_hits_x-htracks_end_x");
cds_EvHough->SetAlias("t_d1z","htrack_hits_z-htracks_end_z");
cds_EvHough->SetAlias("t_d1y","htrack_hits_y-htracks_end_y");

cds_EvHough->SetAlias("t_d2x","htrack_hits_x-htracks_start_x");
cds_EvHough->SetAlias("t_d2y","htrack_hits_y-htracks_start_y");
cds_EvHough->SetAlias("t_d2z","htrack_hits_z-htracks_start_z");

cds_EvHough->SetAlias("range1","sqrt(t_d1x*t_d1x+t_d1y*t_d1y+t_d1z*t_d1z)");
cds_EvHough->SetAlias("range2","sqrt(t_d2x*t_d2x+t_d2y*t_d2y+t_d2z*t_d2z)");
cds_EvHough->SetAlias("range","range1*(htracks_start_y>htracks_end_y)+range2*(htracks_start_y<=htracks_end_y)");

cds_EvHough->SetAlias("range_proj1","(t_d1x*htracks_nx+t_d1y*htracks_ny+t_d1z*htracks_nz)");
cds_EvHough->SetAlias("range_proj2","-(t_d2x*htracks_nx+t_d2y*htracks_ny+t_d2z*htracks_nz)");
cds_EvHough->SetAlias("range_proj","range_proj2*(htracks_start_y>htracks_end_y)+range_proj1*(htracks_start_y<=htracks_end_y)");


cds_EvHough->SetAlias("vt_d1x","htrack_vox_x-htracks_end_x");
cds_EvHough->SetAlias("vt_d1z","htrack_vox_z-htracks_end_z");
cds_EvHough->SetAlias("vt_d1y","htrack_vox_y-htracks_end_y");

cds_EvHough->SetAlias("vt_d2x","htrack_vox_x-htracks_start_x");
cds_EvHough->SetAlias("vt_d2y","htrack_vox_y-htracks_start_y");
cds_EvHough->SetAlias("vt_d2z","htrack_vox_z-htracks_start_z");

cds_EvHough->SetAlias("vrange1","sqrt(vt_d1x*vt_d1x+vt_d1y*vt_d1y+vt_d1z*vt_d1z)");
cds_EvHough->SetAlias("vrange2","sqrt(vt_d2x*vt_d2x+vt_d2y*vt_d2y+vt_d2z*vt_d2z)");
cds_EvHough->SetAlias("vrange","vrange1*(htracks_start_y>htracks_end_y)+vrange2*(htracks_start_y<=htracks_end_y)");

cds_EvHough->SetAlias("vrange_proj1","(vt_d1x*htracks_nx+vt_d1y*htracks_ny+vt_d1z*htracks_nz)");
cds_EvHough->SetAlias("vrange_proj2","-(vt_d2x*htracks_nx+vt_d2y*htracks_ny+vt_d2z*htracks_nz)");
cds_EvHough->SetAlias("vrange_proj","vrange_proj2*(htracks_start_y>htracks_end_y)+vrange_proj1*(htracks_start_y<=htracks_end_y)");

  
  sprintf(fn_string,"PIDA_%s",CRSfname);
printf("Creating output file %s\n",fn_string);
outfile= new TFile(fn_string, "recreate");
outfile->cd();
cds_EvHough_out=cds_EvHough->CloneTree(0);
//cds_TrHough_out=cds_TrHough->CloneTree(0);
//cds_Vtx_out=cds_Vtx->CloneTree(0);

cds_EvHough_out->Branch("pida_A", pida_A,"pida_A[10]/F");
cds_EvHough_out->Branch("pida_B", pida_B,"pida_B[10]/F");
cds_EvHough_out->Branch("pida_C", pida_C,"pida_C[10]/F");
cds_EvHough_out->Branch("vpida_A", vpida_A,"vpida_A[10]/F");
cds_EvHough_out->Branch("vpida_B", vpida_B,"vpida_B[10]/F");
cds_EvHough_out->Branch("vpida_C", vpida_C,"vpida_C[10]/F");
cds_EvHough_out->Branch("upward", upward,"upward[10]/I");



 
c1 = new TCanvas("c1","PIDA",900,450);
c1->Divide(2);
c1->Update(); 

printf("Done. Looping over EvHough tree..\n");
//CalcPIDA(33);

for(int e=0; e<cds_EvHough->GetEntries(); e++)
 {
  CalcPIDA(e);
  c1->Update(); 
  cds_EvHough->GetEntry(e);
  cds_EvHough_out->Fill();
 }


cds_EvHough_out->SetAlias("t_d1x","htrack_hits_x-htracks_end_x");
cds_EvHough_out->SetAlias("t_d1z","htrack_hits_z-htracks_end_z");
cds_EvHough_out->SetAlias("t_d1y","htrack_hits_y-htracks_end_y");

cds_EvHough_out->SetAlias("t_d2x","htrack_hits_x-htracks_start_x");
cds_EvHough_out->SetAlias("t_d2y","htrack_hits_y-htracks_start_y");
cds_EvHough_out->SetAlias("t_d2z","htrack_hits_z-htracks_start_z");

cds_EvHough_out->SetAlias("range1","sqrt(t_d1x*t_d1x+t_d1y*t_d1y+t_d1z*t_d1z)");
cds_EvHough_out->SetAlias("range2","sqrt(t_d2x*t_d2x+t_d2y*t_d2y+t_d2z*t_d2z)");
cds_EvHough_out->SetAlias("range","range1*(htracks_start_y>htracks_end_y)+range2*(htracks_start_y<=htracks_end_y)");

cds_EvHough_out->SetAlias("range_proj1","(t_d1x*htracks_nx+t_d1y*htracks_ny+t_d1z*htracks_nz)");
cds_EvHough_out->SetAlias("range_proj2","-(t_d2x*htracks_nx+t_d2y*htracks_ny+t_d2z*htracks_nz)");
cds_EvHough_out->SetAlias("range_proj","range_proj2*(htracks_start_y>htracks_end_y)+range_proj1*(htracks_start_y<=htracks_end_y)");


cds_EvHough_out->SetAlias("vt_d1x","htrack_vox_x-htracks_end_x");
cds_EvHough_out->SetAlias("vt_d1z","htrack_vox_z-htracks_end_z");
cds_EvHough_out->SetAlias("vt_d1y","htrack_vox_y-htracks_end_y");

cds_EvHough_out->SetAlias("vt_d2x","htrack_vox_x-htracks_start_x");
cds_EvHough_out->SetAlias("vt_d2y","htrack_vox_y-htracks_start_y");
cds_EvHough_out->SetAlias("vt_d2z","htrack_vox_z-htracks_start_z");

cds_EvHough_out->SetAlias("vrange1","sqrt(vt_d1x*vt_d1x+vt_d1y*vt_d1y+vt_d1z*vt_d1z)");
cds_EvHough_out->SetAlias("vrange2","sqrt(vt_d2x*vt_d2x+vt_d2y*vt_d2y+vt_d2z*vt_d2z)");
cds_EvHough_out->SetAlias("vrange","vrange1*(htracks_start_y>htracks_end_y)+vrange2*(htracks_start_y<=htracks_end_y)");

cds_EvHough_out->SetAlias("vrange_proj1","(vt_d1x*htracks_nx+vt_d1y*htracks_ny+vt_d1z*htracks_nz)");
cds_EvHough_out->SetAlias("vrange_proj2","-(vt_d2x*htracks_nx+vt_d2y*htracks_ny+vt_d2z*htracks_nz)");
cds_EvHough_out->SetAlias("vrange_proj","vrange_proj2*(htracks_start_y>htracks_end_y)+vrange_proj1*(htracks_start_y<=htracks_end_y)");

cds_EvHough_out->SetAlias("v1","4.7*(log(htrack_vox_q)-3.2)+log(vrange)");
cds_EvHough_out->SetAlias("v2","htracks_qhts/htracks_tl");
cds_EvHough_out->SetAlias("cut0","abs(v2-30)<10&&abs(v1-8)<9");
cds_EvHough_out->SetAlias("cut1","abs(v2-95)<35&&abs(v1-3)<5");
cds_EvHough_out->SetAlias("cut2","abs(v2-95)<35&&abs(v1-10)<3");
cds_EvHough_out->SetAlias("cut3","abs(v2-95)<35&&abs(v1-17)<4");
cds_EvHough_out->SetAlias("av_dEdx","htracks_qhts[]/htracks_tl[]");

cds_EvHough_out->SetAlias("selectHIPs","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1 && abs(av_dEdx-90)<40 && abs(htracks_rhits[]-7)<3");

printf("Done. Saving output trees.\n");
 outfile->cd();  
 cds_EvHough_out->Write("Hevents",TObject::kOverwrite);  
 outfile->Write("",TObject::kOverwrite);  
}


/*
Hevents->Draw("4.7*(log(htrack_vox_q)-3.2)+log(vrange):htracks_qhts/htracks_tl>>hh(45,0,180,50,-5,25)","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1","colz");
Hevents->SetAlias("v1","4.7*(log(htrack_vox_q)-3.2)+log(vrange)");
Hevents->SetAlias("v2","htracks_qhts/htracks_tl");
Hevents->SetAlias("cut0","abs(v2-30)<10&&abs(v1-8)<9");
Hevents->SetAlias("cut1","abs(v2-85)<25&&abs(v1-3)<5");
Hevents->SetAlias("cut2","abs(v2-85)<25&&abs(v1-10)<3");
Hevents->SetAlias("cut3","abs(v2-85)<25&&abs(v1-17)<4");

 Hevents->Draw("htrack_vox_y:htrack_vox_x:htrack_vox_z","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1 && cut3","");
 Hevents->Draw("4.7*(log(htrack_vox_q)-3.2)+log(vrange):htracks_qhts/htracks_tl>>hh(45,0,180,50,-5,25)","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1 && cut3","colz");

Hevents->Draw("htracks_qhts[]/htracks_tl[]:htracks_rhits[]","htracks_rhits[]>0 ","")
Hevents->Draw("htracks_qhts[]/htracks_tl[]:htracks_rhits[]","htracks_rhits[]>0 && cut3","same")

Hevents->Draw("htracks_qhts[]/htracks_tl[]:htracks_rhits[]","htracks_rhits[]>0 && abs(htracks_qhts[]/htracks_tl[]-90)<40 && abs(htracks_rhits[]-7)<3","")
Hevents->Draw("4.7*(log(htrack_vox_q)-3.2)+log(vrange):htracks_qhts/htracks_tl>>hh(45,0,180,50,-5,25)","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1 && abs(htracks_qhts[]-htracks_tl[]-90)<40 && abs(htracks_rhits[]-7)<3","colz")

*/
