[top]
components : function@FunctionEvaluator quantizer@Quantizer integrator@Integrator
in : 
out : 
Link : 
Link : out@function in@quantizer
Link : out@quantizer in@integrator

[function]
initialValue  : 0 
lastValue     : 6.2832 
cantValues    : 1000
function      : sin 
evalFrequency : 0.001
logFileName   : functioneval_caso2.log

[quantizer]
quantum      : 0.001
logFileName  : quantizer_caso2.log

[integrator]
timeUnit     : 0.0062832 
logFileName  : integrator_caso2.log
