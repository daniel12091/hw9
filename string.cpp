#include <iostream>
#include <string.h>
#include "string.h"

using namespace std;



String::String():data(new char[1]),length(0){

	this->data[0]='\0';
}

String::String(const String &str) : data (new char[str.length+1]),
						           length(str.length){


	strcpy(this->data,str.data);

}

String::String(const char *str) {
	if(str==NULL||*str=='\0'){
		length=0;
		data=new char[1];
		data[0]='\0';
	}
	else{
		length = strlen(str);
		data=new char[length+1];
		strcpy(data,str);
	}
}

String::~String(){

	delete[] data;

}

String& String::operator=(const String &rhs){
	delete[] data;
	length=rhs.length;
	data = new char[length+1];
	strcpy (data,rhs.data);
	return *this;
}
String& String::operator=(const char *str){
	delete[] data;
	length=strlen(str);
	data = new char[length+1];
	strcpy (data,str);
	return *this;
}

bool String::equals(const String &rhs) const{

	return !strcmp(data,rhs.data);
}

bool String::equals(const char *rhs) const{

	return !strcmp(data,rhs);
}



void String::split(const char *delimiters, String **output, size_t *size) const{
	if(this->equals("\0")){
		*output=NULL;
		*size=0;
		return;
	}
	char* tmp= new char [strlen(data)+1];
	strcpy(tmp, data);
	int counter=0;
	for(char *p=strtok(tmp,delimiters); p!=NULL; p=strtok(NULL,delimiters)){
		counter++;
	}

	*size=counter;
	if(output==NULL|| !counter){
		delete[] tmp;
		return;
	}

	*(output) = new String[*size];
	strcpy(tmp, data);
	int i=0;
	for(char *p=strtok(tmp,delimiters); p!=NULL; p=strtok(NULL,delimiters)){
		(*output)[i] = String(p);
		i++;
	}
	delete[] tmp;

}

int String::to_integer() const{

	int count=0;
	for(int i=0;data[i]<='9' && data[i]>='0';i++){
		count=count*10+data[i]-'0';
	}
	return count;
}



String String::trim() const{

	if (length==0){
		return *this;
	}
	char *tmp= new char[length+1];
	strcpy(tmp,data);
	int begin=0;
	while(tmp[begin]==' '&& tmp[begin]!='\0'){
		begin++;
	}
	if (begin==(int)length){

		String str;
		delete[] tmp;
		return str;
	}
	for (int i=0;i<(int)length;i++){
		if(tmp[length-1-i]!=' '){
			tmp[length-i]='\0';
			break;
		}


	}

	String str(tmp+begin*sizeof(char));
	delete[] tmp;
	return str;
}

