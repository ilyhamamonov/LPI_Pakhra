#pragma once
#include "G4SystemOfUnits.hh"
#include <G4PhysicalConstants.hh>
#include <G4UImessenger.hh>
#include <G4UIcmdWithADouble.hh>
#include "G4SolidStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include <G4Torus.hh>
#include <G4Box.hh>
#include <G4Trd.hh>
#include "G4VUserDetectorConstruction.hh"
#include <G4SubtractionSolid.hh>
#include <G4GDMLParser.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

class Geometry  : public G4VUserDetectorConstruction
{
private:
	G4NistManager*				nist;
	G4Material*                 world_mat;
	G4double                    world_sizeXYZ;
	G4Box*                      solidWorld;
	G4LogicalVolume*            logicWorld;
	G4VPhysicalVolume*          physWorld;
	virtual G4VPhysicalVolume*  Construct();	

	G4GDMLParser* parser;
public:
	Geometry();
	virtual ~Geometry();	

	void Place_Section(int PointX, int PointY, int PointZ, int RotateX, int RotateY);
	void Place_Tube(int PointX, int PointY, int PointZ, int RotateX, int RotateY);

	void Place_Tube_Ring(int PointX, int PointY, int PointZ, int RotateX, int RotateY);
	void Place_Tube_Vacuum(int PointX, int PointY, int PointZ, int RotateX, int RotateY);
	void Place_Magnet(int PointX, int PointY, int PointZ, int RotateX, int RotateY);

	void Place_Straight_Tube_Ring(int PointX, int PointY, int PointZ, int RotateX, int RotateY);
	void Place_Straight_Tube_Vacuum(int PointX, int PointY, int PointZ, int RotateX, int RotateY);
	
};
