#include <Geometry.hh>
#include <G4VisAttributes.hh>

Geometry::Geometry()
{
	parser = new G4GDMLParser();
	nist = G4NistManager::Instance();

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
	parser->Read("geometry/name.gdml");

	Place_Section(96, 0, 96, 0, 0);
	Place_Section(96, 0, -96, 180, 0);
	Place_Section(-96, 0, 96, 180, 180);
	Place_Section(-96, 0, -96, 0, 180);

	Place_Tube(496, 0, 0, 0, 0);
	Place_Tube(-496, 0, 0, 0, 0);
	Place_Tube(0, 0, 496, 0, 90);
	Place_Tube(0, 0, -496, 0, 90);

	return physWorld;
}

void Geometry::Place_Section(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	Place_Tube_Ring(PointX, PointY, PointZ, RotateX, RotateY);
	Place_Tube_Vacuum(PointX, PointY, PointZ, RotateX, RotateY);
	Place_Magnet(PointX, PointY, PointZ, RotateX, RotateY);
}

void Geometry::Place_Tube(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	Place_Straight_Tube_Ring(PointX, PointY, PointZ, RotateX, RotateY);
	Place_Straight_Tube_Vacuum(PointX, PointY, PointZ, RotateX, RotateY);
}


void Geometry::Place_Straight_Tube_Ring(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto straight_tube_ring = parser->GetVolume("straight_tube_ring");
	straight_tube_ring->SetVisAttributes(G4Colour::Blue());

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), straight_tube_ring, "straight_tube_ring_PV", logicWorld, false, 0);
}

void Geometry::Place_Straight_Tube_Vacuum(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto straight_tube_vacuum = parser->GetVolume("straight_tube_vacuum");
	straight_tube_vacuum->SetVisAttributes(G4Colour::Yellow());

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), straight_tube_vacuum, "straight_tube_vacuum_PV", logicWorld, false, 0);
}

void Geometry::Place_Tube_Ring(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{	
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto tube_ring = parser->GetVolume("tube_ring");
	tube_ring->SetVisAttributes(G4Colour::Blue());
	
	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), tube_ring, "tube_ring_PV", logicWorld, false, 0);
}

void Geometry::Place_Tube_Vacuum(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto tube_vacuum = parser->GetVolume("tube_vacuum");
	tube_vacuum->SetVisAttributes(G4Colour::Yellow());

	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), tube_vacuum, "tube_vacuum_PV", logicWorld, false, 0);
}

void Geometry::Place_Magnet(int PointX, int PointY, int PointZ, int RotateX, int RotateY)
{
	G4RotationMatrix* rotm = new G4RotationMatrix();
	rotm->rotateX(RotateX * deg);
	rotm->rotateY(RotateY * deg);

	auto magnet = parser->GetVolume("magnet");
	magnet->SetVisAttributes(G4Colour::Red());
	magnet->SetMaterial(nist->FindOrBuildMaterial("G4_Pb"));
	
	new G4PVPlacement(rotm, G4ThreeVector(PointX * cm, PointY * cm, PointZ * cm), magnet, "magnet_PV", logicWorld, false, 0);
}