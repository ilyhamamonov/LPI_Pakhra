#include <PrimaryPat.hh>
#include <G4Neutron.hh>
#include <G4Electron.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

#define MEAN_ENERGY_MeV 500

PrimaryPat::PrimaryPat()
{
	Init_Particle();
}

PrimaryPat::~PrimaryPat()
{
	delete gun;
}


void PrimaryPat::GeneratePrimaries(G4Event* anEvent)
{
	Set_Particle_Energy();
	Set_Particle_Angle();
	Set_Particle_Position();

	gun->GeneratePrimaryVertex(anEvent);
}

void PrimaryPat::Init_Particle(void)
{
	gun = new G4ParticleGun(1);
	gun->SetParticleDefinition(G4Electron::ElectronDefinition());
}

void PrimaryPat::Set_Particle_Angle(void)
{
	//G4double angle = 0;
	//G4double rand = (2 * G4UniformRand() - 1);
	//
	//angle = 1e-3 * 180 / pi / 2 * rand;

	//gun->SetParticleMomentumDirection(G4ThreeVector(angle, 0, 1));
	gun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));

	//std::cout << "angle = " << gun->GetParticleMomentumDirection().getX() << std::endl;
}

void PrimaryPat::Set_Particle_Energy(void)
{
	//G4double energy = 0;
	//G4double mean_energy = MEAN_ENERGY_MeV;
	//G4double sigma_energy = MEAN_ENERGY_MeV * 0.01;
	//
	//do
	//{
	//	energy = G4RandGauss::shoot(mean_energy, sigma_energy);
	//} while (energy > mean_energy + 2 * sigma_energy || energy < mean_energy - 2 * sigma_energy);

	gun->SetParticleEnergy(MEAN_ENERGY_MeV * MeV);

	//std::cout << "energy = " << gun->GetParticleEnergy() << std::endl;
}

void PrimaryPat::Set_Particle_Position(void)
{
	//G4double pos_y = 0;
	//G4double pos_x = 0;
	//
	//G4double mean_pos_y = 0;
	//G4double sigma_pos_y = 7.5;
	//
	//G4double mean_pos_x = 4960;
	//G4double sigma_pos_x = 7.5;
	//
	//do
	//{
	//	pos_y = G4RandGauss::shoot(mean_pos_y, sigma_pos_y);
	//} while (pos_y > mean_pos_y + 2 * sigma_pos_y || pos_y < mean_pos_y - 2 * sigma_pos_y);	
	//
	//do
	//{
	//	pos_x = G4RandGauss::shoot(mean_pos_x, sigma_pos_x);
	//} while (pos_x > mean_pos_x + 2 * sigma_pos_x || pos_x < mean_pos_x - 2 * sigma_pos_x);	

	G4double pos_y = 0;
	G4double pos_x = 4960;

	gun->SetParticlePosition(G4ThreeVector(-pos_x * mm, pos_y * mm, 0));
	
	//std::cout << "pos_y = " << gun->GetParticlePosition().getY() << ", pos_x = " << gun->GetParticlePosition().getX() << std::endl;
}