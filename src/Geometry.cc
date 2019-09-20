#include <Geometry.hh>
#include <G4VisAttributes.hh>

Geometry::Geometry()
{
	parser = new G4GDMLParser();
	nist = G4NistManager::Instance();

	magField = new G4UniformMagField(G4ThreeVector(0.0, 63.2 * gauss, 0.0));
	localFieldMgr = new G4FieldManager(magField);

	world_sizeXYZ = 10000 * mm;
	world_mat = nist->FindOrBuildMaterial("G4_AIR");
	solidWorld = new G4Box("solWorld", 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ, 0.5 * world_sizeXYZ);
	logicWorld = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);
}

Geometry::~Geometry() {

}

G4VPhysicalVolume* Geometry::Construct()
{
	Init_Materials();

	parser->Read("geometry/name.gdml");

	Place_Q_Section(96, 0, 96, 0, 0);
	Place_Q_Section(96, 0, -96, 180, 0);
	Place_Q_Section(-96, 0, 96, 180, 180);
	Place_Q_Section(-96, 0, -96, 0, 180);
	
	Place_L_Section(496, 0, 0, 0, 0);
	Place_L_Section(-496, 0, 0, 0, 0);
	Place_L_Section(0, 0, 496, 0, 90);
	Place_L_Section(0, 0, -496, 0, 90);

	return physWorld;
}

// ---------------------------------- Geometry sectors

void Geometry::Place_L_Section(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	Place_L_Tube(PointX, PointY, PointZ, RotateX, RotateY);
	Place_L_Vacuum(PointX, PointY, PointZ, RotateX, RotateY);
}

void Geometry::Place_Q_Section(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	Place_Q_Tube(PointX, PointY, PointZ, RotateX, RotateY);
	Place_Q_Vacuum(PointX, PointY, PointZ, RotateX, RotateY);
	Place_Q_Magnet(PointX, PointY, PointZ, RotateX, RotateY);
}

// ---------------------------------- Geometry parts

void Geometry::Place_L_Tube(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto l_tube = parser->GetVolume("straight_tube_ring");

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 0, 1, 0.2);

	l_tube->SetVisAttributes(visAttr);
	l_tube->SetMaterial(SiO2);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), l_tube, "l_tube_PV", logicWorld, false, 0);
}

void Geometry::Place_L_Vacuum(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto l_vacuum = parser->GetVolume("straight_tube_vacuum");

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(1, 1, 0, 0.01);

	l_vacuum->SetVisAttributes(visAttr);
	l_vacuum->SetMaterial(Vacuum);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), l_vacuum, "l_vacuum_PV", logicWorld, false, 0);
}

void Geometry::Place_Q_Tube(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{	
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto q_tube = parser->GetVolume("tube_ring");

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 0, 1, 0.2);

	q_tube->SetVisAttributes(visAttr);
	q_tube->SetMaterial(SiO2);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), q_tube, "q_tube_PV", logicWorld, false, 0);
}

void Geometry::Place_Q_Vacuum(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto q_vacuum = parser->GetVolume("tube_vacuum");

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(1, 1, 0, 0.01);

	q_vacuum->SetVisAttributes(visAttr);
	q_vacuum->SetMaterial(Vacuum);
	q_vacuum->SetFieldManager(localFieldMgr, true);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), q_vacuum, "q_vacuum_PV", logicWorld, false, 0);
}

void Geometry::Place_Q_Magnet(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto q_magnet = parser->GetVolume("magnet");
	
	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 1, 0, 0.05);

	q_magnet->SetVisAttributes(visAttr);
	q_magnet->SetMaterial(nist->FindOrBuildMaterial("G4_Pb"));
	
	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), q_magnet, "q_magnet_PV", logicWorld, false, 0);
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