#pragma once
#include "RunAct.hh"
#include <G4UserEventAction.hh>
#include <iostream>

class RunAct;

class EventAct : public G4UserEventAction
{
private:
	RunAct* run;
public:
	EventAct(RunAct* runAct);
	~EventAct();
	void BeginOfEventAction(const G4Event* anEvent);
	void EndOfEventAction(const G4Event* anEvent);

	void set_step_i_to_zero(void);
	void add_step_i(void);
	int get_step_i(void);
};