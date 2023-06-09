
SCRIPTS

tester: is a script containing the test cases mentioned in the report.  
The distinct parameters of each atomic model are encountered specifically in the files 
tester_casoi.ma (with i as case number).  
The outputs from each model (FunctionEvaluator, Quantizer, and Integrator) were 
left in the file <model>_casoi.log (the output files can be specified in the .ma files).

LOG FILES

The log files in the log directory correspond to the output 
of each atomic model for each of the cases executed.

SOURCE

quantizer.h    - quantizer.cpp    : atomic model Quantizer
integrator.h   - integrator.cpp   : atomic model Integrator
functioneval.h - functioneval.cpp : atomic model FunctionEvaluator
function.h     - function.cpp     : support class for FunctionEvaluator

REPORT

"modelos CD++ para sistemas híbridos.doc"
ie. "CD++ models for hybrid systems"
