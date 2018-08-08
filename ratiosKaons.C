void ratiosKaons(){

    const int nenergies = 7;
    double energies[nenergies] = {2.24, 2.32, 4.86, 6.27, 7.62, 8.77, 12.3};
    double ratiosKaons[nenergies] = {1.134831, 1.141011, 0.846900, 0.886257, 0.897888, 0.901752, 0.946277};

    double xmin(1.1),xmax(20.0);
    double ymin(0.0),ymax(1.3);

    TCanvas *c1 = new TCanvas();
    //c1->SetLogx();

    TGraph *graph = new TGraph(nenergies,energies,ratiosKaons);
    graph->SetMarkerColor(1);
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(1.0);
    //graph->Draw("ap");
    graph->GetYaxis()->SetTitle("K^{+}/K^{-}");
    graph->GetYaxis()->SetRangeUser(ymin,ymax);
    graph->GetYaxis()->SetTitleOffset(1.2);
    graph->GetYaxis()->SetTitleFont(42);
    graph->GetXaxis()->SetRangeUser(xmin,xmax);
    graph->GetXaxis()->SetTitle("#sqrt{s} [GeV]");
    graph->GetXaxis()->SetTitleOffset(1.2);
    graph->GetXaxis()->SetTitleFont(42);
    
    TF1 *myfit = new TF1("myfit","[0]*TMath::Power((TMath::Log(x+[1]))/(TMath::Log(x-[2])),[3])");
    graph->Fit(myfit);
    graph->Draw("AL");

    /*TLegend *leg1 = new TLegend(0.15,0.65,0.4,0.88);
    leg1->AddEntry(graph2,"K^{+}/#pi^{+}","ep");
    leg1->AddEntry(graph,"K^{-}/#pi^{-}","ep");
    leg1->SetFillColor(0);
    leg1->SetShadowColor(0); 
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.03);
    leg1->Draw();*/

    c1->SaveAs("ratioKaons.png");

}