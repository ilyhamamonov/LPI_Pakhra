#ifdef G4MULTITHREADED

#include <G4VisManager.hh>
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"
#include "QBBC.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif


#include <iostream>

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

class Loader
{
private:
#ifdef G4MULTITHREADED
    G4MTRunManager* runManager;
#else
    G4RunManager* runManager;
#endif
#ifdef G4VIS_USE
    G4VisManager* visManager;
#endif
public:
    Loader(int argc, char** argv);
    ~Loader();
};