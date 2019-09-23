#include <EventAct.hh>

EventAct::EventAct(RunAct* runAct) :run(runAct)
{

}

EventAct::~EventAct()
{

}

void EventAct::BeginOfEventAction(const G4Event* anEvent)
{
	set_step_zero();
}

void EventAct::EndOfEventAction(const G4Event* anEvent)
{
	
}

int step_i;

void EventAct::set_step_i_to_zero(void)
{
	step_i = 0;
}

void EventAct::add_step_i(void)
{
	step_i = step_i + 1;
}

int EventAct::get_step_i(void)
{
	return step_i;
}