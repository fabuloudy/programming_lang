#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <stack>
using namespace std;
//class Poliz;
class Lex_Analyze{
	int flag = 1;
	static string check16(const string &s);
	static string check10(const string &s);
	static string checkID(const string &s);
	static string istype(const string s);	
	int iskav(int c);
	int ispoint(int c);
	int isoper(int c);
	int isspace(int c);

public:
	struct leks{
		string type;
		string word;
		static leks *make(const string &s){
			leks *object = new leks[1];
			object -> word = s;
			object -> type = istype(s);
			return object;
		}
	};
	void analyze_leks(vector <leks*> &v);
};
	



string Lex_Analyze::check16(const string &s){
	int len = s.length();
		for (int i = 2; i<len; i++){
			if (!(((s[i] <= 'F') && (s[i] >= 'A')) || ((s[i] >= 'a') && (s[i] <= 'f')) || ((s[i] >= '0') && (s[i] <= '9')))){	
				throw s + " : error in \'" + s[i] + "\' symbol for hexadecimal\n";
			}
		}
	return "HEXADECIMAL";
}
string Lex_Analyze::check10(const string &s){
	int len = s.length();
		for (int i = 0; i<len; i++){
			if (!((s[i] <= '9') && (s[i] >='0'))){
				throw s + " : error in \'" + s[i] + "\' symbol for decimal\n";

			}
		}
	return "DECIMAL";
}
string Lex_Analyze::checkID(const string &s){
	int len = s.length();
		for (int i = 1; i<len; i++){
			if ((s[i] == '\'')){
				throw  s + " : error in \'" + s[i+1] + "\' literal symbol for identificator\n";

			}
		}
		if (((s[0] <= 'z') && (s[0] >='a')) || ((s[0] <='Z') && (s[0] >= 'A'))){
			return "ID";
		} else { 
			throw s + " : incorrect identificator!\n";
		}
}

			

string Lex_Analyze::istype(const string s){
	if (!((s[0] >= '0') && (s[0] <= '9'))){
		if (s == "true" || s == "false"){
			return "WBOOL";
		}
		if ((s == "int") || (s == "break") || (s == "for") || (s == "if") || (s == "while") || (s == "read") || ( s == "string") || (s == "bool") || (s == "write") || (s == "do") || (s == "else")){
			if (s == "string" || s == "bool" || s == "int"){
					return "TYPE";
			}
			return "KEYW";
		} else if (s == "program"){
			return "PROGRAM";
		} else if (s == "not" || s == "or" || s == "and"){ 
			return "LOG OPER";
		} else {
			if (s[0] == '<'){
				if (s[1] == '\0') {
					return "OPER";
				}
				if (s[1] == '=') {
					return "OPER";
				}
/*				if (s[1] == '='){
					return "AND EQUAL";
				}*/
			}	
			if ((s[0] == '/') || (s[0] == '%')) {
					return "OPER";
			}
			if (s[0] == '+'){
				return "OPER";
			}
			if (s[0] == '-'){
				return "OPER";
			}
			if (s[0] == '*'){
				return "OPER";
			}
			if (s[0] == '='){
//				cout << "NE PRAVDA" << endl;
				if (s[1] == '\0'){
					return "OPER";
				}
				if (s[1] == '='){
					return "OPER";
				}
			}
			if (s[0] == '>'){
				if (s[1] == '\0') {
					return "OPER";
				}
				if (s[1] == '=') {
					return "OPER";
				}
			}	
			if (s[0] == '!'){
				if (s[1] == '='){
					return "OPER";
				} else {
					cout << "ERROR" << endl;
					exit(0);
				}
			}
			if (s[0] == ';'){
				return "POINT";
			}
			if (s[0] == '('){
				return "BRAC";
			}
			if (s[0] == ')'){
				return "BRAC";
			}
			if (s[0] == '{'){
				return "BRAC";
			}
			if (s[0] == '}'){
				return "BRAC";
			}
			if (s[0] == ','){
				return "POINT";
			}
			return checkID(s);
		}
	} else { 
		if ((s[0] >= '0') && (s[0] <= '9')){
			if (s[0] == '0'){
				if ((s[1] == 'x') || (s[1] == 'X')){
					return check16(s);
				} else {
					if (s.length() != 1){
						throw  s + " : error : incorrect input! (type does not exist)\n";
					} else {
						return check10(s);
					}
				
				} 
			} else {
					return check10(s);
			}
		}
	}
}

int Lex_Analyze::isoper(int c){
	if ((c == '/') || (c == '%') || (c == '*') || (c == '+') || (c == '-')){
//		cout << "ZASHOL" << endl;
	/*	if (c == '/'){
			flag = 0;
		}*/
		return 3;
	}
	if ((c == '<') || (c == '>') || (c == '=') || (c == '!')){
		return 1;
	} 
	return 0;
}

int Lex_Analyze::isspace(int c){
	if ((c == ' ') || (c == '\n') || (c == 0x09)){
		if (c == '\n'){
			if (!flag) { flag = 1;}
		}
		return 2;
	} else {
		return 0;
	}
}

int Lex_Analyze::ispoint(int c){
	if ((c == ';') || (c == '(') || (c == ')') || (c == '{') || (c == '}') || (c == ',')){
		return 3;
	} else {
		return 0;
	}

}
int Lex_Analyze::iskav(int c){
	if (c == '"'){
		return 4;
	} else {
		return 0;
	}
}

void Lex_Analyze::analyze_leks(vector <leks*> &v){
//	vector <leks*> v;
	int c;
	int a;
	int b = 0;
//	int check = 1;
	while ((b == -1) || ((c = getchar()) != EOF)){
		if (b == -1) { c = a;}
		b = 0;
//		string s = "";
//		cout << c << endl;
		/*if ((!flag) && (check)){
			if (c != '/'){
				flag = 1;
			}
			check = 0;
		}*/
		int i = 0;
		string s;
		int check = 0;
		while (flag && !(check = isspace(c)) && !(check = isoper(c)) && !(check = ispoint(c)) && (c != EOF) && !(check = iskav(c))){
//			cout << check << endl;
			s += (char) c;
			i++;
			c = getchar(); 		
		}
		if (i != 0){
			string s1 = s;
//		cout << s << "<where word" <<endl;
			v.push_back(leks::make(s1));
		}
		s = "";
//		cout << check << endl;
		if (check == 4){
			string s2;
			int j = 0;
			c = getchar();
			while (c != '"'){
//				cout << "lol"<< endl;
				s2 += (char) c;
				j++;
			c = getchar();
			if (c == EOF){
				throw string("CLOSE KAVYCHKA!\n");
			} 		
			}
			if (j != 0){
				string s1 = s2;
//		cout << s << "<where word" <<endl;
				leks *litera = new leks[1];
				litera -> type = "STRING CONST";
				litera -> word = s1;
				v.push_back(litera);
			}
		}
	
		if (check == 3){
			if (flag){
				string r;
				r += (char) c;
				string s2 = r;
				v.push_back(leks::make(s2));
			}
		}
		if (check == 1){
			if (flag){
				a = getchar(); 
				if (a != '='){
					b = -1;
					string r;
					r += (char) c;
					string s2 = r;
					v.push_back(leks::make(s2));

				} else {
					string r;
					r += (char) c;
					r += (char) a;
					string s3 = r;
					if (s3 != "//"){ 
						v.push_back(leks::make(s3));
					} else { flag = 0;}
				}
			}
		}

	}
	leks *zero = new leks[1];
	zero -> word = "";
	zero -> type = "VOID";
	v.push_back(zero);
	int i = 0;
	if (v.size() == 0){
		return;
	}
//	cout << "FUH" << endl;
	
/*	while (v[i] != v.back()){
		cout <<v[i] -> type<< ": " << v[i] -> word << endl;
		i++;
	}
	cout <<v[i] -> type<< ": " << v[i] -> word << endl;
*/	
/*	catch (int a){
		cout << "ERROR" << endl;
	}*/
/*	i = 0;
	while (v[i] != v.back()){
		delete [] (v[i]);
		i++;
	}
	delete [] (v[i]);
*/
	return;
}

class Poliz{
public:
	struct var{
		string name;
		enum var_type{BOOL, STRING, INT} t;
		int ivalue;
		string svalue;
		var(string s, var_type tip, string begin): name(s),t(tip),svalue(begin){}
		var(string s, var_type tip, int begin):name(s),t(tip),ivalue(begin){}
	};
	struct assm{
		enum assm_type{BOOL, STRING, INT, OP, NUM, ID_ADD, VAL}type;
		int ivalue;
		string svalue;
		assm(assm_type tip = OP, int ival = 0, string sval = ""):type(tip),ivalue(ival),svalue(sval){}
	};
 	vector <var> table;
	vector <assm> queue;
	void AddTable(string type1, string name1, int value){
		var::var_type ti;
		if(type1 == "int"){
			ti = var::INT;
		} else if(type1 == "bool"){
			ti = var::BOOL;
		} else if(type1 == "string"){
			ti = var::STRING;
		}
		table.push_back(var(name1,ti,value));
	}
	void AddTable(string name1, string value){
		table.push_back(var(name1,var::STRING,value));
	}
	void dump() {
		for (int i = 0; i< table.size(); ++i){
			cout<<table[i].name<<" "<<table[i].t<<" "<<table[i].ivalue<<" "<<table[i].svalue<<endl;
		}
	}
	void dump2() {
		for (int i = 0; i< queue.size(); ++i){
			cout<< i << " "<<queue[i].type<<" "<<queue[i].ivalue<<" "<<queue[i].svalue<<endl;
		}
	}
	void exec();

};

void Poliz::exec(){
	stack <assm> values;
	int index = 0;
	assm i,j;
	int size = queue.size();
	assm curr;
	while (index < size){
		
		curr = queue[index];
		index++;
		if (curr.type == assm::VAL){
			switch (table[curr.ivalue].t){
				case var::BOOL:
					values.push(assm(assm::BOOL,table[curr.ivalue].ivalue,""));
					break;
				case var::STRING:
					values.push(assm(assm::STRING,0,table[curr.ivalue].svalue));
					break;
				case var::INT:
					values.push(assm(assm::INT,table[curr.ivalue].ivalue,""));
			} 
		}
		else if (curr.type != assm::OP){
			values.push(curr);
		}
		else {
			if (curr.svalue == "&-" || curr.svalue == ";" || curr.svalue == "J" || curr.svalue == "read" || curr.svalue == "write"){
				if (values.size() < 1){
					throw string("not enough operands for unary operation\n");
				}
			} else {
				if (values.size()<2){
					throw string("not enough operands for binary operation\n");
				}
			}
			if (curr.svalue == "="){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != assm::ID_ADD){
					throw string("incorrect assignment\n");
				} 
				if ((int)table[j.ivalue].t != (int)i.type){
					throw string("type mismatch\n");	
				}
				switch (i.type){
					case assm::INT:
						table[j.ivalue].ivalue = i.ivalue;
						break;
					case assm::BOOL:
						table[j.ivalue].ivalue = i.ivalue;
						break;

					case assm::STRING:
						table[j.ivalue].svalue = i.svalue;
				} 
				values.push(i);
				
			}
			else if (curr.svalue == "+"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"+\" for boolean\n");
				}
				switch (i.type){
					case assm::INT:
						values.push(assm(assm::INT,j.ivalue + i.ivalue,""));
						break;
					case assm::STRING:
						values.push(assm(assm::STRING,0,j.svalue + i.svalue));
				} 

				
			}
			else if (curr.svalue == "-"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"-\" for boolean\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"-\" for string\n");
				}
				values.push(assm(assm::INT,j.ivalue - i.ivalue,""));
			}
			else if (curr.svalue == "*"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"*\" for boolean\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"*\" for string\n");
				}
				values.push(assm(assm::INT,j.ivalue * i.ivalue,""));
			}
			else if (curr.svalue == "/"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"/\" for boolean\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"/\" for string\n");
				}
				values.push(assm(assm::INT,j.ivalue / i.ivalue,""));

			}
			else if (curr.svalue == "%"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"%\" for boolean\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"%\" for string\n");
				}
				values.push(assm(assm::INT,j.ivalue % i.ivalue,""));

			}
			else if (curr.svalue == "<"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"<\" for boolean\n");
				}
				switch (i.type){
					case assm::INT:
						values.push(assm(assm::BOOL,j.ivalue < i.ivalue,""));
						break;
					case assm::STRING:
						values.push(assm(assm::BOOL,j.svalue < i.svalue,""));
				} 


			}
			else if (curr.svalue == ">"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \">\" for boolean\n");
				}
				switch (i.type){
					case assm::INT:
						values.push(assm(assm::BOOL,j.ivalue > i.ivalue,""));
						break;
					case assm::STRING:
						values.push(assm(assm::BOOL,j.svalue > i.svalue,""));
				} 

			}
			else if (curr.svalue == "<="){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \"<=\" for boolean\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"<=\" for string\n");
				}
				values.push(assm(assm::BOOL,j.ivalue <= i.ivalue,"")); 

			}
			else if (curr.svalue == ">="){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::BOOL){
					throw string("incorrect operation \">=\" for boolean\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \">=\" for string\n");
				}
				values.push(assm(assm::BOOL,j.ivalue >= i.ivalue,"")); 

			}
			else if (curr.svalue == "=="){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				switch (i.type){
					case assm::INT:
						values.push(assm(assm::BOOL,j.ivalue == i.ivalue,""));
						break;
					case assm::BOOL:
						values.push(assm(assm::BOOL,((j.ivalue !=0 && i.ivalue !=0) || (j.ivalue == 0 && i.ivalue == 0)) ? 1 : 0,""));
						break;
					case assm::STRING:
						values.push(assm(assm::BOOL,j.svalue == i.svalue,""));
				} 
 

			}
			else if (curr.svalue == "!="){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				switch (i.type){
					case assm::INT:
						values.push(assm(assm::BOOL,j.ivalue != i.ivalue,""));
						break;
					case assm::BOOL:
						values.push(assm(assm::BOOL,((j.ivalue !=0 && i.ivalue !=0) || (j.ivalue == 0 && i.ivalue == 0)) ? 0 : 1,""));
						break;
					case assm::STRING:
						values.push(assm(assm::BOOL,j.svalue != i.svalue,""));
				} 
 

			}
			else if (curr.svalue == "J"){
				i = values.top();
				values.pop();
				if (i.type != assm::NUM){
					throw string("incorrect argument for unconditional jump\n");
				}
				index = i.ivalue;
			}
			else if (curr.svalue == "JT"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (i.type != assm::NUM){
					throw string("incorrect argument for jump if true\n");
				}
				if (j.type != assm::BOOL){
					throw string("incorrect argument for jump if true\n");
				}
				if (j.ivalue != 0){
					index = i.ivalue;
				}

			}
			else if (curr.svalue == "JF"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (i.type != assm::NUM){
					throw string("incorrect argument for jump if true\n");
				}
				if (j.type != assm::BOOL){
					throw string("incorrect argument for jump if true\n");
				}
				if (j.ivalue == 0){
					index = i.ivalue;
				}

			}
			else if (curr.svalue == ";"){
				values.pop();
			}
			else if (curr.svalue == "read"){
				i = values.top();
				values.pop();
				if (i.type != assm::ID_ADD){
					throw string("incorrect argument for read\n");
				}
				if (table[i.ivalue].t == var::STRING){
					string s;
					cin >> s;
					table[i.ivalue].svalue = s;
				}
				else if (table[i.ivalue].t == var::INT){
					int k;
					cin >> k;
					table[i.ivalue].ivalue = k;
				}
				else if (table[i.ivalue].t == var::BOOL){
					int k;
					cin >> k;
					table[i.ivalue].ivalue = k;
				}


				
			}
			else if (curr.svalue == "write"){
				i = values.top();
				values.pop();
				switch (i.type){
					case assm::INT:
						cout << i.ivalue << endl;
						break;
					case assm::BOOL:
						if (i.ivalue == 0){
							cout << "false" << endl;
						} else {
							cout << "true" << endl;
						}
						break;
					case assm::STRING:
						cout << i.svalue << endl;
				} 

				
			}
			else if (curr.svalue == "and"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::INT){
					throw string("incorrect operation \"and\" for int\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"and\" for string\n");
				}
				values.push(assm(assm::BOOL,j.ivalue && i.ivalue,"")); 
	

			}
			else if (curr.svalue == "or"){
				i = values.top();
				values.pop();
				j = values.top();
				values.pop();
				if (j.type != i.type){
					throw string("type mismatch\n");	
				}
				if (j.type == assm::INT){
					throw string("incorrect operation \"or\" for int\n");
				}
				if (j.type == assm::STRING){
					throw string("incorrect operation \"or\" for string\n");
				}
				values.push(assm(assm::BOOL,j.ivalue || i.ivalue,"")); 
	
			}
			else if (curr.svalue == "not"){
				i = values.top();
				values.pop();
				if (i.type == assm::INT){
					throw string("incorrect operation \"not\" for int\n");
				}
				if (i.type == assm::STRING){
					throw string("incorrect operation \"not\" for string\n");
				}
				values.push(assm(assm::BOOL,!(i.ivalue),"")); 
			

			}
			else if (curr.svalue == "&-"){
				i = values.top();
				values.pop();
				if (i.type == assm::BOOL){
					throw string("incorrect operation \"-\" for boolean\n");
				}
				if (i.type == assm::STRING){
					throw string("incorrect operation \"-\" for string\n");
				}
				values.push(assm(assm::INT,-(i.ivalue),""));

				
			}



		}
			




	}
}

class Sint_Analyze{
	int pos;
	stack <int> st;
	Poliz cons;
	vector <Lex_Analyze::leks *> v;
	Lex_Analyze machine;
	int find_id(string s);
	void check_desc();
	void check_oper();
	void check_wrong_desc();
	void statement(int a);
	int prior(string &s);
public:
	Sint_Analyze(){
		pos = 0;
		machine.analyze_leks(v);
	}
	void analyze_sint();
	void execute();	
};


void Sint_Analyze::execute(){
	cons.exec();
}

void Sint_Analyze::check_wrong_desc(){
	for (int i = 0; i<cons.table.size(); i++){
		for (int j = 0; j<cons.table.size();j++){
			if (i != j){
				if (cons.table[i].name == cons.table[j].name){
					throw string ("second declaration!\n");
				}
			}
		}
	}
} 

void Sint_Analyze::check_desc(){
	int t = 0;
	string type;
	int sign = 0;

//	cout << "RAAMBO"<<endl;
	while (t || (pos < v.size() && v[pos]->type == "TYPE")){
		if (!t){
			type = v[pos]->word;
		}
		++pos;
		if (!(v[pos]->type == "ID")){
			throw string("expected ID after TYPE");	
		}
		string name;
//		cout << pos << endl;

		name = v[pos]->word;
		++pos;
		if (v[pos]->word == "="){
			++pos;
			if (v[pos]->word == "+"){
				sign = 1;
			}
			if (v[pos]->word == "-"){
				sign = 2;
			}
			if (sign){
				pos++;
			}
			if (!(((v[pos]->type == "DECIMAL") && (type == "int")) ||
						((v[pos]->type == "STRING CONST") && (type == "string"))||
						((v[pos]->type == "DECIMAL") && (type == "bool")) || (v[pos]->type == "WBOOL" && type == "bool"))){
				throw string("incorrect type of initializer\n");
			}
			if (v[pos]->type == "DECIMAL" || v[pos]->type == "WBOOL"){
				if (v[pos]->type == "WBOOL"){
					int a;
					if (v[pos]->word == "true"){
						a = 1;
					} else { a = 0;}
					cons.AddTable(type,name,a);
				} else {
					int a = atoi((v[pos]->word).c_str());
					if (sign == 2){ 
						a = -a;
						sign = 0;
					}
					if (sign == 1){
						sign = 0;
					}
					cons.AddTable(type,name,a);
				}
			} else {
				cons.AddTable(name,v[pos]->word);
			}
			pos++;
			if (v[pos]->word == ","){
				t = 1;
				continue;
			} else {
				t = 0;
			}
		} else if (v[pos]->word == ","){
			t = 1;
			if (type == "string"){
				cons.AddTable(name,string(""));
			} else {
				cons.AddTable(type,name,0);
			}
			continue;
			
		} else {
			t = 0;
			if (type == "string"){
				cons.AddTable(name,string(""));
			} else {
				cons.AddTable(type,name,0);
			}
		}
	/*	if (!(v[pos]->word == ";")){
			throw string("expected \";\" in the end\n");
		}*/
		++pos;
//		cout << pos << endl;

	}	
	
}

int Sint_Analyze::find_id(string s){
		for (int i = 0; i < cons.table.size(); i++){
			if (cons.table[i].name == s){
				return i;
			} 
		}
		throw string("identificator wasn't declarated!\n");
		return -1;
}
bool flagUnar = 0;
bool flagUnar2 = 0;

int Sint_Analyze::prior(string &s){
	if (s == "not"){
		return 7;
	} else if (s == "*" || s == "/" || s == "%"){
		return 6;
	} else if (s == "+" || s == "-"){
		return 5;
	} else if (s == "&-"){
		return 0;
	
		
/*		if (s == "-" && (flagUnar2) ){
			return 0;
		} else {
			if (s == "-"){
				return 5;
			} else {
				return 5;
			}
		}*/
	} else if (s == "<" || s == ">" || s == "<=" || s == ">=" || s == "==" || s == "!="){
		return 4;
	} else if (s == "and"){
		return 3;
	} else if (s == "or"){
		return 2;
	} else if (s == "="){
		return 1;
	} else if (s == "(") {
		return -1;
	} else {
		throw string("smth strange happened...\n");
	}

}

int get_int(string s){
	if (s == "true"){
		return 1;
	} else {
		return 0;
	}
}
void Sint_Analyze::statement(int a = 0){
	struct couple{
		string type;
		string name;
		couple(string t,string n){
			type = t;
			name = n;
		}
	};
	stack <couple> st2;
	int r = 0;
	int sc = 0;
//	cout << v[pos]->word << endl;
	/*	not
		* / %
		+ -
		< > <= >= == !=
		and
		or
		=
		-
	*/
	while (v[pos]->type != "KEYW"  && v[pos]->type != "POINT" && v[pos]->type != "VOID" && v[pos]->word != "}" ){
		if (v[pos]->word == ")"){
			if (sc == 0){
				break;
			}
		}
		if (v[pos]->word == "-" && flagUnar){
			flagUnar2 = true;
		} else flagUnar2 = false;

		if (v[pos]->word == "=" || v[pos]->word == "(") {
			flagUnar = true;
		} else flagUnar = false;

		if (v[pos]->type == "ID"){
			cons.queue.push_back(Poliz::assm(Poliz::assm::VAL,find_id(v[pos]->word),""));
		} else if (v[pos]->type == "DECIMAL"){
			cons.queue.push_back(Poliz::assm(Poliz::assm::INT,atoi((v[pos]->word).c_str()),""));
		} else if (v[pos]->type == "WBOOL"){
			cons.queue.push_back(Poliz::assm(Poliz::assm::BOOL,get_int(v[pos]->word),""));
		} else if (v[pos]->type == "STRING CONST"){
			cons.queue.push_back(Poliz::assm(Poliz::assm::STRING,0,v[pos]->word));
		} else if (v[pos]->type == "OPER" || v[pos]->type == "LOG OPER"){
			if (st2.empty()){
				if (v[pos]->word == "="){
//					flagUnar = 1;
					cons.queue[cons.queue.size()-1].type = Poliz::assm::ID_ADD; 	
				}
					st2.push(couple(v[pos]->type,v[pos]->word));
			} else {
				if (v[pos]->word == "="){
//					cout << "DA"<<endl;
					cons.queue[cons.queue.size()-1].type = Poliz::assm::ID_ADD; //!!!!!!!!!!!!!!!!!!!
//					flagUnar = 1;
					while (!(st2.empty())){
						if (prior((st2.top()).name) > prior(v[pos]->word)){
							
							cons.queue.push_back(Poliz::assm(Poliz::assm::OP,prior(st2.top().name) == 0? 1:0,(st2.top()).name));
							st2.pop();
						} else { break; }
					}
					
					//cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,v[pos]->word));
					st2.push(couple(v[pos]->type,v[pos]->word));
				} else {
					while (!(st2.empty())){
						if (prior((st2.top()).name) >= prior(v[pos]->word)){
//							cout << (st2.top()).name << endl;
//							cout << v[pos]->word<< endl;
							cons.queue.push_back(Poliz::assm(Poliz::assm::OP,prior(st2.top().name) == 0? 1:0,(st2.top()).name));
							st2.pop();
						} else { break; }
					}
	//				cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,v[pos]->word));
					if (flagUnar2){
						v[pos]->word = "&-";
					}
					st2.push(couple(v[pos]->type,v[pos]->word));

				}
			}
					
		} else if (v[pos]->word == "("){
			sc++;
			st2.push(couple(v[pos]->type,v[pos]->word));
			int bracket = 1;
		} else if (v[pos]->word == ")"){
			sc--;
			while (!(st2.empty())){
				if ((st2.top()).name != "("){
					cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,(st2.top()).name));
					st2.pop();
					
				} else {
					st2.pop();
					r = 1;
					break;
				} 
			/*	if (!r){
					throw string("problem with bracket1!\n");
				}*/
					
			}	
			if (!r){
				throw string("problem with bracket2!\n");
			}	
		}
		pos++;	
	}
	while (!st2.empty()){
		if ((st2.top()).type == "OPER" || (st2.top()).type == "LOG OPER"){
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,(st2.top()).name));
			st2.pop();
		} else {
			cout << (st2.top()).name<< endl;
			throw string("problem with bracket3!\n");
		}
	}

	if (a){
		cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,";"));
	}
}

void Sint_Analyze::check_oper(){
	
	if (v[pos]->type == "KEYW"){
		if (v[pos]->word == "if"){
			++pos;
			if (v[pos]->word != "("){
				throw string("expected \"(\" after \"if\"\n");
			}
			++pos;
			statement();
			if (v[pos]->word != ")"){
				throw string("expected \")\" after \"oper\"\n");
			}
			int addrelse = cons.queue.size();
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,0,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"JF"));	
			pos++;
			check_oper();
//			pos++;
			cout<<v[pos]->word<<endl;
			cout <<"here"<<endl;
			if (v[pos]->word != "else"){
				cons.queue[addrelse].ivalue = cons.queue.size();
//				return;
			} else {
				int addrif = cons.queue.size();
				cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,0,""));
				cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
				cons.queue[addrelse].ivalue = cons.queue.size();
				pos++;
				check_oper();
//				pos++;
				cons.queue[addrif].ivalue = cons.queue.size();
			}
			
		} else if (v[pos]->word == "do") {
			++pos;
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,cons.queue.size()+4,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
			int a2p = cons.queue.size();
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,0,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
			int rem = cons.queue.size();
			st.push(a2p);
			check_oper();
			st.pop();
//			pos++;
//			cout<<v[pos]->word<<endl;
			if (v[pos]->word != "while"){
				throw string("expected \"while\" after \"do\"\n");
			}
			pos++;
			if (v[pos]->word != "("){
				throw string("expected \"(\" after \"while\"\n");
			}
			pos++;
			statement();
			if (v[pos]->word != ")"){
				throw string("expected \")\" after \"oper\"\n");
			}
			pos++;
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,rem,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"JT"));
			if (v[pos]->word != ";"){
				throw string("expected \";\" after \"do-while operator\"\n");
			}
			pos++;
			cons.queue[a2p].ivalue = cons.queue.size();
			
		} else if (v[pos]->word == "read"){
			pos++;
			if (v[pos]->word != "("){
				throw string("expected \"(\" after \"read\"\n");
			}
			pos++;
			if (v[pos]->type != "ID"){
				throw string("expected ID for read\n");
			} 
			int id = find_id(v[pos]->word); // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
			if (id == -1){
				throw string("undeclared identificator: ") + v[pos]->word ;
			}

			pos++;
			if (v[pos]->word != ")"){
				throw string("expected \")\" after \"(\"\n");
			}
			pos++;
			if (v[pos]->word != ";"){
				throw string("expected \";\" after read operator\n");
			}
			pos++;
			cons.queue.push_back(Poliz::assm(Poliz::assm::ID_ADD,id,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"read"));

		} else if (v[pos]->word == "write"){
/*			pos++;
			if (v[pos]->word != "("){
				throw string("expected \"(\" after \"write\"\n");
			}
			int s = 1;
			pos++;
			statement(); // out from stack 
			while (v[pos]->word == ","){
				s++;
				pos++;
				statement();
			}
			if (v[pos]->word != ")"){
				throw string("expected \")\" after write-operator\n");
			}
			pos++;
			if (v[pos]->word != ";"){
				throw string("expected \";\" after write-operator\n");
			}
			pos++;
			cons.queue.push_back(Poliz::assm(Poliz::assm::INT,s,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"write"));
*/		
			pos++;
			if (v[pos]->word != "("){
				throw string("expected \"(\" after \"write\"\n");
			}
//			int s = 1;
			pos++;
			statement(); // out from stack 				statement();
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"write"));

			while (v[pos]->word == ","){
//				s++;
				pos++;
				statement();
				cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"write"));

			}
			

//			pos++;
			if (v[pos]->word != ")"){
				throw string("expected \")\" after write-operator\n");
			}
			pos++;
			if (v[pos]->word != ";"){
				throw string("expected \";\" after write-operator\n");
			}
			pos++;
/*			cons.queue.push_back(Poliz::assm(Poliz::assm::INT,s,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"write"));*/

		} else if (v[pos]->word == "for"){
			pos++;
			if (v[pos]->word != "("){
				throw string("expected \"(\" after \"for\"\n");
			}
			pos++;
			statement(1);
			if (v[pos]->word != ";"){
				throw string("expected \";\" after for-operator\n");
			}
			int a2 = cons.queue.size();
			pos++;
			statement();
			if (v[pos]->word != ";"){
				throw string("expected \";\" after for-operator\n");
			}
			int a1p = cons.queue.size();
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,0,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"JT"));
			int a4p = cons.queue.size();
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,0,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
			int a3 = cons.queue.size();			
			pos++;
			statement(1);
			if (v[pos]->word != ")"){
				throw string("expected \")\" after \"for\"\n");
			}
			pos++;

			int a2p = cons.queue.size();
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,a2,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
			int a1 = cons.queue.size();
			cons.queue[a1p].ivalue=a1;
			st.push(a4p);
			check_oper();
			st.pop();
			cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,a3,""));
			cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
			cons.queue[a4p].ivalue = cons.queue.size();			
		} else if (v[pos]->word == "break") {
			++pos;
			if (v[pos]->word != ";"){
				throw string("expected \";\" after break-operator\n");
			}
			pos++;
			if (st.size() != 0){		
				cons.queue.push_back(Poliz::assm(Poliz::assm::NUM,st.top(),""));
				cons.queue.push_back(Poliz::assm(Poliz::assm::OP,0,"J"));
			} else { throw string("incorrect using break\n");}
			
		} else {
//			cout << v[pos]->word << endl;
			throw string("incorrect key word");
		}
	} else if (v[pos]->word == "{") {
		++pos;
		while(v[pos]->word != "}"){
//			cout <<v[pos]->word<<endl;
			check_oper();
//			pos++;
		}
		pos++;
	} else { 
		statement(1);
//		pos++;
//		cout<<v[pos]->word<<endl;
		if (v[pos]->word != ";"){
			if (v[pos]->word == ""){
				throw string("unexpected EOF!\n");
			}
			throw string("expected \";\" after operator\n");
		}
		pos++;
//		cout<<v[pos]->word<<endl;

	}
	
}
		
void Sint_Analyze::analyze_sint(){
//	cout<<v.size()<<endl;
	if (v[0]->type== "PROGRAM"){
		if (v.size() != 1 && v[1] -> word == "{"){
			pos += 2;
			check_desc();
			check_wrong_desc();
			while (v.size() != 0 && pos < v.size() && v[pos]->word != "}"){
				check_oper();
//				pos++;
//				cout << v[pos]->word<<endl;
			}
		} else {
			if (v.size() != 1){
				throw string("expected ") + '"' + '{'+ '"' + " after \"program\" instead of \"" + v[1]->word + "\"\n";
			} else { throw string("expected") + '"' + '{' + '"' + "after \"program\"";}
		}
	} else {
		if (v.size() != 0){ 
			throw v[0]->word + " expected \"program\"\n";
		} else { exit(0);}
	}

	cons.dump();
	cons.dump2();  //^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	execute();

	return;	
}

int main(){
//	vector <Lex_Analyze::leks *> v;
//	Lex_Analyze machine;
	try{
		Sint_Analyze machine;
		machine.analyze_sint();
	} 
	catch (string &s){
		cout << s;
	}
//	cout << "end"<< endl;
	return 0;
}

