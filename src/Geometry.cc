#include <Geometry.hh>
#include <G4VisAttributes.hh>

Geometry::Geometry()
{
	world_sizeXYZ = 50 * cm;
	nist = G4NistManager::Instance();
	world_mat = nist->FindOrBuildMaterial("G4_AIR");
	solidWorld = new G4Box("solWorld", 0.5*world_sizeXYZ, 0.5*world_sizeXYZ, 0.5*world_sizeXYZ);
	logicWorld = new G4LogicalVolume(solidWorld, world_mat, "logWorld");
	physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, "phyWorld", 0, false, 0);

	pars_tube = new G4GDMLParser();
}

Geometry::~Geometry() {

}

G4VPhysicalVolume* Geometry::Construct()
{
	Parser_Init(pars_tube, "geometry/name.gdml");

	Place_Tube(pars_tube, 0, 0, 0, 0, 0);
	Place_Tube(pars_tube, 0, 0, 0, 180, 0);

	return physWorld;
}

void Geometry::Place_Tube(G4GDMLParser* parser, int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{	
	auto tube_log = parser->GetWorldVolume()->GetLogicalVolume();
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);
	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), tube_log, "tube_PV", logicWorld, false, 0);
}

void Geometry::Parser_Init(G4GDMLParser* parser, std::string name)
{
	parser->Read(name);
}