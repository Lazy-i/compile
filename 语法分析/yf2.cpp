
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<string>
#include <iostream>
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
char* nextvar();
char* nextlab();
void prtmidcode();
void makemips();
void mkvaladr(const char* item,const char* funcname ,const char* kind,const char* reg);
int getvaladr(const char* item, const char* funcname);
void insmidcode(const char* op,const char* t1, const char* t2,const char* t3);
void insmidcode(const char* op, int t1, int t2,const char* t3);
void insmidcode(const char* op,const char* t1, int t2,const char* t3);
int getfuncpanum(const char* funcname);
void prtfhb();
FILE* in,* out,*mout,*fout,*eout;
int sym = -1;
int rtn = -1;
int rtc = 0;
int glbalval = 0;
int varcnt = 0;
int labcnt = 0;
char temp[10000] = { "\0" };
string var_ioc[10000];
string var_void[10000];
struct fuhaob {
	int type;// integer 0,const 1,function 2，para 3;
	int iocov;//int 1,char 2,void 3;
	int value; // 常量的值
	char nam[64]; //name;
	char cengci[64]; //层次 所属函数名全局变量为global;
	int vadr;
}fhb[10240];
struct hsfuhaob {
	int iocov;//int 1,char 2,void 3;
	char nam[64]; //name;
	int csnum; //参数数量
	string csnam[30];
	int cstype[30]; //参数类型：int 1, char 2;
	int hsadrst;
	int hsadred;
}hsfhb[1024];
struct shuwuchuan {
	int tpye;
	char nam[64];
}srdl[10000];
struct zjdm {
	string op;
	string var1;
	string var2;
	string var3;
}midcode[10240];
int midcodenum = 0;
int hsfhbnum = 0;
int fhbnum = 0;
int $sp = 0;
int $fp = 53687387;
int $s7 = 0;
int galstkst = 67125239;
int galstked;
char dycengci[64] = "global";
const char cc[64] = "main";
const char glb[64] = "global";
char c2mfname[64] = "global";
char dytp[64] = "global";
int var_i = 0;
int var_v = 0;
int isym[2000] = { 0 };
int aynm = 0;
int lnum = 1;
int rtline = 0;
int slnum = 0;
char nowim[200];
char nowarray[200];
int globalchar = 0;
int callres = 0;
int midvar = 0;
int paranum = 0; //存参数时的参数个数 每次paranum--;
int gol = 0; //局部变量或全局变量
int facttype = INTTK;
int main() {
	//fopen_s(&in, "testfile.txt", "r");
	//fopen_s(&out, "error.txt", "w");
	 in = fopen("testfile.txt","r");
	 out = fopen("mips.txt", "w");
	 mout = fopen("midcode.txt", "w");
	 fout = fopen("fhbdata.txt", "w");
	 eout = fopen("error.txt", "w");
	symcx();
	//prtmidcode();
	/*for (int i = 0; i < fhbnum; i++) {
		printf("%d %d %s %d\n", fhb[i].type, fhb[i].iocov, fhb[i].nam, fhb[i].cengci);
	}
	for (int i = 0; i < hsfhbnum; i++) {
		printf("%d %s %d ", hsfhb[i].iocov, hsfhb[i].nam, hsfhb[i].csnum);
		for (int j = 0; j < hsfhb[i].csnum; j++) {
			printf("%s ", hsfhb[i].csnam[j].c_str());
		}
		printf("\n");
	}*/
	prtfhb();
	prtmidcode(); 
  	makemips();
	return 0;
}
void prtfhb() {
	for (int i = 0; i < fhbnum; i++) {
		fprintf(fout, "id:%d\t\tcengci:%s\t\ticv:%d\tnam:%s\t\t\ttype:%d\tvadr:%d\t\tvalue:%d\n",i, fhb[i].cengci, fhb[i].iocov, fhb[i].nam, fhb[i].type, fhb[i].vadr, fhb[i].value);
	}
}


void prtmidcode() {
	for (int i = 0; i < midcodenum; i++) {
		fprintf(mout,"%s %s %s %s \n", midcode[i].op.c_str(), midcode[i].var1.c_str(), midcode[i].var2.c_str(), midcode[i].var3.c_str());
		//printf("%s %s %s %s \n", midcode[i].op.c_str(), midcode[i].var1.c_str(), midcode[i].var2.c_str(), midcode[i].var3.c_str());
	}
}

void insmidcode(const char* op, int t1, int t2, const char* t3) {
	char tp[500];
	midcode[midcodenum].op = op;
	sprintf(tp, "%d", t1);
	midcode[midcodenum].var1 = tp;
	sprintf(tp, "%d", t2);
	midcode[midcodenum].var2 = tp;
	midcode[midcodenum].var3 = t3;
	midcodenum++;
}

void insmidcode(const char* op, const char* t1, const char* t2, const char* t3) {
	midcode[midcodenum].op   = op;
	midcode[midcodenum].var1 = t1;
	midcode[midcodenum].var2 = t2;
	midcode[midcodenum].var3 = t3;
	midcodenum++;
}

void insmidcode(const char* op, const char* t1, int t2, const char* t3) {
	char tp[500];
	midcode[midcodenum].op   = op;
	midcode[midcodenum].var1 = t1;
	sprintf(tp, "%d", t2);
	midcode[midcodenum].var2 = tp;
	midcode[midcodenum].var3 = t3;
	midcodenum++;
}
//生成中间变量
char* nextvar() {
	char *var = (char*)malloc(sizeof(char) * 20);
	sprintf(var, "$_%d", varcnt++);
	strcpy(fhb[fhbnum].nam, var);
	fhb[fhbnum].vadr = $s7 * 4;
	$s7++;
	strcpy(fhb[fhbnum].cengci, "midv");
	fhbnum++;
	return var;
}
//生成标记
char* nextlab() {
	char* lab = (char*)malloc(sizeof(char) * 20);
	strcpy(lab, "_lable_");
	sprintf(lab, "_lable_%d", labcnt++);
	return lab;
}
//获取地址并生成mips码
void mkvaladr(const char* item,const char* funcname,const char* kind,const char* reg) {
	int begin = 0;
	int end = 0;
	for (int i = 0; i < hsfhbnum; i++) {
		if (strcmp(funcname, hsfhb[i].nam) == 0 ) {
			begin = hsfhb[i].hsadrst;
			end = hsfhb[i].hsadred;
			break;
		}
	}
	for (int i = begin; i < end; i++) {
		if (strcmp(item, fhb[i].nam) == 0 && strcmp(fhb[i].cengci,funcname) == 0) {
			 fprintf(out, "\t%s\t%s\t-%d($fp)\n",kind, reg, fhb[i].vadr);
			 return;
		}
	}
	begin = 0;
	end = fhbnum;
	for (int i = begin; i < end; i++) {
		if (strcmp(item, fhb[i].nam) == 0 && strcmp(fhb[i].cengci,glb) == 0) {
			fprintf(out, "\t%s\t%s\t%d($t8)\n",  kind, reg, fhb[i].vadr);
			return ;
		}
	}
	begin = 0;
	end = fhbnum;
	for (int i = begin; i < end; i++) {
		if (strcmp(item, fhb[i].nam) == 0 && strcmp(fhb[i].cengci, "midv") == 0) {
			fprintf(out, "\t%s\t%s\t%d($s7)\n", kind, reg, fhb[i].vadr);
			if (fhb[i].vadr >= 400){
				fprintf(out, "Intermediate variable out of bounds!\n");
			}
			return;
		}
	}
	return;
}
//获取地址
int getvaladr(const char* item, const char* funcname) {
	int begin = 0;
	int end = 0;
	int flag = 0;
	char p3[30];
	gol = 0;
	for (int i = 0; i < hsfhbnum; i++) {
		if (strcmp(funcname, hsfhb[i].nam) == 0) {
			begin = hsfhb[i].hsadrst;
			end = hsfhb[i].hsadred;
			flag = 1;
			break;
		}
	}
	for (int i = begin; i < end; i++) {
		if (strcmp(item, fhb[i].nam) == 0 && strcmp(fhb[i].cengci,funcname) == 0) {
			gol = 1;
			return fhb[i].vadr;
		}
	}
	begin = 0;
	end = fhbnum;
	for (int i = begin; i < end; i++) {
		if (strcmp(item, fhb[i].nam) == 0 && strcmp(fhb[i].cengci,glb) == 0) {
			return fhb[i].vadr;
		}
	}
	begin = 0;
	end = fhbnum;
	for (int i = begin; i < end; i++) {
		if (strcmp(item, fhb[i].nam) == 0 && strcmp(fhb[i].cengci, "midv") == 0) {
			gol = 2;
			return fhb[i].vadr;
		}
	}
	fprintf(out, "#array adr error\n");
	return -1;
}

int getfuncpanum(const char* funcname) {
	for (int i = 0; i < hsfhbnum; i++) {
		if (strcmp(hsfhb[i].nam, funcname) == 0) {
			return hsfhb[i].csnum;
		}
	}
	fprintf(out, "\t\t\t#\tget\tfuncparanumer\terror\n");
	return -1;
}

//生成mips
void makemips() {
	//int tod = -1; //tod == 0 .data // tod == 1 .text
	//fprintf(out, ".data\n");
	//tod = 0;	//.data
	int tod = 0;
	fprintf(out, ".data\n");
	fprintf(out, "enter:.asciiz \"\\n\"\n");
	fprintf(out, ".text\n");
	fprintf(out, "\tli\t$t8\t268500996\n");
	fprintf(out, "\tmove\t$fp\t$sp\n");
	fprintf(out, "\tmove\t$s7\t$gp\n");
	for (int i = 0; i < midcodenum; i++) {
		while (midcode[i].op == "const" || midcode[i].op == "int" || midcode[i].op == "char") {
 			if (tod == 0) {
				if (midcode[i].op == "const") {
					int temp;
					if (midcode[i].var1 == "int") {
						temp = stoi(midcode[i].var2);
					}
					else {
						temp = stoi(midcode[i].var2.c_str());
					}
					fprintf(out, "\tli\t$t0\t%d\n", temp);
					mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
					//fprintf(out, "\taddi\t$t8\t$t8\t4\n");
					fprintf(out, "\t\t\t#存全局常量\n");
					i++;
				}
				else if(midcode[i].var1 == "array"){
					int temp;
					temp = stoi(midcode[i].var2);
					temp = temp * 4;
					//fprintf(out, "\taddi\t$t8\t$t8\t%d\n", temp);
					fprintf(out, "\t\t\t#存全局数组\n");
					i++;
				}
				else {
					//fprintf(out, "\taddi\t$t8\t$t8\t4\n");
					fprintf(out, "\t\t\t#存全局变量\n");
					i++;
				}
			}
			else {
				if (midcode[i].op != "const") {
					if (strcmp(midcode[i].var1.c_str(), "array") != 0) {
						fprintf(out, "\taddi\t$sp\t$sp\t-4\n");
						fprintf(out, "\t\t\t#存局部变量\n");
						i++;
					}
					else {
						int temp;
						temp = stoi(midcode[i].var2);
						temp = temp * 4;
						fprintf(out, "\taddi\t$sp\t$sp\t-%d\n",temp);
						fprintf(out, "\t\t\t#存局部数组\n");
						i++;
					}
				}
				else {
					int temp;
					if (midcode[i].var1 == "int") {
						temp = stoi(midcode[i].var2);
					}
					else {
						temp = stoi(midcode[i].var2.c_str());
					}
					fprintf(out, "\tli\t$t0\t%d\n", temp);
					mkvaladr(midcode[i].var3.c_str(), c2mfname,"sw","$t0");
					fprintf(out, "\taddi\t$sp\t$sp\t-4\n");
					fprintf(out, "\t\t\t#存局部常量\n");
					i++;
				}
			}
		}
		if (tod != 1) {
			tod = 1;
			fprintf(out, "\tj\tmain\n");
		}
		if (strcmp(midcode[i].op.c_str(), "scf") == 0) {  //读语句
			if (midcode[i].var2 == "int") {
				fprintf(out, "\tli\t$v0\t5\n");
				fprintf(out, "\tsyscall\n");
				mkvaladr(midcode[i].var3.c_str(),c2mfname,"sw","$v0");
				fprintf(out, "\t\t\t#读int型变量\n");
			}
			else if (midcode[i].var2 == "char") {
				fprintf(out, "\tli\t$v0\t12\n");
				fprintf(out, "\tsyscall\n");
				mkvaladr(midcode[i].var3.c_str(),c2mfname,"sw","$v0");
				fprintf(out, "\t\t\t#读char变量\n");
			}
			continue;
		}
		else if (strcmp(midcode[i].op.c_str(), "prt") == 0) {	//写语句
			if (midcode[i].var1 != "\0") {
				int strln;
				strln = midcode[i].var1.size();
				for (int j = 0; j < strln; j++) {
					fprintf(out, "\tli\t$v0\t11\n");
					fprintf(out, "\tla\t$a0\t%d\n", int(midcode[i].var1.at(j)));
					fprintf(out, "\tsyscall\n");
					fprintf(out, "\t\t\t#写字符串\n");
				}
			}
			if (midcode[i].var2 != "NULL") {
				if (isdigit(midcode[i].var2.at(0)) != 0 && midcode[i].var3 == "char") {	//单个字符存入为ascii码
					fprintf(out, "\tli\t$v0\t11\n");
					fprintf(out, "\tli\t$a0\t%s\n", midcode[i].var2.c_str());
					fprintf(out, "\tsyscall\n");
					fprintf(out, "\t\t\t#写单个字符（表达式）\n");
				}
				else if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
					fprintf(out, "\tli\t$v0\t1\n");
					fprintf(out, "\tli\t$a0\t%s\n", midcode[i].var2.c_str());
					fprintf(out, "\tsyscall\n");
					fprintf(out, "\t\t\t#写数字\n");
				}
				else if (isdigit(midcode[i].var2.at(0)) == 0 && midcode[i].var3 == "int") {
					mkvaladr(midcode[i].var2.c_str(),c2mfname,"lw","$a0");
					fprintf(out, "\tli\t$v0\t1\n");
					fprintf(out, "\tsyscall\n");
					fprintf(out, "\t\t\t#写int型变量\n");
				}
				else if (isdigit(midcode[i].var2.at(0)) == 0 && midcode[i].var3 == "char") {
					mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$a0");
					fprintf(out, "\tli\t$v0\t11\n");
					fprintf(out, "\tsyscall\n");
					fprintf(out, "\t\t\t#写char型变量\n");
				}
			}
			fprintf(out, "\tla\t$a0\tenter\n");
			fprintf(out, "\tli\t$v0\t4\n");
			fprintf(out, "\tsyscall\n");
			fprintf(out, "\t\t\t#输出回车\n");
			continue;
		}
		else if (strcmp(midcode[i].op.c_str(), "+") == 0) {
			if (isdigit(midcode[i].var1.at(0)) != 0 || midcode[i].var1.at(0) == '-' || midcode[i].var1.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%s\n", midcode[i].var1.c_str());
				fprintf(out, "\t\t\t#加运算读第一个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var1.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#加运算读第一个为变量\n");
			}
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t1\t%s\n", midcode[i].var2.c_str());
				fprintf(out, "\t\t\t#加运算读第二个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t1");
				fprintf(out, "\t\t\t#加运算读第二个为变量\n");
			}
			fprintf(out, "\tadd $t0\t$t0\t$t1\n");
			mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
			fprintf(out, "\t\t\t#存加运算\n");
			continue;
		}
		else if (strcmp(midcode[i].op.c_str(), "-") == 0) {
			if (isdigit(midcode[i].var1.at(0)) != 0 || midcode[i].var1.at(0) == '-' || midcode[i].var1.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%s\n", midcode[i].var1.c_str());
				fprintf(out, "\t\t\t#减运算读第一个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var1.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#减运算读第一个为变量\n");
			}
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t1\t%s\n", midcode[i].var2.c_str());
				fprintf(out, "\t\t\t#减运算读第二个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t1");
				fprintf(out, "\t\t\t#减运算读第二个为变量\n");
			}
			fprintf(out, "\tsub $t0\t$t0\t$t1\n");
			mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
			fprintf(out, "\t\t\t#存减运算\n");
			continue;
		}
		else if (strcmp(midcode[i].op.c_str(), "*") == 0) {
			if (isdigit(midcode[i].var1.at(0)) != 0 || midcode[i].var1.at(0) == '-' || midcode[i].var1.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%s\n", midcode[i].var1.c_str());
				fprintf(out, "\t\t\t#乘运算读第一个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var1.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#乘运算读第一个为变量\n");
			}
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t1\t%s\n", midcode[i].var2.c_str());
				fprintf(out, "\t\t\t#乘运算读第二个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t1");
				fprintf(out, "\t\t\t#乘运算读第二个为变量\n");
			}
			fprintf(out, "\tmul $t0\t$t0\t$t1\n");
			mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
			fprintf(out, "\t\t\t#存乘运算\n");
			continue;
		}
		else if (strcmp(midcode[i].op.c_str(), "/") == 0) {
			if (isdigit(midcode[i].var1.at(0)) != 0 || midcode[i].var1.at(0) == '-' || midcode[i].var1.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%s\n", midcode[i].var1.c_str());
				fprintf(out, "\t\t\t#除运算读第一个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var1.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#除运算读第一个为变量\n");
			}
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t1\t%s\n", midcode[i].var2.c_str());
				fprintf(out, "\t\t\t#除运算读第二个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t1");
				fprintf(out, "\t\t\t#除运算读第二个为变量\n");
			}
			fprintf(out, "\tdiv $t0\t$t0\t$t1\n");
			mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
			fprintf(out, "\t\t\t#存除运算\n");
			continue;
		}
		else if (strcmp(midcode[i].op.c_str(), "=") == 0) {
			if (isdigit(midcode[i].var1.at(0)) != 0) {
				fprintf(out, "\tli\t$t0\t%d\n", stoi(midcode[i].var1));
				mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
				fprintf(out, "\t\t\t#赋值语句等号右边为数字\n");
			}
			else {
				mkvaladr(midcode[i].var1.c_str(), c2mfname, "lw", "$t0");
				mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
				fprintf(out, "\t\t\t#赋值语句等号右边为变量\n");
			}
		}
		else if (strcmp(midcode[i].op.c_str(), "[]=") == 0) {
		int tpadr = 0;
			tpadr = getvaladr(midcode[i].var1.c_str(), c2mfname);
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t9\t%d\n",(4*stoi(midcode[i].var2)));
				fprintf(out, "\t\t\t#数组赋值数组下标为数字\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t9");
				//fprintf(out, "\taddi\t$t9\t$t9\t1\n");
				fprintf(out, "\tsll\t$t9\t$t9\t2\n");
				fprintf(out, "\t\t\t#数组赋值数组下标为变量\n");
			}
			if (isdigit(midcode[i].var3.at(0)) != 0 || midcode[i].var3.at(0) == '-' || midcode[i].var3.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%d\n", stoi(midcode[i].var3));
				fprintf(out, "\t\t\t#数组赋值等号右边为数字\n");
			}
			else {
				mkvaladr(midcode[i].var3.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#数组赋值等号右边为变量\n");

			}
			if (gol == 1) {
				fprintf(out, "\tsub\t$t9\t$fp\t$t9\n");
				fprintf(out, "\tsw\t$t0\t-%d($t9)\n",tpadr);
				fprintf(out, "\t\t\t#若数组为局部变量取地址赋值\n");
			}
			else if (gol == 0) {
				fprintf(out, "\tadd\t$t9\t$t8\t$t9\n");
				fprintf(out, "\tsw\t$t0\t%d($t9)\n",tpadr);
				fprintf(out, "\t\t\t#若数组为全局变量取地址赋值\n");
			}
		}
		else if (strcmp(midcode[i].op.c_str(), "pufa") == 0) {
			if (isdigit(midcode[i].var3.at(0)) != 0 || midcode[i].var3.at(0) == '-' || midcode[i].var3.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%s\n", midcode[i].var3.c_str());
				fprintf(out, "\t\t\t#值参数为数字\n");
			}
			else {
				mkvaladr(midcode[i].var3.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#值参数为变量\n");
			}
			fprintf(out, "\tsw\t$t0\t($sp)\n");
			fprintf(out, "\taddi\t$sp\t$sp\t-4\n");
			fprintf(out, "\t\t\t#值参数值存栈\n");
		}
		else if(strcmp(midcode[i].op.c_str(), "para") == 0){
			int addr;
			addr = paranum * 4;
			fprintf(out, "\tlw\t$t0\t%d($fp)\n", addr);
			mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
			fprintf(out, "\t\t\t#参数存栈\n");
			fprintf(out, "\taddi\t$sp\t$sp\t-4\n");
			fprintf(out, "\t\t\t#栈顶上移\n");
			paranum--;
		}
		else if (strcmp(midcode[i].op.c_str(), "call") == 0) {
			if (midcode[i].var1 == "") {
				fprintf(out, "\tjal\t%s\n", midcode[i].var3.c_str());
				fprintf(out, "\t\t\t#函数调用不需返回值\n");
			}
			else {
				fprintf(out, "\tjal\t%s\n", midcode[i].var3.c_str());
				mkvaladr(midcode[i].var1.c_str(),c2mfname, "sw", "$t4");
				fprintf(out, "\t\t\t#函数调用将$t4（返回值）存入中间变量\n");
			}
		}
		else if (strcmp(midcode[i].op.c_str(), "<=") == 0 || strcmp(midcode[i].op.c_str(), ">=") == 0 || strcmp(midcode[i].op.c_str(), "<") == 0 || strcmp(midcode[i].op.c_str(), ">") == 0 || strcmp(midcode[i].op.c_str(), "!=") == 0 || strcmp(midcode[i].op.c_str(), "==") == 0) {
			if (isdigit(midcode[i].var1.at(0)) != 0 || midcode[i].var1.at(0) == '-' || midcode[i].var1.at(0) == '+') {
				fprintf(out, "\tli\t$t0\t%s\n", midcode[i].var1.c_str());
				fprintf(out, "\t\t\t#关系运算读第一个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var1.c_str(), c2mfname, "lw", "$t0");
				fprintf(out, "\t\t\t#关系运算读第一个为变量\n");
			}
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t1\t%s\n", midcode[i].var2.c_str());
				fprintf(out, "\t\t\t#关系运算读第二个为数字\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t1");
				fprintf(out, "\t\t\t#关系运算读第二个为变量\n");
			}
			if (midcode[i].op == "<=") {
				fprintf(out, "\taddi\t$t1\t$t1\t1\n");
				fprintf(out, "\tslt\t$v0\t$t0\t$t1\n");
				fprintf(out, "\t\t\t#若关系运算符为小于等于判断 a < b + 1\n");
			}
			else if (midcode[i].op == ">=") {
				fprintf(out, "\taddi\t$t0\t$t0\t1\n");
				fprintf(out, "\tslt\t$v0\t$t1\t$t0\n");
				fprintf(out, "\t\t\t#若关系运算符为大于等于判断 b < a + 1\n");

			}
			else if (midcode[i].op == ">") {
				fprintf(out, "\tslt\t$v0\t$t1\t$t0\n");
				fprintf(out, "\t\t\t#若关系运算符为大于号时判断 b < a\n");
			}
			else if (midcode[i].op == "<") {
				fprintf(out, "\tslt\t$v0\t$t0\t$t1\n");
				fprintf(out, "\t\t\t#若关系运算符为小于号时判断 a < b\n");
			}
			else if (midcode[i].op == "!=") {
				char lab1[30];
				char lab2[30];
				strcpy(lab1, nextlab());
				strcpy(lab2, nextlab());
				fprintf(out, "\tbeq\t$t0\t$t1\t%s\n", lab1);
				fprintf(out, "\tli\t$v0\t1\n");
				fprintf(out, "\tj\t%s\n", lab2);
				fprintf(out, "%s:\n", lab1);
				fprintf(out, "\tli\t$v0\t0\n");
				fprintf(out, "%s:\n", lab2);
				fprintf(out, "\t\t\t#若关系运算符为等于号时判断 \n");

			}
			else if (midcode[i].op == "==") {
				//fprintf(out, "\tand\t$t0\t$t0\t$t1\n");
				//fprintf(out, "\t\t\t#若关系运算符为等于号时判断 a and b\n");
				char lab1[30];
				char lab2[30];
				strcpy(lab1, nextlab());
				strcpy(lab2, nextlab());
				fprintf(out, "\tbne\t$t0\t$t1\t%s\n", lab1);
				fprintf(out, "\tli\t$v0\t1\n");
				fprintf(out, "\tj\t%s\n", lab2);
				fprintf(out, "%s:\n", lab1);
				fprintf(out, "\tli\t$v0\t0\n");
				fprintf(out, "%s:\n", lab2);
				fprintf(out, "\t\t\t#若关系运算符为等于号时判断 \n");
			}
		}
		else if (strcmp(midcode[i].op.c_str(), "jne") == 0) {
			fprintf(out, "\tbne\t$v0\t1\t%s\n", midcode[i].var3.c_str());
			fprintf(out, "\t\t\t#满足时跳转\n");
		}
		else if (strcmp(midcode[i].op.c_str(), "jmp") == 0) {
			fprintf(out, "\tj\t%s\n", midcode[i].var3.c_str());
			fprintf(out, "\t\t\t#无条件跳转\n");
		}
		else if (strcmp(midcode[i].op.c_str(), "lab:") == 0) {
			fprintf(out, "%s:\n", midcode[i].var3.c_str());
			fprintf(out, "\t\t\t#输出跳转标签\n");
		}
		else if (strcmp(midcode[i].op.c_str(), "geta") == 0) {
			int tpadr = 0;
			tpadr = getvaladr(midcode[i].var1.c_str(), c2mfname);
			if (isdigit(midcode[i].var2.at(0)) != 0 || midcode[i].var2.at(0) == '-' || midcode[i].var2.at(0) == '+') {
				fprintf(out, "\tli\t$t9\t%d\n",(4*stoi(midcode[i].var2)));
				fprintf(out, "\t\t\t#等号右边的数组的数组下标为数字读相对数组首地址偏移\n");
			}
			else {
				mkvaladr(midcode[i].var2.c_str(), c2mfname, "lw", "$t9");
				//fprintf(out, "\taddi\t$t9\t$t9\t1\n");
				fprintf(out, "\tsll\t$t9\t$t9\t2\n");
				fprintf(out, "\t\t\t#等号右边的数组的数组下标为变量读相对数组首地址偏移\n");

			}
			if (gol == 1) {
				fprintf(out, "\tsub\t$t9\t$fp\t$t9\n");
				fprintf(out, "\tlw\t$t0\t-%d($t9)\n",tpadr);
				fprintf(out, "\t\t\t#若数组为局部变量读数组首地址\n");
			}
			else if (gol == 0) {
				fprintf(out, "\tadd\t$t9\t$t8\t$t9\n");
				fprintf(out, "\tlw\t$t0\t%d($t9)\n",tpadr);
				fprintf(out, "\t\t\t#若数组为全局变量读数组首地址\n");
			}
			mkvaladr(midcode[i].var3.c_str(), c2mfname, "sw", "$t0");
			fprintf(out, "\t\t\t#赋值\n");
		}
		else if (strcmp(midcode[i].op.c_str(), "fund") == 0) {
			strcpy(c2mfname, glb);
			if (midcode[i].var3 != "main") {
				paranum = getfuncpanum(midcode[i].var3.c_str());
				fprintf(out, "end_%s:\n", midcode[i].var3.c_str());
				fprintf(out, "\t\t\t#函数结束标签\n");
				fprintf(out, "\tlw\t$ra\t-4($fp)\n");
				fprintf(out, "\t\t\t#返回ra值\n");
				fprintf(out, "\tmove\t$sp\t$fp\n");
				fprintf(out, "\t\t\t#将sp调制fp位置\n");
				fprintf(out, "\tlw\t$fp\t($fp)\n");
				fprintf(out, "\t\t\t#返回fp值\n");
				fprintf(out, "\taddi\t$sp\t$sp\t%d\n",4*paranum);
				fprintf(out, "\t\t\t#将值参数清除\n");
				fprintf(out, "\tsubi\t$s7\t$s7\t1200\n");
				fprintf(out, "\tjr\t$ra\n");
				fprintf(out, "\t\t\t#跳回原地址\n");
				paranum = 0;
			}
			else {
				fprintf(out, "end_%s:\n", midcode[i].var3.c_str());
				fprintf(out, "\tli\t$v0\t10\n");
				fprintf(out, "\tsyscall\n");
				fprintf(out, "\t\t\t#函数结束\n");
			}


		}
		else if (strcmp(midcode[i].op.c_str(), "func") == 0) {
			paranum = getfuncpanum(midcode[i].var3.c_str());
			fprintf(out,"%s:\n",midcode[i].var3.c_str());
			fprintf(out, "\t\t\t#函数开始标签\n");
			strcpy(c2mfname, midcode[i].var3.c_str());
			if (midcode[i].var3 != "main") {
				fprintf(out, "\t\t\t#不是main函数\n");
				fprintf(out, "\tsw\t$fp\t($sp)\n");
				fprintf(out, "\tmove\t$fp\t$sp\n");
				fprintf(out, "\taddi\t$sp\t$sp\t-4\n");
				fprintf(out, "\t\t\t#保存$fp并将fp移动至栈顶\n");
				fprintf(out, "\tsw\t$ra\t($sp)\n");
				fprintf(out, "\taddi\t$sp\t$sp\t-4\n");
				fprintf(out, "\t\t\t#保存$ra\n");
				fprintf(out, "\taddi\t$s7\t$s7\t1200\n");
			}
		}
		else if (strcmp(midcode[i].op.c_str(), "jeq") == 0) {
			fprintf(out, "\tbeq\t$v0\t1\t%s\n", midcode[i].var3.c_str());
			fprintf(out, "\t\t\t#不满足时跳转\n");
		}
		else if (strcmp(midcode[i].op.c_str(), "ret") == 0) {
			if (midcode[i].var3 != "") {
				if (isdigit(midcode[i].var3.at(0)) != 0 || midcode[i].var3.at(0) == '-' || midcode[i].var3.at(0) == '+') {
					fprintf(out, "\tli\t$t4\t%d\n", stoi(midcode[i].var3));
					fprintf(out, "\t\t\t#$t4\n");
				}
				else {
					mkvaladr(midcode[i].var3.c_str(), c2mfname, "lw", "$t4");
					fprintf(out, "\t\t\t#若返回值为变量将变量值取出至$t4\n");
				}
			}
			fprintf(out, "\tj\tend_%s\n", midcode[i].var1.c_str());
		}
	}	
}
//错误处理
void error(int x){
	switch (x) {
		case 1 :
			fprintf(eout, "%d a\n",lnum);
			//printf("%d a\n", lnum);
			break;
		case 2 :
			fprintf(eout, "%d b\n", lnum);
			break;
		case 3 :
			fprintf(eout, "%d c\n", lnum);
			break;
		case 4 :
			fprintf(eout, "%d d\n", lnum);
			break;
		case 5 :
			fprintf(eout, "%d e\n", lnum);
			break;
		case 6 :
			fprintf(eout, "%d f\n", lnum);
			break;
		case 7 :
			fprintf(eout, "%d g\n", rtline);
			break;
		case 8 :
			fprintf(eout, "%d h\n", rtline);
			break;
		case 9 :
			fprintf(eout, "%d i\n", lnum);
			break;
		case 10:
			fprintf(eout, "%d j\n", lnum);
			break;
		case 11:
			fprintf(eout, "%d k\n", lnum - 1);
			break;
		case 12:
			fprintf(eout, "%d l\n", lnum);
			break;
		case 13:
			fprintf(eout, "%d m\n", lnum);
			break;
		case 14:
			fprintf(eout, "%d n\n", lnum);
			break;
		case 15:
			fprintf(eout, "%d o\n", lnum);
			break;
		default:
			break;
	}
	return ;
}
//返回语句
int symrtyj() {
	if (sym == RETURNTK) {
		char p3[30];
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			int tpbds = symbds();
			strcpy(p3, nowim);
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
				insmidcode("ret", dycengci, "", p3);
			}
			else {
				error(12);
			}
		}
		//fprintf(out, "<返回语句>\n")
		else {
			rtn = 4;
			rtline = lnum;
			insmidcode("ret", dycengci, "", "");
		}
		return 1;

	}
	return 0;
}
//写语句1
int symxyj() {
	char p1[200] = "\0", p2[30] = "NULL";
	if (sym == PRINTFTK) {
 		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			int bdste = 0;
			if (sym == STRCON) {
				strcpy(p1, temp);
				cfot();
				cifa();
				if (sym == COMMA) {
					cfot();
					cifa();
					bdste = symbds();
					if (bdste) {
						strcpy(p2, nowim);
						if (sym == RPARENT) {
							cfot();
							cifa();
							insmidcode("prt", p1, p2, (bdste == 1) ? "int" : "char");
							//fprintf(out, "<写语句>\n");
						}
						else {
							error(12);
							
						}
						return 1;
					}
				}
				else if (sym == RPARENT) {
					insmidcode("prt", p1, p2, (bdste == 1) ? "int" : "char");
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
			else{
				bdste = symbds();
				if (bdste) {
					strcpy(p2, nowim);
					if (sym == RPARENT) {
						insmidcode("prt", p1, p2, (bdste == 1) ? "int" : "char");
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
	}
	return 0;
}
//读语句1
int symdyj() {
	char names[10000];
	if (sym == SCANFTK) {
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (sym == IDENFR) {
				int fla = 0;
				int ioc = 0;
				for (int i = 0; i < fhbnum; i++) {
					if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 )) {
						fla = 1;
						strcpy( names, temp);
						ioc = fhb[i].iocov;
						break;
					}
				}
				if (fla == 0) {
					for (int i = 0; i < fhbnum; i++) {
						if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, glb) == 0)) {
							fla = 1;
							strcpy(names, temp);
							ioc = fhb[i].iocov;
							break;
						}
					}
				}
				if (fla == 0) {
					error(3);
				}
				if (ioc == 1) {
					insmidcode("scf", "  ", "int", names);
				}
				else if (ioc == 2) {
					insmidcode("scf", "  ", "char", names);
				}
				cfot();
				cifa();
				while (sym == COMMA) {
					cfot();
					cifa();
					if (sym == IDENFR) {
						int fla = 0;
						int ioc = 0;
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0 )) {
								fla = 1;
								ioc = fhb[i].iocov;
								strcpy(names, temp);
								break;
							}
						}
						if (fla == 0) {
							for (int i = 0; i < fhbnum; i++) {
								if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, glb) == 0)) {
									fla = 1;
									ioc = fhb[i].iocov;
									strcpy(names, temp);
									break;
								}
							}
						}
						if (fla == 0) {
							error(3);
						}
						if (ioc == 1) {
							insmidcode("scf", "  ", "int", names);
						}
						else if (ioc == 2) {
							insmidcode("scf", "  ", "char", names);
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
//语句列1
int symyjl() {
	if (symyj()) {
		while (symyj()) {
		}
	}
	//fprintf(out, "<语句列>\n");
	return 1;
}
//值参数表1
int symzcsb(int num, int type[30]) {
	int tempnum = 0;
	int tpbds = symbds();
	if (tpbds) {
		$sp += 4;
		insmidcode("pufa", "", "", nowim);
		if (type[tempnum] != tpbds) {
			error(5);
		}
			tempnum++;
		while (sym == COMMA) {
			cfot();
			cifa();
			tpbds = symbds();
			if (tpbds) {
				$sp += 4;
				insmidcode("pufa", "", "", nowim);
				if (type[tempnum] != tpbds) {
					error(5);
				}
				tempnum++;
			}
		}
		if (tempnum != num) {
			error(4);
		}
		insmidcode("pufan", "", tempnum, "");
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
//无返回值函数调用1
int symwfhzhsdyyj() {
	if (sym == IDENFR) {
		int fla = 0;
		int hstype = 0;
		int hscsnum = 0;
		int hscstype[30];
		char namesdw[64];
		for (int i = 0; i < hsfhbnum; i++) {
			if (strcmp(hsfhb[i].nam, temp) == 0) {
				fla = 1;
				hstype = hsfhb[i].iocov;
				hscsnum = hsfhb[i].csnum;
				strcpy(namesdw, hsfhb[i].nam);
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
					insmidcode("call", "", "", namesdw);
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
//有返回值函数调用1
int symyfhzhsdyyj() {
	if (sym == IDENFR) {
		int call;
		int fla = 0;
		int hstype = 0;
		int hscsnum = 0;
		int hscstype[30];
		int hsskadr = 16380;
		char namesdy[64];
		for (int i = 0; i < hsfhbnum; i++) {
			if (strcmp(hsfhb[i].nam, temp) == 0 ) {
				if (hsfhb[i].iocov == 3) {
					return 0;
				}
				fla = 1;
				hstype = hsfhb[i].iocov;
				hscsnum = hsfhb[i].csnum;
				strcpy(namesdy,hsfhb[i].nam);
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
		call = callres;
		if (sym == LPARENT) {
			cfot();
			cifa();
			
			if (symzcsb(hscsnum,hscstype)){
				if (sym == RPARENT) {
					cfot();
					cifa();
					if (call == 0) {
						insmidcode("call", "", "", namesdy);
					}
					else {
						strcpy(nowim, nextvar());
						insmidcode("call", nowim, "", namesdy);
					}
					//fprintf(out, "<有返回值函数调用语句>\n");
					if (hstype == 1) {
						return 1;
					}
					else {
						return 2;
					}
				}
				else {
					error(12);
					if (hstype == 1) {
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
//步长1
int symbc() {
	if(symwfhzs()){
		//fprintf(out, "<步长>\n");
		return 1;
	}
	return 0;
}
//循环语句1
int symxhyj() {
	char lab1[20], lab2[20],p3[30],names[30],names1[30],names2[30],opf[5];
	int p2 = 0;
	if (sym == WHILETK) {
		strcpy(lab1, nextlab());
		strcpy(lab2, nextlab());
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			insmidcode("lab:", "", "", lab1);
			if (symtj()) {
				if (sym == RPARENT) {
					cfot();
					cifa();
					insmidcode("jne", "", "", lab2);
				}
				else {
					error(12);
					return 1;
				}
				if (symyj()) {
					insmidcode("jmp", "", "", lab1);
					insmidcode("lab:", "", "", lab2);
					//fprintf(out, "<循环语句>\n");
					return 1;
				}
			}
		}
	}
	else if (sym == DOTK) {
		strcpy(lab1, nextlab());
		strcpy(lab2, nextlab());
		insmidcode("lab:", "", "", lab1);
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
						insmidcode("jeq", "", "", lab1);
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
		strcpy(lab1, nextlab());
		strcpy(lab2, nextlab());
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (sym == IDENFR) {
				int fla = 0;
				int tptype = 0;
				for (int i = 0; i < fhbnum; i++) {
					if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0)) {
						fla = 1;
						tptype = fhb[i].type;
						strcpy(names, fhb[i].nam);
						if (tptype == 1) {
							error(10);
						}
						break;
					}
				}
				if (fla == 0) {
					for (int i = 0; i < fhbnum; i++) {
						if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, glb) == 0)) {
							fla = 1;
							tptype = fhb[i].type;
							strcpy(names, fhb[i].nam);
							if (tptype == 1) {
								error(10);
							}
							break;
						}
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
						insmidcode("=", nowim, "", names);
						if (sym == SEMICN) {
							insmidcode("lab:", "", "", lab1);
							cfot();
							cifa();
						}
						else {
							error(11);
						}
						if (symtj()) {
							insmidcode("jne", "", "", lab2);
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
									if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0)) {
										fla = 1;
										tptype = fhb[i].type;
										strcpy(names1, fhb[i].nam);
										if (tptype == 1) {
											error(10);
										}
										break;
									}
								}
								if (fla == 0) {
									for (int i = 0; i < fhbnum; i++) {
										if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, glb) == 0)) {
											fla = 1;
											tptype = fhb[i].type;
											strcpy(names1, fhb[i].nam);
											if (tptype == 1) {
												error(10);
											}
											break;
										}
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
											if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0)) {
												fla = 1;
												strcpy(names2, fhb[i].nam);
												break;
											}
										}
										if (fla == 0) {
											for (int i = 0; i < fhbnum; i++) {
												if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, glb) == 0)) {
													fla = 1;
													strcpy(names2, fhb[i].nam);
													break;
												}
											}
										}
										if (fla == 0) {
											error(3);
										}
										cfot();
										cifa();
										int tpppplus = isplus();
										if (tpppplus) {
											if (tpppplus == 1) {
												strcpy(opf, "+");
											}
											else if (tpppplus == 2) {
												strcpy(opf, "-");
											}
											if (symbc()) {
												p2 = glbalval;
												if (sym == RPARENT) {
													cfot();
													cifa();
												}
												else {
													error(12);
												}
												if (symyj()) {
													strcpy(p3, nextvar());
													insmidcode(opf, names2, p2, p3);
													insmidcode("=", p3, "", names1);

													insmidcode("jmp", "", "", lab1);
													insmidcode("lab:", "", "", lab2);
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
//条件1
int symtj() {
	char p1[30], p2[30];
	int tpbds = symbds();
	strcpy(p1, nowim);
	if (tpbds == 1) {
		int tpgx;
		tpgx = isgx();
		if (tpgx) {
			tpbds = symbds();
			if (tpbds == 1) {
				strcpy(p2, nowim);
				if (tpgx == LSS) {
					insmidcode("<", p1, p2, "");
				}else if (tpgx == GRE) {
					insmidcode(">", p1, p2, "");
				}else if (tpgx == GEQ) {
					insmidcode(">=", p1, p2, "");
				}else if (tpgx == NEQ) {
					insmidcode("!=", p1, p2, "");
				}else if (tpgx == EQL) {
					insmidcode("==", p1, p2, "");
				}else if (tpgx == LEQ) {
					insmidcode("<=", p1, p2, "");
				}
				//fprintf(out, "<条件>\n");
				return 1;
			}
			else if (tpbds == 2) {
				error(6);
				return 1;
			}
		}
		strcpy(p2, "0");
		insmidcode("!=", p1, p2, "");
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
//条件语句1
int symtjyj() {
	char lab1[30], lab2[30],tjvalue[30];
	if (sym == IFTK) {
		strcpy(lab1, nextlab());
		strcpy(lab2, nextlab());
		cfot();
		cifa();
		if (sym == LPARENT) {
			cfot();
			cifa();
			if (symtj()) {
				strcpy(tjvalue, nowim);
				insmidcode("jne", "", "", lab1);
				if (sym == RPARENT) {
					cfot();
					cifa();
				}
				else {
					error(12);
				}
				if (symyj()) {
					insmidcode("jmp", "", "", lab2);
					insmidcode("lab:", "", "", lab1);
					if (sym == ELSETK) {
						cfot();
						cifa();
						symyj();
					}
					insmidcode("lab:", "", "", lab2);
					//fprintf(out, "<条件语句>\n");
					return 1;
				}
			}
		}
	}
	return 0;
}
//赋值语句1
int symfzyj() {
	if (sym == IDENFR) {
		char p2[100],p3[100];
		int fla = 0;
		int tptype = 0;
		int isarray = 0;
		char names[50];
		for (int i = 0; i < fhbnum; i++) {
			if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci,dycengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
				fla = 1;
				strcpy(names, temp);
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
			strcpy(p2, nowim);
			isarray = 1;
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
				strcpy(p3, nowim);
				if (isarray == 1) {
					insmidcode("[]=",names,p2,p3);
				}
				else {
					insmidcode("=", p3, "", names);
				}
				//fprintf(out, "<赋值语句>\n");
				return 1;
			}
		}

	}
	return 0;
}
//语句1
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
//因子1
int symyz() {
	char names[30], p3[30];
	callres = 1;
	int hsdy = symyfhzhsdyyj();
	callres = 0;
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
			if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, dycengci) == 0)) {
				fla = 1;
				idtemp = fhb[i].iocov;
				break;
			}
		}
		if (fla == 0) {
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[i].nam, temp) == 0 && (strcmp(fhb[i].cengci, glb) == 0)) {
					fla = 1;
					idtemp = fhb[i].iocov;
					break;
				}
			}
		}
		strcpy(names, temp);
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
				char tttp[30];
				strcpy( tttp,nowim);
				if (tpbds != 1) {
					error(9);
				}
				if (sym == RBRACK) {
					cfot();
					cifa();
					strcpy(nowim, nextvar());
					insmidcode("geta", names, tttp, nowim);
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
					strcpy(nowim, nextvar());
					insmidcode("geta", names, tttp, nowim);
				}
			}
		}
		else {
			strcpy(nowim, names);
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
		facttype = CHARTK;
		sprintf(nowim, "%d", temp[0]);
		cfot();
		cifa();
		//fprintf(out, "<因子>\n");
		return 2;
	}
	return 0;
}
//项1
int symx() {
	char p1[200], p2[200], p3[200];
	int tempyz = symyz();
	
	strcpy(p3, nowim);
	if (tempyz) {
		int flag = 0;
		int mod = ismult();
		while (mod) {
			strcpy(p1, p3);
			symyz();
			strcpy(p2, nowim);
			strcpy(p3, nextvar());
			flag = 1;
			if (mod == 1) {
				insmidcode("*", p1, p2, p3);
			}
			else if (mod == 2) {
				insmidcode("/", p1, p2, p3);
			}
			mod = ismult();
		}
		//fprintf(out, "<项>\n");
		if (flag == 1) {
			strcpy(nowim, p3);
			return 1;
		}
		else {
			strcpy(nowim, p3);
			return tempyz;
		}
	}
	return 0;
}
//表达式1
int symbds() {
	char p1[200], p2[200], p3[200];
	int tpplus = isplus();
	int tpx = symx();
	if (tpplus != 2) {
		if (tpplus == 1) {
			facttype = INTTK;
		}
		strcpy(p3, nowim);
	}
	else {
		strcpy(p1, nowim);
		strcpy(p3, nextvar());
		insmidcode("-", "0", p1, p3);
	}

	if (tpx) {
		int flag = 0;
		tpplus = isplus();
		while (tpplus) {
			facttype = INTTK;
			strcpy(p1, p3);
			symx();
			strcpy(p2, nowim);
			strcpy(p3, nextvar());
			if (tpplus == 1) {
				insmidcode("+", p1, p2, p3);
			}
			else if(tpplus == 2){
				insmidcode("-", p1, p2, p3);
			}
			tpplus = isplus();
			flag = 1;
		} 
		strcpy(nowim, p3);
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
//主函数
int symzhs() {
	rtn = -1;
	$sp = 0;
	char names[64];
	if (sym == VOIDTK) {
		cfot();
		cifa();
		if (sym == MAINTK) {
			strcpy(dytp, dycengci);
			strcpy(dycengci, cc);
			strcpy(hsfhb[hsfhbnum].nam, "main");
			hsfhb[hsfhbnum].iocov = 3;
			hsfhb[hsfhbnum].hsadrst = fhbnum;
			insmidcode("func","  ","  ","main");
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
						hsfhb[hsfhbnum].hsadred = fhbnum;
						hsfhbnum++;
						if (rtn != 4 && rtn != -1) {
							error(7);
							rtn = -1;
						}
						if (sym == RBRACE) {
							cfot();
							//fprintf(out, "<主函数>\n");
							insmidcode("fund", "  ", "  ", "main");
							strcpy(dycengci, dytp);
							return 1;
						}
					}
				}
			}
		}
		insmidcode("fund", "  ", "  ", dycengci);
	 }
	strcpy( dycengci, dytp);
	return 0;
}
//参数表1
int symcsb() {
	int lxtemp;
	int csnum = 0;
	char type[30];
	lxtemp = symlxbsf();
	if (lxtemp) {
		if (lxtemp == 1) {
			hsfhb[hsfhbnum].cstype[csnum] = 1;
			fhb[fhbnum].type = 3;
			fhb[fhbnum].iocov = 1;
			fhb[fhbnum].vadr = $sp;
			$sp += 4;
			strcpy(type, "int");
		}
		else if (lxtemp == 2) {
			hsfhb[hsfhbnum].cstype[csnum] = 2;
			fhb[fhbnum].type = 3;
			fhb[fhbnum].iocov = 2;
			fhb[fhbnum].vadr = $sp;
			$sp += 4;
			strcpy(type, "char");
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
			insmidcode("para", type, "", fhb[fhbnum].nam);
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
						fhb[fhbnum].type = 3;
						fhb[fhbnum].iocov = 1;
						fhb[fhbnum].vadr = $sp;
						$sp += 4;
						strcpy(type, "int");
					}
					else if (lxtemp == 2) {
						hsfhb[hsfhbnum].cstype[csnum] = 2;
						fhb[fhbnum].type = 3;
						fhb[fhbnum].iocov = 2;
						fhb[fhbnum].vadr = $sp;
						$sp += 4;
						strcpy(type, "char");
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
						insmidcode("para", type, "", fhb[fhbnum].nam);
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
//复合语句1
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
//无返回值函数定义1
int symwfhzhsdy() {
	rtn = -1;
	$sp = 8;
	if (sym == VOIDTK) {
		cfot();
		hsfhb[hsfhbnum].iocov = 3;
		cifa();
		if (sym == IDENFR) {
			char names[64];
			var_void[var_v++] = temp;
			strcpy(hsfhb[hsfhbnum].nam, temp);
			strcpy(dytp, dycengci);
			strcpy(dycengci, temp);
			strcpy(names, hsfhb[hsfhbnum].nam);
			hsfhb[hsfhbnum].hsadrst = fhbnum;
			hsfhb[hsfhbnum].iocov = 3;
			insmidcode("func", "void", "", names);
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
								hsfhb[hsfhbnum - 1].hsadred = fhbnum;
								insmidcode("fund", "", "", names);
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
//有返回值函数定义1
int symyfhzhsdy() {
	rtn = -1;
	$sp = 8;
	int tpsmtb = symsmtb();
	if (tpsmtb) {
		char names[64];
		if (sym == LPARENT) {
			cfot();
			cifa();
			hsfhb[hsfhbnum].hsadrst = fhbnum;
			strcpy(names,hsfhb[hsfhbnum].nam);
			if (tpsmtb == 1) {
				insmidcode("func", "int", "", names);
			}
			else {
				insmidcode("func", "char", "", names);
			}
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
							hsfhb[hsfhbnum - 1].hsadred = fhbnum;
							insmidcode("fund", "", "", names);
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
//变量定义1
int symbldy()
 {
	int lxtemp;
	int aytemp = 0;
	string mctp = "";
	lxtemp = symlxbsf();
	if (lxtemp) {
		if (lxtemp == 1) {
			fhb[fhbnum].iocov = 1;
			mctp = "int";
		}
		else if (lxtemp == 2) {
			fhb[fhbnum].iocov = 2;
			mctp = "char";
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
			cfot();
			cifa();
			if (sym == LBRACK) {
				cfot();
				cifa();
				if (symwfhzs()) {
					aytemp = glbalval;
					if (sym == RBRACK) {
						cfot();
						cifa();
					}
					else {
						error(13);
					}
				}
				fhb[fhbnum].vadr = $sp;
				$sp = $sp +  4 * (aytemp);
				insmidcode(mctp.c_str(), "array", aytemp, fhb[fhbnum].nam);
				fhbnum += aytemp;
			}
			else {
				fhb[fhbnum].vadr = $sp;
				$sp += 4;
				insmidcode(mctp.c_str(), "  ", "  ", fhb[fhbnum].nam);
				fhbnum++;
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
					cfot();
					cifa();
					if (sym == LBRACK) {
						cfot();
						cifa();
						if (symwfhzs()) {
							aytemp = glbalval;
							if (sym == RBRACK) {
								cfot();
								cifa();
							}
							else {
								error(13);
							}
						}
						fhb[fhbnum].vadr = $sp;
						$sp = $sp + 4 * (aytemp);
						insmidcode(mctp.c_str(), "array", aytemp, fhb[fhbnum].nam);
						fhbnum += aytemp;
					}
					else {
						fhb[fhbnum].vadr = $sp;
						$sp += 4;
						insmidcode(mctp.c_str(), "	", "  ", fhb[fhbnum].nam);
						fhbnum++;
					}
				}
			}
			//fprintf(out, "<变量定义>\n");
			return 1;
		}
	}
	return 0;
}
//变量说明1
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
//声明头部1
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
			return lxtemp;
		}
		else {
			return 0;
		}
	}
	return 0;
}
//类型标识符1
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
//无符号整数1
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
//整数1
int symzs() {
	int tpps = 0;
	char p1[30];
	tpps = isplus();
	if (tpps == 0) {
		tpps = 1;
	}
	if (symwfhzs()) {
		int tempzs = 0;
		tempzs = glbalval;
		facttype = INTTK;
		if (tpps == 1) {
			sprintf(nowim, "%d", tempzs);
			//fprintf(out, "<整数>\n");
			return tpps;
		}
		else {
			strcpy(p1, nextvar());
			insmidcode("-","0",tempzs,p1);
			strcpy(nowim, p1);
			return tpps;
		}
	}
	return 0;
}
//常量定义1
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
			fhb[fhbnum].vadr = $sp;
			$sp += 4;
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
					error(2);
					break;
				}
			}
			
			cfot();
			cifa();
			if (sym == ASSIGN) {
				cfot();
				cifa();
				int tpzs = 0;
				//tpzs = symzs();
				tpzs = isplus();
				if (tpzs == 0) {
					tpzs = 1;
				}
				if (symwfhzs()) {
					if (tpzs == 1) {

						fhb[fhbnum].value = glbalval;
					}
					else if (tpzs == 2) {
						fhb[fhbnum].value = -glbalval;
					}
				}
				else {
					error(15);
					cifa();
				} 
				insmidcode("const", "int", fhb[fhbnum].value, fhb[fhbnum].nam);
				fhbnum++;
				while (sym == COMMA) {
					cfot();
					cifa();
					if (sym == IDENFR) {
						fhb[fhbnum].type = 1;
						fhb[fhbnum].iocov = 1;
						strcpy(fhb[fhbnum].nam, temp);
						strcpy(fhb[fhbnum].cengci, dycengci);
						fhb[fhbnum].vadr = $sp;
						$sp += 4;
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
								error(2);
								break;
							}
						}
						
						cfot();
						cifa();
						if (sym == ASSIGN) {
							cfot();
							cifa();
							int tpzs = 0;
							/*tpzs = symzs();
							if (tpzs == 1) {
								fhb[fhbnum].value = glbalval;
							}
							else if (tpzs == 2) {
								fhb[fhbnum].value = -glbalval;
							}*/
							//tpzs = symzs();
							tpzs = isplus();
							if (tpzs == 0) {
								tpzs = 1;
							}
							if (symwfhzs()) {
								if (tpzs == 1) {

									fhb[fhbnum].value = glbalval;
								}
								else if (tpzs == 2) {
									fhb[fhbnum].value = -glbalval;
								}
							}
							else {
								error(15);
								cifa();
							}
						}
						insmidcode("const", "int", fhb[fhbnum].value, fhb[fhbnum].nam);
						fhbnum++;
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
		fhb[fhbnum].vadr = $sp;
		$sp += 4;
		if (sym == IDENFR) {
			strcpy(fhb[fhbnum].nam, temp);
			strcpy(fhb[fhbnum].cengci, dycengci);
			for (int i = 0; i < fhbnum; i++) {
				if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
					error(2);
					break;
				}
			}
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
				insmidcode("const", "char", globalchar, fhb[fhbnum].nam);
				fhbnum++;
				while (sym == COMMA) {
					cfot();
					cifa();
					if (sym == IDENFR) {
						fhb[fhbnum].type = 1;
						fhb[fhbnum].iocov = 2;
						fhb[fhbnum].vadr = $sp;
						$sp += 4;
						strcpy(fhb[fhbnum].nam, temp);
						strcpy(fhb[fhbnum].cengci, dycengci);
						for (int i = 0; i < fhbnum; i++) {
							if (strcmp(fhb[fhbnum].nam, fhb[i].nam) == 0 && (strcmp(fhb[fhbnum].cengci,fhb[i].cengci) == 0 || strcmp(fhb[i].cengci,glb) == 0)) {
								error(2);
								break;
							}
						}
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
						insmidcode("const", "char", globalchar, fhb[fhbnum].nam);
						fhbnum++;
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
//常量说明1
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
//程序
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
			galstked = fhbnum;
		}
		else {
			sym = teep;
			galstked = fhbnum;
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
//字符串1
int symzfc(){
	
	if (sym == STRCON) {
		cfot();
		cifa();
		//fprintf(out, "<字符串>\n");
		return 1;
	}
	return 0;
}
//字符1
int symzf() {
	if (sym == CHARCON) {
		globalchar = temp[0];
		cfot();
		cifa();
		return 1;
	}
	return 0;
}
//关系符1
int isgx () {
	if (sym == LSS || sym == LEQ || sym == GRE || sym == GEQ || sym == NEQ || sym == EQL) {
		int temp;
		temp = sym;
		cfot();
		cifa();
		return temp;
	}
	return 0;
}
//乘法运算符1
int ismult() {
	
	if (sym == MULT) {
		cfot();
		cifa();
		return 1;
	}
	else if (sym == DIV) {
		cfot();
		cifa();
		return 2;
	}
	return 0;
}
//加法运算符1
int isplus() {
	if (sym == PLUS || sym == MINU) {
		if (sym == PLUS) {
			cfot();
			cifa();
			return 1;
		}
		else if (sym == MINU) {
			cfot();
			cifa();
			return 2;
		}
	}
	return 0;
}
//词法1
int cifa(){
	char pRintf[] = "printf", rEturn[] = "return";
	char cOnst[] = "const", iNt[] = "int";
	char cHar[] = "char", vOid[] = "void", mAin[] = "main";
	char iF[] = "if", eLse[] = "else", dO[] = "do";
	char wHile[] = "while", fOr[] = "for", sCanf[] = "scanf";
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
		glbalval = atoi(temp);
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
		glbalval = tp;
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
//词法输出1
void cfot() {
	//fprintf(out, "%s %s\n", outtemp[sym].c_str(), temp);
	//printf("%s %s\n", outtemp[sym].c_str(), temp);
	for (int j = 0; j < 10000; j++) {
		temp[j] = '\0';
	}
}
