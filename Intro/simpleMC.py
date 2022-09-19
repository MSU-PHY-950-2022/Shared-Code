# These were the required include files for our C++ program
# No longer to include them, but we do need to import them!
#include <TH1D.h>
#include <TFile.h>
#include <TRandom3.h>
#include <math.h>

#import all the classes we want to use
from ROOT import TH1D, TFile, TRandom3
import math

# open a TFile
file = TFile("simpleMC.root", "recreate")

# Book histograms

h_Uni = TH1D("h_Uni", "uniform random numbers",  100,  0, 1.0)
h_Exp = TH1D("h_Exp", "exponential random numbers",  100,  0, 5.0)


# Create a TRandom3 object to generate random numbers

seed = 12345
ran = TRandom3(seed)

# Generate some random numbers and fill histograms

numValues = 10000
xi = 1.0                # mean of exponential pdf

for i in range(0,numValues):
    r = ran.Rndm()   # uniform in ]0,]
    x = - xi * math.log(r,10)
    h_Uni.Fill(r)
    h_Exp.Fill(x)

# Store all histograms in the output file and close up

file.Write();
file.Close();




