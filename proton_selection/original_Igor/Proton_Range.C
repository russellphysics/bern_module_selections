TTree *tprange;
TGraph *pEfromRange;

void Proton_Range()
{
tprange=new TTree();
tprange->ReadFile("Proton_CSDA_RANGE_in_Ar.txt","E/F:R/F");
int n=tprange->Draw("R*10/1.4:E","E>20&&E<600","goff");
//int n = tree->Draw("x","","",3950,0);
pEfromRange = new TGraph(n, tprange->GetV1(), tprange->GetV2());
pEfromRange->Draw("APL");
}
