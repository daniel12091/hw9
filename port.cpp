#include <iostream>
#include "port.h"


using namespace std;


Port::Port(String pattern):Field(pattern){

	range[0]=0;
	range[1]=0;
}
bool Port::set_value(String val){

	String *out;
	size_t size=0;

	val.split(" -",&out,&size);
	if(size==2){
		this->range[0]=out[0].to_integer();
		this->range[1]=out[1].to_integer();
		if (range[0]>range[1]){
			delete[] out;
			return false;
		}
	}

	delete[] out;
	return true;
}


bool Port::match_value(String val) const{

	int check_value= val.to_integer();
	return (check_value>=this->range[0]&&check_value<=this->range[1]);
}
