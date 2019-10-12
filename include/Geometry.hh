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
#include <G4Box.hh>
#include <G4Tubs.hh>
#include "G4VUserDetectorConstruction.hh"
#include <G4SubtractionSolid.hh>
#include <G4GDMLParser.hh>
#include "G4UniformMagField.hh"
#include "G4FieldManager.hh"
#include "G4TransportationManager.hh"
#include <G4VisAttributes.hh>

class G4VPhysicalVolume;
class G4LogicalVolume;

class Geometry  : public G4VUserDetectorConstruction
{
private:
	G4NistManager*				nist;

	G4LogicalVolume*            logicWorld;
	G4VPhysicalVolume*          physWorld;

	G4LogicalVolume*			parser_l_tube;
	G4LogicalVolume*			parser_l_vacuum;
	G4LogicalVolume*			parser_q_tube;
	G4LogicalVolume*			parser_q_vacuum;
	G4LogicalVolume*			parser_q_magnet;

	virtual G4VPhysicalVolume*  Construct();

	G4Material*					Vacuum;
	G4Material*					SiO2;

	G4GDMLParser* parser;

	void Init_Materials(void);
	void Vacuum_Init(void);
	void SiO2_Init(void);

	void Init_World(void);
	void Init_Parser(void);

	void Init_Accelerator_Geometry(void);

	void Place_L_Section(int PointX, int PointZ, int RotateX, int RotateY, std::string name);
	void Place_Q_Section(int PointX, int PointZ, int RotateX, int RotateY, std::string name);

	void Place_Q_Tube(int PointX, int PointZ, int RotateX, int RotateY, std::string name);
	void Place_Q_Vacuum(int PointX, int PointZ, int RotateX, int RotateY, std::string name);
	void Place_Q_Magnet(int PointX, int PointZ, int RotateX, int RotateY, std::string name);

	void Place_L_Tube(int PointX, int PointZ, int RotateX, int RotateY, std::string name);
	void Place_L_Vacuum(int PointX, int PointZ, int RotateX, int RotateY, std::string name);

	void Place_wolfram_wire(int PointX, int PointZ);
public:
	Geometry();
	virtual ~Geometry();	
};
