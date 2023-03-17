/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 14:55:32
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-09-15 15:21:53
 */

#include "SWNSActionInitialization.hh"
#include "SWNSPrimaryGeneratorAction.hh"
#include "SWNSRunAction.hh"

//--------------------------------------
SWNSActionInitialization::SWNSActionInitialization()
    : G4VUserActionInitialization()
{
}
//--------------------------------------
SWNSActionInitialization::~SWNSActionInitialization()
{
}
//--------------------------------------
void SWNSActionInitialization::BuildForMaster() const
{
    SetUserAction(new SWNSRunAction);
}
//--------------------------------------
void SWNSActionInitialization::Build() const
{
    SetUserAction(new SWNSPrimaryGeneratorAction);
    SetUserAction(new SWNSRunAction);
}
