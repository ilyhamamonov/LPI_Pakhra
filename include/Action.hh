#pragma once
#include <G4VUserActionInitialization.hh>

class Action: public G4VUserActionInitialization
{
public:
    virtual void Build() const;
};