#include <iostream>
#include <string.h>
#include "string.h"
#include "input.h"
#include "ip.h"
#include "port.h"



using namespace std;

int main(int argc, char **argv){
	if (check_args( argc, argv)){
		return 1;
	}
	String pattern(argv[1]);
	size_t size;
	String *check=NULL;
	pattern.split("= ",&check,&size);
	Field field(argv[1]);
	if(field.get_type()==IP){
		Field *rule=new Ip(pattern);
		rule->set_value(check[1]);
		parse_input(*rule);
		delete rule;
	}
	if(field.get_type()==PORT){
		Field *rule=new Port(pattern);
		rule->set_value(check[1]);
		parse_input(*rule);
		delete rule;
	}
	delete[] check;

	return 0;
}


