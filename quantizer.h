#ifndef _QUANTIZER_H
#define _QUANTIZER_H

#include <fstream.h>
#include <strstream.h>
#include "atomic.h"  
#include "except.h" 

#define QUANTIZER_CLASS_NAME	 "Quantizer"

class Quantizer : public Atomic {
  public:
    Quantizer( const string &name = QUANTIZER_CLASS_NAME );    
    ~Quantizer();
  
    virtual string className() const { return QUANTIZER_CLASS_NAME;}
  
  protected:
  
    Model &initFunction() ;
    Model &externalFunction( const ExternalMessage & );
    Model &internalFunction( const InternalMessage & );
    Model &outputFunction( const InternalMessage & );
  
    double  quantize( double value );
  
    Model &openLogFile( const string & );
    Model &closeLogFile();
    Model &log( const string & );
   
  
  private:
    const Port  &in;            // port de entrada ...
    Port        &out;           // ... y de salida
    double      quantum;        // quantum 
    double      inputValue;     // valor a cuantificar
    double      thresold;       // valor del umbral
    double      lastThresold;   // ultimo valor de umbral
    bool        firstValue;     // primer valor recibido
    ofstream    logFile;        // log file
};  


#endif  
