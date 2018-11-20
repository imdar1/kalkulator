#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <complex.h>
#include "boolean.h"
#include "stack.c"

/* Global Variable */
int k=0,i=0,j=0,c=0;
char a[256],ac[20],stk[25];

/* Constant */
#define ValUndef 0

void ShiftReduce(char*Grammar);
/* Melakukan shift dan reduce pada grammar/CFG */

void check();
/* Mengecek input dengan tiap grammar dan memanggil ShiftReduce */

boolean Angka(char c);
/* Mengecek apakah c adalah angka */

void balik(Stack *s1,Stack *s2);
/* Membalik stack */

void operasi1(Stack *s1,Stack *s2);
/* Operasi yang mempunyai tingkat prioritas pertama yaitu ^ */

void operasi2(Stack *s1,Stack *s2);
/* Operasi yang mempunyai tingkat prioritas kedua yaitu * dan / */

void operasi3(Stack *s1,Stack *s2);
/* Operasi yang mempunyai tingkat prioritas terakhir yaitu + dan - */

int main(){
      double inf=INFINITY;
	    char kal[256];
	    boolean found,error,imaginer;
	    infotype token,tmp;
	    long l=0,pj,cnt;
	    double complex save;
	    Stack stemp,s,srev;
	    error=false;


      /* GRAMMAR : \n E->LESE|LELE|ESE|NSE \n B->ESN|NSN|LNLN|LNSN|LESN|LELN|LMSN|LMLN|MSN|MLN|ASN|ALN \n B->BSN|BLN \n A->BDB|BDE \n E->BSE|BLE|BSM|BLM|BLA|BSA \n E->LNSE|LNLE \n E->LNSM|LNLM \n E->LMLM|LMSM|LESM|LELM|LMSE|LMLE \n E->MSM|MLM|ESM|ELM|MSE|MLE \n E->NSM|NLM \n E->ASA|ALA|ASE|ALE|ESA|ELA \n E->NSA|NLA \n E->ASM|ALM|MSA|MLA \n E->LALA|LASA|LALE|LASE|LELA|LESA \n E->LNLA|LNSA|LMLA|LMSA|LASM|LALM \n B->LASN|LALN \n D->. \n A->NDN|NDE|EDN|EDE \n A->AE|EN \n L->- \n S->+|*|/|^ \n M->(E)|(A)|(B) \n E->1|2|3|4|5|6|7|8|9 \n E->EE \n N->0 \n M->(LE)|(LA)|(LB) \n E->EN */
      printf("Selamat datang di kalkulator canggih kami!\n");
      printf("Silakan input string :\n");
      scanf("%s",a);
      strcpy(kal,a);
      c=strlen(a);
      for(k=0,i=0; j<c; k++,i++,j++) {
        stk[i]=a[j];
        a[j]=' ';
        check();
      }
      check();

      if ( ( (( (stk[0] == 'E') || (stk[0] == 'A') || (stk[0] == 'B')|| (stk[0] == 'M') || (stk[0] == 'I') || (stk[0] == 'N') ) && stk[1] == '\0') ||
       (stk[0] == 'L' && (stk[1] =='E' || stk[1]=='N' || stk[1] == 'I' || stk[1] == 'A' || stk[1] == 'M') && stk[2] == '\0') ||
       (stk[0] == '(' && stk[1] == 'L' && stk[2]=='N' && stk[3]==')' && stk[4] == '\0') ||
       (stk[0] == '(' && stk[1]=='N' && stk[2]==')' && stk[3] == '\0' && a[j-1] == ' '))
       && a[j-1] == ' '){
        CreateEmpty(&stemp);CreateEmpty(&s);CreateEmpty(&srev);
        pj=strlen(kal);
	      while(pj>l){
		      if(kal[l]=='i'){	//ketika menemukan i saja
			      token.val=1.000*I;
			      token.opr='.';
			      Push(&s,token); //push 1i dan .
			      l++;
		      }
          else
          if(Angka(kal[l])){	//ketika menemukan angka
			      imaginer=false;
			      found=false;
			      save=0;
			      while(!found&&l<pj){
				      if(kal[l]=='i'){ //jika i berarti bilangan itu imaginer
					      imaginer=true;
					      l++;
				      }
              else
              if(!Angka(kal[l])){ //sudah bukan angka lagi
					      found=true;
				      }
              else { //masih angka
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
					      }
                else
                if (!Angka(kal[l])){ //sudah bukan angka lagi
						      found=true;
					      }
                else{ //masih angka
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
		      }
          else
          if(kal[l]==')'){	//ketika )
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
		      }
          else{
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
	      }
        else{
		      if ((cimag(tmp.val)>(-0.0000001))&&(cimag(tmp.val)<(0.0000001))){ //cek apakah imaginer = 0
			      printf("%.6f",creal(tmp.val));	//tulis realnya saja
		      }
          else
          if((creal(tmp.val)>(-0.0000001))&&(creal(tmp.val)<(0.0000001))){ //cek apakah real = 0
			      printf("%.6fi",cimag(tmp.val)); //tulis imaginer saja
		      }
          else
          if(cimag(tmp.val)<0){ //jika imaginer negatif
			      printf("%.6f%.6fi\n",creal(tmp.val),cimag(tmp.val));
		      }
          else{ //jika imaginer positif
			      printf("%.6f+%.6fi\n",creal(tmp.val),cimag(tmp.val));
          }
        }
      }
      else{
            printf("SYNTAX ERROR\n");
      }
    return 0;
   }

void ShiftReduce(char * Grammar) {
  int l = strlen(Grammar);
  int m = 3;
  int n = 1;
  int o = 0;
  char gsplit[100][10];

  gsplit[0][0] = Grammar[0];
  gsplit[0][1] = '\0';
  while(m < l){
    if (Grammar[m] != '|'){
      gsplit[n][o] = Grammar[m];
      o++;
    }
    else {
      gsplit[n][o] = '\0';
      o = 0;
      n++;
    }
    m++;
  }
  gsplit[n][o] = '\0';

  int pos;
  for (m = 1; m<=n; m++){
    if ( strstr(stk,gsplit[m]) != NULL){
      pos = strstr(stk,gsplit[m])-stk;
      stk[pos] = gsplit[0][0];
      stk[pos+1] = '\0';
      if (strlen(gsplit[m])>2){
        for (k=pos+2;k<=pos+strlen(gsplit[m])-1;k++){
          stk[k] = '\0';
        }
      }
      //printf("$%s\t%s$\t%s\n",stk,a,ac);
      i = i - strlen(gsplit[m]) + 1;
      check();
      break;
    }
  }
}


void check(){
  //strcpy(ac,"REDUCE TO E");

  /*E->LESE|LELE|LNSE|LNLE|LMSM|LMLM|LESM|LELM|LMSE|LMLE|LNSM|LNLM|LASM|LALM|LASE|LALE|LISI|LILI|LISE|LILE|LESI|LELI|LMSI|LMLI|LISM|LILM|LNSI|LNLI|LASI|LALI*/
  ShiftReduce("E->LESE|LELE|LNSE|LNLE|LMSM|LMLM|LESM|LELM|LMSE|LMLE|LNSM|LNLM|LASM|LALM|LASE|LALE|LISI|LILI|LISE|LILE|LESI|LELI|LMSI|LMLI|LISM|LILM|LNSI|LNLI|LASI|LALI");

  /*B->LMSN|LMLN|LNSN|LNLN|LESN|LELN|LMSN|LMLN|LASN|LALN|LISN|LILN*/
  ShiftReduce("B->LMSN|LMLN|LNSN|LNLN|LESN|LELN|LMSN|LMLN|LASN|LALN|LISN|LILN");

  /*M->(LE)|(LA)|(LB)|(LI)*/
  ShiftReduce("M->(LE)|(LA)|(LB)|(LI)");

  /*E->ESE|ELE|MSM|MLM|ESM|ELM|MSE|MLE|NSM|NLM|NSE|NLE|BSE|BLE|BSM|BLM|ASE|ALE|ASM|ALM|ILI|ISI|ALI|ASI|ISE|ILE|ELI|ESI|MLI|MSI|ILM|ISM|NLI|NSI|BLI|BNI*/
  ShiftReduce("E->ESE|ELE|MSM|MLM|ESM|ELM|MSE|MLE|NSM|NLM|NSE|NLE|BSE|BLE|BSM|BLM|ASE|ALE|ASM|ALM|ILI|ISI|ALI|ASI|ISE|ILE|ELI|ESI|MLI|MSI|ILM|ISM|NLI|NSI|BLI|BNI");

  /*B->MSN|MLN|ESN|ELN|BSN|BLN|NSN|NLN|ASN|ALN|ILN|ISN*/
  ShiftReduce("B->MSN|MLN|ESN|ELN|BSN|BLN|NSN|NLN|ASN|ALN|ILN|ISN");

  /*A->NDN|NDE|BDN|BDE|EDN|EDE*/
  ShiftReduce("A->NDN|NDE|BDN|BDE|EDN|EDE");

  /*M->(E)|(A)|(B)|(I)*/
  ShiftReduce("M->(E)|(A)|(B)|(I)");

  /*E->EE|EN*/
  ShiftReduce("E->EE|EN");

  /*A->AN|AE*/
  ShiftReduce("A->AN|AE");

  /*I->BC|EC|NC|AC*/
  ShiftReduce("I->BC|EC|NC|AC");

  /*I->C*/
  ShiftReduce("I->C");

  /*C->i*/
  ShiftReduce("C->i");

  /*N->0*/
  ShiftReduce("N->0");

  /*D->.*/
  ShiftReduce("D->.");

  /*L->-*/
  ShiftReduce("L->-");

  /*S->+|*|/|^*/
  ShiftReduce("S->+|*|/|^");

  /*E->1|2|3|4|5|6|7|8|9*/
  ShiftReduce("E->1|2|3|4|5|6|7|8|9");

}

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
