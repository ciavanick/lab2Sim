#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4GenericMessenger.hh"
//------------------------------------------------
#include "G4SystemOfUnits.hh" //system of units


class MyDetectorConstruction : public G4VUserDetectorConstruction //user detector construction class implemented in geant4
{
    public:
    MyDetectorConstruction();
    ~MyDetectorConstruction();

    virtual G4VPhysicalVolume *Construct(); //all the description of the detector must be put in that function
    
    private:
    void DefineMaterials();

    G4Material *worldMat, *feMat, *concreteMat, *siliconMat;
    G4Box *solidWorld, *solidFeBlock, *solidConcreteBlock, *solidSiBlock;
    G4LogicalVolume *logicWorld, *logicFeBlock, *logicConcreteBlock, *logicSiBlock;
    G4VPhysicalVolume *physWorld, *physFeMat, *physConcreteMat, *physSiMat;
    G4GenericMessenger *fMessenger;
    G4int nOfIronBlocks;

};


#endif