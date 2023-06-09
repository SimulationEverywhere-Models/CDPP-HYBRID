[top]
components : function@FunctionEvaluator quantizer@Quantizer integrator@Integrator
in : 
out : 
Link : 
Link : out@function in@quantizer
Link : out@quantizer in@integrator

[function]
initialValue  : 0 
lastValue     : 1 
cantValues    : 1000 
function      : identity 
evalFrequency : 0.001
logFileName   : functioneval_caso4.log

[quantizer]
quantum      : 0.01
logFileName  : quantizer_caso4.log

[integrator]
timeUnit     : 0.001 
logFileName  : integrator_caso4.log
