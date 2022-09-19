import numpy as np
import matplotlib.pyplot as plt

def myFunction(rand):
    return 3*pow(rand,3) - rand


#Declare some useful variables here
nTrials = 20
nSamples = 50
mean = 0
variance = 0

trials = []

#run several trials to get a sense for mean and RMS
for t in range(0,nTrials):
    integral = 0

    #For each trial, use the same number of samples
    for b in range(0,nSamples):
        xi = np.random.random()    #Uniform in [0.0,1.0)
        fi = myFunction(xi)/nSamples  #Why divide by nSamples?
        integral += fi

    print("Integral:  %.5f" % integral)
    
    trials.append(integral)
    mean += integral
  
mean /= nTrials

print("Mean: %.5f" % mean)

# Calculate average (x-mu)^2
for t in range(0,nTrials):
    variance += pow(trials[t]-mean,2)

variance /= nTrials
variance = np.sqrt(variance)  #variance is (std dev)^2
  
print("Std Dev: %.5f" % variance)

#Make a plot of these values!
plt.hist(trials, density=False, bins=30)  # `density=True` would normalize to 1
plt.ylabel('Frequency')
plt.xlabel('Integral');
plt.show()


