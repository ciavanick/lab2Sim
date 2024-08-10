#include "run.h"

MyRunAction::MyRunAction()
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("t1", "all data for primary muons here");
    man->CreateNtupleDColumn("fPosX");
    man->CreateNtupleDColumn("fPosY");
    man->CreateNtupleDColumn("fPosZ");
    man->CreateNtupleIColumn("StopInFe");
    man->CreateNtupleIColumn("StopInWorld");
    man->CreateNtupleIColumn("StepNumber");
    man->CreateNtupleIColumn("fEventID");
    man->FinishNtuple(0);

    man->CreateNtuple("t2", "all data for electron here");
    man->CreateNtupleDColumn("fPosX");
    man->CreateNtupleDColumn("fPosY");
    man->CreateNtupleDColumn("fPosZ");
    man->CreateNtupleIColumn("fDecay");
    man->CreateNtupleIColumn("fElectrons");
    man->CreateNtupleIColumn("fInFe");
    man->CreateNtupleIColumn("fNumOfSecondary");
    man->CreateNtupleDColumn("fKinEnergy");
    man->CreateNtupleIColumn("fEventID");
    man->FinishNtuple(1);

    man->CreateNtuple("t3", "all data for electron absorbed here");
    man->CreateNtupleDColumn("fPosX");
    man->CreateNtupleDColumn("fPosY");
    man->CreateNtupleDColumn("fPosZ");
    man->CreateNtupleIColumn("StopInSi");
    man->CreateNtupleIColumn("StopInFe");
    man->CreateNtupleIColumn("fElectronsStop");
    man->CreateNtupleIColumn("fNumOfSecondaryStop");
    man->CreateNtupleIColumn("StepNumber");
    man->CreateNtupleIColumn("fEventID");
    man->CreateNtupleIColumn("fDecay");
    man->FinishNtuple(2);

}

MyRunAction::~MyRunAction() {}

void MyRunAction::BeginOfRunAction(const G4Run *run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();
    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile("output" + strRunID.str() + ".root");
}

void MyRunAction::EndOfRunAction(const G4Run *)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}