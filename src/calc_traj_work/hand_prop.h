#ifndef HAND_PROP_H
#define HAND_PROP_H

#include <string>

typedef struct Hand_Prop_s
{
	std::string name ;
	std::string propertyNumber ;
	std::string activity ;
	float stallForce ;
	float unloadedSpeed ;

} Hand_Prop ;

#endif // HAND_PROP_H
