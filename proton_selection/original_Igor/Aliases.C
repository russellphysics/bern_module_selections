#define PIXPITCH 4.434
//TH3D * xyz;
void Aliases()
{
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


Hevents->SetAlias("vrange_proj1","(vt_d1x*nx+vt_d1y*ny+vt_d1z*nz)");
Hevents->SetAlias("vrange_proj2","-(vt_d2x*nx+vt_d2y*ny+vt_d2z*nz)");
Hevents->SetAlias("vrange_proj","vrange_proj2*(htracks_start_y>htracks_end_y)+vrange_proj1*(htracks_start_y<=htracks_end_y)");
//Hevents->SetAlias("vpida_proj","(log(htrack_vox_q)-3.15)/(11-log(vrange_proj))");


Hevents->SetAlias("v1","4.7*(log(htrack_vox_q)-3.2)+log(vrange)");
Hevents->SetAlias("v2","htracks_qhts/htracks_tl");
Hevents->SetAlias("cut0","abs(v2-30)<10&&abs(v1-8)<9");
Hevents->SetAlias("cut1","abs(v2-95)<35&&abs(v1-3)<5");
Hevents->SetAlias("cut2","abs(v2-95)<35&&abs(v1-10)<3");
Hevents->SetAlias("cut3","abs(v2-95)<35&&abs(v1-17)<4");
Hevents->SetAlias("av_dEdx","htracks_qhts[]/htracks_tl[]");

Hevents->SetAlias("selectHIPs","htracks_rhits[]>0 && htracks_ID==0 &&nhtracks==1 && abs(av_dEdx-90)<40 && abs(htracks_rhits[]-7)<3");

// xyz = new TH3D("3D_view","3D_view", 140,-PIXPITCH*70,PIXPITCH*70 ,140,-PIXPITCH*70,PIXPITCH*70, 280,-PIXPITCH*140,PIXPITCH*140);
}

/*
Hevents->Draw("htracks_ay:htracks_ax:htracks_az>>3D_view","selectHIPs && (htracks_tl<50 || abs(htracks_ny)<0.3)","")
Hevents->Draw("htracks_ay:htracks_ax:htracks_az>>3D_view","(htracks_tl<50 || abs(htracks_ny)<0.3)","")
*/
