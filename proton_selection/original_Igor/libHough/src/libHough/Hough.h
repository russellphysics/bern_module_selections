#ifndef ROOT_Hough
#define ROOT_Hough

//-- Author :  Igor Kreslo, 2022

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// Hough                                                                //
//                                                                      //
// Class for Hough-transform based TPC track reco                       //
// Igor Kreslo, LHEP Uni-Bern (Igor.Kreslo@cern.ch)                     //
//////////////////////////////////////////////////////////////////////////


#include "TObject.h"
#include "TCanvas.h"
#include "TH3D.h"
#include "TVector3.h"
#include "TGraph2D.h"

#define BINS_THETA 100
#define BINS_PHI 100
#define BINS_R 100

class Hough;

//______________________________________________________________________________
class Hough : public TObject {

private:
Double_t GetLineR(Double_t x, Double_t y, Double_t z, Double_t theta, Double_t phi);
 TVector3 vec_n;
 TVector3 vec_p;  //point radius vector


public:
TH3D* xyz; //input volume of hits
TH3D* tpr; //output volume of 2 angles and radius (line defined as radius-vector normal to the line: two angles theta and phi; r-norm)

  Hough();
  Hough(TH3D* xyz);
  virtual ~Hough();
void PrintSummary();
void Draw();
TH3D* Transform(); 

void Test();

  ClassDef(Hough,1)  // Hough Transform
};


#endif /* ROOT_Hough */



