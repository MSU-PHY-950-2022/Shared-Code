                      TMVA Examples
                      -------------

The programs in this directory contain simple examples of multivariate
analyses using routines in the TMVA package.  The examples are
must be linked used with the ROOT and TMVA libraries.  Normally TMVA 
should be included automatically with ROOT.

These programs have been designed to run correctly when compiled with
ROOT's ACLiC interpreter.  Thus, to run them you must do: 

root -l program.cc+

The compiling has been tested on both Linux and MacOS distributions of ROOT.
Please report any compilation errors to Prof. Fisher.  NOTE:  the exception
to this is the plotting program "plotInputs.C".  You shouldn't compile that one.

For more information on the TMVA methods, see the website

 http://tmva.sourceforge.net/

The example programs are:

generateData.cc -- generates data according to a 3-dimensional
	        distribution for two different hypotheses
		(signal and background) and stores the
		result in a root file (as two TTree objects).

readData.cc     -- a test program to read the data.  This is just
                for your reference.

tmvaTrain.cc    -- reads in the root file and trains two
		simple multivariate discriminators:  a
		Fisher discriminant and a multilayer 
		perceptron (neural network).  The 
		coefficients for the discriminant functions
		are stored in a subdirectory ./dataset/weights/.

analyzeData.cc  -- reads in n-tuples of signal and background
		data and computes the discriminating variable.
		The user can select events, compute efficiency,
		purity, etc.


The programs should be run in sequence to get the desired output:

generateData.cc  >> creates files testData.root and trainingData.root
tmvaTrain.cc     >> creates weight files for MVA selected in ./dataset/weights/
analyzeData.cc   >> creates file analysis.root containing any user-defined output
