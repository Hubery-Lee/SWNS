/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-05-31 22:41:04
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-07-29 11:13:08
 */
#ifndef SWNSRunAction_h
#define SWNSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;
class G4Timer;

class SWNSRunAction: public G4UserRunAction
{
public:
    SWNSRunAction();
    virtual ~SWNSRunAction();

    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);

private:
    /*data*/
    G4Timer* fTimer;
};

#endif