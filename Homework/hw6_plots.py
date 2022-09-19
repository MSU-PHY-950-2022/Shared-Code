#!/usr/bin/python

from ROOT import TH1D,TStyle,TCanvas,TFile,gStyle,TLegend

def h1_style(h1, title): #make the plots pretty
    h1.GetXaxis().SetTitle("X")
    h1.GetYaxis().SetTitle("N(X)")
    h1.GetXaxis().SetTitleSize(0.05)
    h1.GetYaxis().SetTitleSize(0.05)
    
    h1.GetXaxis().SetLabelSize(0.04)
    h1.GetYaxis().SetLabelSize(0.04)
    h1.SetTitle(title)
    
    h1.SetMaximum(1.25*h1.GetMaximum())


def main():
    gStyle.SetOptStat(0);

    fin = TFile("hw6_hypotheses.root","READ")

    h1 = fin.Get("Background")
    h2 = fin.Get("Signal")
    
    data = fin.Get("Data")

    # This fixes the signal rate to be 5%
    # of the background rate.
    h2.Scale(0.05);

    # Sum the histograms to make H1 for the 5% signal rate
    h3 = h1.Clone("Signal + Bkgd");
    h3.Add(h2);
    h3.SetLineColor(4);

    h1.Scale(data.Integral())
    h3.Scale(data.Integral())
    
    print("Integral H1: {0}, Integral H2: {1}".format(h1.Integral(),h3.Integral()))

    data.SetLineColor(1);
    data.SetMarkerStyle(22);
    data.SetMarkerSize(1);

    h1_style(h1,"")

    leg = TLegend(0.65,0.6, 0.95, 0.85)
    leg.AddEntry(h1, "Background-Only")
    leg.AddEntry(h2, "Signal + Background")
    leg.AddEntry(data, "Data")
    leg.SetFillColor(0)

    c1 = TCanvas("c1","c1")
    h1.Draw()
    h3.Draw("same")
    data.Draw("PEsame")
    c1.SetLeftMargin(0.11)
    c1.SetBottomMargin(0.11)
    c1.SetTopMargin(0.035)
    c1.SetRightMargin(0.035)
    leg.Draw("same")
    c1.Print("myPlot.jpg")
    
if __name__ == "__main__":
    main()
