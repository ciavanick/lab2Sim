#include "stepping.h"

MySteppingAction::MySteppingAction() = default;

MySteppingAction::~MySteppingAction() = default;

void MySteppingAction::UserSteppingAction(const G4Step *step)
{
    
   G4AnalysisManager *man = G4AnalysisManager::Instance();

    const auto track = step->GetTrack();
    const auto &partName = track->GetDefinition()->GetParticleName();
    const auto &physVolume = step->GetPreStepPoint()->GetPhysicalVolume()->GetName();
    //const auto globalTime = step->GetPreStepPoint()->GetGlobalTime() / ns;
    const auto kinE = step->GetPreStepPoint()->GetKineticEnergy();
    const auto stepNb = track->GetCurrentStepNumber();
    const auto parentID = track->GetParentID();
    const auto trackStatus = track->GetTrackStatus();
    const auto currentEvent = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    G4String stoppingAlMaterial = "physAlMat";
    G4String stoppingFeMaterial = "physFeMat";

    const auto stopCondition = ((trackStatus == fStopButAlive) || (trackStatus == fStopAndKill) || (trackStatus == fSuspend)); //stopping condition
    if((parentID == 0) && stopCondition == true)
    {
        man->FillNtupleDColumn(0, 0, track->GetPosition().x()/ mm); //x posirion in cm
        man->FillNtupleDColumn(0, 1, track->GetPosition().y()/ mm); //y posirion in cm
        man->FillNtupleDColumn(0, 2, track->GetPosition().z()/ mm); //z posirion in cm
        man->FillNtupleIColumn(0, 3, (physVolume == "physFeMat")); //check if the volume is Iron
        man->FillNtupleIColumn(0, 4, 1); //all stops
        man->FillNtupleIColumn(0, 5, stepNb); //retrieve the step number
        man->FillNtupleIColumn(0, 6, currentEvent); //Save the eventID
        man->AddNtupleRow(0);
    }

    if(parentID == 1 && stepNb == 1){
        man->FillNtupleDColumn(1, 0, track->GetPosition().x()/ mm); //x posirion in cm
        man->FillNtupleDColumn(1, 1, track->GetPosition().y()/ mm); //y posirion in cm
        man->FillNtupleDColumn(1, 2, track->GetPosition().z()/ mm); //z posirion in cm
        man->FillNtupleIColumn(1, 3, (track->GetCreatorProcess()->GetProcessName() == "Decay")); //check if the particle is an electron 
        man->FillNtupleIColumn(1, 4, (partName == "e-")); //check if the particle is an electron
        man->FillNtupleIColumn(0, 5, (physVolume == "physFeMat")); //check if the volume is Aluminium
        man->FillNtupleIColumn(1, 6, 1); //count the total number of secondary particles
        man->FillNtupleDColumn(1, 7, kinE); //get kinetic energy
        man->FillNtupleIColumn(1, 8, currentEvent); //Save the eventID
        man->AddNtupleRow(1);
    }

    if((parentID == 1) && stopCondition && track->GetCreatorProcess()->GetProcessName() == "Decay")
    {
        man->FillNtupleDColumn(2, 0, track->GetPosition().x()/ mm); //x posirion in cm
        man->FillNtupleDColumn(2, 1, track->GetPosition().y()/ mm); //y posirion in cm
        man->FillNtupleDColumn(2, 2, track->GetPosition().z()/ mm); //z posirion in cm
        man->FillNtupleIColumn(2, 3, (physVolume == "physSiMat")); //check if the volume is Aluminium
        man->FillNtupleIColumn(2, 4, (physVolume == "physFeMat")); //check if the volume is Iron
        man->FillNtupleIColumn(2, 5, (partName == "e-")); //check if the particle stopped is an electron
        man->FillNtupleIColumn(2, 6, 1); //count all secondary particles that stops
        man->FillNtupleIColumn(2, 7, stepNb); //retrieve the step number
        man->FillNtupleIColumn(2, 8, currentEvent); //Save the eventID
        man->FillNtupleIColumn(2, 9, track->GetCreatorProcess()->GetProcessName() == "Decay");
        man->AddNtupleRow(2);
    }
    
    
}