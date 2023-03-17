/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 11:33:29
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-08-15 18:52:14
 */
#include "SWNSDetectorConstruction.hh"
#include "SWNSActionInitialization.hh"
// #include "SWNSRunAction.hh"      //?
// #include "SWNSPrimaryGeneratorAction.hh"  //?
//mandatory class - physics some examples are showed bellow
// 参考物理过程
#include "QBBC.hh"
#include "QGS_BIC.hh"
#include "QGSP_BERT.hh"
#include "QGSP_BERT_HP.hh"
#include "QGSP_BIC.hh"
#include "QGSP_BIC_HP.hh"
#include "QGSP_BIC_AllHP.hh"
#include "QGSP_FTFP_BERT.hh"
#include "QGSP_INCLXX_HP.hh"
#include "FTF_BIC.hh"
#include "FTFQGSP_BERT.hh"
#include "FTFP_BERT.hh"
#include "FTFP_BERT_HP.hh"
#include "FTFP_BERT_ATL.hh" 
#include "FTFP_BERT_TRV.hh"
#include "FTFP_INCLXX_HP.hh"
#include "Shielding.hh"
#include "ShieldingLEND.hh"
#include "LBE.hh"

// 光过程
#include "G4OpticalPhysics.hh"

// 电磁过程
#include "G4EmStandardPhysics.hh"
#include "G4EmStandardPhysics_option1.hh"
#include "G4EmStandardPhysics_option2.hh"
#include "G4EmStandardPhysics_option3.hh"
#include "G4EmStandardPhysics_option4.hh"

// 读取物理过程
#include "istream"
#include "fstream"
#include "string"
#include "vector"

#include "G4GenericBiasingPhysics.hh"
#include "G4StepLimiterPhysics.hh"
#include "G4Types.hh"

//! easy to use
#include "G4PhysListFactory.hh"
#include "G4RunManagerFactory.hh"
#include "G4ScoringManager.hh"

//
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

//assitance
#include "G4Version.hh"
#include "Randomize.hh" //随机数这里产生

//system heads
#include <ctime> // initialize random seed

//====================================================================
// Un-comment this line for user defined score writer
//    #include "RE03UserScoreWriter.hh"
//====================================================================

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc, char **argv)
{
    // Instantiate G4UIExecutive if interactive mode
    G4UIExecutive *ui = nullptr;
    if (argc == 1)
    {
        ui = new G4UIExecutive(argc, argv);
    }

    //!------------
    // Choose the Random engine
    //
    // G4Random::setTheEngine(new CLHEP::RanecuEngine);

    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(0);
    CLHEP::HepRandom::setTheSeed(seed);
    // Run manager
    //
    // 自动获取核数，并可以通过第三个参数设置使用内核数
    auto *runManager = G4RunManagerFactory::CreateRunManager();
    G4int nThreads = G4Threading::G4GetNumberOfCores();
    if (argc == 3)
        nThreads = G4UIcommand::ConvertToInt(argv[2]);
    runManager->SetNumberOfThreads(nThreads);

    // !Activate UI-command base scorer see//example/extend/runAndEvent/RE03
    G4ScoringManager * scManager = G4ScoringManager::GetScoringManager();
    scManager->SetVerboseLevel(1);

    //====================================================================
    // Un-comment this line for user defined score writer
    //    scManager->SetScoreWriter(new RE03UserScoreWriter());
    //====================================================================

    // User Initialization classes (mandatory)
    //! construction detector
    runManager->SetUserInitialization(new SWNSDetectorConstruction);

    //! maybe changed, explore to understand G4  see //example/extended/physiclists/factory
    

    //读取物理过程
    std::ifstream phy("physiclists.txt");
    std::string physiclist_name;
    bool label;
    std::vector<std::string> phys_name;
    std::vector<bool> vlabel;
    std::string cbf; //读取注释
    char chd;        //注释标志符号
    while (!phy.eof())
    {
        chd = phy.peek();
        if (chd == '#' || chd == 0x20 || chd == 0xA)
        {                      //修复空行带来的bug,空行可能是" "或者"\n"
            getline(phy, cbf); //一次读取一行
        }
        else
        {
            phy >> physiclist_name >> label;
            phys_name.push_back(physiclist_name);
            vlabel.push_back(label);
        }
    }

    G4VModularPhysicsList *physicsList = 0;
    for (int i = 0; i < int(vlabel.size()); i++)
    {
        if (vlabel[i] > 0)
        {
            if (phys_name[i].compare("QBBC") == 0)
            {
                physicsList = new QBBC;
            }
            else if (phys_name[i].compare("QGS_BIC") == 0)
            {
                physicsList = new QGS_BIC;
            }else if (phys_name[i].compare("QGSP_BERT") == 0)
            {
                physicsList = new QGSP_BERT;
            }else if (phys_name[i].compare("QGSP_BERT_HP") == 0)
            {
                physicsList = new QGSP_BERT_HP;
            }else if (phys_name[i].compare("QGSP_BIC") == 0)
            {
                physicsList = new QGSP_BIC;
            }else if (phys_name[i].compare("QGSP_BIC_HP") == 0)
            {
                physicsList = new QGSP_BIC_HP;
            }else if (phys_name[i].compare("QGSP_BIC_AllHP") == 0)
            {
                physicsList = new QGSP_BIC_AllHP;
            }else if (phys_name[i].compare("QGSP_FTFP_BERT") == 0)
            {
                physicsList = new QGSP_FTFP_BERT;
            }else if (phys_name[i].compare("QGSP_INCLXX_HP") == 0)
            {
                physicsList = new QGSP_INCLXX_HP;
            }else if (phys_name[i].compare("FTF_BIC") == 0)
            {
                physicsList = new FTF_BIC;
            }else if (phys_name[i].compare("FTFQGSP_BERT") == 0)
            {
                physicsList = new FTFQGSP_BERT;
            }else if (phys_name[i].compare("FTFP_BERT") == 0)
            {
                physicsList = new FTFP_BERT;
            }else if (phys_name[i].compare("FTFP_BERT_HP") == 0)
            {
                physicsList = new FTFP_BERT_HP;
            }
            else if (phys_name[i].compare("FTFP_BERT_ATL") == 0)
            {
                physicsList = new FTFP_BERT_ATL;
            }
            else if (phys_name[i].compare("FTFP_BERT_TRV") == 0)
            {
                physicsList = new FTFP_BERT_TRV;
            }
            else if (phys_name[i].compare("FTFP_INCLXX_HP") == 0)
            {
                physicsList = new FTFP_INCLXX_HP;
            }
            else if (phys_name[i].compare("Shielding") == 0)
            {
                physicsList = new Shielding;
            }
            else if (phys_name[i].compare("ShieldingLEND") == 0)
            {
                physicsList = new ShieldingLEND;
            }
            else if (phys_name[i].compare("LBE") == 0)
            {
                physicsList = new LBE;
            }
            else if (phys_name[i].compare("G4EmStandardPhysics") == 0)
            {
                physicsList->ReplacePhysics(new G4EmStandardPhysics);
            }
            else if (phys_name[i].compare("G4EmStandardPhysics_option1") == 0)
            {
                physicsList->ReplacePhysics(new G4EmStandardPhysics_option1);
            }
            else if (phys_name[i].compare("G4EmStandardPhysics_option2") == 0)
            {
                physicsList->ReplacePhysics(new G4EmStandardPhysics_option2);
            }
            else if (phys_name[i].compare("G4EmStandardPhysics_option3") == 0)
            {
                physicsList->ReplacePhysics(new G4EmStandardPhysics_option3);
            }
            else if (phys_name[i].compare("G4EmStandardPhysics_option4") == 0)
            {
                physicsList->ReplacePhysics(new G4EmStandardPhysics_option4);
            }
            else if (phys_name[i].compare("OpticalPhysics") == 0)
            {
                // physicsList->SetWLSTimeProfile("delta");

                // physicsList->SetScintillationYieldFactor(1.0);
                // physicsList->SetScintillationExcitationRatio(0.0);

                // physicsList->SetMaxNumPhotonsPerStep(100);
                // physicsList->SetMaxBetaChangePerStep(10.0);

                // physicsList->SetTrackSecondariesFirst(kCerenkov, true);
                // physicsList->SetTrackSecondariesFirst(kScintillation, true);

                physicsList->RegisterPhysics(new G4OpticalPhysics);
            }
        }
    }

    phys_name.clear();
    vlabel.clear();
    phy.close();

    physicsList->RegisterPhysics(new G4StepLimiterPhysics());
    runManager->SetUserInitialization(physicsList);

    // User Action classes
    //
    //MT  runManager->SetUserAction(new ExTGPrimaryGeneratorAction);

    runManager->SetUserInitialization(new SWNSActionInitialization);

    // Run action that dumps GEANT4 in-memory geometry to text file
    //MT  runManager->SetUserAction(new SWNSRunAction); //?

    //-----------------------
    // Initialize visualization
    auto visManager = new G4VisExecutive;
    visManager->Initialize();

    // Get the pointer to the User Interface manager
    auto UImanager = G4UImanager::GetUIpointer();

    if (!ui) // batch mode
    {
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }
    else // interactive mode : define visualization and UI terminal
    {
        UImanager->ApplyCommand("/control/execute run.mac");
        ui->SessionStart();
        delete ui;
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program !

    delete visManager;
    delete runManager;

    return 0;
}