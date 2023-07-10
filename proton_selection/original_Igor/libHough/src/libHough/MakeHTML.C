void MakeHTML()
{
  THtml h;
  h.SetDocPath("./htmldoc");
  h.SetInputDir("$(ROOTSYS):./");
  h.MakeAll(kFALSE, "Hough*");
  h.MakeIndex("Hough*");
 // h.CreateJavascript();
 // h.CreateStylesheet();
}
