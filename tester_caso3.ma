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
logFileName   : functioneval_caso3.log

[quantizer]
quantum      : 0.1
logFileName  : quantizer_caso3.log

[integrator]
timeUnit     : 0.001 
logFileName  : integrator_caso3.log
