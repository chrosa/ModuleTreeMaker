run2(){
  TFile *f = TFile::Open("tree2.root");
  TTree* t = (TTree *) f->Get("t");
  t->Process("ModuleSelector2.C+");
}
