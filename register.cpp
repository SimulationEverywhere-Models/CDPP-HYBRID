

#include "modeladm.h" 
#include "mainsimu.h"

//#include "function.h"
#include "functioneval.h"
#include "integrator.h"
#include "quantizer.h"

void MainSimulator::registerNewAtomics()
{

	//SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Function>() , "Function" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<FunctionEvaluator>() , "FunctionEvaluator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Integrator>() , "Integrator" ) ;
	SingleModelAdm::Instance().registerAtomic( NewAtomicFunction<Quantizer>() , "Quantizer" ) ;

}
