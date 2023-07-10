
#include "TROOT.h"
#include "TStyle.h"
#include "TColor.h"
#include "TSystem.h"
#include "TH1F.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TStyle.h"

TH1F *inh0;
TH1F *inh;
TH1F *outh;
TH1F *kernel;
TFile *f;
TH3D *xyz;
TH3D *xyz0;
TH3D *xyz_out;

#define P 5

TCanvas *c;
Float_t resval;
Float_t fracq;

void KernelTest(const char* fname)
{
gStyle->SetPalette(1);

   f=new TFile(fname);
   if(!f) return;
   if(f) xyz=(TH3D*)(f->Get("xyz"));
   if(!xyz) return;
   xyz0=(TH3D*)(xyz->Clone());
   xyz_out=(TH3D*)(xyz->Clone());
   xyz_out->Clear();
   
 //  inh=new TH1F("inh","inh",140,0,140);
 //  outh=new TH1F("outh","outh",140,0,140);
   kernel=new TH1F("kernel","kernel",100,0,100);
   c=new TCanvas("c","c",800,1200);
   c->Divide(2);
   c->Draw();
   c->cd(1);
   
   
//   for(int i=0;i<100;i++) kernel->Fill(i,1./TMath::Power(P,i));
   for(int i=0;i<100;i++) kernel->Fill(i,1./(i*0.5+1));
   
 /*
  TPC z(drift) is X axis of TH3D
  TPC x is Y axis
  TPC y is Z axis
 */
    for(int iz=xyz->GetNbinsZ();iz>0;iz--)
    for(int iy=xyz->GetNbinsY();iy>0;iy--)
// Part for Z<0
    for(int i=xyz->GetNbinsX()/2;i>0;i--)
   {
     if(xyz->GetBinContent(i,iy,iz)<=0) continue;
     xyz_out->SetBinContent(i,iy,iz,xyz->GetBinContent(i,iy,iz));
     for(int j=i;j>=0;j--) for(int k=-(i-j); k<=(i-j); k++) for(int l=-(i-j); l<=(i-j); l++) 
     {
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

// Part for Z>0
    for(int i=xyz->GetNbinsX()/2;i<xyz->GetNbinsX();i++)
   {
     if(xyz->GetBinContent(i,iy,iz)<=0) continue;
     xyz_out->SetBinContent(i,iy,iz,xyz->GetBinContent(i,iy,iz));
     for(int j=i;j<xyz->GetNbinsX();j++) for(int k=-(j-i); k<=(j-i); k++) for(int l=-(j-i); l<=(j-i); l++) 
     {
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
     }
   }
}

    for(int iz=xyz->GetNbinsZ();iz>0;iz--)
    for(int iy=xyz->GetNbinsY();iy>0;iy--)
    for(int i=xyz->GetNbinsX();i>0;i--)
   {
     if(xyz_out->GetBinContent(i,iy,iz)<=50) xyz_out->SetBinContent(i,iy,iz,0); //apply threshold
   }
   
  xyz_out->Scale(xyz0->Integral()/xyz_out->Integral()); 

  c->cd(1);
   xyz0->Draw("BOX2 COLZ");
   c->cd(2);
   xyz_out->Draw("BOX2 COLZ");
   c->Update();
  
}

void KernelTest2()
{

   
   inh=new TH1F("inh","inh",140,0,140);
   outh=new TH1F("outh","outh",140,0,140);
   kernel=new TH1F("kernel","kernel",20,0,20);
   c=new TCanvas("c","c",800,400);
   c->Divide(2);
   c->Draw();
   c->cd(1);
   
   inh->Fill(71,0.5);
   inh->Fill(72,0.25);
   inh->Fill(73,0.125);
   for(int i=70;i>0;i--) inh->Fill(i,1./TMath::Power(P,(70-i)));
   for(int i=60;i>0;i--) inh->Fill(i,0.4/TMath::Power(P,(60-i)));
   inh0=(TH1F*)(inh->Clone());
   inh->Draw("histo");
   
   for(int i=0;i<20;i++) kernel->Fill(i,1./TMath::Power(P-0.1,i));
   
  /* 
   
   for(int i=4;i>0;i--) kernel->Fill(i,2.*(i%2-0.5)/TMath::Power(3.,(5-i)));
   for(int i=6;i<10;i++) kernel->Fill(i,2.*(i%2-0.5)/TMath::Power(3.,(i-5)));
   kernel->Fill(5,-kernel->Integral()+1);
   kernel->Draw("histo");
   
   for(int i=0;i<140;i++)
   {
     for(int j=0;j<10;j++) outh->Fill(i,inh->GetBinContent(i-j-5+1)*kernel->GetBinContent(j-5+1));
   }
   
   */
 
    for(int i=141;i>=0;i--)
   {
     outh->SetBinContent(i,inh->GetBinContent(i));
     for(int j=i;j>=0;j--) 
     {
     fracq=outh->GetBinContent(i)*kernel->GetBinContent(i-j+1);
     resval=inh->GetBinContent(j)-fracq;
     if(resval<=0) 
      {
       resval=0;
    if(i!=j)   outh->SetBinContent(i,outh->GetBinContent(i)+inh->GetBinContent(j));
      }
      else 
      {
     if(i!=j)  outh->SetBinContent(i,outh->GetBinContent(i)+fracq);
      } 
     inh->SetBinContent(j,resval);
     }
   }
  
  c->cd(1);
   inh0->Draw("histo");
   c->cd(2);
   outh->Draw("histo");
   c->Update();
  
}



