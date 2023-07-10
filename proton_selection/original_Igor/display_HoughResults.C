#define PIXPITCH 4.434

//#include <TSystem.h>
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"
int i=0;
  TCanvas *c;
   TVirtualPad *c_4=0;
  TFile *cdsf;
   TH3D *xyz=0;
   TH2D *xy=0, *zy=0;
int devent(int e);


  TTree *cds_EvHough;
  TTree *Hevents;
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


void display_HoughResults(const char * CRSfname)
{
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

  cdsf= new TFile(CRSfname , "READ" );
  cout<<"Open CRS file:" << CRSfname <<endl;

  cdsf->GetObject("Hevents",cds_EvHough);  
  if(!cds_EvHough) {printf("Cant find HEvents tree! Exiting.\n"); return;}
  Hevents=cds_EvHough;
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

cds_EvHough->SetAlias("vt_d1x","htrack_vox_x-htracks_end_x");
cds_EvHough->SetAlias("vt_d1z","htrack_vox_z-htracks_end_z");
cds_EvHough->SetAlias("vt_d1y","htrack_vox_y-htracks_end_y");

cds_EvHough->SetAlias("vt_d2x","htrack_vox_x-htracks_start_x");
cds_EvHough->SetAlias("vt_d2y","htrack_vox_y-htracks_start_y");
cds_EvHough->SetAlias("vt_d2z","htrack_vox_z-htracks_start_z");

cds_EvHough->SetAlias("vrange1","sqrt(vt_d1x*vt_d1x+vt_d1y*vt_d1y+vt_d1z*vt_d1z)");
cds_EvHough->SetAlias("vrange2","sqrt(vt_d2x*vt_d2x+vt_d2y*vt_d2y+vt_d2z*vt_d2z)");
cds_EvHough->SetAlias("vrange","vrange1*(htracks_start_y>htracks_end_y)+vrange2*(htracks_start_y<=htracks_end_y)");

devent(0);

}

int devent(int e)
{

Float_t Xmax=-1e3, Xmin=1e3, Ymax=-1e3, Ymin=1e3, Zmax=-1e3, Zmin=1e3;
cds_EvHough->GetEntry(e);
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


      for(int t=0; t<nhtracks; t++) for(int h=0; h<htracks_nhts[t]; h++)
   {
        //filling plots
	xyz->Fill(htrack_hits_z[t][h], htrack_hits_x[t][h], htrack_hits_y[t][h], htrack_hits_q[t][h]);
	xy->Fill(htrack_hits_x[t][h], htrack_hits_y[t][h], htrack_hits_q[t][h]);
	zy->Fill(htrack_hits_z[t][h], htrack_hits_y[t][h], htrack_hits_q[t][h]);
	if(Xmax<htracks_end_x[t]) Xmax=htracks_end_x[t];
	if(Xmax<htracks_start_x[t]) Xmax=htracks_start_x[t];
	if(Ymax<htracks_end_y[t]) Ymax=htracks_end_y[t];
	if(Ymax<htracks_start_y[t]) Ymax=htracks_start_y[t];
	if(Zmax<htracks_end_z[t]) Zmax=htracks_end_z[t];
	if(Zmax<htracks_start_z[t]) Zmax=htracks_start_z[t];

	if(Xmin>htracks_end_x[t]) Xmin=htracks_end_x[t];
	if(Xmin>htracks_start_x[t]) Xmin=htracks_start_x[t];
	if(Ymin>htracks_end_y[t]) Ymin=htracks_end_y[t];
	if(Ymin>htracks_start_y[t]) Ymin=htracks_start_y[t];
	if(Zmin>htracks_end_z[t]) Zmin=htracks_end_z[t];
	if(Zmin>htracks_start_z[t]) Zmin=htracks_start_z[t];

	
   }

   
   //xyz->GetZaxis()->SetRangeUser(0,1200);
//   xyz->SetMaximum(400);
   xyz->GetZaxis()->SetRangeUser(Ymin-100,Ymax+100);
   xyz->GetYaxis()->SetRangeUser(Xmin-100,Xmax+100);
   xyz->GetXaxis()->SetRangeUser(Zmin-100,Zmax+100);
   xyz->SetMaximum(300);
   xyz->Draw("BOX2 Z");
   
 //  xyz->Draw("GLBOX1 Z");

   gPad->SetTheta(5);
   gPad->SetPhi(30);
   c->cd(2);

   xy->SetTitle(Form("event %d xy view",eventID));
   xy->SetStats(0);
   xy->GetXaxis()->SetRangeUser(Xmin-100,Xmax+100);
   xy->GetYaxis()->SetRangeUser(Ymin-100,Ymax+100);
   xy->Draw("colz");
   c->cd(3);
   
   zy->SetTitle(Form("Event %d zy view",eventID));
   zy->SetStats(0);
   zy->GetXaxis()->SetRangeUser(Zmin-100,Zmax+100);
   zy->GetYaxis()->SetRangeUser(Ymin-100,Ymax+100);
   zy->Draw("colz");


        c->cd(5);
	double max_light = max(lnegx320->GetMaximum() , lposx320->GetMaximum()); 
	//max_light = min(4000.00 , max_light);
   	lnegx320->SetMaximum(max_light);
	lnegx320->SetMinimum(min(lnegx320->GetMinimum() , lposx320->GetMinimum()));
//	lnegx320->SetMinimum(-1);
	    for(int i=0; i<=lnegx320->GetNbinsX(); i++)  for(int j=0; j<=lnegx320->GetNbinsY(); j++) if(lnegx320->GetBinContent(i,j)==0) lnegx320->SetBinContent(i,j,0.1);
        lnegx320->GetXaxis()->SetTitle("z [mm]");
        lnegx320->GetYaxis()->SetTitle("y [mm]");
	lnegx320->SetStats(0);
   	lnegx320->Draw("colz");

   	c->cd(6);
   	lposx320->SetMaximum(max_light);
        lposx320->SetMinimum(min(lnegx320->GetMinimum() , lposx320->GetMinimum()));
	//    lposx320->SetMinimum(-1);
	    for(int i=0; i<=lposx320->GetNbinsX(); i++)  for(int j=0; j<=lposx320->GetNbinsY(); j++) if(lposx320->GetBinContent(i,j)==0) lposx320->SetBinContent(i,j,0.1);
        lposx320->GetXaxis()->SetTitle("z [mm]");
        lposx320->GetYaxis()->SetTitle("y [mm]");
        lposx320->SetStats(0);
   	lposx320->Draw("colz");


      for(int t=0; t<nhtracks; t++) 
   {
   	
    c->cd(1);   	
   TGraph2D *g=new TGraph2D(2);
   g->SetPoint(0,htracks_end_z[t],htracks_end_x[t],htracks_end_y[t]);
   g->SetPoint(1,htracks_start_z[t],htracks_start_x[t],htracks_start_y[t]);
   g->SetLineWidth(2);
   if(htracks_npts[t]>50) g->SetLineColor(kBlack);
   else g->SetLineColor(kMagenta);
   g->Draw("LINEsame");


   TGraph2D *ga=new TGraph2D(2);
   ga->SetPoint(0,Zmin-100,Xmin-100,Ymin-100);
   ga->SetPoint(1,htracks_az[t],htracks_ax[t],htracks_ay[t]);
   ga->SetLineWidth(2);
   ga->SetLineColor(kGreen);
   ga->Draw("LINEsame");

   TGraph2D *gn=new TGraph2D(2);
   gn->SetPoint(0,htracks_az[t],htracks_ax[t],htracks_ay[t]);
   gn->SetPoint(1,htracks_az[t]+htracks_nz[t]*100,htracks_ax[t]+htracks_nx[t]*100,htracks_ay[t]+htracks_ny[t]*100);
   gn->SetLineWidth(2);
   gn->SetLineColor(kYellow);
   gn->Draw("LINEsame");



    c->cd(2);
    TGraph *gxy=new TGraph(2);
   gxy->SetPoint(0,htracks_end_x[t],htracks_end_y[t]);
   gxy->SetPoint(1,htracks_start_x[t],htracks_start_y[t]);
   gxy->SetLineWidth(1);
   if(htracks_npts[t]>50) gxy->SetLineColor(kBlack);
   else gxy->SetLineColor(kMagenta);
   gxy->Draw("LINEsame");

    c->cd(3);
    TGraph *gzy=new TGraph(2);
   gzy->SetPoint(0,htracks_end_z[t],htracks_end_y[t]);
   gzy->SetPoint(1,htracks_start_z[t],htracks_start_y[t]);
   gzy->SetLineWidth(1);
   if(htracks_npts[t]>50) gzy->SetLineColor(kBlack);
   else gzy->SetLineColor(kMagenta);
   gzy->Draw("LINEsame");
   
   
   c->Update();
   }
   	
return 1;
}



