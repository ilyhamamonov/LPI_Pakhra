#include <PrimaryPat.hh>
#include <G4Neutron.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

PrimaryPat::PrimaryPat()
{
	gun = new G4ParticleGun(1);

	//gun->SetParticleDefinition(G4Neutron::NeutronDefinition());
	//gun->SetParticlePosition(G4ThreeVector(-10 * cm, 0, 0));
	//gun->SetParticleEnergy(5 * MeV);
}

PrimaryPat::~PrimaryPat()
{
	delete gun;
}


void PrimaryPat::GeneratePrimaries(G4Event* anEvent)
{
	//gun->SetParticleMomentum(G4ThreeVector(2 * G4UniformRand() - 1, 2 * G4UniformRand() - 1, 2 * G4UniformRand() - 1));
	gun->SetParticleDefinition(G4Neutron::NeutronDefinition());
	gun->SetParticlePosition(G4ThreeVector(-10 * cm, 0, 0));
	gun->SetParticleEnergy(5 * MeV);
	gun->GeneratePrimaryVertex(anEvent);

	double i = G4UniformRand();

	G4cout << "i ======================= " << i << G4endl;

	if (i > 0.8) {
		gun->SetParticleDefinition(G4Neutron::NeutronDefinition());
		gun->SetParticlePosition(G4ThreeVector(-10 * cm, 5 * cm, 0));
		gun->SetParticleEnergy(5 * MeV);
		gun->GeneratePrimaryVertex(anEvent);

		
	}
}