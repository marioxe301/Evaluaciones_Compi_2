# TODO

Crear un pequeño interprete en Bison para un lenguaje que soporta
sentencias de asignación y de salida en pantalla (print). Además
de eso el lenguaje también soportará expresiones aritmeticas con
suma, resta, multiplicación y división.

Las sentencias deberán estar separadas por fin de linea.

Tenga en cuenta que deberá una tabla de simbolos para el manejo de
identificadores.

Su implementación solo se enfocará en la parte de Bison, el lexer ya está 
dado.

Ejemplo:
x = (10 + 5)*2
y = (x + 10)
print x
print y

La salida de este pequeño programa debería ser:
30
40
