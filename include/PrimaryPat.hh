#pragma once
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithADouble.hh>
#include "Geometry.hh"

class PrimaryPat: public G4VUserPrimaryGeneratorAction
{
private:
	G4ParticleGun* gun;

	void Init_Particle(void);

	void Set_Particle_Angle(void);
	void Set_Particle_Energy(void);
	void Set_Particle_Position(void);
public:
	PrimaryPat();
	virtual ~PrimaryPat();
	virtual void GeneratePrimaries(G4Event*);
};
