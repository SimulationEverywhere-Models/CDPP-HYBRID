
Scripts

tester : este script contiene los casos de test mencionados en el informe. Los 
distintos parámetros de cada modelo atómico se encuentran especificados en los 
archivos tester_casoi.ma (con i nro. de caso). La salida de cada modelo 
(FunctionEvaluator, Quantizer e Integrator) quedará en el archivo cuyo nombre es 
<modelo>_casoi.log (los archivos de salida podrán configurarse en los archivos .ma)

Archivos de log

Los archivos de log que se encuentran en el directorio log corresponden a la salida 
de cada modelo atómico para cada uno de los casos ejecutados.

Fuentes

quantizer.h    - quantizer.cpp    : modelo atómico cuantificador
integrator.h   - integrator.cpp   : modelo atómico integrador
functioneval.h - functioneval.cpp : modelo atómico evaluador de funciones
function.h     - function.cpp     : clase soporte para funciones de evaluación implementadas

Informe

modelos CD++ para sistemas híbridos.doc