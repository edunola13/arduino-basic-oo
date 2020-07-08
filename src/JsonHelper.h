#ifndef JsonHelper_h
#define JsonHelper_h
//#include "WConstants.h"
#include <Arduino.h>

/**
 * Esta libreria sirve para que los objetos se puedan serializar a json y para que en base a un string se parseen sus valores
 * Incluye 2 clase:
 *  JsonInterface: De esta deben heredar las clases que nosotros queramos que sean serializables. Tiene metodos virtuales que hay que implementar
 *  TestJsonInterface: Esta clase sirve de ejemplo para mostrar como se deben completar los metodos a implementar
 *
 *  Note: La idea es parsiar solo un nivel de objetos, tal vez para pasar a json si se pueda pero para parsear no esta contemplado.
 *  Es importante notar tambien que para parsear todos los valores siempre van a tener que estar entre "", si no el parseo fallara. Ej: "numero": 1 (incorrecto), "numero": "1" (bien),
 *  despues se puede parsear a numero.
 */

String parseProperty(String* json, String property, uint8_t maxLength= 3);
String parsePropertyTy2(String* json, String property, uint8_t maxLength= 3);

class JsonInterface {
  protected:
    String propertyToJson(String name, String value, bool comillas, bool ultimo);
    //virtual String jsonProperties();
	  virtual void jsonProperties(String &value);

    String parseProperty(String* json, String property, uint8_t maxLength= 3);

  public:
	  uint8_t tyJs = 1;
    String toJson();

    virtual void parseJson(String* json);
};

#endif
