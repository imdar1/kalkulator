#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boolean.h"
#include "stack.c"
#include <math.h>
#include <complex.h>
#define ValUndef 0
boolean Angka(char c); //mengecek apakah c merupakan angka
/*void printStack(Stack *s);*/
void balik(Stack *s1,Stack *s2);// membalik stack
void operasi1(Stack *s1,Stack *s2); //operasi yang mempunyai tingkat prioritas pertama yaitu ^
void operasi2(Stack *s1,Stack *s2); //operasi yang mempunyai tingkat prioritas kedua yaitu * dan /
void operasi3(Stack *s1,Stack *s2); //operasi yang mempunyai tingkat prioritas terakhir yaitu + dan -
int main(){
	double inf=INFINITY;
	char kal[100];
	boolean found,error,imaginer;
	scanf("%s",&kal);
	infotype token,tmp;
	long l=0,pj=strlen(kal),cnt;
	double complex save;
	Stack stemp,s,srev;
	error=false;
	CreateEmpty(&stemp);CreateEmpty(&s);CreateEmpty(&srev);
	while(pj>l){
	//	printf("%d %c\n",l,kal[l]);
		if(kal[l]=='i'){	//ketika menemukan i saja 
			token.val=1.000*I;	
			token.opr='.';
			Push(&s,token); //push 1i dan .
			l++;
		}else if(Angka(kal[l])){	//ketika menemukan angka
			imaginer=false;
			found=false;
			save=0;
			while(!found&&l<pj){
				if(kal[l]=='i'){ //jika i berarti bilangan itu imaginer
					imaginer=true;
					l++;
				}else if(!Angka(kal[l])){ //sudah bukan angka lagi
					found=true;
				}else{ //masih angka
					save=save*10+(kal[l]-'0'); //angka digabung ditaruh ke save
					l++; 
				}
			}
			if (kal[l]=='.'){ //ketika menemukan . maka menjadi bilangan desimal
				found=false;
				cnt=1;
				l++;
				while(!found&&l<pj){
					if(kal[l]=='i'){ //bilangan merupakan imaginer
						imaginer=true;
						l++;
					}else if (!Angka(kal[l])){ //sudah bukan angka lagi
						found=true;
					}else{ //masih angka
						save=save+pow(10,cnt*(-1.000))*((kal[l]-'0')*1.00); //angka digabung dibelakang ditaruh ke save
						cnt++;
						l++;
					}
				}
			}
			token.val=save*1.000;	
			if (imaginer){	//bilangan imaginer
				token.val*=I;// buat imaginer
			}
			//printf("%.1f+%.1fi\n",creal(token.val),cimag(token.val));
			token.opr='.';
			//printf("%.2f\n",token.val);
			Push(&s,token); //push amgka dan .
		}else if(kal[l]==')'){	//ketika )
			Pop(&s,&tmp);
			while (tmp.opr!='('){ //pop terus hingga ( dan push ke suatu stack baru
				Push(&srev,tmp);
				Pop(&s,&tmp);
			}
			//untuk kasus awalnya negatif
			Pop(&srev,&tmp);  
			if (tmp.opr=='-'){
				Pop(&srev,&tmp);
				tmp.val=tmp.val*(-1);
			}
			Push(&srev,tmp);
			//melakukan semua operasi
			balik(&srev,&stemp);
			operasi1(&stemp,&srev);
			operasi2(&srev,&stemp);
			balik(&stemp,&srev);
			operasi3(&srev,&s);
			l++;
		}else{
			//jika operator
			token.val=ValUndef;
			token.opr=kal[l];
			Push(&s,token); //push operator dan valundef
			l++;
		}
	}
	//balik s dulu
	balik(&s,&srev);
	//untuk kasus awalnya negatif
	Pop(&srev,&tmp);
	if (tmp.opr=='-'){
		Pop(&srev,&tmp);
		tmp.val=tmp.val*(-1);
	}
	Push(&srev,tmp);
	//melakukan semua operasi
	balik(&srev,&s);
	operasi1(&s,&stemp);
	operasi2(&stemp,&srev);
	balik(&srev,&stemp);
	operasi3(&stemp,&s);
	Pop(&s,&tmp);
	//cek apakah math error
	if ((cimag(tmp.val)==inf)||(cimag(tmp.val)==-inf)||(creal(tmp.val)==-inf)||(creal(tmp.val)==inf)||(creal(tmp.val)!=creal(tmp.val))||cimag(tmp.val)!=cimag(tmp.val)){
		printf("MATH ERROR");
	}else{
		if ((cimag(tmp.val)>(-0.0000001))&&(cimag(tmp.val)<(0.0000001))){ //cek apakah imaginer = 0
			printf("%.6f",creal(tmp.val));	//tulis realnya saja
		}else if((creal(tmp.val)>(-0.0000001))&&(creal(tmp.val)<(0.0000001))){ //cek apakah real = 0
			printf("%.6fi",cimag(tmp.val)); //tulis imaginer saja
		}else if(cimag(tmp.val)<0){ //jika imaginer negatif
			printf("%.6f%.6fi\n",creal(tmp.val),cimag(tmp.val));	
		}else{ //jika imaginer positif
			printf("%.6f+%.6fi\n",creal(tmp.val),cimag(tmp.val));
		}
	}
}
/*void printStack(Stack *s){
	Stack stmp;
	infotype tmp;
	CreateEmpty(&stmp);
	while (!IsEmpty(*s)){
		Pop(s,&tmp);
		printf("%.6f+%.6fi\n",creal(tmp.val),cimag(tmp.val));
		Push(&stmp,tmp);
	}	
	balik(&stmp,s);
}*/
boolean Angka(char c){ //validasi angka
	return ((c-'0'<=10)&&(c-'0'>=0));
}
void balik(Stack *s1,Stack *s2){ //balik stack s1 ke s2
	infotype tmp;
	
	CreateEmpty(s2);
	while (!IsEmpty(*s1)){
		Pop(s1,&tmp);
		Push(s2,tmp);
	}
}
void operasi1(Stack *s1,Stack *s2){ //melakukan operasi ^ dari s1 ke s2 
	infotype tmp,save;
	while (!IsEmpty(*s1)){
		Pop(s1,&tmp);
		if (tmp.opr=='^'){
			Pop(s2,&save);
			Pop(s1,&tmp);
			tmp.val=cpow(tmp.val,save.val);
			tmp.opr='.';	
		}
		Push(s2,tmp);
	}
}
void operasi2(Stack *s1,Stack *s2){ //melakukan operasi * dan / dari s1 ke s2
	infotype tmp,save;
	while (!IsEmpty(*s1)){
		Pop(s1,&tmp);
		if (tmp.opr=='*'){
			Pop(s2,&save);
			Pop(s1,&tmp);
			tmp.val=tmp.val*save.val;
			tmp.opr='.';	
		}else if (tmp.opr=='/'){
			Pop(s2,&save);
			Pop(s1,&tmp);
			tmp.val=save.val/tmp.val;
			tmp.opr='.';	
		}
		Push(s2,tmp);
	}
}
void operasi3(Stack *s1,Stack *s2){ //melakukan operasi + dan - dari s1 ke s2
	infotype tmp,save,x;
	x.val=0;
	x.opr='.';
	while (!IsEmpty(*s1)){
		Pop(s1,&tmp);
		if (tmp.opr=='-'){
			Pop(s2,&save);
			Pop(s1,&tmp);
			tmp.val=save.val-tmp.val;
			tmp.opr='.';	
		}else if (tmp.opr=='+'){
			Pop(s2,&save);
			Pop(s1,&tmp);
			//printf("%.0f %.0f",save.val,tmp.val);
			tmp.val=save.val+tmp.val;
			tmp.opr='.';
		}
		Push(s2,tmp);
	}
}
