
void myFirstMacro(void){

  float x =5; 
  float y=7;
  //  y=7;
  
  cout << "x*sqrt(y) = " << x*sqrt(y) << endl;

  for(int i=2; i<7; i++) printf("sqrt(%d) = %f\n",i,sqrt(i));

  //  TF1* f1 = new TF1("f1","sin(x)/x",0,10);
  //  f1->Draw();

  //This is a comment....

  /* Another comment
     on multiple lines
  */

  TF1 f1("f1","sin(x)/x",0,10);
  f1.Draw();

  return;
}

