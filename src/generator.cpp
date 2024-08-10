#include "generator.h"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    G4int nOfParticles = 1;
    fParticleGun = new G4ParticleGun(nOfParticles); // inside G4ParticleGun we have the number of particles per event, one run contains several events and each event can contain several particle, here just 1 particle (one vertex per event)

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String  particleName = "mu-";
    G4ParticleDefinition *particle = particleTable->FindParticle(particleName);

    G4ThreeVector pos(0., 2.42*m, 0.);
    G4ThreeVector mom(0., -1., 0.); //particle in z direction

    fParticleGun->SetParticleEnergy(1*GeV);
    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent) // here we want to create the particle gun
{


    fParticleGun->GeneratePrimaryVertex(anEvent);


}