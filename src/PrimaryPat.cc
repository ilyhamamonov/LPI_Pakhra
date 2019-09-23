#include <PrimaryPat.hh>
#include <G4Neutron.hh>
#include <G4Electron.hh>
#include <G4SystemOfUnits.hh>
#include <Randomize.hh>

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
	Set_Particle_Angle();
	Set_Particle_Energy();
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
	G4double angle = 0;
	G4double rand = (2 * G4UniformRand() - 1);

	angle = 1e-3 * 180 / pi / 2 * rand;

	//gun->SetParticleMomentum(G4ThreeVector(-1, 0, angle));
	gun->SetParticleMomentum(G4ThreeVector(-1, 0, 0));

	//std::cout << "angle = " << angle << std::endl;
}

void PrimaryPat::Set_Particle_Energy(void)
{
	G4double energy = 0;

	G4double mean_energy = 7;
	G4double sigma_energy = 0.07;

	do
	{
		energy = G4RandGauss::shoot(mean_energy, sigma_energy);
	} while (energy > mean_energy + 2 * sigma_energy || energy < mean_energy - 2 * sigma_energy);	

	gun->SetParticleEnergy(energy * MeV);

	//std::cout << "energy = " << energy << std::endl;
}

void PrimaryPat::Set_Particle_Position(void)
{
	G4double pos_y = 0;
	G4double pos_z = 0;

	G4double mean_pos_y = 0;
	G4double sigma_pos_y = 7.5;

	G4double mean_pos_z = 4960;
	G4double sigma_pos_z = 7.5;

	do
	{
		pos_y = G4RandGauss::shoot(mean_pos_y, sigma_pos_y);
	} while (pos_y > mean_pos_y + 2 * sigma_pos_y || pos_y < mean_pos_y - 2 * sigma_pos_y);	

	do
	{
		pos_z = G4RandGauss::shoot(mean_pos_z, sigma_pos_z);
	} while (pos_z > mean_pos_z + 2 * sigma_pos_z || pos_z < mean_pos_z - 2 * sigma_pos_z);		

	gun->SetParticlePosition(G4ThreeVector(0, pos_y * mm, - pos_z * mm));

	//std::cout << "pos_y = " << pos_y << ", pos_z = " << pos_z << std::endl;
}