/*
 * @Descripttion: 
 * @version: 
 * @Author: Hubery-Lee
 * @Date: 2021-07-13 14:54:57
 * @E-mail: hrbeulh@126.com
 * @LastEditors: Hubery-Lee
 * @LastEditTime: 2021-07-13 15:40:42
 */
#ifndef SWNSActionInitialization_h
#define SWNSActionInitialization_h 

#include "G4VUserActionInitialization.hh"

class SWNSActionInitialization:public G4VUserActionInitialization
{
public:
    SWNSActionInitialization();
    virtual ~SWNSActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};
#endif