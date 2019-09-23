#pragma once
#include <G4UserSteppingAction.hh>
#include "EventAct.hh"

#define print_val(value) std::cout << value << std::endl;

class EventAct;

class StepAct :public G4UserSteppingAction
{
private:
	EventAct* event;
public:
	StepAct(EventAct* eventAct) {};
	~StepAct() {};
	void UserSteppingAction(const G4Step*);
};