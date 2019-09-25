#include <G4Step.hh>
#include <StepAction.hh>
#include <G4VProcess.hh>
#include <G4SIunits.hh>
#include <iostream>

void StepAct::UserSteppingAction(const G4Step* step)
{
	G4StepPoint* psp = new G4StepPoint();
	G4String volume_name = "";

	psp = step->GetPreStepPoint();

	volume_name = step->GetTrack()->GetVolume()->GetName();

	if (volume_name == "l_vacuum_L4")
		event->add_step_i();

	if (event->get_step_i() >= 30)
		step->GetTrack()->SetTrackStatus(fStopAndKill);
}