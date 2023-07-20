//For module 0
//#define LDS_PATH "/data/LRS/SingleModule_2021/Converted/rwf_20210405_203834.data.root"
//#define CRS_PATH "/media/daq/My Book Duo/SingleModule_March21/TPC12/dataRuns/evdData/good_michel/michel_datalog_2021_04_05_20_38_29_CEST_evd.root"

//Path for module 1
//#define LDS_PATH "/data/LRS/SingleModule_Jan22/Converted/rwf_0cd913fb_20220211_050032.data.root"
#define LDS_PATH "/mnt/synology/data/Mod1_data/LRS/SingleModule_Jan22/Converted/rwf_0cd93db0_20220211_050032.data.root"
//"/data/LRS/SingleModule_Jan22/Converted/rwf_0cd93db0_20220211_050032.data.root"
#define CRS_PATH "/mnt/synology120TB/data/Mod1_data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/packet_2022_02_11_05_00_12_CETevd.root"

//"/data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/test/packet_2022_02_11_05_00_12_CETevd.root"

//#define CRS_PATH "/data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/packet_2022_02_11_05_00_12_CETevd.root"

#define OUT_PATH "combied_test.root"
//"/data/LArPix/SingleModule_Jan2022/TPC12/dataRuns/evdData/rootFiles/test/packet_2022_02_11_05_00_12_CETevd_w_light.root"

#define offset_ns_nmax 128*10

#define ADC1 215553019 //sn ADC1 CD913FB ACL
#define ADC2 215563696 //sn ADC2 CD93DB0 LCM
#define ADC3 215564636 //sn ADC3 CD9415C SUM

#include <TSystem.h>

  TFile *comf;
  TFile *cdsf;
  TFile *ldsf;
  TObjString *lds_os;
  TObjString *cds_os;
  TTree *comb_tr;
  TTree *cds_Evtr;
  TTree *cds_Trtr;
  TTree *lds_rwftr;
  TTree *output_Evtr;
  TTree *output_Trtr;

  //TFile *my_file;
  //TTree *my_tr;
  //TEventList *my_list;

  char cut_string[256];

  TH1S * chh;
 
  
      // Declaration of leaf types
   UInt_t          event =0;
   UInt_t          sn =0;
   UInt_t          ch =0;
   ULong64_t       ntp_ms =0;
   ULong64_t       tai_ns =0;
   ULong64_t       pps_ns =0;
   TH1S            *th1s_ptr;
   TH1I		   *th1i_ptr= new TH1I("wf","wf",1000,0,1000);
   Int_t offset_ns[offset_ns_nmax] ={0};
   Int_t offset_ns_n=0;
   Int_t wf =0;
   Int_t t_window =300;

  //Decleration of charge data leaf types
  Int_t track_ID =0, track_nhits=0, event_ID=0, event_ntracks=0, event_nhits=0, event_unix_ts=0, event_start_t=0,
	        track_eventID =0, track_no_in_event=0, track_t0=0, track_ts_start=0, track_ts_end=0;
  Float_t theta=0.0, phi=0.0, dl=0.0, track_q=0.0, event_q=0.0, dx=0.0, dy=0.0, dz=0.0;
  //tracks hit properties
  Float_t tr_h_x[100000], tr_h_y[100000],tr_h_z[100000], tr_h_q[100000], tr_h_dr[100000];
  Int_t tr_h_ts[100000],  tr_h_Dt[100000];

  //events hit properties
  Float_t ev_h_x[100000] ={0.0}, ev_h_y[100000]={0.0},ev_h_z[100000]={0.0}, ev_h_q[100000]={0.0};
  Int_t ev_h_ts[100000] ={0}, ev_h_Dt[100000]={0};

  Int_t dev=0;
  EColor color=kBlack;

TCanvas *c;
TCanvas *ct;
TCanvas *cc;

TEventList *tr_elist; //list of associated entries in Tracks tree in CDS file
TEventList *rwf_elist; //list of associated entries (by time) in Hits tree in LDS file

Int_t eventID;
Int_t Dt_unix_ms;
Int_t Dt_ns;

//#define offset_ns_nmax 128*10
void new_select(int ev);
void check_match();
void display_event(int ev);
void select_event(int ev);
int GetNTracks();
void select_track(int tr);
int GetNWaveforms();
TH1I* GetWaveform(int wf);
//TH1S* GetWaveform(int wf);
TH1S* GetNextWaveform();

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


void RestoreBL(TH1I * h) // TH1S * h
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

void FilterSinus(TH1S * h)
{
 TH1 *hm =0;
 TH1 *hp =0;
 int n=h->GetXaxis()->GetNbins();
 //cout<<" The n bins in the filter sinus is:" <<n<<endl; // There are 256 bins
 TVirtualFFT::SetTransform(0);
 hm = h->FFT(hm, "MAG");
 hp = h->FFT(hp, "PH");
 TVirtualFFT *fft = TVirtualFFT::GetCurrentTransform();
 Double_t *re_full = new Double_t[n];
 Double_t *im_full = new Double_t[n];
 fft->GetPointsComplex(re_full,im_full);
int i1,i2;
if(n==2048) { i1=198; i2=212;}
if(n==1024) { i1=99; i2=106;}
if(n==512) { i1 =48; i2 =52;}
if(n==256) { i1=22; i2=28;}
for(int i=i1; i<=i2; i++) 
  { 
    im_full[i]=0;
    im_full[n-i]=0;
    re_full[i]=0;
    re_full[n-i]=0;
  }
for(int i=2*i1; i<=2*i2; i++) 
  {
    im_full[i]=0;
    im_full[n-i]=0;
    re_full[i]=0;
    re_full[n-i]=0;
  }
for(int i=3*i1; i<=3*i2; i++) 
  {
    im_full[i]=0;
    im_full[n-i]=0;
    re_full[i]=0;
    re_full[n-i]=0;
  }

for(int i=4*i1; i<=4*i2; i++) 
  {
    im_full[i]=0;
    im_full[n-i]=0;
    re_full[i]=0;
    re_full[n-i]=0;
  }
for(int i=5*i1; i<=5*i2; i++) 
  {
    im_full[i]=0;
    //im_full[n-i]=0;
    re_full[i]=0;
    //re_full[n-i]=0;
  }


if(n==256)
//if(n==1024) 
//for(int i = 1; i<4; i++) 
   { 
    int i=3;
    im_full[i]=0;
    im_full[n-i]=0;
    re_full[i]=0;
    re_full[n-i]=0;
    }
TVirtualFFT *fft_back = TVirtualFFT::FFT(1, &n, "C2R M K");
fft_back->SetPointsComplex(re_full,im_full);
fft_back->Transform();
TH1 *hb = 0;
hb = TH1::TransformHisto(fft_back,hb,"Re");
h->Reset();
h->Add(hb, 1./n);
delete hb;
delete hm;
delete hp;
}
 

char fname1[256];
char fname2[256];

void Module1_event_matching_for_correct_xy(const char * fname)
{
  //comf= new TFile(fname);
  //comf->GetObject("LDS",lds_os);
  //comf->GetObject("CDS",cds_os); 

  //my_file = TFile::Open((std::string(LDS_PATH)+ std::string( basename(lds_os->GetName()) ) ).c_str() );
  //my_tr = (TTree*)my_file->Get("rwf");
  /*
  printf("File links %s and %s\n",(std::string(LDS_PATH)+ std::string( basename(lds_os->GetString().Data()) )).c_str() , (std::string(CRS_PATH) + std::string(basename(cds_os->GetString().Data()))).c_str() );
  comf->GetObject("comb_tr",comb_tr);
  comb_tr->SetBranchAddress("eventID",&eventID);
  comb_tr->SetBranchAddress("tracks",&tr_elist);
  comb_tr->SetBranchAddress("lds",&rwf_elist);
  comb_tr->SetBranchAddress("Dt_unix_ms",&Dt_unix_ms);
  comb_tr->SetBranchAddress("Dt_ns",&Dt_ns);
  comb_tr->SetBranchAddress("offset_ns_n",&offset_ns_n);
  comb_tr->SetBranchAddress("offset_ns",&offset_ns[0]);
  */
  //cdsf=new TFile(cds_os->GetString().Data());
  cdsf= new TFile(std::string(CRS_PATH).c_str() , "UPDATE" );
  cout<<"Open file:" << std::string(CRS_PATH).c_str() <<endl;

  cdsf->GetObject("events",cds_Evtr);  //Get event tree
  cdsf->GetObject("tracks",cds_Trtr);
  //output_Evtr = cds_Evtr->CloneTree(0);

   cds_Trtr->SetBranchAddress("track_nhits",&track_nhits);
   cds_Trtr->SetBranchAddress("trackID", &track_ID);
   cds_Trtr->SetBranchAddress("eventID",&track_eventID);
   cds_Trtr->SetBranchAddress("track_no_in_event",&track_no_in_event);

   cds_Trtr->SetBranchAddress("track_t0",&track_t0);
   cds_Trtr->SetBranchAddress("track_ts_start", &track_ts_start);
   cds_Trtr->SetBranchAddress("track_ts_end",&track_ts_end);

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

   cds_Trtr->BuildIndex("eventID","track_no_in_event");

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
   cds_Evtr->SetBranchAddress("event_hits_Dt", ev_h_Dt);

   //ldsf=new TFile(lds_os->GetString().Data());
   ldsf= new TFile( std::string(LDS_PATH).c_str());
   ldsf->GetObject("rwf",lds_rwftr);  //Get light tree
   //lds_rwftr->Print();

   lds_rwftr->SetBranchAddress("event", &event);
   lds_rwftr->SetBranchAddress("sn", &sn);
   lds_rwftr->SetBranchAddress("ch", &ch);
   lds_rwftr->SetBranchAddress("ntp_ms", &ntp_ms);
   lds_rwftr->SetBranchAddress("tai_ns", &tai_ns);
   lds_rwftr->SetBranchAddress("tslpps_ns", &pps_ns);
   lds_rwftr->SetBranchAddress("th1s_ptr", &th1s_ptr);

  if(chh==0) 
  {
   chh=new TH1S("chh","chh",31000,-1000,30000);
   //chh->GetYaxis()->SetRangeUser(-32800,5000);
   chh->GetXaxis()->SetTitle("ns");
   chh->GetYaxis()->SetTitle("ADC");
   chh->SetStats(0);
  } 

//select_event(0);
//new_select(0);
//select_track(0);
//lds_rwftr->GetEntry(0);
}

Int_t bins;
Int_t trel;

int GetNWaveforms()
{
  return rwf_elist->GetN();
 //return my_list->GetN();
}

TH1I* GetWaveform(int wf)  //Changed from TH1S
{
  lds_rwftr->GetEntry(rwf_elist->GetEntry(wf));
  //lds_rwftr->GetEntry(my_list->GetEntry(wf));
  //if(ch==8 || ch==40 || ch==24 || ch==56 ) { FilterSinus(th1s_ptr); th1s_ptr->Smooth(4);} 
  //if(ch<9 || (ch>17 && ch<25) || (ch>33 && ch<41) || (ch>49 && ch<57) ) { FilterSinus(th1s_ptr); th1s_ptr->Smooth(4);} 

  //RestoreBL(th1s_ptr);
  //trel=offset_ns[wf];
  trel=(tai_ns-36000000000)-1000*(event_unix_ts*1000000+event_start_t/10);
  bins=th1s_ptr->GetXaxis()->GetNbins();
  //cout<<"number of bins: "<<bins<<endl;
  th1s_ptr->SetLineColor(kRed);
  th1s_ptr->GetXaxis()->Set(bins,0,998);
  //th1s_ptr->GetXaxis()->Set(bins,trel,trel+bins*16);
  
  //th1s_ptr->SetMinimum( min(-5000.0, th1s_ptr->GetMinimum() ));
  //th1s_ptr->SetMaximum( max(1000.0, th1s_ptr->GetMaximum() ));
  //th1s_ptr->Draw("");
  //th1i_ptr = new TH1I("wf","wf",1000,0,1000);
  for(int b = 0; b<1000; b++){
	th1i_ptr->SetBinContent(b,th1s_ptr->GetBinContent(b));
  }
  th1i_ptr->SetTitle(th1s_ptr->GetTitle());
  th1i_ptr->SetName(th1s_ptr->GetName());
  RestoreBL(th1i_ptr);

  return th1i_ptr; //Changed from TH1S
}
/*
TH1S* GetNextWaveform()
{
  lds_rwftr->GetEntry(rwf_elist->Next());
  //lds_rwftr->GetEntry(my_list->Next());
  //if(ch<9 || (ch>17 && ch<25) || (ch>33 && ch<41) || (ch>49 && ch<57) ) { FilterSinus(th1s_ptr); th1s_ptr->Smooth(4);} 
  //if(ch==8 || ch==40 || ch==24 || ch==56 ) { FilterSinus(th1s_ptr); th1s_ptr->Smooth(4);} 
  RestoreBL(th1s_ptr);
  trel=offset_ns[wf];
  bins=th1s_ptr->GetXaxis()->GetNbins();
  th1s_ptr->SetLineColor(color);
  th1s_ptr->GetXaxis()->Set(bins,trel,trel+bins*10);
  th1s_ptr->SetMinimum( min(-5000.0, th1s_ptr->GetMinimum() ));
  th1s_ptr->SetMaximum( max(1000.0, th1s_ptr->GetMaximum() ));
  //th1s_ptr->Draw();
  return th1s_ptr;
}
*/

int GetNTracks()
{
 return tr_elist->GetN();
}


void select_track(int tr)
{
 cds_Trtr->GetEntry(tr_elist->GetEntry(tr));
}

void select_event(int ev)
{
  //comb_tr->GetEntry(ev);
  cds_Evtr->GetEntry(ev);
  cds_Trtr->SetEventList(tr_elist);
  lds_rwftr->SetEventList(rwf_elist);
}


void new_select(int ev){
  cds_Evtr->GetEntry(ev);
 
   //cout<<"calling event "<<ev<<endl;
   //cout<<"charge event time [us]: "<< (long long)event_unix_ts*1000000 + event_start_t /10 <<endl;
   //cout<<event_unix_ts << " , " <<event_start_t <<endl; 

   sprintf(cut_string, "abs(tai_ns/1000-36000000-%lld)< %d ",(long long)event_unix_ts*1000000 + event_start_t /10 , t_window);
   ldsf->cd();
   lds_rwftr->SetEventList(0); //This line solved the bug. it will clear the event list 
   lds_rwftr->Draw(">>elist_light", cut_string,"*");
   rwf_elist=(TEventList*)gDirectory->Get("elist_light");
   lds_rwftr->SetEventList(rwf_elist);
   //cout<<"Found waveforms: "<<rwf_elist->GetN()<<endl;
   lds_rwftr->GetEntry(rwf_elist->GetEntry(0));
   //cout<<"light event time [us]: "<< (long long)tai_ns/1000 -36000000 <<endl;

   cds_Trtr->SetEventList(0);
   cds_Trtr->Draw(">>el_tr",Form("eventID== %d",event_ID),"*");
   tr_elist = (TEventList*)gDirectory->Get("el_tr");
   cds_Trtr->SetEventList(tr_elist);
}


  
void display_event(int ev)
{
   new_select(ev);
   cout<< "Plotting event "<<ev<<" with ID "<<event_ID<<endl;
   int id = event_ID;
   int map_sn_ch_to_ybin[2][64]  =  {{-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17,-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17,-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17,-1,-1,-1,-1,0,1,2,3,4,5,12,13,14,15,16,17},
				    {-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23,-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23,-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23,-1,-1,-1,-1,6,7,8,9,10,11,18,19,20,21,22,23}};

   int map_sn_ch_to_xbin[2][64]  =  {{-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1},
                                     {-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1}};

   int map_sn_ch_to_tpc[2][64]   =  {{-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2},
				    {-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2}}; 

   int map_sn_ch_to_display[2][64]  =  {{-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1},
                                        {-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,2,2,2,2,2,2,2,2,2,2,2,2,-1,-1,-1,-1,1,1,1,1,1,1,1,1,1,1,1,1}}; 

   int zbin;
   TH3D *xyz = new TH3D("3D_view","3D_view", 62,-310,310 ,62,-310,310, 124,-620,620);
   TH2D *xy = new TH2D("xy","xy",62, -310,310, 124, -620,620);
   TH2D *zy = new TH2D("zy","zy",62, -310,310, 124, -620,620);
   TH2D *l_display_1 = new TH2D("light-310","light readout at x=-310 mm",2,-310,310,24,-620,620);
   TH2D *l_display_2 = new TH2D("light+310","light readout at x=+310 mm",2,-310,310,24,-620,620);
   //TH1S *temp, *hsum1[9], *hsum2[9];
   TH1I *temp, *hsum1[9], *hsum2[9];

   //c->Clear();
   c = new TCanvas("c","display",700,800);
   c->Divide(3,2);

   //3D view
   c->cd(1);
   for(int i=0; i< event_nhits; i++){
	xyz->Fill(ev_h_z[i], ev_h_x[i], ev_h_y[i], ev_h_q[i]*0.245);
   }
   xyz->GetXaxis()->SetTitle("z [mm]");
   xyz->GetYaxis()->SetTitle("x [mm]");
   xyz->GetZaxis()->SetTitle("y [mm]");
   xyz->SetLineWidth(0);
   xyz->Draw("BOX2 Z");

   gPad->SetTheta(5);
   gPad->SetPhi(30);

   c->cd(2);

   //cds_Evtr->Draw("event_hits_y: event_hits_x: event_hits_q*0.245>>xy_view(50,0,1000,31,-310,310,62,-620,620)",Form("eventID == %d",id),"colz");
   for(int t=0; t< event_ntracks; t++){
	select_track(t);
	//cout<<"track "<< t <<" nhits: "<< track_nhits << " track_q "<<track_q<< " hit x " << tr_h_x[1] << endl;

	for(int i=0; i<track_nhits; i++){
        	xy->Fill( tr_h_x[i], tr_h_y[i], tr_h_q[i]*0.245);
	}
   }

   //xy = (TH2D*)gDirectory->Get("xy_view");
   xy->GetXaxis()->SetTitle("x [mm]");
   xy->GetYaxis()->SetTitle("y [mm]");
   xy->GetYaxis()->SetTitleOffset(1.5);
   xy->SetTitle(Form("event %d xy view",id));
   xy->SetStats(0);
   xy->Draw("colz1");


   c->cd(3);
   for(int t=0; t< event_ntracks; t++){
        select_track(t);
        //cout<<"track "<< t <<" nhits: "<< track_nhits << " track_q "<<track_q<< " hit x " << tr_h_x[1] << endl;

        for(int i=0; i<track_nhits; i++){
                 zy->Fill( tr_h_z[i], tr_h_y[i], tr_h_q[i]*0.245);
        }
   }

   //cds_Evtr->Draw("event_hits_y: event_hits_z: event_hits_q*0.245 >>zy_view(50,0,1000,155,-310,310,310,-620,620)",Form("eventID == %d",id),"colz");

   //zy =(TH2D*)gDirectory->Get("zy_view");
   zy->GetXaxis()->SetTitle("z [mm]");
   zy->GetYaxis()->SetTitle("y [mm]");
   zy->GetYaxis()->SetTitleOffset(1.5);
   zy->SetTitle(Form("Event %d zy view",id));
   zy->SetStats(0);
   zy->Draw("colz1");

   //c->cd(4);
   cout<<" N waveforms: "<< GetNWaveforms()<<endl;
   //if(GetNWaveforms() == 0) continue;

   //new_select(ev);

   try{
   	if(GetNWaveforms() ==0) throw 1;
	if(GetNWaveforms() ==58) throw 2;
   	for(int i =0; i < GetNWaveforms(); i++){
	    int adc = -1;
	    double integral_temp = 0;
	    temp = GetWaveform(i);
            //temp->Draw();
 	    
	    if(sn == ADC1 && gain[0][ch]!=-1){ cout<<"waveform " <<i <<" form ADC1 sn: "<< sn <<" ch: "<<ch << " y bin: " << map_sn_ch_to_ybin[0][ch] \
				<<" x bin: " << map_sn_ch_to_xbin[0][ch] << " tpc " << map_sn_ch_to_tpc[0][ch]  <<" Integral: "<<-1*temp->Integral(61,92)*4/gain[0][ch] << endl;
			integral_temp = -1*temp->Integral(61,92)*4/gain[0][ch];
	    }
            if(sn == ADC2 && gain[1][ch]!=-1){ cout<<"waveform " <<i <<" form ADC2 sn: "<< sn <<" ch: "<<ch << " y bin: " << map_sn_ch_to_ybin[1][ch] \
				<<" x bin: " << map_sn_ch_to_xbin[1][ch] << " tpc " << map_sn_ch_to_tpc[1][ch] <<" Integral: "<<-1*temp->Integral(61,92)/gain[1][ch] << endl;
                        integral_temp = -1*temp->Integral(61,92)/gain[1][ch];
	    }
            if(sn == ADC3 ) cout<<"waveform " <<i <<" form ADC3 sn: "<< sn <<" ch: "<<ch <<" SUM Integral: "<<-1*temp->Integral(61,92)/200 << endl;


	    if (sn == ADC1) adc = 0;
            if (sn == ADC2) adc = 1;

            if(map_sn_ch_to_display[adc][ch] == 1)
		l_display_1->Fill((double)-150.0 + 300*map_sn_ch_to_xbin[adc][ch] ,(double)-610 + (640+640)/24 *map_sn_ch_to_ybin[adc][ch],(double) integral_temp); //(temp->FindBin(900),temp->FindBin(1400))/(gain_1[1][ch] * 64.0))) );

            if(map_sn_ch_to_display[adc][ch] == 2)
                l_display_2->Fill((double)-150.0 + 300*map_sn_ch_to_xbin[adc][ch] ,(double)-610 + (640+640)/24 *map_sn_ch_to_ybin[adc][ch],(double) integral_temp);

   	 }

        c->cd(5);
	double max_light = max(l_display_1->GetMaximum() , l_display_2->GetMaximum()); 
	//max_light = min(4000.00 , max_light);
   	l_display_1->SetMaximum(max_light);
	l_display_1->SetMinimum(min(l_display_1->GetMinimum() , l_display_2->GetMinimum()));
        l_display_1->GetXaxis()->SetTitle("z [mm]");
        l_display_1->GetYaxis()->SetTitle("y [mm]");
	l_display_1->GetYaxis()->SetTitleOffset(1.5);
	l_display_1->SetStats(0);
   	l_display_1->Draw("colz1");

   	c->cd(6);
   	l_display_2->SetMaximum(max_light);
        l_display_2->SetMinimum(min(l_display_1->GetMinimum() , l_display_2->GetMinimum()));
        l_display_2->GetXaxis()->SetTitle("z [mm]");
        l_display_2->GetYaxis()->SetTitle("y [mm]");
        l_display_2->GetYaxis()->SetTitleOffset(1.5);
        l_display_2->SetStats(0);
   	l_display_2->Draw("colz1");


        // This is to duplicate exactly Igor sum plots
   	//TCanvas *c2 = new TCanvas("c2","display_waveforms, tpc1_blue, tpc2_red",500,800);
	TVirtualPad *c_4 = c->cd(4); 
	c_4->cd();
	c_4->Divide(2,4);

	TH1S *tpc1_sum[9], *tpc2_sum[9];
	for(int i =0; i < GetNWaveforms(); i++){

     		temp = GetWaveform(i);
                if (sn != ADC3) continue;
      		if(ch == 15){ tpc1_sum[7] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[7]"<<endl;} 
      		if(ch == 47){ tpc1_sum[5] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[5]"<<endl;}
      		if(ch == 14){ tpc1_sum[3] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[3]"<<endl;}
      		if(ch == 46){ tpc1_sum[1] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[1]"<<endl;}

      		if(ch == 13){ tpc1_sum[8] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[8]"<<endl;}
      		if(ch == 45){ tpc1_sum[6] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[6]"<<endl;}
      		if(ch == 12){ tpc1_sum[4] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[4]"<<endl;}
      		if(ch == 44){ tpc1_sum[2] =(TH1S*)temp->Clone();}//cout<<"test clone temp to tpc1_sum[2]"<<endl;} 

      		if(ch == 31){ tpc2_sum[8] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[7]"<<endl;} 
      		if(ch == 63){ tpc2_sum[6] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[5]"<<endl;} 
      		if(ch == 30){ tpc2_sum[4] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[3]"<<endl;} 
      		if(ch == 62){ tpc2_sum[2] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[1]"<<endl;} 

      		if(ch == 29){ tpc2_sum[7] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[8]"<<endl;} 
      		if(ch == 61){ tpc2_sum[5] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[6]"<<endl;} 
      		if(ch == 28){ tpc2_sum[3] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[4]"<<endl;} 
      		if(ch == 60){ tpc2_sum[1] = (TH1S*)temp->Clone();}//cout<<"test clone temp to tpc2_sum[2]"<<endl;} 
   	}
        cout<<"Sum waveforms filled"<<endl;

	for(Int_t j=1; j<9; j++){
      		c_4->cd(j);
		//cout<<"filling c pad "<< j <<endl;

      		tpc1_sum[j]->SetLineColor(kBlue);
      		tpc1_sum[j]->GetYaxis()->SetRangeUser(-54000,5000);
		tpc1_sum[j]->GetYaxis()->SetTitleOffset(0.9);
      		tpc1_sum[j]->Draw("hist");
		//cout<<"draw h "<<j<<endl;

      		tpc2_sum[j]->SetLineColor(kRed);
      		tpc2_sum[j]->GetYaxis()->SetRangeUser(-54000,5000);
      		tpc2_sum[j]->Draw("histsame");
   	}
	
	cout<<"done"<<endl;
   //end of try
   } catch (int i ){
       if(i==1) cout<<"There is no waveforms.";
	if(i==2) cout<<"Half of the waveforms are missing.";
   }

}

void check_match(){
	cds_Evtr->GetEntries();

	for(int i=200; i< cds_Evtr->GetEntries(); i++){
		if(i ==196) {cout<<"Test here breaks"<<endl; continue;}
		if(i ==214) {cout<<"Test here breaks"<<endl; continue;}
                if(i ==709) {cout<<"Test here breaks"<<endl; continue;}
                if(i ==718) {cout<<"Test here breaks"<<endl; continue;}


		//select_event(i);
		new_select(i);
		cout<<"ev" <<i << ", N waveforms"<<GetNWaveforms() << endl;
		//if(i==194) continue;
		if(GetNWaveforms() == 0) { cout<<"skip"<<endl; continue; }
		//cout<<"test"<<endl;
		try{ GetWaveform(0); }
		catch(exception){ cout<<"something wrong"<<endl; }
		

		cout<<"event n "<<i <<endl;
//		cout<<"Light ev, ntp_ms: "<<ntp_ms<<"\t tai_ns: "<<tai_ns<< "\t in us: " << (ntp_ms*1000 + tai_ns/1000)<<endl;
//		cout<<"Charge ev, event_unix_ts: "<<event_unix_ts<<"\t event_start_t: "<<event_start_t<< "\t in us: "<<(long long)event_unix_ts *1000000 + event_start_t/10<<endl;

		cout<<"Difference in sec: "<< (long long)(ntp_ms) - ((long long)event_unix_ts *1000) <<endl;
		cout<<"Difference: in us "<< (long long)(tai_ns/1000) - ((long long) event_start_t/10) <<endl;
	}
}

void sum_light(){
	//cds_Evtr->GetEntries();
	float_t total_light;
	float_t int_ch_waveform;
	float_t ch_gain;
	int count =0;

 	TH1F *tot_l = new TH1F("total_light","total_light",50,0,50000);
        TH1F *tot_ch = new TH1F("total_charge","total_charge",50,0,50000);

	for(int i=0; i<400; i++){
		cds_Evtr->GetEntry(i);
		if(event_q>50000 || event_q<10000) continue;
		count ++ ;
		//if(count >50) break;
		new_select(i);
		total_light =0;
		cout<<"event "<< i <<", N tracks: "<< event_ntracks <<", N waveforms: "<<GetNWaveforms()<<"\r"<<flush;
		//cout<<"Total charge: "<< event_q <<endl;
		for(int j =0; j<GetNWaveforms();j++){
			auto *s = GetWaveform(j);
			ch_gain = (sn ==ADC1) ? gain[0][ch] : gain[1][ch];
			int_ch_waveform = -1.0 * s->Integral(s->FindBin(900),s->FindBin(1400))/(64.0 * ch_gain);
			//cout<<"sn: "<<sn<<" ch: "<<ch<<" gain: "<<ch_gain<<" N photons: "<< int_ch_waveform<< endl;
			if(ch_gain !=-1) total_light += int_ch_waveform; 
		}

		//cout<<"total light: "<<total_light<<endl;

		tot_l->Fill(total_light);
		tot_ch->Fill(event_q);

	}// Event loop finished

	TCanvas *c_light = new TCanvas("c_light","c_light",700,500);
	c_light->Divide(2,1);
	c_light->cd(1);
	tot_ch->Draw("hist");
	c_light->cd(2);
	tot_l ->Draw("hist");
}


void plot_waveforms_all(int ev){
	TH1I *h [2][64];
	bool check_fill[2][64] = {{false}};

	TCanvas *c0 = new TCanvas("w_0","waveforms_ADC1",1600,900);
	c0->cd();
	c0->Divide(8,8);
        TCanvas *c1 = new TCanvas("w_1","waveforms_ADC2",1600,900);
	c1->cd();
	c1->Divide(8,8);

	new_select(ev);
	for(int i=0; i<GetNWaveforms(); i++){
		//cout<<"waveform ch"<<i ;
		auto *s = GetWaveform(i);
		//cout<<" ch "<<ch <<endl;
		if( sn == ADC1 ) {
			h[0][ch] = (TH1I*)s->Clone();
			check_fill[0][ch]= true;
		}if( sn == ADC2 ) {
			h[1][ch] = (TH1I*)s->Clone();
			check_fill[1][ch] = true;
		}
	}

	c0->Clear();
	c0->Divide(8,8);
	for(int j=0; j<64; j++){
		if(check_fill[0][j] == true){
			c0->cd(j+1);
			h[0][j]->SetMaximum(max(7000.0, h[0][j]->GetMaximum() ));
			h[0][j]->SetMinimum(min(-30000.0, h[0][j]->GetMinimum() ));
			h[0][j]->Draw("hist");
		}
	}
	c1->Clear();
	//c1->cd();
	c1->Divide(8,8);
	for(int j=0; j<64; j++){
                if(check_fill[1][j] ==true){
			c1->cd(j+1);
                        h[1][j]->SetMaximum(max(7000.0, h[1][j]->GetMaximum() ));
                        h[1][j]->SetMinimum(min(-30000.0, h[1][j]->GetMinimum() ));
                        h[1][j]->Draw("hist");
		}
	}
}


float Get_dy(int ev){

	float ymax =0.0, ymin=0.0;

	cds_Evtr->GetEntry(ev);
	for(int i=0; i<event_nhits; i++){
		if (i ==0) {ymax = ev_h_y[i]; ymin = ev_h_y[i];}
		else{
			if(ev_h_y[i] > ymax) ymax = ev_h_y[i];
			if(ev_h_y[i] < ymin) ymin = ev_h_y[i];
		}
	}
	//cout<<"dy = "<<(float)(ymax - ymin) <<endl;
	return (ymax - ymin);
}

void doIntegral(){

        Float_t lds_integral[2][64] ={{0.0}};
        Float_t lds_nph[2][64]= {{0.0}};
	Float_t lds_gain[2][64]={{0.0}};
	Float_t total_photons;

	Int_t lds_ch[2][64] ={{0}};

        TBranch *blds_integral;
        TBranch *blds_nph;
	TBranch *blds_ch;
	TBranch *blds_gain;
	TBranch *btotal_photons;

        //TH1S *h1;
	TH1I *h1;

        //Clone tree here for output
	TFile *out_file = new TFile(std::string(OUT_PATH).c_str(),"NEW");
        output_Evtr = cds_Evtr->CloneTree(0);
	output_Trtr = cds_Trtr->CloneTree(0);

        //cdsf->cd();  //Changed form cds_Evtr to output_Evtr
        btotal_photons  = output_Evtr->Branch("total_photons", 	& total_photons,"total_photons/F");
        blds_integral 	= output_Evtr->Branch("lds_integral",	&lds_integral,	"lds_integral[2][64]/F");
        blds_nph 	= output_Evtr->Branch("lds_nph",	&lds_nph,	"lds_nph[2][64]/F");
	blds_ch 	= output_Evtr->Branch("lds_ch",		&lds_ch,	"lds_ch[2][64]/I");
	blds_gain 	= output_Evtr->Branch("lds_gain",	&lds_gain, 	"lds_gain[2][64]/F");


        int neve=cds_Evtr->GetEntries();
	for(int i=0;i<neve;i++){
		//if(i==50) break;
		cout<<"ev: "<<i << "\r"<<flush;

		//reset
                memset(lds_integral, 	0, sizeof(lds_integral));
                memset(lds_nph, 	0, sizeof(lds_nph));
                memset(lds_ch, 		0, sizeof(lds_ch));
                memset(lds_gain, 	0, sizeof(lds_gain));
		total_photons =0.0;

		cds_Evtr->GetEntry(i);

		//selection cuts

		//if( event_ntracks<6 && Get_dy(i)>1000) {  // criteria used for selecting long through going vertical tracks
		//if(event_nhits>20 && event_nhits<200 && event_start_t>1000000 && event_start_t<10000000 && event_q <10000 && event_ntracks <3 ){

			/*//criteria for finding at least one long track in the event
			bool track_is_long = false;
                        int long_track_index= -1;
                        for(int j =0; j<event_ntracks; j++){
                                cds_Trtr->GetEntryWithIndex(i,j);
                                if( dy>=1000) long_track_index = j;
                        }
                        //if(long_track_index !=-1){
			*/
		new_select(i);
             	for(int j=0;j<GetNWaveforms();j++){
                       	//if(GetNWaveforms()!=116) break;
      	               	h1=GetWaveform(j);

              		if(sn==ADC1){ 
				lds_ch[0][ch] = ch;
				lds_gain[0][ch] =gain[0][ch];
                              	lds_integral[0][ch]= -1*h1->Integral(61,92);
      	                	lds_nph[0][ch]= (float_t)lds_integral[0][ch]/(float_t)gain[0][ch];
				total_photons += (float_t)lds_integral[0][ch]/(float_t)gain[0][ch];
                       	}
               		else if(sn==ADC2){
				lds_ch[1][ch] = ch;
                      		lds_gain[1][ch] =gain[1][ch];
            			lds_integral[1][ch]=-1*h1->Integral(61,92);
                    		lds_nph[1][ch]= (float_t)lds_integral[1][ch]/(float_t)gain[1][ch];
				total_photons += (float_t)lds_integral[1][ch]/(float_t)gain[1][ch];
                       	}
      		} //end for

		//}//end if //enable this line if running for long vertical tracks
		//}//end if
/*
                blds_integral->Fill();
                blds_nph->Fill();
		blds_ch->Fill();
		blds_gain->Fill();
		btotal_photons->Fill();
*/
		output_Evtr->Fill();

		if(i % 10 ==0) output_Evtr->AutoSave();
        }//end ev for

	//track tree
	for(int i = 0; i< cds_Trtr->GetEntries(); i++){
		if( i ==50) break;
		cds_Trtr->GetEntry(i);
		output_Trtr->Fill();
	}

//        TFile *out_file = new TFile(std::string(OUT_PATH).c_str(),"NEW");
        out_file->cd();
	output_Evtr->Write("",TObject::kOverwrite);
	output_Trtr->Write("",TObject::kOverwrite);
	out_file->Close();

	/*
	cdsf->cd();
        cds_Evtr->Write("", TObject::kOverwrite);
        cds_Trtr->Write("", TObject::kOverwrite);
        cdsf->Close();
	*/
}
