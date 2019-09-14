#pragma once
#include <G4UserSteppingAction.hh>
#include "EventAct.hh"

class EventAct;

class StepAct :public G4UserSteppingAction
{
public:
	StepAct(EventAct* eventAct) {};
	~StepAct() {};
	void UserSteppingAction(const G4Step*);
private:	
	EventAct* event;
};