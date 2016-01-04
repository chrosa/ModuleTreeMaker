run(){
  TFile *f = TFile::Open("tree.root");
  TTree* t = (TTree *) f->Get("modules");
  t->Process("ModuleSelector.C+");
}
