# arduino-basic-oo
En este proyecto se encuentran clases y metodos que seran utilizadas de forma generica por demas librerias o proyectos.

Por un lado tenemos el modulo ComponentAbstract donde se definen clases de las que pueden extender todas las clases que implementen funcionalidad
de sensores, actuadores, controladores, etc. Con esta clase todas las que la hereden sabran guardarse en la EEPROM y van a respetar cierta interface
segun el tipo.
Tambien estan los metodos directos para que no haya necesidad de heredar en caso de querer usarlos de forma directa.

Despues tenemos modulos separados para actuadores, sensores y controladores donde heredan lo que corresponde y se hacen clases especificas.

## Deprecated
Usar lib ArduinoJson.

Por otro lado tenemos JsonHelper, esta libreria sirve para que los objetos se puedan serializar a json y para que en base a un string se parseen sus valores
La clase JsonInterface: De esta deben heredar las clases que nosotros queramos que sean serializables. Tiene metodos virtuales que hay que implementar

Nota: La idea es parsiar solo un nivel de objetos, tal vez para pasar a json si se pueda pero para parsear no esta contemplado.
Es importante notar tambien que para parsear todos los valores siempre van a tener que estar entre "", si no el parseo fallara. Ej: "numero": 1 (incorrecto), "numero": "1" (bien), despues se puede parsear a numero.
