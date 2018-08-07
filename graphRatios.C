void graphRatios(){

    const int nenergies = 6;
    double energies[nenergies] = {2.32, 4.86, 6.27, 7.62, 8.77, 12.3};
    double ratiosPositive[nenergies] = {0.003518, 0.076822, 0.101882, 0.115242, 0.121653, 0.138833};
    double ratiosNegative[nenergies] = {0.001722, 0.061721, 0.084539, 0.098124, 0.105656, 0.122275};

    double xmin(1.1),xmax(20.0);
    double ymin(0.0),ymax(0.17);

    TCanvas *c1 = new TCanvas();
    //c1->SetLogx();

    TGraph *graph = new TGraph(nenergies,energies,ratiosNegative);
    graph->SetTitle();
    graph->SetMarkerColor(1);
    graph->SetMarkerStyle(20);

    TGraph *graph2 = new TGraph(nenergies,energies,ratiosPositive);
    graph2->SetMarkerColor(1);
    graph2->SetMarkerStyle(4);
    graph2->SetMarkerSize(1.0);

    TMultiGraph *multiGraph = new TMultiGraph();
    multiGraph->Add(graph);
    multiGraph->Add(graph2);
    multiGraph->Draw("ap");
    multiGraph->GetYaxis()->SetTitle("K/#pi");
    multiGraph->GetYaxis()->SetRangeUser(ymin,ymax);
    multiGraph->GetYaxis()->SetTitleOffset(1.2);
    multiGraph->GetYaxis()->SetTitleFont(42);
    multiGraph->GetXaxis()->SetRangeUser(xmin,xmax);
    multiGraph->GetXaxis()->SetTitle("#sqrt{s} [GeV]");
    multiGraph->GetXaxis()->SetTitleOffset(1.2);
    multiGraph->GetXaxis()->SetTitleFont(42);

    TLegend *leg1 = new TLegend(0.15,0.65,0.4,0.88);
    leg1->AddEntry(graph2,"K^{+}/#pi^{+}","ep");
    leg1->AddEntry(graph,"K^{-}/#pi^{-}","ep");
    leg1->SetFillColor(0);
    leg1->SetShadowColor(0); 
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.03);
    leg1->Draw();

    c1->SaveAs("ratios.png");

}