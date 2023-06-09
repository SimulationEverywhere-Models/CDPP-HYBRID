#ifndef _INTEGRATOR_H
#define _INTEGRATOR_H

#include <fstream.h>
#include "atomic.h"  
#include "except.h" 


#define INTEGRATOR_CLASS_NAME	 "Integrator"

class Integrator : public Atomic {
  public:
  
    Integrator( const string &name = INTEGRATOR_CLASS_NAME );    
    ~Integrator();
  
    virtual string className() const { return INTEGRATOR_CLASS_NAME;}
  
  protected:
  
    Model    &initFunction() ;
    Model    &externalFunction( const ExternalMessage & );
    Model    &internalFunction( const InternalMessage & );
    Model    &outputFunction( const InternalMessage & );
  
    double   integrate( double value, double time );
  
    Model    &openLogFile( const string & );
    Model    &closeLogFile();
    Model    &log( const string & );
  
  
  private:
  
    Port      &in;      // port de entrada ...
    Port      &out;     // ... y de salida
    double    integral; // integral	
    double    incT;     // diferencial de tiempo
    double    timeUnit; // unidad del delta de tiempo
    bool      first;    
    ofstream  logFile;  // log file

};  


#endif  
