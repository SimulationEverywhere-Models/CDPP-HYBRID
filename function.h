#ifndef _FUNCTION_H
#define _FUNCTION_H

#include <math.h>
#include <string>
#include "except.h"

/************************************
 * Funcion generica
 ************************************/

class Function {
  public:
    
    static Function *createFunction( const string & );

    virtual ~Function() {};
  
    virtual double  f( double x ) const = 0;
    
    virtual string  getFunctionName() const = 0;
    virtual string  getFunctionInfo() const { return getFunctionName(); };
            
  protected:
  
    Function() {};   

};  

/************************************
 * Excepcion
 ************************************/

class FunctionException : public MException {};

/************************************
 * Funcion coseno
 ************************************/

class CosFunction : public Function {

  public:

    double f( double x ) const;
    string getFunctionName()  const { return "f(x) = cos(x)"; }
    
};


/*** funciones inline ***/
inline
double CosFunction::f( double x ) const 
{
  return cos( x );
}

/************************************
 * Funcion seno
 ************************************/

class SinFunction : public Function {

  public:

    double f( double x ) const;
    string getFunctionName()  const { return "f(x) = sin(x)"; }
    
};


/*** funciones inline ***/
inline
double SinFunction::f( double x ) const 
{
  return sin( x );
}

/************************************
 * Funcion pow
 ************************************/

class PowFunction : public Function {

  public:

    double f( double x ) const;
    string getFunctionName()  const { return "f(x) = x^2"; }
    
};


/*** funciones inline ***/
inline
double PowFunction::f( double x ) const 
{
  return pow( x, 2 );
}

/************************************
 * Funcion identidad
 ************************************/

class IdentityFunction : public Function {

  public:

    double f( double x ) const;
    string getFunctionName()  const { return "f(x) = x"; }
    
};


/*** funciones inline ***/
inline
double IdentityFunction::f( double x ) const 
{
  return x;
}


/************************************
 * Funcion exp
 ************************************/

class ExpFunction : public Function {

  public:

    double f( double x ) const;
    string getFunctionName()  const { return "f(x) = e^x"; }
    
};


/*** funciones inline ***/
inline
double ExpFunction::f( double x ) const 
{
  return exp( x );
}


/************************************
 * Funcion sqrt
 ************************************/

class SqrtFunction : public Function {

  public:

    double f( double x ) const;
    string getFunctionName()  const { return "f(x) = x^1/2"; }
    
};


/*** funciones inline ***/
inline
double SqrtFunction::f( double x ) const 
{
  if ( x < 0 ) {
    FunctionException e;
    e.addText( string( "Invalid value " ) + x );
    throw e;
  }
  return sqrt( x );
}
#endif  
