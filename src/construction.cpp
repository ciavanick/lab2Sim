#include "construction.h"

MyDetectorConstruction::MyDetectorConstruction()
{
    fMessenger = new G4GenericMessenger(this, "/blocks/", "Blocks construction");
    fMessenger->DeclareProperty("nBlocks", nOfIronBlocks, "Number of blocks");
    nOfIronBlocks = 10;
    DefineMaterials();
}

MyDetectorConstruction::~MyDetectorConstruction() {}

void MyDetectorConstruction::DefineMaterials()
{
    G4NistManager *nist = G4NistManager::Instance();
    worldMat = nist->FindOrBuildMaterial("G4_AIR");
    feMat = nist->FindOrBuildMaterial("G4_Fe");
    concreteMat = nist->FindOrBuildMaterial("G4_CONCRETE");
    siliconMat = nist->FindOrBuildMaterial("G4_Si");
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{
    G4double feDimX = 245 * mm;
    G4double feDimY = 0.5* 0.5 * cm;
    G4double feDimZ = 670 * mm;

    G4double worldDimX = 1. * m;
    G4double worldDimY = 2.45 * m + nOfIronBlocks * feDimY;
    G4double worldDimZ = 1. * m;

    solidWorld = new G4Box("solidWorld", worldDimX, worldDimY, worldDimZ);
    logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, true);

    solidFeBlock = new G4Box("solidFeBlock", feDimX, feDimY, feDimZ);
    for (G4int i = 0; i != nOfIronBlocks; ++i)
    {
        logicFeBlock = new G4LogicalVolume(solidFeBlock, feMat, "logicFeBlock");
        physFeMat = new G4PVPlacement(0, G4ThreeVector(0., -80. * cm - i * 2 * feDimY, 0.), logicFeBlock, "physFeMat", logicWorld, false, i, true);
    }

    solidConcreteBlock = new G4Box("solidConcreteBlock", 0.5 * m, 0.5 * m, 0.5 * m);
    logicConcreteBlock = new G4LogicalVolume(solidConcreteBlock, concreteMat, "logicConcreteBlock");
    physConcreteMat = new G4PVPlacement(0, G4ThreeVector(0., 1.40 * m, 0.), logicConcreteBlock, "physConcreteMat", logicWorld, false, 0, true);

    solidSiBlock = new G4Box("solidSiBlock", worldDimX, 0.001 * mm, worldDimZ);
    logicSiBlock = new G4LogicalVolume(solidSiBlock, siliconMat, "logicSiBlock");
    physSiMat = new G4PVPlacement(0, G4ThreeVector(0., -80. * cm + feDimY + 0.001 * mm , 0.), logicSiBlock, "physSiMat", logicWorld, false, 1, true);
    logicSiBlock = new G4LogicalVolume(solidSiBlock, siliconMat, "logicSiBlock");
    physSiMat = new G4PVPlacement(0, G4ThreeVector(0., -80. * cm - nOfIronBlocks * 2 * feDimY - feDimY - 0.001 * mm, 0.), logicSiBlock, "physSiMat", logicWorld, false, 2, true);

    return physWorld;
}
