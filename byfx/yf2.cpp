
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include"string"
#include"stdio.h"
#include"define2.h"
using namespace std;

string outtemp[50] = {"IDENFR","INTCON","CHARCON","STRCON","CONSTTK","INTTK","CHARTK","VOIDTK","MAINTK",\
"IFTK","ELSETK","DOTK","WHILETK","FORTK","SCANFTK","PRINTFTK","RETURNTK","PLUS","MINU","MULT","DIV","LSS","LEQ",\
"GRE","GEQ","EQL","NEQ","ASSIGN","SEMICN","COMMA","LPARENT","RPARENT","LBRACK","RBRACK","LBRACE","RBRACE"};
char ftf[20] = { '0', 'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o' };
int x;
void  error(int x);
int cifa();
int cifal();
void cfot();
int isplus();
int ismult();
int isgx();
int symzf();
int symzfc();
int symcx();
int symclsm();
int symcldy();
int symwfhzs();
int symzs();
int symwfhzs();
int symbsf();
int symsmtb();
int symblsm();
int symbldy();
int symlxbsf();
int symyfhzhsdy();
int symwfhzhsdy();
int symfhyj();
int symcsb();
int symzhs();
int symbds();
int symx();
int symyz();
int symyj();
int symfzyj();
int symtjyj();
int symtj();
int symxhyj();
int symbc();
int symyfhzhsdyyj();
int symwfhzhsdyyj();
int symzcsb(int num,int type[30]);
int symyjl();
int symdyj();
int symxyj();
int symrtyj();
int num();
int nznum();
int zero();
FILE* in,* out;
int sym = -1;
int rtn = -1;
int rtc = 0;
char temp[10000] = { "\0" };
string var_ioc[10000];
string var_void[10000];
struct fuhaob {
	int type;// integer 0,const 1,function 2;
	int iocov;//int 1,char 2,void 3;
	char nam[64]; //name;
	char cengci[64]; //层次 所属函数名全局变量为global;
}fhb[1024];
struct hsfuhaob {
	int iocov;//int 1,char 2,void 3;
	char nam[64]; //name;
	int csnum; //参数数量
	string csnam[30];
	int cstype[30]; //参数类型：int 1, char 2;
}hsfhb[1024];
int hsfhbnum = 0;
int fhbnum = 0;
char dycengci[64] = "global";
const char cc[64] = "mainval";
const char glb[64] = "global";
char dytp[64] = "global";
int var_i = 0;
int var_v = 0;
int isym[2000] = { 0 };
int aynm = 0;
int lnum = 1;
int rtline = 0;
/*int main() {
	//fopen_s(&in, "testfile.txt", "r");
	//fopen_s(&out, "error.txt", "w");
	 in = fopen("testfile.txt","r");
	 out = fopen("error.txt", "w");
	symcx();
	/*for (int i = 0; i < fhbnum; i++) {
		printf("%d %d %s %d\n", fhb[i].type, fhb[i].iocov, fhb[i].nam, fhb[i].cengci);
	}
	for (int i = 0; i < hsfhbnum; i++) {
		printf("%d %s %d ", hsfhb[i].iocov, hsfhb[i].nam, hsfhb[i].csnum);
		for (int j = 0; j < hsfhb[i].csnum; j++) {
			printf("%s ", hsfhb[i].csnam[j].c_str());
		}
		printf("\n");
	}
	//return 0;
 }
/*
int zero() {
	if (sym == ZERO) {
		cfot();
		cifa();
		return 1;
	}
	else {
		return 0;
	}
}
int nznum() {
	if (sym == INTCON) {
		cfot();
		cifa();
		return 1;
	}
	else {
		return 0;
	}
}
int num() {
	if (zero()) {
		cfot();
		cifa();
		return 1;
	}
	if (nznum()) {
		cfot();
		cifa();
		return 1;
	}
	return 
}*/
void error(int x) {
	switch (x) {
		case 1 :
			fprintf(out, "%d a\n",lnum);
			//printf("%d a\n", lnum);
			break;
		case 2 :
			fprintf(out, "%d b\n", lnum);
			break;
		case 3 :
			fprintf(out, "%d c\n", lnum);
			break;
		case 4 :
			fprintf(out, "%d d\n", lnum);
			break;
		case 5 :
			fprintf(out, "%d e\n", lnum);
			break;
		case 6 :
			fprintf(out, "%d f\n", lnum);
			break;
		case 7 :
			fprintf(out, "%d g\n", rtline);
			break;
		case 8 :
			fprintf(out, "%d h\n", rtline);
			break;
		case 9 :
			fprintf(out, "%d i\n", lnum);
			break;
		case 10:
			fprintf(out, "%d j\n", lnum);
			break;
		case 11:
			fprintf(out, "%d k\n", lnum - 1);
			break;
		case 12:
			fprintf(out, "%d l\n", lnum);
			break;
		case 13:
			fprintf(out, "%d m\n", lnum);
			break;
		case 14:
			fprintf(out, "%d n\n", lnum);
			break;
		case 15:
			fprintf(out, "%d o\n", lnum);
			break;
		default:
			break;
	}
	return ;
}

int symrtyj() {
	if (sym == RETURNTK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			int tpbds = symbds();
			if (tpbds == 1) {
				rtn = 1;
				rtline = lnum;
	
			}
			else if(tpbds == 2){
				rtn = 2;
				rtline = lnum;	
			}
			else {
				rtn = 3;
				rtline = lnum;
			}
			if (sym == RPARENT) {
				cfot();
				cifa();
			}
			else {
				error(12);
			}
		}
		//fprintf(out, "<返回语句>\n")
		else {
			rtn = 4;
			rtline = lnum;
		}
		return 1;

	}
	return 0;
}

int symxyj() {
	if (sym == PRINTFTK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symzfc()) {
				if (sym == COMMA) {
					cfot();
					cifa();
					if (symbds()) {
						if (sym == RPARENT) {
							cfot();
							cifa();
							//fprintf(out, "<写语句>\n");
						}
						else {
							error(12);
							
						}
						return 1;
					}
				}
				else if (sym == RPARENT) {
					cfot();
					cifa();
					//fprintf(out, "<写语句>\n");
					return 1;
				}
				else {
					error(12);
					return 1;
				}
			}
			else if (symbds()) {
				if (sym == RPARENT) {
					cfot();
					cifa();
					//fprintf(out, "<写语句>\n");
					return 1;
				}
				else {
					error(12);
					return 1;
				}
			}
		}
	}
	return 0;
}

int symdyj() {
	if (sym == SCANFTK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (sym == IDENFR) {
				int fla = 0;
				for (int i = 0; i < fhbnum; i++) {
					if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 || strcmp(fhb[i].cengci, glb) == 0)) {
						fla = 1;
						break;
					}
				}
				if (fla == 0) {
					error(3);
				}
				cfot();
				cifa();
				while (sym == COMMA) {
					cfot();
					cifa();
					if (sym == IDENFR) {
						int fla = 0;
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 || strcmp(fhb[i].cengci, glb) == 0)) {
								fla = 1;
								break;
							}
						}
						if (fla == 0) {
							error(3);
						}
						cfot();
						cifa();
					}
				}
				if (sym == RPARENT) {
					cfot();
					cifa();
					//fprintf(out, "<读语句>\n");
					return 1;
				}
				else {
					error(12);
					return 1;
				}
			}

		}
	}
	return 0; 
}

int symyjl() {
	if (symyj()) {
		while (symyj()) {
		}
	}
	//fprintf(out, "<语句列>\n");
	return 1;
}

int symzcsb(int num, int type[30]) {
	int tempnum = 0;
	int tpbds = symbds();
	if (tpbds) {
		if (type[tempnum] != tpbds) {
			error(5);
		}
			tempnum++;
		while (sym == COMMA) {
			cfot();
			cifa();
			tpbds = symbds();
			if (tpbds) {
				if (type[tempnum] != tpbds) {
					error(5);
				}
				tempnum++;
			}
		}
		if (tempnum != num) {
			error(4);
		}
		//fprintf(out, "<值参数表>\n");
		return 1;
	}
	else if (sym == RPARENT) {
		//fprintf(out, "<值参数表>\n");
		if (tempnum != num) {
			error(4);
		}
		return 1;
	}
	else {
		error(12);
		return 1;
	}
	return 0;
}

int symwfhzhsdyyj() {
	if (sym == IDENFR) {
		int fla = 0;
		int hstype = 0;
		int hscsnum = 0;
		int hscstype[30];
		for (int i = 0; i < hsfhbnum; i++) {
			if (strcmp(hsfhb[i].nam, temp) == 0) {
				fla = 1;
				hstype = hsfhb[i].iocov;
				hscsnum = hsfhb[i].csnum;
				for (int j = 0; j < hscsnum; j++) {
					hscstype[j] = hsfhb[i].cstype[j];
				}
				break;
			}
		}
		if (fla == 0) {
			int te = ftell(in);;
			int tesym = sym;
			char tetemp[50];
			strcpy(tetemp, temp);
			cifal();
			if (sym != LPARENT) {
				fseek(in, te, SEEK_SET);
				sym = tesym;
				strcpy(temp, tetemp);
				return 0;
			}
			else {
				fseek(in, te, SEEK_SET);
				sym = tesym;
				strcpy(temp, tetemp);
				error(3);
			}
		}
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symzcsb(hscsnum, hscstype)) {
				if (sym == RPARENT) {
					cfot();
					cifa();
					//fprintf(out, "<无返回值函数调用语句>\n");
					return 1;
				}
				else {
					error(12);
					return 1;
				}
			}
		}
	}
	return 0;
}

int symyfhzhsdyyj() {
	if (sym == IDENFR) {
		int fla = 0;
		int hstype = 0;
		int hscsnum = 0;
		int hscstype[30];
		for (int i = 0; i < hsfhbnum; i++) {
			if (strcmp(hsfhb[i].nam, temp) == 0) {
				fla = 1;
				hstype = hsfhb[i].iocov;
				hscsnum = hsfhb[i].csnum;
				for (int j = 0; j < hscsnum; j++) {
					hscstype[j] = hsfhb[i].cstype[j];
				}
				break;
			}
		}
		if (fla == 0) {
			int te = ftell(in);;
			int tesym = sym;
			char tetemp[50];
			strcpy(tetemp, temp);
			cifal();
			if (sym != LPARENT) {
				fseek(in, te, SEEK_SET);
				sym = tesym;
				strcpy(temp, tetemp);
				return 0;
			}
			else {
				fseek(in, te, SEEK_SET);
				sym = tesym;
				strcpy(temp, tetemp);
				error(3);
			}
		}
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symzcsb(hscsnum,hscstype)){
				if (sym == RPARENT) {
					cfot();
					cifa();
					//fprintf(out, "<有返回值函数调用语句>\n");
					if (hstype == 0) {
						return 1;
					}
					else {
						return 2;
					}
				}
				else {
					error(12);
					if (hstype == 0) {
						return 1;
					}
					else {
						return 2;
					}
				}
			}
		}
	}
	return 0;
}

int symbc() {
	if(symwfhzs()){
		//fprintf(out, "<步长>\n");
		return 1;
	}
	return 0;
}

int symxhyj() {
	if (sym == WHILETK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symtj()) {
				if (sym == RPARENT) {
					cfot();
					cifa();
				}
				else {
					error(12);
					return 1;
				}
				if (symyj()) {
					//fprintf(out, "<循环语句>\n");
					return 1;
				}
			}
		}
	}
	else if (sym == DOTK) {
		cfot();
		cifa();
		if (symyj()) {
			if (sym == WHILETK) {
				cfot();
				cifa();
			}
			else {
				error(14);
			}
			if (sym == LPARENT) {
				cfot();
				cifa();
				if (symtj()) {
					if (sym == RPARENT) {
						cfot();
						cifa();
						//fprintf(out, "<循环语句>\n");
						return 1;
					}
					else {
						error(12);
						return 1;
					}
				}
			}
		}
	}
	else if (sym == FORTK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (sym == IDENFR) {
				int fla = 0;
				int tptype = 0;
				for (int i = 0; i < fhbnum; i++) {
					if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 || strcmp(fhb[i].cengci, glb) == 0)) {
						fla = 1;
						tptype = fhb[i].type;
						if (tptype == 1) {
							error(10);
						}
						break;
					}
				}
				if (fla == 0) {
					error(3);
				}
				cfot();
				cifa();
				if (sym == ASSIGN) {
					cfot();
					cifa();
					if (symbds()) {
						if (sym == SEMICN) {
							cfot();
							cifa();
						}
						else {
							error(11);
						}
						if (symtj()) {
							if (sym == SEMICN) {
								cfot();
								cifa();
							}
							else {
								error(11);
							}
							if (sym == IDENFR) {
								int fla = 0;
								int tptype = 0;
								for (int i = 0; i < fhbnum; i++) {
									if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 || strcmp(fhb[i].cengci, glb) == 0)) {
										fla = 1;
										tptype = fhb[i].type;
										if (tptype == 1) {
											error(10);
										}
										break;
									}
								}
								if (fla == 0) {
									error(3);
								}
								cfot();
								cifa();
								if (sym == ASSIGN) {
									cfot();
									cifa();
									if (sym == IDENFR) {
										int fla = 0;
										for (int i = 0; i < fhbnum; i++) {
											if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 || strcmp(fhb[i].cengci, glb) == 0)) {
												fla = 1;
												break;
											}
										}
										if (fla == 0) {
											error(3);
										}
										cfot();
										cifa();
										if (isplus()) {
											if (symbc()) {
												if (sym == RPARENT) {
													cfot();
													cifa();
												}
												else {
													error(12);
												}
												if (symyj()) {
													//fprintf(out, "<循环语句>\n");
													return 1;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int symtj() {
	int tpbds = symbds();
	if (tpbds == 1) {
		if (isgx()) {
			tpbds = symbds();
			if (tpbds == 1) {
				//fprintf(out, "<条件>\n");
				return 1;
			}
			else if (tpbds == 2) {
				error(6);
				return 1;
			}
		}
		//fprintf(out, "<条件>\n");
		return 1;
	}
	else if (tpbds == 2) {
		error(6);
		if (isgx()) {
			tpbds = symbds();
			if (tpbds == 1) {
				//fprintf(out, "<条件>\n");
				return 1;
			}
			else if (tpbds == 2) {
				return 1;
			}
		}
		//fprintf(out, "<条件>\n");
		return 1;
	}
	return 0;
}

int symtjyj() {
	if (sym == IFTK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symtj()) {
				if (sym == RPARENT) {
					cfot();
					cifa();
				}
				else {
					error(12);
				}
				if (symyj()) {
					if (sym == ELSETK) {
						cfot();
						cifa();
						symyj();
					}
					//fprintf(out, "<条件语句>\n");
					return 1;
				}
			}
		}
	}
	return 0;
}

int symfzyj() {
	if (sym == IDENFR) {
		int fla = 0;
		int tptype = 0;
		for (int i = 0; i < fhbnum; i++) {
			if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci,dycengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
				fla = 1;
				tptype = fhb[i].type;
				if (tptype == 1) {
					error(10);
				}
				break;
			}
		}
		if (fla == 0) {
			error(3);
		}
		cfot();
		cifa();
		if (sym == LBRACK) {
			cfot();
			cifa(); 
			int tpbds = symbds();
			if (tpbds) {
				if (tpbds != 1) {
					error(9);
				}
				if (sym == RBRACK) {
					cfot();
					cifa();
				}
				else {
					error(13);
				}
			}
		}
		if (sym == ASSIGN) {
			cfot();
			cifa();
			if (symbds()) {
				//fprintf(out, "<赋值语句>\n");
				return 1;
			}
		}

	}
	return 0;
}

int symyj() {
	if (symtjyj()) {
		//fprintf(out, "<语句>\n");
		return 1;
	}
	else if (symxhyj()) {
		//fprintf(out, "<语句>\n");
		return 1;
	}
	else if (sym == LBRACE) {
		cfot();
		cifa();
		if (symyjl()) {
			if (sym == RBRACE) {
				cfot();
				cifa();
				//fprintf(out, "<语句>\n");
				return 1;
			}
		}

	}
	else if (symyfhzhsdyyj()) {
		if (sym == SEMICN) {
			cfot();
			cifa();
			//fprintf(out, "<语句>\n");
			return 1;
		}
		else {
			error(11);
			return 1;
		}
	}
	else if (symwfhzhsdyyj()) {
		if (sym == SEMICN) {
			cfot();
			cifa();
			//fprintf(out, "<语句>\n");
			return 1;
		}
		else {
			error(11);
			return 1;
		}
	}
	else if (symfzyj()) {
		if (sym == SEMICN) {
			cfot();
			cifa();
			//fprintf(out, "<语句>\n");
			return 1;
		}
		else {
			error(11);
			return 1;
		}
	}
	else if (symdyj()) {
		if (sym == SEMICN) {
			cfot();
			cifa();
			//fprintf(out, "<语句>\n");
			return 1;
		}
		else {
			error(11);
			return 1;
		}
	}
	else if (symxyj()) {
		if (sym == SEMICN) {
			cfot();
			cifa();
			//fprintf(out, "<语句>\n");
			return 1;
		}
		else {
			error(11);
			return 1;
		}
	}
	else if (symrtyj()) {
		if (sym == SEMICN) {
			cfot();
			cifa();
			//fprintf(out, "<语句>\n");
			return 1;
		}
		else {
			error(11);
			return 1;
		}
	}
	else if (sym == SEMICN) {
		cfot();
		cifa();
		//fprintf(out, "<语句>\n");
		return 1;
	}
	else {
		return 0;
	}
	return 1;
}

int symyz() {
	int hsdy = symyfhzhsdyyj();
	if (hsdy) {
	//fprintf(out, "<因子>\n");
		if (hsdy == 1) {
			return 1;
		}
		else {
			return 2;
		}
	}
	else if (sym == IDENFR) {
		int fla = 0;
		int idtemp = 0;
		for (int i = 0; i < fhbnum; i++) {
			if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 || strcmp(fhb[i].cengci, glb) == 0)) {
				fla = 1;
				idtemp = fhb[i].iocov;
				break;
			}
		}
		if (fla == 0) {
			error(3);
		}
		cfot();
		cifa();
		if (sym == LBRACK) {
			cfot();
			cifa();
			int tpbds = symbds();
			if (tpbds) {
				if (tpbds != 1) {
					error(9);
				}
				if (sym == RBRACK) {
					cfot();
					cifa();
					//fprintf(out, "<因子>\n");
					if (idtemp == 1) {
						return 1;
					}
					else {
						return 2;
					}
				}
				else {
					error(13);
				}
			}
		}
		else {
			//fprintf(out,"<因子>\n");
			if (idtemp == 1) {
				return 1;
			}
			else {
				return 2;
			}
		}
	}
	else if (sym == LPARENT) {
		cfot();
		cifa();
		if (symbds()) {
			if (sym == RPARENT) {
				cfot();
				cifa();
				//fprintf(out, "<因子>\n");
				return 1;
			}
			else {
				error(12);
				return 1;
			}
		}

	}
	else if (symzs()) {
		//fprintf(out, "<因子>\n");
		return 1;
	}
	else if (sym == CHARCON) {
		cfot();
		cifa();
		//fprintf(out, "<因子>\n");
		return 2;
	}
	return 0;
}

int symx() {
	int tempyz = symyz();
	if (tempyz) {
		int flag = 0;
		while (ismult()) {
			symyz();
			flag = 1;
		}
		//fprintf(out, "<项>\n");
		if (flag == 1) {
			return 1;
		}
		else {
			return tempyz;
		}
	}
	return 0;
}

int symbds() {
	int tpplus = isplus();
	int tpx = symx();
	if (tpx) {
		int flag = 0;
		while (isplus()) {
			symx();
			flag = 1;
		} 
		//fprintf(out, "<表达式>\n"); 
		if (flag == 1) {
			return 1;
		}
		else {
			if (tpplus) {
				return 1;
			}
			else {
				return tpx;
			}
		}
	}
	return 0;

}

int symzhs() {
	rtn = -1;
	if (sym == VOIDTK) {
		cfot();
		cifa();
		if (sym == MAINTK) {
			strcpy(dytp, dycengci);
			strcpy(dycengci, cc);
			cfot();
			cifa();
			if (sym == LPARENT) {
				cfot();
				cifa();
				if (sym == RPARENT) {
					cfot();
					cifa();
				}
				else {
					error(12);
				}
				if (sym == LBRACE) {
					cfot();
					cifa();
					if (symfhyj()) {
						if (rtn != 4 && rtn != -1) {
							error(7);
							rtn = -1;
						}
						if (sym == RBRACE) {
							cfot();
							//fprintf(out, "<主函数>\n");
							strcpy(dycengci, dytp);
							return 1;
						}
					}
				}
			}
		}
	 }
	return 0;
}

int symcsb() {
	int lxtemp;
	int csnum = 0;
	lxtemp = symlxbsf();
	if (lxtemp) {
		if (lxtemp == 1) {
			hsfhb[hsfhbnum].cstype[csnum] = 1;
			fhb[fhbnum].type = 0;
			fhb[fhbnum].iocov = 1;
		}
		else if (lxtemp == 2) {
			hsfhb[hsfhbnum].cstype[csnum] = 2;
			fhb[fhbnum].type = 0;
			fhb[fhbnum].iocov = 2;
		}
		if (sym == IDENFR) {
			strcpy(fhb[fhbnum].nam,temp);
			strcpy(fhb[fhbnum].cengci, dycengci);
			hsfhb[hsfhbnum].csnam[csnum] = temp;
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
					error(2);
					break;
				}
			}
			csnum++;
			fhbnum++;
			cfot();
			cifa();
			while (sym == COMMA) {
				cfot();
				cifa();
				lxtemp = symlxbsf();
				if (lxtemp) {
					if (lxtemp == 1) {
						hsfhb[hsfhbnum].cstype[csnum] = 1;
						fhb[fhbnum].type = 0;
						fhb[fhbnum].iocov = 1;
					}
					else if (lxtemp == 2) {
						hsfhb[hsfhbnum].cstype[csnum] = 2;
						fhb[fhbnum].type = 0;
						fhb[fhbnum].iocov = 2;
					}
					if (sym == IDENFR) {
						strcpy(fhb[fhbnum].nam,temp);
						strcpy(fhb[fhbnum].cengci, dycengci);
						hsfhb[hsfhbnum].csnam[csnum] = temp;
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
								error(2);
								break;
							}
						}
						csnum++;
						fhbnum++;
						cfot();
						cifa();
					}
				}
			}
			hsfhb[hsfhbnum].csnum = csnum;
			//fprintf(out, "<参数表>\n");
			return 1;
		}
	}
	else if (sym == RPARENT) {
		//fprintf(out, "<参数表>\n");
		hsfhb[hsfhbnum].csnum = csnum;
		return 1;
	}
	else {
		error(12);
		hsfhb[hsfhbnum].csnum = csnum;
		return 1;
	}
	return 0;
}

int symfhyj() {
	symclsm();
	symblsm();
	int tpyjl = symyjl();
 	if (tpyjl) {
		//fprintf(out, "<复合语句>\n");
		return tpyjl;
	}
	return 0;
}

int symwfhzhsdy() {
	rtn = -1;
	if (sym == VOIDTK) {
		cfot();
		hsfhb[hsfhbnum].iocov = 3;
		cifa();
		if (sym == IDENFR) {
			var_void[var_v++] = temp;
			strcpy(hsfhb[hsfhbnum].nam, temp);
			strcpy(dytp, dycengci);
			strcpy(dycengci, temp);
			for (int i = 0; i < hsfhbnum; i++) {
				if (strcmp(hsfhb[hsfhbnum].nam, hsfhb[i].nam) == 0) {
					error(2);
					break;
				}
			}
			cfot();
			cifa();
			if (sym == LPARENT) {
				cfot();
				cifa();
				if (symcsb()) {
					hsfhbnum++;
					if (sym == RPARENT) {
						cfot();
						cifa();
					}
					else {
						error(12);
					}
					if (sym == LBRACE) {
						cfot();
						cifa();
						if (symfhyj()) {
							if (rtn != 4 && rtn != -1) {
								error(7);
								rtn = -1;
							}
							if (sym == RBRACE) {
								cfot();
								cifa();
								strcpy(dycengci, dytp);
								//fprintf(out, "<无返回值函数定义>\n");
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}

int symyfhzhsdy() {
	rtn = -1;
	int tpsmtb = symsmtb();
	if (tpsmtb) {
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symcsb()) {
				hsfhbnum++;
				if (sym == RPARENT) {
					cfot();
					cifa();
				}
				else {
					error(12);
				}
				if (sym == LBRACE) {
					cfot();
					cifa();
					if (symfhyj()) {
						if (rtn != tpsmtb) {
							if (rtn == -1) {
								rtline = lnum;
							}
							error(8);
							rtn = -1;
						}
						if (sym == RBRACE) {
							cfot();
							cifa();
							strcpy(dycengci,dytp);
							//fprintf(out, "<有返回值函数定义>\n");
							return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

int symbldy() {
	int lxtemp;
	lxtemp = symlxbsf();
	if (lxtemp) {
		if (lxtemp == 1) {
			fhb[fhbnum].iocov = 1;
		}
		else if (lxtemp == 2) {
			fhb[fhbnum].iocov = 2;
		}
		if (sym == IDENFR) {
			fhb[fhbnum].type = 0;
			strcpy(fhb[fhbnum].nam, temp);
			strcpy(fhb[fhbnum].cengci, dycengci);
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
					error(2);
					break;
				}
			}
			fhbnum++;
			cfot();
			cifa();
			if (sym == LBRACK) {
				cfot();
				cifa();
				if (symwfhzs()) {
					if (sym == RBRACK) {
						cfot();
						cifa();
					}
					else {
						error(13);
					}
				}
			}
			while (sym == COMMA) {
				cfot();
				cifa();
				if (sym == IDENFR) {
					fhb[fhbnum].type = 0;
					fhb[fhbnum].iocov = lxtemp;
					strcpy(fhb[fhbnum].cengci, dycengci);
					strcpy(fhb[fhbnum].nam, temp);
					for (int i = 0; i < fhbnum; i++) {
						if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
							error(2);
							break;
						}
					}
					fhbnum++;
					cfot();
					cifa();
					if (sym == LBRACK) {
						cfot();
						cifa();
						if (symwfhzs()) {
							if (sym == RBRACK) {
								cfot();
								cifa();
							}
							else {
								error(13);
							}
						}
					}
				}
			}
			//fprintf(out, "<变量定义>\n");
			return 1;
		}
	}
	return 0;
}

int symblsm() {
	if (symbldy()) {
		int te;
		int tesym;
		char tetemp[500];
		if (sym == SEMICN) {
			cfot();
			cifa();
			if (sym != INTTK & sym != CHARTK) {
				return 1;
			}
			te = ftell(in);
			strcpy(tetemp, temp);
			tesym = sym;
			cifal();
			cifal();
		}
		else {
			error(11);
			if (sym != INTTK & sym != CHARTK) {
				return 1;
			}
			te = ftell(in);
			strcpy(tetemp, temp);
			tesym = sym;
			cifal();
			cifal();
		}
		while (sym != LPARENT) {
			fseek(in, te, SEEK_SET);
			sym = tesym;
			strcpy(temp, tetemp);
			if (symbldy()) {
				if (sym == SEMICN) {
					cfot();
					cifa();
					if (sym != INTTK & sym != CHARTK) {
						return 1;
					}
					te = ftell(in);
					strcpy(tetemp, temp);
					tesym = sym;
					cifal();
					cifal();
				}
				else {
					error(11);
					if (sym != INTTK & sym != CHARTK) {
						return 1;
					}
					te = ftell(in);
					strcpy(tetemp, temp);
					tesym = sym;
					cifal();
					cifal();
				}
			}
		}
		fseek(in, te, SEEK_SET);
		sym = tesym;
		strcpy(temp, tetemp);
		return 1;
	}
	return 0;
}

int symsmtb() {
	int lxtemp;
	lxtemp = symlxbsf();
	if (lxtemp) {
		if (lxtemp == 1) {
			hsfhb[hsfhbnum].iocov = 1;
		}
		else if (lxtemp == 2) {
			hsfhb[hsfhbnum].iocov = 2;
		}
		if (sym == IDENFR) {
			var_ioc[var_i++] = temp;
			strcpy(hsfhb[hsfhbnum].nam, temp);
			strcpy(dytp, dycengci);
			strcpy(dycengci, temp);
			for (int i = 0; i < hsfhbnum; i++) {
				if (strcmp(hsfhb[hsfhbnum].nam, hsfhb[i].nam) == 0) {
					error(2);
					break;
				}
			}
			cfot();
			cifa();
			//fprintf(out, "<声明头部>\n");
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

int symlxbsf() {
	if (sym == INTTK || sym == CHARTK) {
		cfot();
		fhb[fhbnum].type = 0;
		if (sym == INTTK) {
			cifa();
			return 1;
		}
		else {
			cifa();
			return 2;
		}
	}
	else {
		return 0;
	}

}

int symwfhzs() {
	if (sym == ZERO || sym == INTCON) {
		cfot();
		if (sym == INTCON) {
			cifa();
			//fprintf(out, "<无符号整数>\n");
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

int symzs() {
	if (isplus()) {
	}
	if (symwfhzs()) {
		//fprintf(out, "<整数>\n");
		return 1;
	}
	return 0;
}

int symcldy() {
	if (sym == INTTK) {
		int tempicv = 1;
		cfot();
		cifa();
		if (sym == IDENFR) {
			fhb[fhbnum].iocov = tempicv;
			fhb[fhbnum].type = 1;
			strcpy(fhb[fhbnum].nam, temp);
			strcpy(fhb[fhbnum].cengci, dycengci);
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
					error(2);
					break;
				}
			}
			fhbnum++;
			cfot();
			cifa();
			if (sym == ASSIGN) {
				cfot();
				cifa();
				if (symzs()) {
				}
				else {
					error(15);
					cifa();
				}
				while (sym == COMMA) {
					cfot();
					cifa();
					if (sym == IDENFR) {
						fhb[fhbnum].type = 1;
						fhb[fhbnum].iocov = 1;
						strcpy(fhb[fhbnum].nam, temp);
						strcpy(fhb[fhbnum].cengci, dycengci);
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
								error(2);
								break;
							}
						}
						fhbnum++;
						cfot();
						cifa();
						if (sym == ASSIGN) {
							cfot();
							cifa();
							if (symzs()) {
							}
							else {
								error(15);
								cifa();
							}
						}
					}
				}
				//fprintf(out, "<常量定义>\n");
				return 1;
			}
		}

	}
	else if (sym == CHARTK) {
		cfot();
		cifa();
		fhb[fhbnum].type = 1;
		fhb[fhbnum].iocov = 2;
		if (sym == IDENFR) {
			strcpy(fhb[fhbnum].nam, temp);
			strcpy(fhb[fhbnum].cengci, dycengci);
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
					error(2);
					break;
				}
			}
			fhbnum++;
			cfot();
			cifa();
			if (sym == ASSIGN) {
				cfot();
				cifa();
				if (symzf()) {
				}
				else {
					error(15);
					cifa();
				}
				while (sym == COMMA) {
					cfot();
					cifa();
					if (sym == IDENFR) {
						fhb[fhbnum].type = 1;
						fhb[fhbnum].iocov = 2;
						strcpy(fhb[fhbnum].nam, temp);
						strcpy(fhb[fhbnum].cengci, dycengci);
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
								error(2);
								break;
							}
						}
						fhbnum++;
						cfot();
						cifa();
						if (sym == ASSIGN) {
							cfot();
							cifa();
							if (symzf()) {
							}
							else {
								error(15);
								cifa();
							}
						}
					}
				}
				//fprintf(out, "<常量定义>\n");
				return 1;
			}
		}
	}
	else {

	}
	return 0;
}

int symclsm() {
	if (sym == CONSTTK) {
		cfot();
		cifa();
		symcldy();
		if (sym == SEMICN) {
			cfot();
			cifa();
		}
		else {
			error(11);
		}
		while (sym == CONSTTK) {
			cfot();
			cifa();
			symcldy();
			if (sym == SEMICN) {
				cfot();
				cifa();
			}
			else {
				error(11);
			}
		}
		//fprintf(out, "<常量说明>\n");
  		return 1;
	}
	return 0;
	
}

int symcx() {
	cifa();
	symclsm();
	if (sym == INTTK ||sym == CHARTK) {
		int teep = 0,te = 0;
		char ttep[10000];
		teep = sym;
		for (int i = 0; i < strlen(temp); i++) {
			ttep[i] = temp[i];
		}
		te = ftell(in);
		cifal();
		cifal();
		if (sym != LPARENT) {
			sym = teep;
			for (int i = 0; i <strlen(temp) || i < strlen(ttep); i++) {
				temp[i] = ttep[i];
			}
			fseek(in, te, SEEK_SET);
			symblsm();
		}
		else {
			sym = teep;
			for (int i = 0; i < strlen(temp) || i < strlen(ttep); i++) {
				temp[i] = ttep[i];
			}
			fseek(in, te, SEEK_SET);
		}
		
	}
	while (sym == INTTK || sym == CHARTK || sym == VOIDTK) {
		if (sym == VOIDTK) {
			int teep = 0,te = ftell(in);
			char ttep[500];
			for (int i = 0; i < strlen(temp); i++) {
				ttep[i] = temp[i];
			 }
			teep = sym;
			cifal();
			if (sym == IDENFR) {
				for (int i = 0; i < strlen(temp) || i < strlen(ttep); i++) {
					temp[i] = ttep[i];
				}
				sym = teep;
				fseek(in, te, SEEK_SET);
				symwfhzhsdy();
			}
			else {
				for (int i = 0; i < strlen(temp) || i < strlen(ttep); i++) {
					temp[i] = ttep[i];
				}
				sym = teep;
				fseek(in, te, SEEK_SET);
				break;
			}
		}
		else {
			symyfhzhsdy();
		}
	}
 	symzhs();
	//fprintf(out, "<程序>\n");
	return 1;
}

int symzfc(){
	
	if (sym == STRCON) {
		cfot();
		cifa();
		//fprintf(out, "<字符串>\n");
		return 1;
	}
	return 0;
}

int symzf() {
	if (sym == CHARCON) {
		cfot();
		cifa();
		return 1;
	}
	return 0;
}

int isgx() {
	if (sym == LSS || sym == LEQ || sym == GRE || sym == GEQ || sym == NEQ || sym == EQL) {
		cfot();
		cifa();
		return 1;
	}
	return 0;
}

int ismult() {
	
	if (sym == MULT || sym == DIV) {
		cfot();
		cifa();
		return 1;
	}
	return 0;
}

int isplus() {
	if (sym == PLUS || sym == MINU) {
		cfot();
		cifa();
		return 1;
	}
	return 0;
}

int cifa(){
	char pRintf[] = "printf", rEturn[] = "return";
	char cOnst[] = "const", iNt[] = "int";
	char cHar[] = "char", vOid[] = "void", mAin[] = "main";
	char iF[] = "if", eLse[] = "else", dO[] = "do";
	char wHile[] = "while", fOr[] = "for", sCanf[] = "scanf";
	int num = 0;
	char e = '\0';
	if (e == '\n') {
		lnum = lnum + 1;
	}
	e = fgetc(in);
	while (isspace(e) != 0 ) {
		if (e == '\n') {
			lnum = lnum + 1;
		}
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

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, iNt) == 0) {
			sym = INTTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, cHar) == 0) {
			sym = CHARTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, vOid) == 0) {
			sym = VOIDTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, mAin) == 0) {
			sym = MAINTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, iF) == 0) {
			sym = IFTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, eLse) == 0) {
			sym = ELSETK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, dO) == 0) {
			sym = DOTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, wHile) == 0) {
			sym = WHILETK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, fOr) == 0) {
			sym = FORTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, sCanf) == 0) {
			sym = SCANFTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, pRintf) == 0) {
			sym = PRINTFTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, rEturn) == 0) {
			sym = RETURNTK;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else {
			sym = IDENFR;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		/*
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		*/
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
		if (temp[0] == '0' && temp[1] != '\0') {
			sym = -1;
		}

		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		/*
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		*/
		ungetc(e, in);
	

	}

	else if (e == 39) {
		e = fgetc(in);
		char tp;
		tp = e;
		if ((tp < 48 && (tp != 43 && tp != 45 && tp != 42 && tp !=  47)) || (tp > 57 && tp < 65) || tp > 122) {
			error(1);
		}
		temp[0] = tp;
		e = fgetc(in);
		if (e == 39) {
			sym = CHARCON;

			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else {
			error(1);
		}
	}
	else if (e == 34) {
		int i = 0;
		e = fgetc(in);
		if (((e < 35 && e != 32 && e != 33) || e > 126) && e != 34) {
			error(1);
			e = fgetc(in);
		}
		while (e == 32 || e == 33 || (e >= 35 && e <= 125)) {
			if (e == ')') {
				e = fgetc(in);
				if (e == ';') {
					e = fgetc(in);
					if (e == '\n') {
						ungetc('\n', in);
						ungetc(';', in);
						ungetc(')',in);
						sym = STRCON;
						break;
					}
					else {
						ungetc(e, in);
						ungetc(';', in);
						e = ')';
					}
				}
				else {
					ungetc(e, in);
					e = ')';
				}
			}
			temp[i++] = e;
			e = fgetc(in);
			if (((e < 35 && e != 32 && e != 33) || e > 126) && e != 34) {
				error(1);
				e = fgetc(in);
			}
		}
		if (e == 34) {
			sym = STRCON;
		}
		else {
			if(e != EOF)
			error(1);
		}


		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		/*
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		*/
	}
	else if (e == '+') {
		temp[0] = e;
		sym = PLUS;

		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '-') {
		temp[0] = e;
		sym = MINU;

		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '*') {
		temp[0] = e;
		sym = MULT;

		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '/') {
		temp[0] = e;
		sym = DIV;

		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '<') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '<';
			temp[1] = '=';
			sym = LEQ;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[1] = '\0';
		//	temp[0] = '\0';
		}
		else {
			temp[0] = '<';
			sym = LSS;

		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '>') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '>';
			temp[1] = '=';
			sym = GEQ;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[1] = '\0';
		//	temp[0] = '\0';
		}
		else {
			temp[0] = '>';
			sym = GRE;

		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '=') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '=';
			temp[1] = '=';
			sym = EQL;

		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[1] = '\0';
		//	temp[0] = '\0';
		}
		else {
			temp[0] = '=';
			sym = ASSIGN;

		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '!') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '!';
			temp[1] = '=';
			sym = NEQ;

		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		//	temp[1] = '\0';
		//	temp[0] = '\0';
		}
		else {
			ungetc(e, in);
		}
	}
	else if (e == ';') {
		temp[0] = e;
		sym = SEMICN;

		//fprintf(out, "%s %s"\n, outtemp[sym].c_str(), temp);
	//	temp[0] = '0';
	}
	else if (e == ',') {
		temp[0] = e;
		sym = COMMA;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else if (e == '(') {
		temp[0] = e;
		sym = LPARENT;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else if (e == ')') {
		temp[0] = e;
		sym = RPARENT;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else if (e == '[') {
		temp[0] = e;
		sym = LBRACK;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else if (e == ']') {
		temp[0] = e;
		sym = RBRACK;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else if (e == '{') {
		temp[0] = e;
		sym = LBRACE;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else if (e == '}') {
		temp[0] = e;
		sym = RBRACE;

	//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//	temp[0] = '\0';
	}
	else {
	error(1);
	cifa();
	}
	return sym;
}

int cifal() {
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
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, iNt) == 0) {
			sym = INTTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, cHar) == 0) {
			sym = CHARTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, vOid) == 0) {
			sym = VOIDTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, mAin) == 0) {
			sym = MAINTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, iF) == 0) {
			sym = IFTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, eLse) == 0) {
			sym = ELSETK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, dO) == 0) {
			sym = DOTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, wHile) == 0) {
			sym = WHILETK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, fOr) == 0) {
			sym = FORTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, sCanf) == 0) {
			sym = SCANFTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, pRintf) == 0) {
			sym = PRINTFTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else if (strcmp(temp, rEturn) == 0) {
			sym = RETURNTK;
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
		else {
			sym = IDENFR;
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
			//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		}
	}
	else if (e == 34) {
		int i = 0;
		while ((e = fgetc(in)) != 34) {
			temp[i++] = e;
		}
		sym = STRCON;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
		
		for (int j = 0; j < i; j++) {
			temp[j] = '\0';
		}
		
	}
	else if (e == '+') {
		temp[0] = e;
		sym = PLUS;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '-') {
		temp[0] = e;
		sym = MINU;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '*') {
		temp[0] = e;
		sym = MULT;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '/') {
		temp[0] = e;
		sym = MULT;
		//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	}
	else if (e == '<') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '<';
			temp[1] = '=';
			sym = LEQ;
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			temp[0] = '<';
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[0] = '\0';
			ungetc(e, in);
		}
	}
	else if (e == '>') {
		if ((e = fgetc(in)) == '=') {
			temp[0] = '>';
			temp[1] = '=';
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			temp[0] = '>';
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
			//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
				temp[1] = '\0';
				temp[0] = '\0';
		}
		else {
			temp[0] = '=';
			sym = ASSIGN;
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
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == ',') {
		temp[0] = e;
		sym = COMMA;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '(') {
		temp[0] = e;
		sym = LPARENT;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == ')') {
		temp[0] = e;
		sym = RPARENT;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '[') {
		temp[0] = e;
		sym = LBRACK;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == ']') {
		temp[0] = e;
		sym = RBRACK;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '{') {
		temp[0] = e;
		sym = LBRACE;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}
	else if (e == '}') {
		temp[0] = e;
		sym = RBRACE;
		//	fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
			temp[0] = '\0';
	}

	return sym;
}

void cfot() {
	//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//printf("%s %s\n", outtemp[sym].c_str(), temp);
	for (int j = 0; j < 10000; j++) {
		temp[j] = '\0';
	}
}
