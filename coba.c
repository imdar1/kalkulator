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

      if ( ( (( (stk[0] == 'E') || (stk[0] == 'A') || (stk[0] == 'B')|| (stk[0] == 'M') || (stk[0] == 'I')) && stk[1] == '\0') ||
       (stk[0] == 'L' && (stk[1] =='E' || stk[1]=='N') && stk[2] == '\0') ||
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
      printf("$%s\t%s$\t%s\n",stk,a,ac);
      i = i - strlen(gsplit[m]) + 1;
      check();
      break;
    } 
  }
}


void check(){
  strcpy(ac,"REDUCE TO E");

  /*E->1|2|3|4|5|6|7|8|9*/
  ShiftReduce("E->1|2|3|4|5|6|7|8|9");

  /* C -> i */
  ShiftReduce("C->i");

  /*E->EE*/
  ShiftReduce("E->EE");

  /*I->BC|EC|NC|AC*/
  ShiftReduce("I->BC|EC|NC|AC");

  /*I->C*/
  ShiftReduce("I->C");

  /* S->+|*|/|^ */
  ShiftReduce("S->+|*|/|^");

  /*N->0*/
  ShiftReduce("N->0");

  /*D->.*/
  ShiftReduce("D->.");

  /*L->-*/
  ShiftReduce("L->-");

  /* E->LESE | LELE */
  ShiftReduce("E->LESE|LELE");

  /* E->LNSE | LNLE */
  ShiftReduce("E->LNSE|LNLE");

  /* E->LMSM | LMLM */
  ShiftReduce("E->LMSM|LMLM");

  /* E->LESM | LELM */
  ShiftReduce("E->LESM|LELM");

  /* E->LMSE | LMLE */
  ShiftReduce("E->LMSE|LMLE"); 
         
  /* E->LNSM | LNLM */
  ShiftReduce("E->LNSM|LNLM");

  /* E->LMSN | LMLN */
  ShiftReduce("E->LMSN|LMLN"); 

  /* B->LNSN|LNLN */
  ShiftReduce("B->LNSN|LNLN");  

  /* B->LESN | LELN */
  ShiftReduce("B->LESN|LELN"); 

  /* B->LMSN | LMLN */
  ShiftReduce("B->LMSN|LMLN"); 

  /* M->(LE) */
  ShiftReduce("M->(LE)"); 

  /*E->EN*/
  ShiftReduce("E->EN");

  /* E->ESE | ELE */
  ShiftReduce("E->ESE|ELE");
        
  /* E->MSM | MLM */
  ShiftReduce("E->MSM|MLM");

  /* E->ESM | ELM */
  ShiftReduce("E->ESM|ELM");

  /* E->MSE | MLE */
  ShiftReduce("E->MSE|MLE");

  /* E->NSM | NLM */
  ShiftReduce("E->NSM|NLM");

  /* B->MSN | MLN */
  ShiftReduce("B->MSN|MLN");

  /* B->ESN | ELN */
  ShiftReduce("B->ESN|ELN");

  /* E->NSE | NLE */
  ShiftReduce("E->NSE|NLE");

  /* E->BSE | BLE */
  ShiftReduce("E->BSE|BLE");

  /* E->BSM | BLM */
  ShiftReduce("E->BSM|BLM");

  /* E->BSA | BLA */
  ShiftReduce("E->BSA|BLA");

  /* B->BSN | BLN */
  ShiftReduce("B->BSN|BLN");

  /* B->NSN | NLN */
  ShiftReduce("B->NSN|NLN");

  /*M->(E)|(A)|(B)|(I)*/
  ShiftReduce("M->(E)|(A)|(B)|(I)");

  /*Bagian Koma*/
  /* A->NDN | NDE */
  ShiftReduce("A->NDN|NDE");

  /* A->BDN | BDE */
  ShiftReduce("A->BDN|BDE");

  /* A->EDN | EDE */
  ShiftReduce("A->EDN|EDE");

  /*A->AN | AE*/
  ShiftReduce("A->AN|AE");

  /* E->LNSA | LNLA */
  ShiftReduce("E->LNSA|LNLA");

  /* E->LESA | LELA */
  ShiftReduce("E->LESA|LELA");

  /* E->LASA | LALA */
  ShiftReduce("E->LASA|LALA");

  /* B->LASN | LALN */
  ShiftReduce("B->LASN|LALN");

  /* E->LMSA | LMLA */
  ShiftReduce("E->LMSA|LMLA");

  /* E->LASM | LALM */
  ShiftReduce("E->LASM|LALM");

  /* E->LASE | LALE */
  ShiftReduce("E->LASE|LALE");

  /* E->ASA | ALA */
  ShiftReduce("E->ASA|ALA");

  /* E->ASE | ALE */
  ShiftReduce("E->ASE|ALE");

  /* E->ESA | ELA */
  ShiftReduce("E->ESA|ELA");

  /* B->ASN | ALN */
  ShiftReduce("B->ASN|ALN");

  /* E->NSA | NLA */
  ShiftReduce("E->NSA|NLA");

  /* E->ASM | ALM */
  ShiftReduce("E->ASM|ALM");

  /* E->MSA | MLA */
  ShiftReduce("E->MSA|MLA");

  /*Imajiner*/
  /* E->LISI | LILI */
  ShiftReduce("E->LISI|LILI");

  /* E->LISE | LILE */
  ShiftReduce("E->LISE|LILE");

  /* E->LESI | LELI */
  ShiftReduce("E->LESI|LELI");

  /* E->LMSI | LMLI */
  ShiftReduce("E->LMSI|LMLI");

  /* E->LISM | LILM */
  ShiftReduce("E->LISM|LILM");

  /* E->LNSI | LNLI */
  ShiftReduce("E->LNSI|LNLI");

  /* E->LASI | LALI */
  ShiftReduce("E->LASI|LALI");

  /* B->LISN | LILN */
  ShiftReduce("B->LISN|LILN");

  /* E->ILI | ISI */
  ShiftReduce("E->ILI|ISI");

  /* E->ALI | ASI */
  ShiftReduce("E->ALI|ASI");

  /* E->ILE | ISE */
  ShiftReduce("E->ILE|ISE");

  /* E->ELI | ESI */
  ShiftReduce("E->ELI|ESI");

  /* E->MLI | MSI */
  ShiftReduce("E->MLI|MSI");

  /* E->ILM | ISM */
  ShiftReduce("E->ILM|ISM");

  /* E->NLI | NSI */
  ShiftReduce("E->NLI|NSI");

  /* B->ILN | ISN */
  ShiftReduce("B->ILN|ISN");

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
