#include <Geometry.hh>

Geometry::Geometry()
{	
	nist = G4NistManager::Instance();	

	Init_Materials();
	Init_World();
}

Geometry::~Geometry() {

}

G4VPhysicalVolume* Geometry::Construct()
{
	Init_Accelerator_Geometry();

	Place_wolfram_wire(-4960, 960);

	Init_Channel_Geometry();

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
	parser_q2_ring =	parser->GetVolume("tube_q2_ring");
}

// ---------------------------------- World define

void Geometry::Init_World(void)
{
	G4double world_sizeX = 10000 * mm;
	G4double world_sizeY = 10000 * mm;
	G4double world_sizeZ = 100000 * mm;
	G4Box* solidWorld = new G4Box("solWorld", 0.5 * world_sizeX, 0.5 * world_sizeY, 0.5 * world_sizeZ);
	logicWorld = new G4LogicalVolume(solidWorld, nist->FindOrBuildMaterial("G4_AIR"), "logWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);
}

// ---------------------------------- Wolfram wire ----------------------------------

void Geometry::Place_wolfram_wire(int PointX, int PointZ)
{
	G4double transparency = 1;
	G4double thickness = 750 * um;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(90 * deg);

	G4Tubs* wolfram_wire_tube = new G4Tubs("wolfram_wire_tube", 0, thickness / 2, 60 * mm, 0, 360);
	G4LogicalVolume* wolfram_wire = new G4LogicalVolume(wolfram_wire_tube, nist->FindOrBuildMaterial("G4_W"), "wolfram_wire_lv");

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 1, 1, transparency);

	wolfram_wire->SetVisAttributes(visAttr);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), wolfram_wire, "wolfram_wire", logicWorld, false, 0);
}

// ---------------------------------- Accelerator Geometry ----------------------------------
// ---------------------------------- Geometry sectors

void Geometry::Init_Accelerator_Geometry(void)
{
	Init_Parser();
	
	Place_Q_Section(-960, -960, 0, 180, "Q1");
	Place_Q2_Section(-960, 960, 180, 180);
	Place_Q_Section(960, 960, 0, 0, "Q3");
	Place_Q_Section(960, -960, 180, 0, "Q4");

	Place_L_Section(0, -4960, 0, 90, "L1");
	Place_L_Section(4960, 0, 0, 0, "L2");
	Place_L_Section(0, 4960, 0, 90, "L3");
	Place_L_Section(-4960, 0, 0, 0, "L4");
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

void Geometry::Place_Q2_Section(int PointX, int PointZ, int RotateX, int RotateY)
{
	std::string name = "Q2";

	Place_Q2_Tube(PointX, PointZ, RotateX, RotateY);
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

void Geometry::Place_Q2_Tube(int PointX, int PointZ, int RotateX, int RotateY)
{
	G4double transparency = 0.2;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	G4LogicalVolume* q2_tube = parser_q2_ring;

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(0, 0, 1, transparency);

	q2_tube->SetVisAttributes(visAttr);
	q2_tube->SetMaterial(SiO2);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), q2_tube, "q_tube_Q2", logicWorld, false, 0);
}

void Geometry::Place_Q_Vacuum(int PointX, int PointZ, int RotateX, int RotateY, std::string name)
{
	G4double mag_field = 4.175 * kilogauss;
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

// ---------------------------------- Channel Geometry ----------------------------------
// ---------------------------------- Geometry sectors
void Geometry::Init_Channel_Geometry(void)
{
	G4double wire_x = -4960;
	G4double wire_z = 960;

	Place_C1_Channel(			wire_x,	 wire_z + 4000,	 0);
	Place_W1_T_Channel(			wire_x,	 wire_z + 6500,	 0);
	Place_C2_Channel(			wire_x,	 wire_z + 18000, 0);
	Place_M1_Channel(			wire_x,	 wire_z + 20000, 0);
	Place_GEc_M2_Channel(		wire_x,	 wire_z + 40000, 0);
	Place_C3_PbWall_Channel(	wire_x,	 wire_z + 43200, 0);
}

// ---------------------------------- Geometry parts
void Geometry::Place_C1_Channel(int PointX, int PointZ, int RotateY)
{
	G4double x_size = 400 * mm;
	G4double y_size = 200 * mm;
	G4double z_size = 150 * mm;

	G4double d_in = 30 * mm;
	G4double d_out = 13 * mm;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateY(RotateY * deg);

	G4Box* c1_channel_box = new G4Box("c1_channel_box", x_size / 2, y_size / 2, z_size / 2);
	G4Cons* c1_channel_cons = new G4Cons("c1_channel_cons", 0, d_in / 2, 0, d_out / 2, z_size, 0, 360);
	G4SubtractionSolid* c1_channel_subtraction = new G4SubtractionSolid("box-cons", c1_channel_box, c1_channel_cons);
	G4LogicalVolume* c1_channel = new G4LogicalVolume(c1_channel_subtraction, nist->FindOrBuildMaterial("G4_Pb"), "c1_channel_lv");

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), c1_channel, "c1_channel", logicWorld, false, 0);
}

void Geometry::Place_W1_T_Channel(int PointX, int PointZ, int RotateY)
{
	// W1
	G4double x_size = 5000 * mm;
	G4double y_size = 1000 * mm;
	G4double z_size = 3000 * mm;
	// T	
	G4double d_size = 110 * mm;
	G4double thickness = 5 * mm;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateY(RotateY * deg);

	G4Box* w1_channel_box = new G4Box("w1_channel_box", x_size / 2, y_size / 2, z_size / 2);
	G4Tubs* w1_channel_hole = new G4Tubs("w1_channel_hole", 0, d_size / 2, z_size, 0, 360);
	G4SubtractionSolid* w1_channel_subtraction = new G4SubtractionSolid("box-cons", w1_channel_box, w1_channel_hole);
	// SET MATERIAL!
	G4LogicalVolume* w1_channel = new G4LogicalVolume(w1_channel_subtraction, nist->FindOrBuildMaterial("G4_Pb"), "w1_channel_lv");
	
	G4Tubs* t_channel_tube = new G4Tubs("t_channel_tube", d_size / 2 - thickness, d_size / 2, z_size / 2 * 1.1, 0, 360);
	// SET MATERIAL!
	G4LogicalVolume* t_channel = new G4LogicalVolume(t_channel_tube, nist->FindOrBuildMaterial("G4_Pb"), "t_channel_lv");

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), t_channel, "t_channel", logicWorld, false, 0);
	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), w1_channel, "w1_channel", logicWorld, false, 0);
}

void Geometry::Place_C2_Channel(int PointX, int PointZ, int RotateY)
{
	G4double x_size = 200 * mm;
	G4double y_size = 100 * mm;
	G4double z_size = 70 * mm;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateY(RotateY * deg);

	G4Box* c2_channel_box = new G4Box("c2_channel_box", x_size / 2, y_size / 2, z_size / 2);

	G4Tubs* c2_channel_30mm_hole = new G4Tubs("c2_channel_30mm_hole", 0, 30/2 *mm, z_size, 0, 360);
	G4SubtractionSolid* c2_channel_30mm_ss = new G4SubtractionSolid("box-cons", c2_channel_box, c2_channel_30mm_hole);
	// SET MATERIAL!
	G4LogicalVolume* c2_channel_30mm = new G4LogicalVolume(c2_channel_30mm_ss, nist->FindOrBuildMaterial("G4_Pb"), "c2_channel_30mm_ss_lv");

	G4Tubs* c2_channel_50mm_hole = new G4Tubs("c2_channel_50mm_hole", 0, 50/2 * mm, z_size, 0, 360);
	G4SubtractionSolid* c2_channel_50mm_ss = new G4SubtractionSolid("box-cons", c2_channel_box, c2_channel_50mm_hole);
	// SET MATERIAL!
	G4LogicalVolume* c2_channel_50mm = new G4LogicalVolume(c2_channel_50mm_ss, nist->FindOrBuildMaterial("G4_Pb"), "c2_channel_50mm_ss_lv");

	new G4PVPlacement(rotm, G4ThreeVector( 280 * sin(RotateY * deg) + PointX * mm, 0, - 280 * cos(RotateY * deg) + PointZ * mm), c2_channel_30mm, "c2_channel_30mm_ss", logicWorld, false, 0);
	new G4PVPlacement(rotm, G4ThreeVector( 140 * sin(RotateY * deg) + PointX * mm, 0, - 140 * cos(RotateY * deg) + PointZ * mm), c2_channel_50mm, "c2_channel_50mm", logicWorld, false, 0);
	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), c2_channel_30mm, "c2_channel_30mm_ss", logicWorld, false, 0);
	new G4PVPlacement(rotm, G4ThreeVector(-140 * sin(RotateY * deg) + PointX * mm, 0, 140 * cos(RotateY * deg) + PointZ * mm), c2_channel_50mm, "c2_channel_50mm", logicWorld, false, 0);
	new G4PVPlacement(rotm, G4ThreeVector(-280 * sin(RotateY * deg) + PointX * mm, 0, 280 * cos(RotateY * deg) + PointZ * mm), c2_channel_30mm, "c2_channel_30mm_ss", logicWorld, false, 0);
}

void Geometry::Place_M1_Channel(int PointX, int PointZ, int RotateY)
{
	G4double x_size = 500 * mm;
	G4double y_size = 50 * mm;
	G4double z_size = 150 * mm;

	G4double mag_field = 0 * kilogauss;
	G4double transparency = 0.3;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateY(RotateY * deg);

	G4Box* m1_channel_box = new G4Box("m1_channel_box", x_size / 2, y_size / 2, z_size / 2);
	G4LogicalVolume* m1_channel = new G4LogicalVolume(m1_channel_box, nist->FindOrBuildMaterial("G4_AIR"), "m1_channel_lv");

	G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(0.0, mag_field, 0.0));
	G4FieldManager* localFieldMgr = new G4FieldManager(magField);
	m1_channel->SetFieldManager(localFieldMgr, true);

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(1, 1, 1, transparency);

	m1_channel->SetVisAttributes(visAttr);

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), m1_channel, "m1_channel", logicWorld, false, 0);
}

void Geometry::Place_GEc_M2_Channel(int PointX, int PointZ, int RotateY)
{
	G4double GEc_x_size = 5 * mm;
	G4double GEc_y_size = 50 * mm;
	G4double GEc_z_size = 1 * mm;

	G4double M2_d_size = 920 * mm;
	G4double M2_z_size = 60 * mm;
	G4double mag_field = 0 * kilogauss;
	G4double transparency = 0.3;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateY(RotateY * deg);

	G4RotationMatrix* rotm2 = new G4RotationMatrix();
	rotm2->rotateY(RotateY * deg);
	rotm2->rotateX(90 * deg);

	G4Box* GEc_channel_box = new G4Box("GEc_channel_box", GEc_x_size / 2, GEc_y_size / 2, GEc_z_size / 2);
	G4LogicalVolume* GEc_channel = new G4LogicalVolume(GEc_channel_box, nist->FindOrBuildMaterial("G4_Cu"), "GEc_channel_lv");

	G4Tubs* M2_channel_tube = new G4Tubs("M2_channel_tube", 0, M2_d_size / 2 * mm, M2_z_size, 0, 360);
	G4LogicalVolume* M2_channel = new G4LogicalVolume(M2_channel_tube, nist->FindOrBuildMaterial("G4_AIR"), "M2_channel_lv");

	G4MagneticField* magField = new G4UniformMagField(G4ThreeVector(0.0, 0.0, mag_field));
	G4FieldManager* localFieldMgr = new G4FieldManager(magField);
	M2_channel->SetFieldManager(localFieldMgr, true);

	G4VisAttributes visAttr = new G4VisAttributes();
	visAttr.SetColor(1, 1, 1, transparency);

	M2_channel->SetVisAttributes(visAttr);

	new G4PVPlacement(rotm, G4ThreeVector(M2_d_size / 2 * sin(RotateY * deg) + PointX * mm, 0, -M2_d_size / 2 * cos(RotateY * deg) + PointZ * mm), GEc_channel, "GEc_channel", logicWorld, false, 0);
	new G4PVPlacement(rotm2, G4ThreeVector(PointX * mm, 0, PointZ * mm), M2_channel, "M2_channel", logicWorld, false, 0);
}

void Geometry::Place_C3_PbWall_Channel(int PointX, int PointZ, int RotateY)
{
	// pbwall
	G4double x_size = 3000 * mm;
	G4double y_size = 1500 *mm;
	G4double z_size = 100 * mm;
	// c3
	G4double d_size = 10 * mm;

	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateY(RotateY * deg);

	G4Box* pbwall_channel_box = new G4Box("pbwall_channel_box", x_size / 2, y_size / 2, z_size / 2);
	G4Tubs* c3_channel_hole = new G4Tubs("c3_channel_hole", 0, d_size / 2, z_size, 0, 360);
	G4SubtractionSolid* pbwall_channel_subtraction = new G4SubtractionSolid("box-hole", pbwall_channel_box, c3_channel_hole);
	// SET MATERIAL!
	G4LogicalVolume* pbwall_channel = new G4LogicalVolume(pbwall_channel_subtraction, nist->FindOrBuildMaterial("G4_Pb"), "pbwall_channel_lv");

	new G4PVPlacement(rotm, G4ThreeVector(PointX * mm, 0, PointZ * mm), pbwall_channel, "pbwall_channel", logicWorld, false, 0);
}
