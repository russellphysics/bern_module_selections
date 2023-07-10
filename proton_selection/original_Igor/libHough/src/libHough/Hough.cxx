//-- Author :  Igor Kreslo, 2022

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Hough                                                                //
//                                                                      //
// Class for Hough-transform based TPC track reco                       //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdio.h>

#include <TSystem.h>
#include <TObject.h>
#include <TClass.h>
#include <TRandom.h>
#include <TMath.h>
#include <TH3.h>
#include <TPolyLine3D.h>

#include "Hough.h"

#define pi 3.14152

ClassImp(Hough)


//______________________________________________________________________________
Hough::Hough():TObject()
{
tpr=NULL;
xyz=NULL;
}

//______________________________________________________________________________
Hough::Hough(TH3D* in_xyz):TObject()
{
xyz=in_xyz;
if(tpr==NULL) tpr=new TH3D("Hough","Hough", BINS_THETA,0,pi,BINS_PHI,-pi,pi,BINS_R,0,800);
else tpr->Clear();

}



//______________________________________________________________________________
Hough::~Hough()
{
    if(tpr) {tpr->Delete(); delete tpr; tpr=NULL;}
}

//______________________________________________________________________________
TH3D*  Hough::Transform() 
{ 
int binsx,binsy,binsz;
Double_t theta, phi, R,q;
Double_t x,y,z;
char line[128];
TString s;

binsx=xyz->GetNbinsX();
binsy=xyz->GetNbinsY();
binsz=xyz->GetNbinsZ();

printf("Input space %dx%dx%d bins. Hough transform is in progress..\n",binsx,binsy,binsz);
gSystem->Exec("rm testdata.dat");
gSystem->Exec("rm out.dat");
for(int xb=1; xb<binsx-1; xb++)
for(int yb=1; yb<binsy-1; yb++)
for(int zb=1; zb<binsz-1; zb++)
 {
   q=xyz->GetBinContent(xb,yb,zb);
   if(q==0) continue;
   x=((TAxis*)xyz->GetXaxis())->GetBinCenter(xb);
   y=((TAxis*)xyz->GetYaxis())->GetBinCenter(yb);
   z=((TAxis*)xyz->GetZaxis())->GetBinCenter(zb);
   /*
   for(int tb=1; tb<=BINS_THETA; tb++)
   for(int pb=1; pb<=BINS_PHI; pb++)
   {
     theta=((TAxis*)tpr->GetXaxis())->GetBinCenter(tb);
     phi=((TAxis*)tpr->GetYaxis())->GetBinCenter(pb);
     R=GetLineR(x,y,z,theta,phi);
//     tpr->Fill(theta,phi,R,q);
     tpr->Fill(phi,theta,R,q);
   }
   */
   sprintf(line,"echo %f,%f,%f >>testdata.dat",x,y,z);
   gSystem->Exec(line);
 }

   s=gSystem->GetFromPipe("./hough3dlines testdata.dat -dx 0.4 -raw");
   printf("out: \n%s\n",s.Data());


printf("End Test part.\n");
return tpr;

}

//______________________________________________________________________________
Double_t Hough::GetLineR(Double_t x, Double_t y, Double_t z, Double_t theta, Double_t phi)
{
 Double_t retval=0;
 vec_p.SetXYZ(x,y,z);
 vec_n.SetXYZ(1,1,1);
 vec_n.SetTheta(theta); 
 vec_n.SetPhi(phi); 
 retval=(vec_p.Cross(vec_n)).Mag() / vec_n.Mag();
 //printf("Bin (%f,%f,%f), theta=%f, phi=%f, return %f\n",x,y,z,theta,phi,retval);
 
 return retval;
}

//______________________________________________________________________________
void  Hough::Draw() 
{ 
if(tpr) tpr->Draw("BOX2 Z");
}

#define PIXPITCH 4.434

//______________________________________________________________________________
void  Hough::Test() 
{ 
TCanvas *c;
xyz = new TH3D("3D_view","3D_view", 140,-PIXPITCH*70,PIXPITCH*70 ,140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140);
if(tpr==NULL) tpr=new TH3D("Hough","Hough", BINS_THETA,0,pi,BINS_PHI,-pi,pi,BINS_R,0,800);
else tpr->Clear();

Int_t maxBin;
Int_t maxBinx;
Int_t maxBiny;
Int_t maxBinz;
Double_t max_theta,max_phi,max_R;

for(int i=0;i<100; i++)
//for(int i=0;i<1; i++)
 {
 //  xyz->Fill(20+i,20+i,40+i*2,1);   
   xyz->Fill(20+i,20+i,50.0,1.0);   
 }
   Transform();
   c=new TCanvas();
   c->Divide(2);
   c->cd(1);
   xyz->Draw("BOX2 Z");
   c->cd(2);
/*   tpr->SetMinimum(80);
   tpr->Draw("BOX2 Z");
   maxBin=tpr->GetMaximumBin();
   tpr->GetBinXYZ(maxBin,maxBinx,maxBiny,maxBinz);
   max_theta=((TAxis*)tpr->GetXaxis())->GetBinCenter(maxBinx);
   max_phi=((TAxis*)tpr->GetYaxis())->GetBinCenter(maxBiny);
   max_R=((TAxis*)tpr->GetZaxis())->GetBinCenter(maxBinz);
  
   printf("Max value of %f at theta=%f phi=%f R=%f\n",tpr->GetBinContent(maxBin),max_theta,max_phi,max_R);
   */
   c->cd(1);
   TGraph2D *g=new TGraph2D(2);
//   g->SetPoint(0,-100*cos(max_phi),-100*sin(max_phi),-100*cos(max_theta));
//   g->SetPoint(1,100*cos(max_phi),100*sin(max_phi),100*cos(max_theta));
   g->Draw("LINEsame");
}



//______________________________________________________________________________
void Hough::PrintSummary()
{

 printf("***********************************************************************\n");

}




