/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 14:54:11
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-07-29 10:34:00
 */

#ifndef SWNSDetectorConstruction_h
#define SWNSDetectorConstruction_h

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "vector"
using namespace std;

class G4tgrMessenger;
class SWNSDetectorConstruction: public G4VUserDetectorConstruction
{
private:
    /* data */
    G4tgrMessenger * fMessenger;
    G4LogicalVolume *logicVol;

public:
    SWNSDetectorConstruction(/* args */);
    ~SWNSDetectorConstruction();

    G4VPhysicalVolume* Construct();
    // void ConstructSDandField(vector<G4String> SDv);
    void ConstructSDandField();
    // void DefineOneSD(G4String SDname);
};
#endif