//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jul 26 07:03:50 2018 by ROOT version 6.14/00
// from TTree particles/particle tree
// found on file: event000.root
//////////////////////////////////////////////////////////

#ifndef Particles_h
#define Particles_h
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Particles {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         particle_mass;
   Float_t         particle_t;
   Float_t         particle_x;
   Float_t         particle_y;
   Float_t         particle_z;
   Float_t         particle_e;
   Float_t         particle_px;
   Float_t         particle_py;
   Float_t         particle_pz;
   Int_t           particle_decayed;
   Int_t           particle_pid;
   Int_t           particle_fatherpid;
   Int_t           particle_rootpid;
   Int_t           particle_eid;
   Int_t           particle_fathereid;
   UInt_t          particle_eventid;

   // List of branches
   TBranch        *b_particle;   //!

   Particles(TTree *tree=0);
   virtual ~Particles();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Particles_cxx
Particles::Particles(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("event000.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("event000.root");
      }
      f->GetObject("particles",tree);

   }
   Init(tree);
}

Particles::~Particles()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Particles::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Particles::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Particles::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("particle", &particle_mass, &b_particle);
   Notify();
}

Bool_t Particles::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Particles::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Particles::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Particles_cxx
