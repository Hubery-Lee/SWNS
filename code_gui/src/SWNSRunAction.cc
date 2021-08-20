/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-05-31 22:41:52
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-08-07 13:22:14
 */
#include "SWNSRunAction.hh"
//#include "g4csv.hh"  //! for scoring to file
#include "g4root.hh"
#include "G4TScoreHistFiller.hh"  //! for scoring to file

#include "G4Timer.hh"
#include "G4RunManager.hh"
#include "G4Run.hh"
// #include "G4AccumulableManager.hh"
#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

SWNSRunAction::SWNSRunAction()
    : G4UserRunAction(),fTimer(0)
{
  // count time
  fTimer = new G4Timer;

  // set printing event number per each event
  G4RunManager::GetRunManager()->SetPrintProgress(1000);
    
  // Create analysis manager
  // The choice of analysis technology is done via selectin of a namespace
  // in B4Analysis.hh
  auto analysisManager = G4AnalysisManager::Instance();
  G4cout << "Using " << analysisManager->GetType() << G4endl;

  auto histFiller = new G4TScoreHistFiller<G4AnalysisManager>;
  // analysisManager->CreateH1("Primary Generator Fluence", "Primary Generator Fluence", 1000, 0, 15.0* MeV);
}

SWNSRunAction::~SWNSRunAction()
{
  delete G4AnalysisManager::Instance();
}

void SWNSRunAction::BeginOfRunAction(const G4Run * aRun)
{
  //Time count start
  G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
  fTimer->Start();

  // Get analysis manager
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile();
  // Open an output file
  //
  // G4String fileName = "SDST";
  // analysisManager->OpenFile(fileName);


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SWNSRunAction::EndOfRunAction(const G4Run * aRun)
{
  auto analysisManager = G4AnalysisManager::Instance();

  // save histograms & ntuple
  //
  analysisManager->Write();
  analysisManager->CloseFile();

  // Time count stop
  fTimer->Stop();
  G4cout << "number of event = " << aRun->GetNumberOfEvent()
         << " " << *fTimer << G4endl;

}
