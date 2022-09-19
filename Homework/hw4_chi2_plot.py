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
    gStyle.SetOptStat(0)

    fin = TFile("hw4_chi2.root","READ")

    h1 = fin.Get("Hypothesis 1")
    h2 = fin.Get("Hypothesis 2")
    data = fin.Get("Data")

    rebinF = 4
    data.Rebin(rebinF)
    h1.Rebin(rebinF)
    h2.Rebin(rebinF)

    h1.Scale(data.Integral())
    h2.Scale(data.Integral())

    print("Integral H1: {0}, Integral H2: {1}".format(h1.Integral(),h2.Integral()))

    #print out contents of each bin of each histogram
    if True :
        print("Histogram Bin Contents:")
        print("Format: <bin> <h1 content> <h2 content> <data content>")
        for i in range(1, h1.GetNbinsX()+1):
            print("Bin {} : {}, {}, {}".format(i, h1.GetBinContent(i), h2.GetBinContent(i), data.GetBinContent(i)))


    data.SetLineColor(1)
    data.SetMarkerStyle(22)
    data.SetMarkerSize(1)

    h1_style(h1,"")

    leg = TLegend(0.65,0.6, 0.95, 0.85)
    leg.AddEntry(h1, "Hypothesis 1")
    leg.AddEntry(h2, "Hypothesis 2")
    leg.AddEntry(data, "Data")
    leg.SetFillColor(0)

    c1 = TCanvas("c1","c1")
    h1.Draw()
    h2.Draw("same")
    data.Draw("PEsame")
    c1.SetLeftMargin(0.11)
    c1.SetBottomMargin(0.11)
    c1.SetTopMargin(0.035)
    c1.SetRightMargin(0.035)
    leg.Draw("same")
    c1.Print("myPlot.jpg")
    
if __name__ == "__main__":
    main()
