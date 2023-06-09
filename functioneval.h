#ifndef _FUNCTIONGEN_H
#define _FUNCTIONGEN_H

#include <fstream.h>
#include "atomic.h"  
#include "except.h" 
#include "function.h"

#define FUNCTIONEVAL_CLASS_NAME	 "FunctionEvaluator"

class FunctionEvaluator : public Atomic {
  public:
    FunctionEvaluator( const string &name = FUNCTIONEVAL_CLASS_NAME );   
    ~FunctionEvaluator();
  
    virtual string  className() const { return FUNCTIONEVAL_CLASS_NAME; }
  
       
  protected:
  
    Model &initFunction() ;
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const InternalMessage & );
  
    Model &openLogFile();
    Model &closeLogFile();
    Model &log( const string & );
  
  private:
    Port        &in;
    Port        &out;  
    double      initValue;      // cota inferior del intervalo de evaluacion
    double      lastValue;      // cota superior del intervalo de evaluacion
    double      inc;            // incremento en el intervalo
    double      cantValues;     // cantidad de valores a evaluar
    double      x;              // valor evaluado
    double      evalFreq;       // frecuencia de evaluacion
    Function    *fc;            // funcion a evaluar
    string      logFileName;    // log file name
    ofstream    logFile;        // log file
};  


#endif  
