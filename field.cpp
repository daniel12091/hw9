#include <iostream>
#include <string.h>
#include "field.h"
#include "port.h"
#include "ip.h"

using namespace std;


Field::Field(String pattern, field_type type){

	this->type=type;
	String *check;
	size_t size;
	pattern.trim();
	pattern.split("= ", &check, &size);
	this->pattern=check[0];
	delete[] check;

}

Field::Field(String pattern){
	type=GENERIC;
	String *check;
	size_t size;
	pattern.trim();
	pattern.split("= ", &check, &size);

	if (check[0].equals("src-port")||check[0].equals("dst-port")){
		type=PORT;
	}
	else if (check[0].equals("src-ip")||check[0].equals("dst-ip")){
		type=IP;
	}

	this->pattern=check[0];

	delete[] check;


}
Field::~Field(){


}
field_type Field::get_type() const{

	return this->type;
}


bool Field::set_value(String val){


	if (this->type==IP){
		Ip *ip= (Ip*)this;
		return ip->set_value(val);
	}
	else if(this->type==PORT){
		Port *port=(Port*)this;
		return port->set_value(val);
	}
	return false;
}

bool Field::match_value(String val) const{

	if (this->type==IP){
		Ip *ip= (Ip*)this;
		return ip->match_value(val);
	}
	else if(this->type==PORT){
		Port *port=(Port*)this;
		return port->match_value(val);
	}
	return false;
}
bool Field::match(String packet){
	if(packet.equals("\0")){
		return false;
	}
	String *out;
	size_t size=0;
	packet.split("=, ",&out, &size );
	for(int i=0;i<=(int)size-2;i=i+2){
		if(this->pattern.equals(out[i])){
			bool ret_val= match_value(out[i+1]);
			delete[] out;
			return ret_val;
		}
	}

	delete[] out;

	return false;

}
