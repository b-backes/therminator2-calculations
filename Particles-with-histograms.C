#define Particles_cxx
#include "Particles.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TFile.h>
#include <TH1D.h>
#include <cmath>
#include <iostream>
#include <TMath.h>

using namespace std;

void Particles::Loop()
{
//   In a ROOT session, you can do:
//      root> .L Particles.C
//      root> Particles t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();
   TFile *Results = new TFile("Results","recreate");       // File to save results

   // Create histograms for transverse momentum. Case1 stands for particles with |eta| < 1
   // and Case2 stands for |eta| < 0.5

   Float_t limit_bins[] = {0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.55, 0.6, 0.65, 
   0.7, 0.75, 0.8, 0.85, 0.9, 0.95, 1., 1.05, 1.1, 1.15, 1.2, 1.25, 1.3, 1.35, 1.4,
   1.45, 1.5, 1.55, 1.6, 1.65, 1.7, 1.75, 1.8, 1.85, 1.9, 1.95, 2., 2.05, 2.1, 2.2, 2.3, 2.4, 2.5, 2.7, 2.9,
   3.2, 3.5, 3.8, 4.3, 4.7, 5.0};

   Int_t n_bins = 50;
   
   TH1D *HistPtPiPlusCase1 = new TH1D("HistPtPiPlusCase1", "", n_bins, limit_bins);     // Pi+ with |eta| < 1
   TH1D *HistPtPiMinusCase1 = new TH1D("HistPtPiMinusCase1", "", n_bins, limit_bins);   // Pi- with |eta| < 1
   TH1D *HistPtKaPlusCase1 = new TH1D("HistPtKaPlusCase1", "", n_bins, limit_bins);     // K+ with |eta| < 1
   TH1D *HistPtKaMinusCase1 = new TH1D("HistPtKaMinusCase1", "", n_bins, limit_bins);   // K- with |eta| < 1
   TH1D *HistPtPiPlusCase2 = new TH1D("HistPtPiPlusCase2", "", n_bins, limit_bins);     // Pi+ with |eta| < 0.5
   TH1D *HistPtPiMinusCase2 = new TH1D("HistPtPiMinusCase2", "", n_bins, limit_bins);   // Pi- with |eta| < 0.5
   TH1D *HistPtKaPlusCase2 = new TH1D("HistPtKaPlusCase2", "", n_bins, limit_bins);     // K+ with |eta| < 0.5
   TH1D *HistPtKaMinusCase2 = new TH1D("HistPtKaMinusCase2", "", n_bins, limit_bins);   // K- with |eta| < 0.5

   // Declaration of variables

   Float_t pt, pseudorapidity;
   Int_t CountsKaPlus = 0, CountsKaMinus = 0, CountsPiPlus = 0, CountsPiMinus = 0;
   Float_t RatioPositive, RatioNegative;

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }

    for(Int_t i = 0; i < nentries; i++){
        fChain->GetEntry(i);    // Here we are getting the i-th entry from the tree
        pt = sqrt(particle_px*particle_px + particle_py*particle_py);    // And calculating pt                                               // For each one of them.

        pseudorapidity = asinh(particle_pz/pt);     // Calculates pseudorapidity

        /* In the following part of the code we fill different histograms for different particles.
        The number are the particle identification numbers for Monte Carlo simulations
        from Particle Data Group, following the indicated in the Therminator2 manual. */

        switch (particle_pid) {
            case 211:
                if (abs(pseudorapidity) < 1){
                    HistPtPiPlusCase1->Fill(pt);
                }
                if (abs(pseudorapidity) < 0.5){
                    HistPtPiPlusCase2->Fill(pt);
                }
                CountsPiPlus++;
                break;
            case 321:
                if (abs(pseudorapidity) < 1){
                    HistPtKaPlusCase1->Fill(pt);
                }
                if (abs(pseudorapidity) < 0.5){
                    HistPtKaPlusCase2->Fill(pt);
                }
                CountsKaPlus++;
                break;
            case -211:
                if (abs(pseudorapidity) < 1){
                    HistPtPiMinusCase1->Fill(pt);
                }
                if (abs(pseudorapidity) < 0.5){
                    HistPtPiMinusCase2->Fill(pt);
                }
                CountsPiMinus++;
                break;
            case -321:
                if (abs(pseudorapidity) < 1){
                    HistPtKaMinusCase1->Fill(pt);
                }
                if (abs(pseudorapidity) < 0.5){
                    HistPtKaMinusCase2->Fill(pt);
                }
                CountsKaMinus++;
                break;
        }
    }

    RatioPositive = float(CountsKaPlus)/float(CountsPiPlus);
    RatioNegative = float(CountsKaMinus)/float(CountsPiMinus);

    std::cout << "Histograms for pt are filled!" << endl;
    std::cout << "K+ = " << CountsKaPlus << " counts" << endl;
    std::cout << "K- = " << CountsKaMinus << " counts" << endl;
    std::cout << "Pi+ = " << CountsPiPlus << " counts" << endl;
    std::cout << "Pi- = " << CountsPiMinus << " counts" << endl;
    std::cout << "The K+/Pi+ ratio is " << RatioPositive << endl;
    std::cout << "The K-/Pi- ratio is " << RatioNegative << endl;

    HistPtPiPlusCase1->Write();
    HistPtPiMinusCase1->Write();
    HistPtKaPlusCase1->Write();
    HistPtKaMinusCase1->Write();
    HistPtPiPlusCase2->Write();
    HistPtPiMinusCase2->Write();
    HistPtKaPlusCase2->Write();
    HistPtKaMinusCase2->Write();
    Results->Write();
    Results->Close();

}
