void ratiosPions(){

    const int nenergies = 8;
    double energies[nenergies] = {2.24, 2.32, 4.86, 6.27, 7.62, 8.77, 12.3, 17.3};
    double ratiosPions[nenergies] = {0.583262, 0.558518, 0.680421, 0.735390, 0.764515, 0.779945, 0.833416, 0.862454};

    double xmin(1.1),xmax(20.0);
    double ymin(0.5),ymax(0.9);

    TCanvas *c1 = new TCanvas();
    //c1->SetLogx();

    TGraph *graph = new TGraph(nenergies,energies,ratiosPions);
    graph->SetTitle();
    graph->SetMarkerColor(1);
    graph->SetMarkerStyle(4);
    graph->SetMarkerSize(1.0);
    graph->Draw("ap");
    graph->GetYaxis()->SetTitle("#pi^{+}/#pi^{-}");
    graph->GetYaxis()->SetRangeUser(ymin,ymax);
    graph->GetYaxis()->SetTitleOffset(1.2);
    graph->GetYaxis()->SetTitleFont(42);
    graph->GetXaxis()->SetRangeUser(xmin,xmax);
    graph->GetXaxis()->SetTitle("#sqrt{s} [GeV]");
    graph->GetXaxis()->SetTitleOffset(1.2);
    graph->GetXaxis()->SetTitleFont(42);

    /*TLegend *leg1 = new TLegend(0.15,0.65,0.4,0.88);
    leg1->AddEntry(graph2,"K^{+}/#pi^{+}","ep");
    leg1->AddEntry(graph,"K^{-}/#pi^{-}","ep");
    leg1->SetFillColor(0);
    leg1->SetShadowColor(0); 
    leg1->SetBorderSize(0);
    leg1->SetTextSize(0.03);
    leg1->Draw();*/

    c1->SaveAs("ratioPions.png");

}