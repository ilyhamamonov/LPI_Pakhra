#pragma once
#include <G4UserRunAction.hh>

class RunAct : public G4UserRunAction
{
public:
	RunAct();
	~RunAct();
	void BeginOfRunAction(const G4Run* aRun);
	void EndOfRunAction(const G4Run* aRun);
};
