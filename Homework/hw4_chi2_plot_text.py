#!/usr/bin/python

import numpy as np
import matplotlib.pyplot as plt

def processText(line):
    #split string on delimeter
    split = line.split(": ")
    # work with 2nd array element
    output = split[1]
    # remove trailing newline character(s)
    output = float(output.rstrip())
    return output


def scaleToData(data,hypo):
    # histogram integrals
    sumD = np.sum(data)
    sumH = np.sum(hypo) + 1e-6

    # scale hypothesis to data
    for idx in range(len(hypo)):
        hypo[idx] = hypo[idx] * sumD/sumH

        
def rebinArray(arr, factor):
    # Sanity check!
    if (len(arr) % factor) != 0:
        print("Input array with ",len(arr), " bins is not divisible by ",factor)
        return arr

    sum = 0
    newArr = []
    # Loop over bins and add sums to new array
    for idx in range(len(arr)):
        sum = sum + arr[idx]
        if ((idx+1) % factor) == 0:
            newArr.append(sum)
            sum = 0

    return np.asarray(newArr,dtype=arr.dtype)


def plotData(data,hypo):

    scaleToData(data,hypo)
    
    xbins = range(0,len(data))

    # Matplotlib's pyplot.hist returns the bin counts, bin edges,
    # and the actual rendered blocks of the histogram (which we don't need)
    bin_counts, bin_edges, patches = plt.hist(xbins,len(xbins),weights=data)
    bin_centers = (bin_edges[:-1] + bin_edges[1:]) / 2

    # Generate some dummy error values, of the same dimensions as the bin counts
    y_error = np.sqrt(data)

    #clear the plot
    plt.clf()
    # Plot the error bars, centred on (bin_center, bin_count), with length y_error
    plt.hist(xbins,len(xbins),weights=hypo)
    plt.errorbar(x=bin_centers, y=bin_counts, yerr=y_error, fmt='o', capsize=2)

    plt.show()

def main():

    # Read the data files into lists
    with open("HW4_Problem3_Data.txt") as f:
        dataBins = f.readlines()

    with open("HW4_Problem3_H1.txt") as f:
        h1Bins = f.readlines()

    with open("HW4_Problem3_H2.txt") as f:
        h2Bins = f.readlines()

    # Remove extraneous columns and new line chars
    for idx in range(len(dataBins)):
        dataBins[idx] = processText(dataBins[idx])
        h1Bins[idx] = processText(h1Bins[idx])
        h2Bins[idx] = processText(h2Bins[idx])

    # cast as NumPy arrays for convenience
    dataArray = np.asarray(dataBins,dtype=int)
    h1Array = np.asarray(h1Bins,dtype=float)
    h2Array = np.asarray(h2Bins,dtype=float)

    # Rebin arrays by 4
    dataArrayRB = rebinArray(dataArray,4)
    h1ArrayRB = rebinArray(h1Array,4)
    h2ArrayRB = rebinArray(h2Array,4)

    # Make a histogram
    plotData(dataArrayRB,h1ArrayRB)
    plotData(dataArrayRB,h2ArrayRB)

if __name__ == "__main__":
    main()
