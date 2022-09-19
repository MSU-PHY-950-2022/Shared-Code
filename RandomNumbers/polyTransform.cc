void polyTransform(void){

    TH1D* h1 = new TH1D("f(x)=x","f(x)=x",100,0,1);
    TH1D* h2 = new TH1D("uniform","uniform",100,0,1);

    TRandom rand(1122);
    for(int i=0; i<100000; i++){
      double v = rand.Uniform();
      h2->Fill(v);
      double func = sqrt(v);
      h1->Fill(func);
    }

    h1->Scale(1.0/h1->Integral());
    h2->Scale(1.0/h2->Integral());
    
    TCanvas* c1 = new TCanvas("c1","c1");
    h1->SetMinimum(0);
    h1->Draw();

    TCanvas* c2 = new TCanvas("c2","c2");
    h2->SetMinimum(0);
    h2->Draw();


    TCanvas* c3 = new TCanvas("c3","c3");
    TF1* ff = new TF1("f1","x",0,1);
    ff->Draw("");
    TF1* ff2 = new TF1("f2","x^2",0,1);
    ff2->SetLineColor(4);
    ff2->Draw("same");
}
