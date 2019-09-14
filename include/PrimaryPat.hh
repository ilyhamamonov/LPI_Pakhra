#pragma once
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4ParticleGun.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithADouble.hh>
#include "Geometry.hh"

class PrimaryPat: public G4VUserPrimaryGeneratorAction
{
private:
	G4ParticleGun * gun;
public:
	PrimaryPat();
	virtual ~PrimaryPat();
	virtual void GeneratePrimaries(G4Event*);
};
