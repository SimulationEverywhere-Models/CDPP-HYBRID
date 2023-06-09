#include "integrator.h" 
#include "message.h"   
#include "mainsimu.h"

#define DEFAULT_TIME_UNIT  1

/*******************************************************************
* Function Name: Integrator
* Description: constructor
********************************************************************/
Integrator::Integrator( const string &name )
: Atomic( name )
, in( addInputPort( "in" ) )
, out( addOutputPort( "out" ) )
{
  try {

    // Archivo de log del modelo
    string logFileName = MainSimulator::Instance().getParameter( description(), "logFileName" );

    if ( logFileName != "" ) {
      openLogFile( logFileName );
    }

    // unidad para el delta de tiempo
    string unit( MainSimulator::Instance().getParameter( description(), "timeUnit" ) );


    if ( unit == "" ) {
      timeUnit = DEFAULT_TIME_UNIT;
    } else {
      timeUnit = atof( unit.data() );
      if ( timeUnit <= 0 ) {
        throw MException( "Invalid Time Unit value : " + unit );
      }
    }


  } catch ( MException &e ) {
    e.print( cerr );         
    MTHROW( e ) ;            
  }
}

/*******************************************************************
* Function Name: ~Integrator
* Destructor
********************************************************************/
Integrator::~Integrator()
{
  closeLogFile();
}

/*******************************************************************
* Function Name: initFunction
********************************************************************/
Model &Integrator::initFunction()
{
  integral = 0;
  incT     = 0;
  first    = true;
  log( "\nTiempo\tValor integrado\n" );
  passivate(); 
  return *this ;
}

/*******************************************************************
* Function Name: externalFunction
********************************************************************/
Model &Integrator::externalFunction( const ExternalMessage &msg )
{
  if ( msg.port() == in ) {
    if ( state() == passive ) {
      double inputValue, iValue, time;
      inputValue = msg.value();     
      time       = msg.time().asMsecs() * timeUnit;
      iValue     = integrate( inputValue, time );
      log( Real( time ).asString() + "\t" + Real( iValue ).asString() + "\n" );
      holdIn( active, Time::Zero );
    }
  }
  return *this;
}

/*******************************************************************
* Function Name: internalFunction
********************************************************************/
Model &Integrator::internalFunction( const InternalMessage & )
{
  passivate(); 
  return *this ;
}

/*******************************************************************
* Function Name: outputFunction
********************************************************************/
Model &Integrator::outputFunction( const InternalMessage &msg )
{
  sendOutput( msg.time(), out, integral ) ;
  return *this ;
}

/*******************************************************************
* Function Name: integrate - Integra por el metodo de Euler
********************************************************************/
double Integrator::integrate( double value, double time )
{ 
  // calculo el diferencial de tiempo
  double delta = time - incT;

  // integro el valor
  integral = integral + value * ( first ? 1 : delta );
  
  incT += delta; 
  first = false;

  return integral;
}

/*******************************************************************    
* Function Name: openLogFile                                            
********************************************************************/   
Model &Integrator::openLogFile( const string &logFileName )                                         
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
Model &Integrator::closeLogFile()                                        
{                                                                       
  if ( logFile ) {
    logFile.close();                                                    
  }
  return *this;                                                         
}                                                                       

/*******************************************************************    
* Function Name: log                                                    
********************************************************************/   
Model &Integrator::log( const string &msg )                              
{                    
  if ( logFile ) {
    logFile << msg;                                                     
  } else {
    cout << msg;                                                        
  }                                                                     
  return *this;                                                         
}                                                                       
