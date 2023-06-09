#include "functioneval.h" 
#include "message.h"   
#include "mainsimu.h"

#define DEFAULT_INIT_VALUE  0
#define DEFAULT_LAST_VALUE  100
#define DEFAULT_CANT        10
#define DEFAULT_FREQ        0.001


/*******************************************************************
* FunctionEvaluator Name: FunctionEvaluator
* Description: constructor
********************************************************************/
FunctionEvaluator::FunctionEvaluator( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
{
  try {
    // Archivo de log del modelo
    logFileName = MainSimulator::Instance().getParameter( description(), "logFileName" );

    if ( logFileName != "" ) {
      openLogFile();
    }

    // cota inferior del intervalo
    string initVal( MainSimulator::Instance().getParameter( description(), "initialValue" ) );
    initValue = ( initVal == "" ? DEFAULT_INIT_VALUE : atof( initVal.data() ) );


    // cota superior del intervalo
    string lastVal( MainSimulator::Instance().getParameter( description(), "lastValue" ) );
    lastValue = ( lastVal == "" ? DEFAULT_LAST_VALUE : atof( lastVal.data() ) );


    if ( initValue > lastValue ) {
      throw MException( string( "Invalid interval [" ) + initValue + string( ", " ) + lastValue + string( "]" ) );
    }

    // cantidad de valores 
    string cant( MainSimulator::Instance().getParameter( description(), "cantValues" ) );
    cantValues = ( cant == "" ? DEFAULT_CANT : atof( cant.data() ) );

    if ( cantValues == 0 ) {
      cantValues = DEFAULT_CANT;
    }

    // funcion a evaluar
    string functionName( MainSimulator::Instance().getParameter( description(), "function" ) );

    fc =  Function::createFunction( functionName );

    // velocidad de emision
    string freq( MainSimulator::Instance().getParameter( description(), "evalFrequency" ) );
    evalFreq = ( freq == "" ? DEFAULT_FREQ : atof( freq.data() ) );


  } catch ( MException &e ) {
    e.print( cerr );  
    MTHROW( e ) ;
  }
}

/*******************************************************************
* FunctionEvaluator Name: ~FunctionEvaluator
* Destructor
********************************************************************/
FunctionEvaluator::~FunctionEvaluator()
{
  closeLogFile();
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &FunctionEvaluator::initFunction()
{
  x = initValue;
  inc = ( lastValue - initValue ) / cantValues;
  log( "\nFuncion   : " + fc->getFunctionInfo() );
  log( string( "\nIntervalo : [" ) + initValue + string( "," ) + lastValue + string( "]" ) );
  log( string( "\nCantidad de valores evaluados: " )  + cantValues );
  log( string( "\nIncremento: " )  + inc );
  log( string( "\nFrecuencia de evaluación : 1 valor/" ) + evalFreq + "seg" );
  log( "\n\n     x\t\t\tf(x)\n" );
  holdIn( active, Time::Zero );
  return *this ;
}


/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &FunctionEvaluator::externalFunction( const ExternalMessage &msg )
{
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &FunctionEvaluator::internalFunction( const InternalMessage & )
{
  // Si todavia quedan elementos del intervalo por evaluar...
  if ( x <= lastValue ) {
    holdIn( active, Time( static_cast< float >( evalFreq ) ) );
     
  } else {
    passivate();
  }
  return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &FunctionEvaluator::outputFunction( const InternalMessage &msg )
{
  // Evaluo la funcion
  double y = fc->f( x );
  log( Real( x ).asString() + "\t" + Real( y ).asString() + "\n" );
  sendOutput( msg.time(), out, y ) ; 
  // Incremento el valor a evaluar
  x += inc;
  return *this ;
}                                       

/*******************************************************************
* Function Name: openLogFile
********************************************************************/
Model &FunctionEvaluator::openLogFile()
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
Model &FunctionEvaluator::closeLogFile()
{
  if ( logFile ) {
    logFile.close();
  }
  return *this;
}

/*******************************************************************
* Function Name: log
********************************************************************/
Model &FunctionEvaluator::log( const string &msg )
{
  if ( logFile ) {
    logFile << msg;
  } else {
    cout << msg;
  }
  return *this;
}


