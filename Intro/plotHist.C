// To execute inside root session, type .X plotHist.C
{
  TFile* f = new TFile("simpleMC.root");
  f->ls();
  TH1D* h1 = (TH1D*)f->Get("h_Exp");
  h1->SetXTitle("x");
  h1->SetYTitle("f(x;#xi)");
  h1->Draw();
}
