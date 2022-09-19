print(__doc__)
import matplotlib.pyplot as plt
import numpy as np
import math as math

from sklearn.neural_network import MLPClassifier
from sklearn.preprocessing import MinMaxScaler
from sklearn.datasets.base import Bunch
from sklearn.discriminant_analysis import LinearDiscriminantAnalysis

from sklearn import datasets,metrics
import scikitplot as skplt


def getDataset(seed, nEvt, doBkgd, doSignal):
    np.random.seed(seed)
    sigma = 0.4

    
    data = []
    target = []

    #generate signal events
    if doSignal == True:
        for i in range(nEvt):        
            #signal is uniform [0,1] for all variables
            x = np.random.random()
            y = np.random.random()
            z = np.random.random()
            target.append(1)
            data.append([x,y,z])
            
    #generate background events
    if doBkgd == True:
        for i in range(nEvt):
            # background is gaussian, pseudo-gaussian and a power law
            x = np.random.normal()
            y = x - np.random.normal()
            z = math.pow(np.random.random(),0.4)
            target.append(0)
            data.append([x,y,z])

    return Bunch(data=data,target=target)

def main_sklearn():

    #create a MultiLayer Perceptron with not-exactly-random parameters
    mlp = MLPClassifier(verbose=0, random_state=0,
                        max_iter=400,solver='sgd',
                        learning_rate='constant',
                        momentum=0.9, nesterovs_momentum=True, learning_rate_init=0.2,
                        hidden_layer_sizes=(3,), activation='logistic')

    #create a Linear Discriminator (basically Fisher's discriminant in N-Dimensions)
    lda = LinearDiscriminantAnalysis(n_components=1)

    
    #generate some data
    data = getDataset(55,500,1,1)   
    X = MinMaxScaler().fit_transform(data.data)
    y = data.target

    #train the classifiers
    mlp.fit(X, y)
    lda.fit(X, y)

    #report how we did
    print("MLP Training set score: %f" % mlp.score(X, y))
    print("MLP Training set loss: %f" % mlp.loss_)
    print("LDA Training set score: %f" % lda.score(X, y))


    #let's plot our data to see if it makes sense
    data_sig = getDataset(55,10000,0,1)   
    X_sig = MinMaxScaler().fit_transform(data_sig.data)
    data_bkg = getDataset(55,10000,1,0)   
    X_bkg = MinMaxScaler().fit_transform(data_bkg.data)
    
    splot = plt.subplot(3,2,1)
    splot.hist(X_sig[:,0],50, alpha=0.5,label="Signal")
    splot.hist(X_bkg[:,0],50, alpha=0.5,label="Background")
    splot.text(0,550,"Variable 1")
    
    splot = plt.subplot(3,2,2)
    splot.hist(X_sig[:,1],50, alpha=0.5,label="Signal")
    splot.hist(X_bkg[:,1],50, alpha=0.5,label="Background")
    splot.text(0,500,"Variable 2")
    
    splot = plt.subplot(3,2,3)
    splot.hist(X_sig[:,2],50, alpha=0.5,label="Signal")
    splot.hist(X_bkg[:,2],50, alpha=0.5,label="Background")
    splot.text(0,500,"Variable 3")
    
    y_sig_score = mlp.predict_proba(X_sig)
    y_bkg_score = mlp.predict_proba(X_bkg)
    splot = plt.subplot(3,2,5)
    splot.hist(y_sig_score[:,0],50, alpha=0.5,label="Signal")
    splot.hist(y_bkg_score[:,1],50, alpha=0.5,label="Background")
    splot.set_title("Multilayer Perceptron")

    y_sig_score = lda.predict_proba(X_sig)
    y_bkg_score = lda.predict_proba(X_bkg)
    splot = plt.subplot(3,2,6)
    splot.hist(y_sig_score[:,0],50, alpha=0.5,label="Signal")
    splot.hist(y_bkg_score[:,1],50, alpha=0.5,label="Background")
    splot.set_title("Linear Discriminant")
    splot.legend(loc="center")

    plt.tight_layout()
    plt.show()




    #Now let's make the ROC curves!
    data = getDataset(2255,10000,1,1)   
    X = MinMaxScaler().fit_transform(data.data)
    y = data.target
    print("MLP Testing set score: %f" % mlp.score(X, y))
    print("MLP Testing set loss: %f" % mlp.loss_)
    print("LDA Testing set score: %f" % lda.score(X, y))
    
    # Compute fpr, tpr, thresholds and roc auc
    y_score = mlp.predict_proba(X)
    fpr, tpr, thresholds = metrics.roc_curve(y, y_score[:,1])
    roc_auc = metrics.auc(y, y_score[:,1])

    # Plot ROC curve
    plt.plot(fpr, tpr, 'r', label='MLP (area = %0.3f)' % roc_auc)

    #Go get the LDA curve
    y_score = lda.predict_proba(X)
    fpr, tpr, thresholds = metrics.roc_curve(y, y_score[:,1])
    roc_auc = metrics.auc(y, y_score[:,1])
    plt.plot(fpr, tpr, 'b--', label='LDA (area = %0.3f)' % roc_auc)

    plt.plot([0, 1], [0, 1], 'k--')  # random predictions curve
    plt.xlim([0.0, 1.0])
    plt.ylim([0.0, 1.0])
    plt.xlabel('False Positive Rate')
    plt.ylabel('True Positive Rate')
    plt.title('Receiver Operating Characteristic')
    plt.legend(loc="lower right")
    plt.margins(x=-0.25,y=-0.25)

    
    plt.show()
    
if __name__ == "__main__":
    main_sklearn()
