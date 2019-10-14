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

	if (event->get_step_i() >= 4)
		step->GetTrack()->SetTrackStatus(fStopAndKill);

	for (int i = 0; i <= 4; i++)
	{
		if (!volume_name.compare("q_tube_Q" + std::to_string(i)))
			step->GetTrack()->SetTrackStatus(fStopAndKill);
		if (!volume_name.compare("l_tube_L" + std::to_string(i)))
			step->GetTrack()->SetTrackStatus(fStopAndKill);
		if (!volume_name.compare("q_magnet_L" + std::to_string(i)))
			step->GetTrack()->SetTrackStatus(fStopAndKill);
	}
}