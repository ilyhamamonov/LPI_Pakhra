#pragma once
#include <Action.hh>
#include <PrimaryPat.hh>
#include "EventAct.hh"
#include "StepAction.hh"
#include "RunAct.hh"

void Action::Build() const
{
	SetUserAction(new PrimaryPat);

	RunAct* runAct = new RunAct;
	SetUserAction(runAct);

	EventAct* eventAct = new EventAct(runAct);
	SetUserAction(eventAct);

	SetUserAction(new StepAct(eventAct));
}