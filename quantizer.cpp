#include "quantizer.h" 
#include "message.h"   
#include "mainsimu.h"

#define DEFAULT_QUANTUM	1

/*******************************************************************
* Function Name: Quantizer
* Description: constructor
********************************************************************/
Quantizer::Quantizer( const string &name )
: Atomic( name )
,in( addInputPort( "in" ) )
,out( addOutputPort( "out" ) )
{
  try {
    // Archivo de log del modelo
    string logFileName = MainSimulator::Instance().getParameter( description(), "logFileName" );

    if ( logFileName != "" ) {
      openLogFile( logFileName );
    }

    // quantum
    string Quantum( MainSimulator::Instance().getParameter( description(), "quantum" ) );


    if ( Quantum == "" ) {
      quantum = DEFAULT_QUANTUM;
    } else {
      quantum = atof( Quantum.data() );
      if ( quantum <= 0 ) {
        throw MException( "Invalid quantum value : " + Quantum );
      }
    }
  } catch ( MException &e ) {
    e.print( cerr ); 
    MTHROW( e ) ;
  }
}

/*******************************************************************
* Function Name: ~Quantizer
* Destructor
********************************************************************/
Quantizer::~Quantizer()
{
  closeLogFile();
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Quantizer::initFunction()
{
  firstValue = true;  
  log( "\nValor Original\tValor emitido\n" );
  passivate(); 
  return *this ;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Quantizer::externalFunction( const ExternalMessage &msg )
{
  if ( msg.port() == in ) {
    if ( state() == passive ) {
      inputValue = msg.value();     
      // cuantifico el valor
      thresold = quantize( inputValue );
      holdIn( active, Time::Zero );
    }
  }
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Quantizer::internalFunction( const InternalMessage & )
{
  passivate(); 
  return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Quantizer::outputFunction( const InternalMessage &msg )
{
  if ( firstValue || ( thresold != lastThresold ) ) {
    firstValue   = false;
    lastThresold = thresold;
    // Emito valor
    sendOutput( msg.time(), out, thresold ) ;
  } 
  log( Real( inputValue ).asString() + "\t" + Real( thresold ).asString() + "\n" );
  return *this ;
}

/*******************************************************************
* Function Name: openLogFile
********************************************************************/
Model &Quantizer::openLogFile( const string &logFileName )
{
  logFile.open( logFileName.c_str() ); 

  if ( !logFile ) {
    MException e;
    e.addText( "Error opennig file " + logFileName );
    throw e;
  }
  return *this;
}

/*******************************************************************
* Function Name: closeLogFile
********************************************************************/
Model &Quantizer::closeLogFile()
{
  if ( logFile ) {
    logFile.close();
  }
  return *this;
}

/*******************************************************************
* Function Name: log
********************************************************************/
Model &Quantizer::log( const string &msg )
{
  if ( logFile ) {
    logFile << msg;
  } else {
    cout << msg;
  }
  return *this;
}

/*******************************************************************
* Function Name: quantize
********************************************************************/
double Quantizer::quantize( double fvalue )
{
  #define PREC 10000
  double value = fvalue / quantum;
  double lvalue = (long)( ceil( value * PREC ) / PREC );
  lvalue = lvalue * quantum;
  return lvalue;
}
