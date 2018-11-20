#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <complex.h>
#include "boolean.h"
#include "stack.c"

/* Global Variable */
int k=0,z=0,i=0,j=0,c=0;
char a[256],ac[20],stk[15],act[10];
void check();
#define ValUndef 0

boolean Angka(char c); //mengecek apakah c merupakan angka
/*void printStack(Stack *s);*/
void balik(Stack *s1,Stack *s2);// membalik stack
void operasi1(Stack *s1,Stack *s2); //operasi yang mempunyai tingkat prioritas pertama yaitu ^
void operasi2(Stack *s1,Stack *s2); //operasi yang mempunyai tingkat prioritas kedua yaitu * dan /
void operasi3(Stack *s1,Stack *s2); //operasi yang mempunyai tingkat prioritas terakhir yaitu + dan -

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
      printf("enter input string : \n");
      scanf("%s",a);
      strcpy(kal,a);
      c=strlen(a);
      strcpy(act,"SHIFT->");
      for(k=0,i=0; j<c; k++,i++,j++) {
        stk[i]=a[j];
        a[j]=' ';
        check();
      }

      check();

      if (( (stk[0] == 'E') || (stk[0] == 'A') || stk[0] == 'B') && stk[1] == '\0' && a[j-1] == ' '){        
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
            printf("SYNTAX_ERROR\n");
      }
    return 0;
   }


void check()
   {
     /*E->1|2|3|4|5|6|7|8|9*/
     strcpy(ac,"REDUCE TO E");
     for(z=0; z<15; z++)
       if(stk[z]=='1' || stk[z]=='2' || stk[z]=='3' || stk[z]=='4' || stk[z]=='5' || stk[z]=='6' || stk[z]=='7' || stk[z]=='8' || stk[z]=='9')
         {
           stk[z]='E';
           stk[z+1]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
         }

      /*E->EE*/
     for(z=0; z<15; z++)
       if(stk[z] == 'E' && stk[z+1] == 'E')
         {
           stk[z]='E';
           stk[z+1]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
           i=i-1;
           check();
         }
    /* S->+|-|*|/|^ */
   for(z=0; z<15; z++)
     if(stk[z] == '+' || stk[z] == '*' || stk[z] == '/' || stk[z] == '^')
       {
         stk[z]='S';
         stk[z+1]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         check();
       }
   /*N->0*/
   for(z=0; z<15; z++)
     if(stk[z] == '0')
       {
         stk[z]='N';
         stk[z+1]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         check();
       }

  /*D->.*/
   for(z=0; z<15; z++)
     if(stk[z] == '.')
       {
         stk[z]='D';
         stk[z+1]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         check();
       }

   /*L->-*/
   for(z=0; z<15; z++)
     if(stk[z] == '-')
       {
         stk[z]='L';
         stk[z+1]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         check();
       }

   /* E->LESE | LELE */
    for(z=0; z<15; z++)
      if(stk[z]=='L' &&  stk[z+1]=='E' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='E')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

    /* E->LMSM | LMLM */
     for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='M' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='M')
         {
           stk[z]='E';
           stk[z+1]='\0';
           stk[z+2]='\0';
           stk[z+3]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
           i=i-3;
           check();
         }

     /* E->LESM | LELM */
      for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='E' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='M')
          {
            stk[z]='E';
            stk[z+1]='\0';
            stk[z+2]='\0';
            stk[z+3]='\0';
            printf("\n$%s\t%s$\t%s",stk,a,ac);
            i=i-3;
            check();
          }

      /* E->LMSE | LMLE */
       for(z=0; z<15; z++)
         if(stk[z]=='L' &&  stk[z+1]=='M' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='E')
           {
             stk[z]='E';
             stk[z+1]='\0';
             stk[z+2]='\0';
             stk[z+3]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-3;
             check();
           }

         /* E->LNSM | LNLM */
          for(z=0; z<15; z++)
            if(stk[z]=='L' &&  stk[z+1]=='N' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='M')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                stk[z+3]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-3;
                check();
              }

          /* E->LMSN | LMLN */
           for(z=0; z<15; z++)
             if(stk[z]=='L' &&  stk[z+1]=='M' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='N')
               {
                 stk[z]='E';
                 stk[z+1]='\0';
                 stk[z+2]='\0';
                 stk[z+3]='\0';
                 printf("\n$%s\t%s$\t%s",stk,a,ac);
                 i=i-3;
                 check();
               }

       /* E->LNSN | LNLN */
        for(z=0; z<15; z++)
          if(stk[z]=='L' &&  stk[z+1]=='N' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='N')
            {
              stk[z]='B';
              stk[z+1]='\0';
              stk[z+2]='\0';
              stk[z+3]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-3;
              check();
            }

        /* E->LESN | LELN */
         for(z=0; z<15; z++)
           if(stk[z]=='L' &&  stk[z+1]=='E' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='N')
             {
               stk[z]='B';
               stk[z+1]='\0';
               stk[z+2]='\0';
               stk[z+3]='\0';
               printf("\n$%s\t%s$\t%s",stk,a,ac);
               i=i-3;
               check();
             }

         /* E->LMSN | LMLN */
          for(z=0; z<15; z++)
            if(stk[z]=='L' &&  stk[z+1]=='M' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='N')
              {
                stk[z]='B';
                stk[z+1]='\0';
                stk[z+2]='\0';
                stk[z+3]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-3;
                check();
              }

    /* E->(LE) */
     for(z=0; z<15; z++)
       if(stk[z]=='(' &&  stk[z+1]=='L' && ( stk[z+2]=='E' || stk[z+2]=='A' || stk[z+2]=='B' )  && stk[z+3]==')')
         {
           stk[z]='M';
           stk[z+1]='\0';
           stk[z+2]='\0';
           stk[z+3]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
           i=i-3;
           check();
         }
   /*E->EN*/
   for(z=0; z<15; z++)
     if(stk[z] == 'E' && stk[z+1] == 'N')
       {
         stk[z]='E';
         stk[z+1]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-1;
         check();
       }
    /* E->ESE | ELE */
     for(z=0; z<15; z++)
       if(stk[z]=='E' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='E')
         {
           stk[z]='E';
           stk[z+1]='\0';
           stk[z+2]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
           i=i-2;
           check();
         }

     /* E->MSM | MLM */
      for(z=0; z<15; z++)
        if(stk[z]=='M' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='M')
          {
            stk[z]='E';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t%s",stk,a,ac);
            i=i-2;
            check();
          }

      /* E->ESM | ELM */
       for(z=0; z<15; z++)
         if(stk[z]=='E' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='M')
           {
             stk[z]='E';
             stk[z+1]='\0';
             stk[z+2]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-2;
             check();
           }

       /* E->MSE | MLE */
        for(z=0; z<15; z++)
          if(stk[z]=='M' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='E')
            {
              stk[z]='E';
              stk[z+1]='\0';
              stk[z+2]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-2;
              check();
            }

      /* E->NSM | NLM */
       for(z=0; z<15; z++)
         if(stk[z]=='N' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='M')
           {
             stk[z]='E';
             stk[z+1]='\0';
             stk[z+2]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-2;
             check();
           }

       /* E->MSN | MLN */
        for(z=0; z<15; z++)
          if(stk[z]=='M' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='N')
            {
              stk[z]='B';
              stk[z+1]='\0';
              stk[z+2]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-2;
              check();
            }
     /* E->ESN | ELN */
      for(z=0; z<15; z++)
        if(stk[z]=='E' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='N')
          {
            stk[z]='B';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t%s",stk,a,ac);
            i=i-2;
            check();
          }
      /* E->NSE | NLE */
       for(z=0; z<15; z++)
         if(stk[z]=='N' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='E')
           {
             stk[z]='E';
             stk[z+1]='\0';
             stk[z+2]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-2;
             check();
           }

     /* E->BSE | BLE */
      for(z=0; z<15; z++)
        if(stk[z]=='B' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='E')
          {
            stk[z]='E';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t%s",stk,a,ac);
            i=i-2;
            check();
          }

    /* E->BSM | BLM */
     for(z=0; z<15; z++)
       if(stk[z]=='B' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='M')
         {
           stk[z]='E';
           stk[z+1]='\0';
           stk[z+2]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
           i=i-2;
           check();
         }

       /* E->BSA | BLA */
        for(z=0; z<15; z++)
          if(stk[z]=='B' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='A')
            {
              stk[z]='E';
              stk[z+1]='\0';
              stk[z+2]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-2;
              check();
            }

      /* B->BSN | BLN */
       for(z=0; z<15; z++)
         if(stk[z]=='B' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='N')
           {
             stk[z]='B';
             stk[z+1]='\0';
             stk[z+2]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-2;
             check();
           }
       /* E->NSN | NLN */
        for(z=0; z<15; z++)
          if(stk[z]=='N' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='N')
            {
              stk[z]='B';
              stk[z+1]='\0';
              stk[z+2]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-2;
              check();
            }
      /*E->(E)*/
     for(z=0; z<15; z++)
       if(stk[z]=='(' && (stk[z+1]=='E' || stk[z+1]=='A' || stk[z+1] == 'B') && stk[z+2]==')')
         {
           stk[z]='M';
           stk[z+1]='\0';
           stk[z+2]='\0';
           printf("\n$%s\t%s$\t%s",stk,a,ac);
           i=i-2;
           check();
         }

   /*Bagian Koma*/
     /* A->NDN | NDE */
      for(z=0; z<15; z++)
        if(stk[z]=='N' && stk[z+1] == 'D' && (stk[z+2] == 'N' || stk[z+2] == 'E'))
          {
            stk[z]='A';
            stk[z+1]='\0';
            stk[z+2]='\0';
            printf("\n$%s\t%s$\t%s",stk,a,ac);
            i=i-2;
            check();
          }

          /* A->BDN | BDE */
          for(z=0; z<15; z++)
            if(stk[z]=='B' && stk[z+1] == 'D' && (stk[z+2] == 'N' || stk[z+2] == 'E'))
              {
                stk[z]='A';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }

      /* A->EDN | EDE */
       for(z=0; z<15; z++)
         if(stk[z]=='E' && stk[z+1] == 'D' && (stk[z+2] == 'N' || stk[z+2] == 'E'))
           {
             stk[z]='A';
             stk[z+1]='\0';
             stk[z+2]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-2;
             check();
           }

       /*A->AN | AE*/
       for(z=0; z<15; z++)
         if(stk[z] == 'A' && (stk[z+1] == 'N' || stk[z+1] == 'E'))
           {
             stk[z]='A';
             stk[z+1]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-1;
             check();
           }

       /* E->LNSA | LNLA */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='N' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='A')
       {
         stk[z]='E';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* E->LESA | LELA */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='E' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='A')
       {
         stk[z]='E';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* E->LASA | LALA */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='A' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='A')
       {
         stk[z]='E';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* B->LASN | LALN */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='A' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='N')
       {
         stk[z]='B';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* E->LMSA | LMLA */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='M' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='A')
       {
         stk[z]='E';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* E->LASM | LALM */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='A' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='M')
       {
         stk[z]='E';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* E->LASE | LALE */
       for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='A' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='E')
       {
         stk[z]='E';
         stk[z+1]='\0';
         stk[z+2]='\0';
         stk[z+3]='\0';
         printf("\n$%s\t%s$\t%s",stk,a,ac);
         i=i-3;
         check();
       }

       /* E->ASA | ALA */
        for(z=0; z<15; z++)
          if(stk[z]=='A' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='A')
            {
              stk[z]='E';
              stk[z+1]='\0';
              stk[z+2]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-2;
              check();
            }

      /* E->ASE | ALE */
       for(z=0; z<15; z++)
         if(stk[z]=='A' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='E')
           {
             stk[z]='E';
             stk[z+1]='\0';
             stk[z+2]='\0';
             printf("\n$%s\t%s$\t%s",stk,a,ac);
             i=i-2;
             check();
           }

       /* E->ESA | ELA */
        for(z=0; z<15; z++)
          if(stk[z]=='E' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='A')
            {
              stk[z]='E';
              stk[z+1]='\0';
              stk[z+2]='\0';
              printf("\n$%s\t%s$\t%s",stk,a,ac);
              i=i-2;
              check();
            }

        /* E->ASN | ALN */
         for(z=0; z<15; z++)
           if(stk[z]=='A' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='N')
             {
               stk[z]='B';
               stk[z+1]='\0';
               stk[z+2]='\0';
               printf("\n$%s\t%s$\t%s",stk,a,ac);
               i=i-2;
               check();
             }

         /* E->NSA | NLA */
          for(z=0; z<15; z++)
            if(stk[z]=='N' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='A')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }

        /* E->ASM | ALM */
         for(z=0; z<15; z++)
           if(stk[z]=='A' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='M')
             {
               stk[z]='E';
               stk[z+1]='\0';
               stk[z+2]='\0';
               //printf("\n$%s\t%s$\t%s",stk,a,ac);
               i=i-2;
               check();
             }

         /* E->MSA | MLA */
          for(z=0; z<15; z++)
            if(stk[z]=='M' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='A')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }

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
