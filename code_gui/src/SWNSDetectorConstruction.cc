/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 14:55:13
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-08-10 11:56:25
 */

#include "SWNSDetectorConstruction.hh"

#include "G4LogicalVolume.hh"
#include "G4SDManager.hh"

#include "G4tgrMessenger.hh"
#include "G4tgbVolumeMgr.hh"

#include "G4NistManager.hh"
// #include "CADMesh.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4CutTubs.hh"
#include "G4Cons.hh"            //锥形（体）
#include "G4Para.hh"            //平行六面体
#include "G4Trap.hh"            //通用梯形台
#include "G4Sphere.hh"          //球壳
#include "G4Orb.hh"             //球体
#include "G4Torus.hh"           //环面
#include "G4Polycone.hh"        //多锥体
#include "G4GenericPolycone.hh" //
#include "G4Polyhedra.hh"       //多面体
#include "G4EllipticalTube.hh"  //椭圆柱
#include "G4Ellipsoid.hh"       //椭球体
#include "G4EllipticalCone.hh"  //椭球锥
#include "G4Paraboloid.hh"      //抛物面
#include "G4Hype.hh"            //双曲面
#include "G4Tet.hh"             //四面体 tetrahedra
#include "G4TessellatedSolid.hh"
// 其他的扭曲结构，见BookForApplicationDevelopers

#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4PVReplica.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4AutoDelete.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
//--------------------------------------------
SWNSDetectorConstruction::SWNSDetectorConstruction(/* args */)
{
  fMessenger = new G4tgrMessenger;
}
//--------------------------------------------
SWNSDetectorConstruction::~SWNSDetectorConstruction()
{
  delete fMessenger;
}
//--------------------------------------------
G4VPhysicalVolume *SWNSDetectorConstruction::Construct()
{
  //------------------------------------------------
  // Define one or several text files containing the geometry description
  //------------------------------------------------
  G4String filename = "SWNSgeom.txt";
  G4tgbVolumeMgr *volmgr = G4tgbVolumeMgr::GetInstance();
  volmgr->AddTextFile(filename);

  //------------------------------------------------
  // Read the text files and construct the GEANT4 geometry
  //------------------------------------------------
  G4VPhysicalVolume *physiWorld = volmgr->ReadAndConstructDetector();

  //------------------------------------------------
  // Build another volume and place it in the text geometry
  //------------------------------------------------
  // G4Box *solid = new G4Box("mybox", 10. * cm, 10. * cm, 10. * cm);

  // G4Material *water = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");

  // // G4LogicalVolume *logicVol = new G4LogicalVolume(solid, water, "mybox", 0, 0, 0);
  // logicVol = new G4LogicalVolume(solid, water, "mybox", 0, 0, 0);
  // //----- Place the volume in the world of the text geometry
  // G4LogicalVolume *textWorldVol = physiWorld->GetLogicalVolume();

  // // NOTE: if you want to place your full text geometry in the C++ geometry,
  // //       you should use this G4LogicalVolume and place it in a C++ logical
  // //       volume
  // new G4PVPlacement(0,                          // no rotation
  //                   G4ThreeVector(0., -20., 0), // at (x,y,z)
  //                   logicVol,                   // its logical volume
  //                   "mybox",                   // its name
  //                   textWorldVol,               // its mother  volume
  //                   false,                      // no boolean operations
  //                   0);                         // copy number

  // //----- Place the volume inside a volume of the text geometry
  // G4LogicalVolume *textSphereVol =
  //     G4tgbVolumeMgr::GetInstance()->FindG4LogVol("Sphere", 1);
  // new G4PVPlacement(0,                        // no rotation
  //                   G4ThreeVector(0., 0., 0), // at (x,y,z)
  //                   logicVol,                 // its logical volume
  //                   "myBox2",                 // its name
  //                   textSphereVol,            // its mother  volume
  //                   false,                    // no boolean operations
  //                   1);                       // copy number

  return physiWorld;
}
//--------------------------------------------
// void SWNSDetectorConstruction::ConstructSDandField(vector<G4String> SDv)
// {
//   for (int i = 0; i < SDv.size(); i++)
//   {
//     DefineOneSD(SDv[i]);
//   }
// }
//--------------------------------------------
void SWNSDetectorConstruction::ConstructSDandField()
{
  // // DefineOneSD("det");
  // G4LogicalVolume *logicSD =
  //     G4tgbVolumeMgr::GetInstance()->FindG4LogVol("det", 0);

  // if (logicSD)
  // {
  //   G4SDManager *SDman = G4SDManager::GetSDMpointer();
  //   SWNSTrackSD *sd1 = new SWNSTrackSD(logicSD->GetName());
  //   SDman->AddNewDetector(sd1);
  //   logicSD->SetSensitiveDetector(sd1);
  // }
  // else
  // {
  //   G4Exception("DetectorConstruction::Construct()",
  //               "InvalidGeometry", JustWarning,
  //               "Volume does not exists in geometry: Chamber");
  // }
  // // logicVol->SetSensitiveDetector(aTrackSD);
}
// //--------------------------------------------
// void SWNSDetectorConstruction::DefineOneSD(G4String SDLog_V_name)
// {
//   // //------------------------------------------------
//   // // Sensitive detectors
//   // //------------------------------------------------
//   // // G4String trackerSDname = "SWNS/SensitiveDetector";
//   // // SWNSTrackSD *aTrackSD = new SWNSTrackSD(trackerSDname);
//   // SWNSTrackSD *aTrackSD = new SWNSTrackSD(SDLog_V_name);
//   // G4SDManager::GetSDMpointer()->AddNewDetector(aTrackSD);
//   // G4LogicalVolume *logicSD =
//   //     G4tgbVolumeMgr::GetInstance()->FindG4LogVol(SDLog_V_name, 0);

//   // G4String aWarning = "Volume does not exists in geometry:" + SDLog_V_name;
//   // cout<<aWarning<<endl;

//   // if (logicSD)
//   // {
//   //   cout<<"########## !!!!!!"<<endl;
//   //   // SetSensitiveDetector(SDLog_V_name, aTrackSD);
//   //   logicSD->SetSensitiveDetector(aTrackSD);
//   // }
//   // else
//   // {
//   //   G4Exception("SWNSDetectorConstruction::Construct()",
//   //               "InvalidGeometry", JustWarning,
//   //               aWarning);
//   // }
// }
