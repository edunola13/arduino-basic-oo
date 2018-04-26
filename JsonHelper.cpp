/*
Morse.cpp - Library for flashing Morse code. Created by David A. Mellis, November 2, 2007. Released into the public domain.
*/

//#include "WProgram.h"
#include <Arduino.h>
#include "JsonHelper.h"

String parseProperty(String* json, String property, uint8_t maxLength){
  String val= "\"" + property + "\":";
  int i= json->indexOf(val);
  if(i != -1){
    String subStr= json->substring(i + val.length() + 1, i + val.length() + 1 + maxLength + 1);
    i= subStr.indexOf("\"");
    subStr= subStr.substring(0, i);
    return subStr;
  }else{
    return "null";
  }
}
String parsePropertyTy2(String* json, String property, uint8_t maxLength){
  String val= property + "=";
  int i= json->indexOf(val);
  if(i != -1){
    String subStr= json->substring(i + val.length(), i + val.length() + maxLength + 1);
    i= subStr.indexOf("|");
    subStr= subStr.substring(0, i);
    return subStr;
  }else{
    return "null";
  }
}

//
//JsonInterface
String JsonInterface::propertyToJson(String name, String value, bool comillas, bool ultimo){
  if(tyJs == 1){
	String val= "\"" + name + "\": ";
	if(comillas){
	  val+= "\"" + value + "\"";        
	}else{
	  val+= value;
	}
	if(!ultimo){
	  val+=",";
	}
	return val;
  }else{
    String val= name + "=";
	val+= value + "|";
	return val;
  }
}

String JsonInterface::parseProperty(String* json, String property, uint8_t maxLength){
  if(tyJs == 1){
	String val= "\"" + property + "\":";
	int i= json->indexOf(val);
	if(i != -1){
	  String subStr= json->substring(i + val.length() + 1, i + val.length() + 1 + maxLength + 1);
	  i= subStr.indexOf("\"");
	  subStr= subStr.substring(0, i);
	  return subStr;
	}else{
	  return "null";
	}
  }else{
    String val= property + "=";
	int i= json->indexOf(val);
	if(i != -1){
	  String subStr= json->substring(i + val.length(), i + val.length() + maxLength + 1);
      i= subStr.indexOf("|");
      subStr= subStr.substring(0, i);
      return subStr;
	}else{
      return "null";
    }
  }
}

String JsonInterface::toJson(){
  if(tyJs == 1){
	String val= "{";
	//val+= this->jsonProperties();
	this->jsonProperties(val);
	val+= "}";
	return val;
  }else{
    String val= "";
	//val+= this->jsonProperties();
	this->jsonProperties(val);
	return val;
  }
}
