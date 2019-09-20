#include <PrimaryPat.hh>
#include <G4Neutron.hh>
#include <G4Electron.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

PrimaryPat::PrimaryPat()
{
	gun = new G4ParticleGun(1);
	gun->SetParticleDefinition(G4Electron::ElectronDefinition());
	gun->SetParticlePosition(G4ThreeVector(0, 0, 496 *cm));
	gun->SetParticleEnergy(7 * MeV);
}

PrimaryPat::~PrimaryPat()
{
	delete gun;
}


void PrimaryPat::GeneratePrimaries(G4Event* anEvent)
{	
	gun->GeneratePrimaryVertex(anEvent);
}