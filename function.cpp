#include "function.h" 

#include "message.h"   
#include "mainsimu.h"

/*******************************************************************
********************************************************************/
Function *Function::createFunction( const string &functionName )
{
  Function *fc;

  if ( functionName == "cos" ) {
    fc = new CosFunction();
  }
  else if ( functionName == "sin" ) {
    fc = new SinFunction();
  }
  else if ( functionName == "pow" ) {
    fc = new PowFunction();
  }
  else if ( functionName == "identity" ) {
    fc = new IdentityFunction();
  }
  else if ( functionName == "exp" ) {
    fc = new ExpFunction();
  }
  else if ( functionName == "sqrt" ) {
    fc = new SqrtFunction();
  }   
  else {
    FunctionException e;
    e.addText( "Function " + functionName + " not implemented" );
    throw e;
  }
  return fc;
}
