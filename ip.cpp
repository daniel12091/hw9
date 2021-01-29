#include <iostream>
#include <string.h>
#include "ip.h"
#define ONES_VEC 0xffffffff 

using namespace std;


Ip::Ip(String pattern):Field(pattern),low(0), high(0){

}

bool Ip::set_value(String val){
	if(val.equals("\0")){
		return false;
	}
	String *out;
	size_t size=0;
	val.split("./",&out, &size );
	if(size!=5){
		return false;
	}
	int ip_vals[5];
	
	ip_vals[4]=out[4].to_integer();
	if(ip_vals[4]>32 || ip_vals[4]<0){ 
		delete[] out;
		return false;
	}
	if(ip_vals[4]==0){
		delete[] out;
		this->low=0;
		this->high= ONES_VEC;
		return true;
	}
	int ip_num=0;
	for(int i=0;i<(int)size-1;i++){
		ip_vals[i]=out[i].to_integer();
		if(ip_vals[i]>255 || ip_vals[i]<0){ 
			delete[] out;
			return false;
		}
		ip_num = ip_num | ip_vals[i]<<(8*(3-i));
	}

	int mask=ONES_VEC<<(32-ip_vals[4]);
	
	this->low=ip_num & mask;
	this->high=ip_num | (~mask);
	delete[] out;
	return true;
}

bool Ip::match_value(String val) const{
	if(val.equals("\0")){
		return false;
	}
	String *out;
	size_t size=0;
	val.split("./ ",&out, &size );
	if(size!=4){
		delete[] out;
		return false;
	}
	int ip_vals[4];
	unsigned int ip_num=0;
	for(int i=0;i<(int)size;i++){
		ip_vals[i]=out[i].to_integer();
		if(ip_vals[i]>255 || ip_vals[i]<0){ 
			delete[] out;
			return false;
		}
		ip_num = ip_num | ip_vals[i]<<(8*(3-i));

	}
	
	delete[] out;
	return ((ip_num<=this->high) && (ip_num>=this->low));
}

