{
   auto canvas = new TCanvas("c47","c47", 600,400);
   auto mg = new TMultiGraph;
  // mg->GetXaxis()->SetTitle("E_{#gamma} (MeV)");
  // mg->GetYaxis()->SetTitle("Counts/Neutron");

   TGraph * fon = new TGraph("fon.txt");
   fon->SetTitle("HPGe Background");
   fon->SetLineColor(kBlue);
   fon->SetLineWidth(3);
   // fon->GetYaxis()->SetRangeUser(1, 7500);
   mg->Add( fon );

   TGraph * gr = new TGraph("must.txt");
   gr->SetTitle("HPGe Mustard gas");
   gr->SetLineColor(kRed);
   // gr->GetYaxis()->SetRangeUser(1, 7500);
   mg->Add( gr );

   // gr->GetListOfFunctions()->Add(gFit);
   // mg->Add(gFit);

   mg->GetXaxis()->SetTitle("E_{#gamma} (MeV)");
   mg->GetYaxis()->SetTitle("Counts / Neutron");
   mg->GetYaxis()->SetRangeUser(0*std::pow(10, -11), 0.15*std::pow(10, -6));
   mg->Draw("ALL");

   canvas->BuildLegend();
   
   return canvas;
}
