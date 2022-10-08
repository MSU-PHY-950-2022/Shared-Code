# This program estimates the average number of leaves on a tree in an "average"
# forest.  We will assume the following:
#
# 1) The forest has roughly 1000 trees with a Gaussian standard deviation of 126
# 2) The trees vary in age from 1 year to 100 years with a linearly increasing age profile
# 3) Each tree has number of branches that follows a Poisson distribution with mean age*2+3
# 4) Each branch has a number of leaves that is drawn randomly from the function 10+20*sqrt(age)
#
# The goal is to plot the number of leaves for 1000 forests.
# In doing so, we should also plot the distributions in 1-4 as a sanity check.
# Finally, we need to report the average number of trees in in our "average" forest.
#
# Don't forget to calculate some averages so that everything can be checked step by step

# This code will not work as is.  You must fix all coding errors before proceeding.
# There are also logic errors that will significantly alter the results of the simulation.
# Fix the errors to reproduce the results listed in the homework text.

import numpy as np
import matplotlib.pyplot as plt

_nForests = 100

_trees = []
_meanTrees = 1000
_treeStdDev = 126

_ages = []
_minAge = 1
_maxAge = 100

_branches = []
_leaves = []


#generate forest distribution
for f in range(0,_nForests):
    _trees.append(int(np.random.gaus(_meanTrees,_treeStdDev)))


print("Mean trees: {} +/- {}".format(np.mean(_trees), np.std(_trees)))


#generate an age profile for each forest
_allAges = []
for t in _trees:
    _thisAgeList = []
    for n in range(0,t):        
        _thisAgeList.append(_minAge + _maxAge*pow(np.random.uniform(0,1),2))
        #let's calculate the mean age of a tree over all forests
        _allAges.append(_thisAgeList[n])

    _ages.append(_thisAgeList)

print("Mean tree age: {} +/- {}".format(np.mean(_allAges),np.std(_allAges)))


#generate a branch number for each tree
_allBranches = []
for t in range(0,len(_trees)):
    _thisBranchList = []
    for n in range(0,_trees[t]):
        _thisBranchList.append(int(10+20*np.random.poisson(_ages[t][n])))
        _allBranches.append(_thisBranchList[n])
        
    _branches.append(_thisBranchList)

print("Mean # of branches: {} +/- {}".format(np.mean(_allBranches),np.std(_allBranches)))


#generate a leaf number for each branch, sum them for the tree
_allLeaves = []
_allTree = []
_allForest = []
for t in range(0,len(_trees)):  #forests
    _thisLeafList = []
    
    for n in range(0,_trees[t]): #trees
        leaves = 0

        for b in range(0,_branches[t]): #branches per tree
            tLeaf = int(10+20*pow(np.random.uniform(0,_ages[t][n]),2/3.0))
            _allLeaves.append(tLeaf)
            # sum leaves over all branches for this tree
            leaves += tLeaf

        _thisLeafList.append(leaves) #leaves per tree
        _allTree.append(leaves)

    _leaves.append(_thisLeafList)
    _allForest.append(np.sum(_thisLeafList))
    
print("Mean leaves per branch: {} +/- {}".format(np.mean(_allLeaves),np.std(_allLeaves)))
print("Mean leaves per tree: {} +/- {}".format(np.mean(_allTree),np.std(_allTree)))
print("Mean leaves per forest: {} +/- {}".format(np.mean(_allForest),np.std(_allForest)))

#Now make some figures
fig, axs = plt.subplots(2,2)

#Make a plot of the trees!
axs[0,0].hist(_trees, density=True, bins=30)  # `density=True` would normalize to 1
axs[0,0].set_title("# Trees")

#Make a plot of the ages for one forest
axs[0,1].hist(_ages[2], density=True, bins=30)  # `density=True` would normalize to 1
axs[0,1].set_title("Tree Ages")

#Make a plot of the # of branches for one forest
axs[1,0].hist(_branches[3], density=True, bins=30)  # `density=True` would normalize to 1
axs[1,0].set_title("# Branches per Tree")

#Make a plot of the # of leaves for one forest
axs[1,1].hist(_leaves[4], density=True, bins=30)  # `density=True` would normalize to 1
axs[1,1].set_title("# Leaves per Tree")

plt.tight_layout()
plt.show()
