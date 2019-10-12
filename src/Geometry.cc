#include <Geometry.hh>

Geometry::Geometry()
{	
	nist = G4NistManager::Instance();	

	Init_Materials();
	Init_World();
	Init_Parser();
}

Geometry::~Geometry() {

}

G4VPhysicalVolume* Geometry::Construct()
{
	Init_Accelerator_Geometry();

	Place_wolfram_wire(960, -4960);

	return physWorld;
}

// ---------------------------------- Parser

void Geometry::Init_Parser(void)
{
	parser = new G4GDMLParser();
	parser->Read("geometry/name.gdml");
	parser_l_tube =		parser->GetVolume("straight_tube_ring");
	parser_l_vacuum =	parser->GetVolume("straight_tube_vacuum");
	parser_q_tube =		parser->GetVolume("tube_ring");
	parser_q_vacuum =	parser->GetVolume("tube_vacuum");
	parser_q_magnet =	parser->GetVolume("magnet");
}

// ---------------------------------- World define

void Geometry::Init_World(void)
{
	G4double world_sizeXYZ = 10000 * mm;
	G4Box* solidWorld = new G4Box("solWorld", 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ);
	logicWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_AIR"), "logWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);
}

// ---------------------------------- Wolfram wire ----------------------------------

void Geometry::Place_wolfram_wire(int PointX, int PointZ)
{
	G4double transparency = 1;
	G4double thickness = 250 * um;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(90 * deg);

	G4Tubs* wolfram_wire_tube = new G4Tubs("wolfram_wire_tube", 0, thickness / 2, 60 * mm, 0, 360);
	G4LogicalVolume* wolfram_wire = new G4LogicalVolume(wolfram_wire_tube, nist->FindOrBuildMaterial("G4_W"), "wolfram_wire_lv");

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 1, 1, transparency);

	wolfram_wire->SetVisAttributes(visAttr);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), wolfram_wire, "wolfram_wire_", logicWorld, false, 0);
}

// ---------------------------------- Accelerator Geometry ----------------------------------
// ---------------------------------- Geometry sectors

void Geometry::Init_Accelerator_Geometry(void)
{
	Place_Q_Section(960, -960, 180, 0, "Q1");
	Place_Q_Section(-960, -960, 0, 180, "Q2");
	Place_Q_Section(-960, 960, 180, 180, "Q3");
	Place_Q_Section(960, 960, 0, 0, "Q4");

	Place_L_Section(4960, 0, 0, 0, "L1");
	Place_L_Section(0, 4960, 0, 90, "L2");
	Place_L_Section(-4960, 0, 0, 0, "L3");
	Place_L_Section(0, -4960, 0, 90, "L4");
}


void Geometry::Place_L_Section(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	Place_L_Tube(PointX, PointZ, RotateX, RotateY, name);
	Place_L_Vacuum(PointX, PointZ, RotateX, RotateY, name);
}

void Geometry::Place_Q_Section(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	Place_Q_Tube(PointX, PointZ, RotateX, RotateY, name);
	Place_Q_Vacuum(PointX, PointZ, RotateX, RotateY, name);
	Place_Q_Magnet(PointX, PointZ, RotateX, RotateY, name);
}

// ---------------------------------- Geometry parts

void Geometry::Place_L_Tube(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	G4double transparency = 0.2;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	G4LogicalVolume* l_tube = parser_l_tube;

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 0, 1, transparency);

	l_tube->SetVisAttributes(visAttr);
	l_tube->SetMaterial(SiO2);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), l_tube, "l_tube_" + name, logicWorld, false, 0);
}

void Geometry::Place_L_Vacuum(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	G4double transparency = 0.01;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	G4LogicalVolume* l_vacuum = parser_l_vacuum;

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(1, 1, 0, transparency);

	l_vacuum->SetVisAttributes(visAttr);
	l_vacuum->SetMaterial(Vacuum);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), l_vacuum, "l_vacuum_" + name, logicWorld, false, 0);
}

void Geometry::Place_Q_Tube(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{	
	G4double transparency = 0.2;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	G4LogicalVolume* q_tube = parser_q_tube;

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 0, 1, transparency);

	q_tube->SetVisAttributes(visAttr);
	q_tube->SetMaterial(SiO2);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), q_tube, "q_tube_" + name, logicWorld, false, 0);
}

void Geometry::Place_Q_Vacuum(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	G4double mag_field = 63 * gauss;
	G4double transparency = 0.01;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	G4LogicalVolume* q_vacuum = parser_q_vacuum;

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(1, 1, 0, transparency);

	q_vacuum->SetVisAttributes(visAttr);
	q_vacuum->SetMaterial(Vacuum);
	
	G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(0.0, mag_field, 0.0));
	G4FieldManager* localFieldMgr = new G4FieldManager(magField);
	q_vacuum->SetFieldManager(localFieldMgr, true);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), q_vacuum, "q_vacuum_" + name, logicWorld, false, 0);
}

void Geometry::Place_Q_Magnet(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	G4double transparency = 0.05;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	G4LogicalVolume* q_magnet = parser_q_magnet;
	
	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 1, 0, transparency);

	q_magnet->SetVisAttributes(visAttr);
	q_magnet->SetMaterial(nist->FindOrBuildMaterial("G4_Pb"));
	
	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), q_magnet, "q_magnet_" + name, logicWorld, false, 0);
}

// ---------------------------------- Materials

void Geometry::Init_Materials(void)
{
	Vacuum_Init();
	SiO2_Init();
}

void Geometry::Vacuum_Init(void)
{
	G4double A, Z, density;
	G4int natoms, nel;
	G4State   state;
	G4double  temp;
	G4double  pressure;

	G4Element* elN = new G4Element("Nitrogen", "N", Z = 7., A = 14.00674 * g / mole);
	G4Element * elO = new G4Element("Oxygen", "O", Z = 8., A = 15.9994 * g / mole);

	density = universe_mean_density;
	Vacuum = new G4Material("Vacuum", density, nel = 2, state = kStateGas, temp = 293.15 * kelvin, pressure = 1e-7 * pascal);
	Vacuum->AddElement(elN, .7);
	Vacuum->AddElement(elO, .3);
}

void Geometry::SiO2_Init(void)
{
	G4double A, Z, density;
	G4int natoms, nel;

	G4Element *O = new G4Element("Oxygen", "O", Z = 8., A = 16.00 * g / mole);
	G4Element *Si = new G4Element("Silicon", "Si", Z = 14., A = 28.0855 * g / mole);

	density = 2.6 * g / cm3;
	SiO2 = new G4Material("SiO2", density, nel = 2);
	SiO2->AddElement(Si, natoms = 1);
	SiO2->AddElement(O, natoms = 2);
}