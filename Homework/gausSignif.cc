

void gausPvalue(double nSigma){

  double p = TMath::Erfc(nSigma/sqrt(2.0))/2;

  printf("%f standard deviation(s) corresponds to a one-sided p-value of: %f (%fe-6)\n",nSigma,p,p*1e6);

  return;

}

void gausSignif(double pValue){
  
  double n = sqrt(2.0)*TMath::ErfInverse(1.0-2.0*pValue);
  
  printf("A pValue of %f (%fe-6) corresponds\n",pValue,pValue*1e6);
  printf("to a Gaussian significance (z-value) of %0.3f sigma\n",n);

}

