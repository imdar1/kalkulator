#include<stdio.h>
#include<string.h>
int k=0,z=0,i=0,j=0,c=0;
char a[256],ac[20],stk[15],act[10];
void check();
int main()
   {

      puts("GRAMMAR is : \n E->LESE|LELE|ESE|NSE \n B->ESN|NSN|LNLN|LNSN|LESN|LELN|LMSN|LMLN|MSN|MLN|ASN|ALN \n B->BSN|BLN \n A->BDB|BDE \n E->BSE|BLE|BSM|BLM|BLA|BSA \n E->ISI|ILI|ISE|ILE|ELI|ESI \n E->MLI|MSI|ILM|ISM|ASI|ALI|NLI|NSI \n E->LILI|LISI|LISE|LILE|LESI|LELI \n E->LMLI|LMSI|LISM|LILM|LNLI|LNSI|LALI|LASI \n B->LILN|LISN \n B->ILN|ISN \n E->LNSE|LNLE \n E->LNSM|LNLM \n E->LMLM|LMSM|LESM|LELM|LMSE|LMLE \n E->MSM|MLM|ESM|ELM|MSE|MLE \n E->NSM|NLM \n E->ASA|ALA|ASE|ALE|ESA|ELA \n E->NSA|NLA \n E->ASM|ALM|MSA|MLA \n E->LALA|LASA|LALE|LASE|LELA|LESA \n E->LNLA|LNSA|LMLA|LMSA|LASM|LALM \n B->LASN|LALN \n D->. \n A->NDN|NDE|EDN|EDE \n A->AE|EN \n L->- \n S->+|*|/|^ \n M->(E)|(A)|(B)|(I) \n E->1|2|3|4|5|6|7|8|9 \n E->EE \n N->0 \n M->(LE)|(LA)|(LB)|(LI) \n E->EN \n I->EC|NC|AC|C \n C->i");
      puts("enter input string ");
      gets(a);
      c=strlen(a);
      strcpy(act,"SHIFT->");
      puts("stack \t input \t action");
      for(k=0,i=0; j<c; k++,i++,j++)
       {
              stk[i]=a[j];
              a[j]=' ';
              printf("\n$%s\t%s$\t%sid",stk,a,act);
              check();
       }

       check();

       if (stk[0] == 'E' && stk[1] == '\0' && a[j-1] == ' ')
			printf("\nMASUK");

      if (stk[0] == 'A' && stk[1] == '\0' && a[j-1] == ' ')
     printf("\nMASUK");

     if (stk[0] == 'B' && stk[1] == '\0' && a[j-1] == ' ')
    printf("\nMASUK");

    if (stk[0] == 'M' && stk[1] == '\0' && a[j-1] == ' ')
   printf("\nMASUK");

   if (stk[0] == 'I' && stk[1] == '\0' && a[j-1] == ' ')
  printf("\nMASUK");

   /*Ini Bahaya*/
   if(stk[0] == 'L' && (stk[1] =='E' || stk[1]=='N') && stk[2] == '\0' && a[j-1] == ' ')
   printf("\nMASUK");

   if(stk[0] == '(' && stk[1] == 'L' && stk[2]=='N' && stk[3]==')' && stk[4] == '\0' && a[j-1] == ' ')
    printf("\nMASUK");

    if(stk[0] == '(' && stk[1]=='N' && stk[2]==')' && stk[3] == '\0' && a[j-1] == ' ')
     printf("\nMASUK");

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

     for(z=0; z<15; z++)
       if(stk[z]=='i')
         {
           stk[z]='C';
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

     /*I->BC|EC|NC|AC*/
    for(z=0; z<15; z++)
      if((stk[z] == 'B' || stk[z] == 'E' || stk[z] == 'N' || stk[z] == 'A') && stk[z+1] == 'C')
        {
          stk[z]='I';
          stk[z+1]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-1;
          check();
        }

    /*I->C*/
    for(z=0; z<15; z++)
      if(stk[z]=='C')
        {
          stk[z]='I';
          stk[z+1]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
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

    /* E->LNSE | LNLE */
     for(z=0; z<15; z++)
       if(stk[z]=='L' &&  stk[z+1]=='N' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='E')
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

    /* M->(LE) */
     for(z=0; z<15; z++)
       if(stk[z]=='(' &&  stk[z+1]=='L' && ( stk[z+2]=='E' || stk[z+2]=='A' || stk[z+2]=='B' || stk[z+2] == 'I' )  && stk[z+3]==')')
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
       if(stk[z]=='(' && (stk[z+1]=='E' || stk[z+1]=='A' || stk[z+1] == 'B' || stk[z+1] == 'I') && stk[z+2]==')')
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
               printf("\n$%s\t%s$\t%s",stk,a,ac);
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

        /*Imajiner*/
        /* E->LISI | LILI */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='I' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='I')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->LISE | LILE */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='I' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='E')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->LESI | LELI */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='E' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='I')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->LMSI | LMLI */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='M' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='I')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->LISM | LILM */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='I' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='M')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->LNSI | LNLI */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='N' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='I')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->LASI | LALI */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='A' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='I')
        {
          stk[z]='E';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* B->LISN | LILN */
        for(z=0; z<15; z++)
        if(stk[z]=='L' &&  stk[z+1]=='I' && (stk[z+2]=='S' || stk[z+2]=='L')  && stk[z+3]=='N')
        {
          stk[z]='B';
          stk[z+1]='\0';
          stk[z+2]='\0';
          stk[z+3]='\0';
          printf("\n$%s\t%s$\t%s",stk,a,ac);
          i=i-3;
          check();
        }

        /* E->ILI | ISI */
         for(z=0; z<15; z++)
           if(stk[z]=='I' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='I')
             {
               stk[z]='E';
               stk[z+1]='\0';
               stk[z+2]='\0';
               printf("\n$%s\t%s$\t%s",stk,a,ac);
               i=i-2;
               check();
             }

         /* E->ALI | ASI */
          for(z=0; z<15; z++)
            if(stk[z]=='A' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='I')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }


         /* E->ILE | ISE */
          for(z=0; z<15; z++)
            if(stk[z]=='I' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='E')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }

        /* E->ELI | ESI */
         for(z=0; z<15; z++)
           if(stk[z]=='E' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='I')
             {
               stk[z]='E';
               stk[z+1]='\0';
               stk[z+2]='\0';
               printf("\n$%s\t%s$\t%s",stk,a,ac);
               i=i-2;
               check();
             }

         /* E->MLI | MSI */
          for(z=0; z<15; z++)
            if(stk[z]=='M' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='I')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }

          /* E->ILM | ISM */
           for(z=0; z<15; z++)
             if(stk[z]=='I' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='M')
               {
                 stk[z]='E';
                 stk[z+1]='\0';
                 stk[z+2]='\0';
                 printf("\n$%s\t%s$\t%s",stk,a,ac);
                 i=i-2;
                 check();
               }

         /* E->NLI | NSI */
          for(z=0; z<15; z++)
            if(stk[z]=='N' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='I')
              {
                stk[z]='E';
                stk[z+1]='\0';
                stk[z+2]='\0';
                printf("\n$%s\t%s$\t%s",stk,a,ac);
                i=i-2;
                check();
              }

        /* B->ILN | ISN */
         for(z=0; z<15; z++)
           if(stk[z]=='I' && ( stk[z+1]=='S' || stk[z+1]=='L' ) && stk[z+2]=='N')
             {
               stk[z]='B';
               stk[z+1]='\0';
               stk[z+2]='\0';
               printf("\n$%s\t%s$\t%s",stk,a,ac);
               i=i-2;
               check();
             }

   }
