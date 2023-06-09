
Scripts

tester : este script contiene los casos de test mencionados en el informe. Los 
distintos par�metros de cada modelo at�mico se encuentran especificados en los 
archivos tester_casoi.ma (con i nro. de caso). La salida de cada modelo 
(FunctionEvaluator, Quantizer e Integrator) quedar� en el archivo cuyo nombre es 
<modelo>_casoi.log (los archivos de salida podr�n configurarse en los archivos .ma)

Archivos de log

Los archivos de log que se encuentran en el directorio log corresponden a la salida 
de cada modelo at�mico para cada uno de los casos ejecutados.

Fuentes

quantizer.h    - quantizer.cpp    : modelo at�mico cuantificador
integrator.h   - integrator.cpp   : modelo at�mico integrador
functioneval.h - functioneval.cpp : modelo at�mico evaluador de funciones
function.h     - function.cpp     : clase soporte para funciones de evaluaci�n implementadas

Informe

modelos CD++ para sistemas h�bridos.doc