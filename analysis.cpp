void analysis(Int_t count = 0, TString rootFilePath = "build/output0.root")
{
    TTree *t1, *t2, *t3, *t4 = new TTree();
    TFile *file = new TFile(rootFilePath, "read");
    // retrieving the tree
    t1 = (TTree *)file->Get("t1");
    t2 = (TTree *)file->Get("t2");
    t3 = (TTree *)file->Get("t3");

    Int_t StopInFe_t1, StopInFe_t3;
    Int_t fEventID_t1, fEventID_t2, fEventID_t3, fEventID_t4;
    Int_t fElectrons, fInFe, fDecay_t2;
    Int_t fElectronsStop, StopInSi;
    std::vector<Int_t> ID_vector;
    std::vector<Int_t> ID_vector_stop;
    std::vector<Int_t> ID_track_created;
    std::vector<Int_t> Is_already;
    Int_t fElectrons_t4, fSecondaryInIron, fNumOfSecondary;
    Int_t fTrackID_t2, fTrackID_t3, fTrackID_t4;

    t1->SetBranchAddress("StopInFe", &StopInFe_t1);
    t1->SetBranchAddress("fEventID", &fEventID_t1);

    t2->SetBranchAddress("fElectrons", &fElectrons);
    t2->SetBranchAddress("fInFe", &fInFe);
    t2->SetBranchAddress("fEventID", &fEventID_t2);
    t2->SetBranchAddress("fDecay", &fDecay_t2);
    fNumOfSecondary = 0;
    Int_t nEl = 0;

    t3->SetBranchAddress("fElectronsStop", &fElectronsStop);
    t3->SetBranchAddress("StopInFe", &StopInFe_t3);
    t3->SetBranchAddress("fEventID", &fEventID_t3);
    t3->SetBranchAddress("StopInSi", &StopInSi);
    Int_t nElSi = 0;

Int_t nMu=0;

    auto nEntries = static_cast<Int_t>(t1->GetEntries());
    for (Int_t i = 0; i != nEntries; ++i)
    {
        t1->GetEntry(i);
        if (StopInFe_t1 == 1)
            ID_vector.push_back(fEventID_t1);
            ++nMu;
    }

    nEntries = static_cast<Int_t>(t2->GetEntries());
    for (Int_t i = 0; i != nEntries; ++i)
    {
        t2->GetEntry(i);
        bool fromDecay = std::find(std::begin(ID_vector), std::end(ID_vector), fEventID_t2) != std::end(ID_vector);
        //std::cout<<fElectrons<<"\t"<<fInFe<<"\t"<<fDecay_t2<<"\n";
        if (fElectrons == 1 && fInFe == 1 && fDecay_t2 == 1)
        {
            ++nEl;
        }
    }

    nEntries = static_cast<Int_t>(t3->GetEntries());
    for (Int_t i = 0; i != nEntries; ++i)
    {
        t3->GetEntry(i);
        //bool fromDecay = std::find(std::begin(ID_vector), std::end(ID_vector), fEventID_t3) != std::end(ID_vector);
        //bool isIron = std::find(std::begin(ID_track_created), std::end(ID_track_created), fTrackID_t3) != std::end(ID_track_created);
        if (fElectronsStop == 1 && StopInFe_t3 == 1 )
            ++nElSi;
    }


    std::cout << "Numbers of electrons produced in " << (count + 1) * 0.5 << " cm of Iron : " << nMu << "\n";
    std::cout << "Numbers of electron that were produced in " << (count + 1) * 0.5 << " cm of Iron, absorbed : " << nEl - nElSi << "\n";
    std::cout << "Numbers of electron that were produced in " << (count + 1) * 0.5 << " cm of Iron, not absorbed : " << nElSi << "\n";
}