#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include<string>
#include"define.h"
using namespace std;
FILE* in, * out;
string outtemp[50] = { "IDENFR","INTCON","CHARCON","STRCON","CONSTTK","INTTK","CHARTK","VOIDTK","MAINTK",\
"IFTK","ELSETK","DOTK","WHILETK","FORTK","SCANFTK","PRINTFTK","RETURNTK","PLUS","MINU","MULT","DIV","LSS","LEQ",\
"GRE","GEQ","EQL","NEQ","ASSIGN","SEMICN","COMMA","LPARENT","RPARENT","LBRACK","RBRACK","LBRACE","RBRACE" };
char temp[200] = { "\0" };
int aynm = 0;
int sym;
int isym[50];
string ctp[50];

int cifa() {
	char pRintf[] = "printf", rEturn[] = "return";
	char cOnst[] = "const", iNt[] = "int";
	char cHar[] = "char", vOid[] = "void", mAin[] = "main";
	char iF[] = "if", eLse[] = "else", dO[] = "do";
	char wHile[] = "while", fOr[] = "for", sCanf[] = "scanf";
	int num = 0;
	char e = '\0';
	e = fgetc(in);
	while (isspace(e) != 0) {
		e = fgetc(in);
	}
	if (e == '_' || (e >= 'A' && e <= 'Z') || (e >= 'a' && e <= 'z')) {
		int i = 0;
		temp[i++] = e;
		e = fgetc(in);
		while (e == '_' || (e >= 'A' && e <= 'Z') || (e >= 'a' && e <= 'z') || (e >= '0' && e <= '9')) {
			temp[i++] = e;
			e = fgetc(in);
		}
		if (strcmp(temp, cOnst) == 0) {
			sym = CONSTTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, iNt) == 0) {
			sym = INTTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, cHar) == 0) {
			sym = CHARTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, vOid) == 0) {
			sym = VOIDTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, mAin) == 0) {
			sym = MAINTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, iF) == 0) {
			sym = IFTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, eLse) == 0) {
			sym = ELSETK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, dO) == 0) {
			sym = DOTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, wHile) == 0) {
			sym = WHILETK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, fOr) == 0) {
			sym = FORTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, sCanf) == 0) {
			sym = SCANFTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, pRintf) == 0) {
			sym = PRINTFTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, rEturn) == 0) {
			sym = RETURNTK;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else {
			sym = IDENFR;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		
		ungetc(e, in);
	}
	else if (e >= '0' && e <= '9') {
		int i = 0;
		temp[i] = e;
		i++;
		while ((e = fgetc(in)) >= '0' && e <= '9') {
			temp[i++] = e;
		}
		num = atoi(temp);
		sym = INTCON;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		
		ungetc(e, in);
	}
	else if (e == 39) {
		e = fgetc(in);
		char tp;
		tp = e;
		temp[0] = tp;
		e = fgetc(in);
		if (e == 39) {
			sym = CHARCON;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
	}
	else if (e == 34) {
		int i = 0;
		while ((e = fgetc(in)) != 34) {
			temp[i++] = e;
		}
		sym = STRCON;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		
	}
	else if (e == '+') {
		temp[0] = e;
		sym = PLUS;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '-') {
		temp[0] = e;
		sym = MINU;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '*') {
		temp[0] = e;
		sym = MULT;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '/') {
		temp[0] = e;
		sym = MULT;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '<') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '<';
			temp[1] = '=';
			sym = LEQ;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			temp[0] = '<';
			sym = LSS;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '>') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '>';
			temp[1] = '=';
			sym = GEQ;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			temp[0] = '>';
			sym = GRE;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '=') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '=';
			temp[1] = '=';
			sym = EQL;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			temp[0] = '=';
			sym = ASSIGN;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '!') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '!';
			temp[1] = '=';
			sym = NEQ;
			ctp[aynm] = temp;
			isym[aynm++] = sym;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			ungetc(e, in);
		}
	}
	else if (e == ';') {
		temp[0] = e;
		sym = SEMICN;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '0';
	}
	else if (e == ',') {
		temp[0] = e;
		sym = COMMA;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '(') {
		temp[0] = e;
		sym = LPARENT;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == ')') {
		temp[0] = e;
		sym = RPARENT;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '[') {
		temp[0] = e;
		sym = LBRACK;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == ']') {
		temp[0] = e;
		sym = RBRACK;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '{') {
		temp[0] = e;
		sym = LBRACE;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '}') {
		temp[0] = e;
		sym = RBRACE;
		ctp[aynm] = temp;
		isym[aynm++] = sym;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}

	return sym;
}

void cfot() {
	for (int i = 0; i <= aynm; i++) {
		fprintf(out, "%s %s\n", outtemp[isym[i]].c_str(), ctp[i].c_str());
		ctp[i].erase();
	}
	aynm = 0;
}

int main() {
	char pRintf[] = "printf", rEturn[] = "return";
	char cOnst[] = "const", iNt[] = "int";
	char cHar[] = "char", vOid[] = "void", mAin[] = "main";
	char iF[] = "if", eLse[] = "else", dO[] = "do";
	char wHile[] = "while", fOr[] = "for", sCanf[] = "scanf";
	fopen_s(&in, "testfile.txt", "r");
	fopen_s(&out, "output.txt", "w");
	for (int i = 0; i < 50; i++) {
		cifa();
	}
}
