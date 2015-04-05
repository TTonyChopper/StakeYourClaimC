#include <stdio.h>

int main()
{
    int jeu = 1;
    int m=0;
    int n=0;
    int a=0;
    int b=0;
    int t[552];
    int vraisindices[552];
    int resultsi=0;
    int resultsp=0;
    int q;
    for(q=0;q<552;q++)
    {
     vraisindices[q]=0;
    }
    int nbtour = 0;
    int casemn=0;
    imprimertableau0(&a,&b,t);
    creerindices(a,b,vraisindices);
    do
    {
        int parite=(nbtour)%2;
        (parite) ? tourpair(&nbtour,&m,&n,a,b,t,&casemn,vraisindices) : tourimpair(&nbtour,&m,&n,a,b,t,&casemn,vraisindices);
        imprimertableaufinal(a,b,t);
        jeu=testerfindejeu(a,b,t,&jeu,vraisindices,parite);
    }
    while (jeu);
    printf("                            GAME OVER                         \n");
    points(a,b,t,vraisindices,&resultsi,&resultsp);
    Gagnant(&resultsi,&resultsp,nbtour);
    return 0;
}

void imprimertableau0(int *pa,int *pb,int t[])
{
    int i;
    printf("\n\n                             STAKE YOUR CLAIM\n\n");
    printf("Nombre de lignes(26max)?");
    scanf("\n%d",pb);
    printf("Nombre de colonnes(18max)?");
    scanf("%d",pa);
    imprimerligne0(*pa);
    inittableau(t);
    for(i=0; i < *pb; i++)
    {
        imprimerbord(*pa);
        imprimercases0(*pa,i);
    }
    imprimerbord(*pa);
}

void imprimerligne0(int a)
{
    int i;int z;
    printf(" ");
    for(i=0,z='1'; i < a; i++,z++)
    {
        printf("   %c",z);
    }
    printf("\n");
}

void inittableau(int t[])
{
    int i;
    for (i = 0 ; i < 552; i++)
    {
      t[i] =' ';
    }
}

void imprimerbord(int a)
{
    int i;
    printf("  ");
    for(i=0; i<a; i++)
    {
        printf("+---");
    }
    printf("+\n");
}

void imprimercases0(int a,int i)
{
    int j;
    int z='A'+i;
    printf("%c ",z);
    for(j=0; j<a; j++)
    {
        printf("|   ");
    }
    printf("|\n");
}

void creerindices(int a,int b,int *vraisindices[])
{
 int i;
 for(i=0;i<a*b;i++)
 {
  int k=0;
  k=i/a;
  vraisindices[i]=a+2+i+k;
 }
}

int coupimpossible(int a,int b,int casemn,int vraisindices[])
 {
  int i;
  int couphorscases = 1;
  for(i=0;i<a*b;i++)
   {
    if (casemn==vraisindices[i])
     {
         (couphorscases=0);
     }
   }
  return couphorscases;
 }

void tourimpair(int *pnbtour,int *pm,int *pn,int a,int b,int *t[],int *pcasemn,int *vraisindices[])
{
    *pnbtour=(*pnbtour)+1;
    do
    {
        do
      {
        printf("Tour No%d,Joueur 1(X) :\nChoisissez la case(LettreChiffre):",*pnbtour);
        scanf("\n%c",pm);
        scanf("\n%c",pn);
        *pcasemn=(*pm -'A'+1)*(a+1)+(*pn-'1'+2)-1;
        if (coupimpossible(a,b,*pcasemn,vraisindices))
           {
            printf("         Case INTROUVABLE!\n             Rejouez\n");
           }
      }
      while (coupimpossible(a,b,*pcasemn,vraisindices));
      printf("VOUS AVEZ JOUE :%c%c\n",*pm,*pn);
    }
    while (verificationimpair(t,pcasemn)!=1);
    t[*pcasemn]='X';
    adji(a,t,pcasemn);
}

int verificationimpair(int *t[],int *pcasemn)
{
    int R = 1;
    if (t[*pcasemn]=='#'||t[*pcasemn]=='o'||t[*pcasemn]=='O'||t[*pcasemn]=='X')
    {
        printf("         Coup NON AUTORISE!\n             Rejouez\n");
        R = 0;
    }
    return R;
}

void adji(int a,int *t[],int *pcasemn)
{
  int doubleif = 0;
  *pcasemn = (*pcasemn)-1;
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)-(a);
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)+(a+2);
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)+(a);
     if (t[*pcasemn] == 'o'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'X')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='x';
      }
}

void tourpair(int *pnbtour,int *pm,int *pn,int a,int b,int *t[],int *pcasemn,int *vraisindices[])
{
    *pnbtour=(*pnbtour)+1;
    do
    {
        do
      {
        printf("Tour No%d,Joueur 2(O) :\nChoisissez la case(LettreChiffre):",*pnbtour);
        scanf("\n%c",pm);
        scanf("\n%c",pn);
        *pcasemn=(*pm -'A'+1)*(a+1)+(*pn-'1'+2)-1;
        if (coupimpossible(a,b,*pcasemn,vraisindices))
           {
             printf("         Case INTROUVABLE!\n             Rejouez\n");
           }
      }
      while (coupimpossible(a,b,*pcasemn,vraisindices));
      printf("VOUS AVEZ JOUE :%c%c\n",*pm,*pn);
    }
    while (verificationpair(t,pcasemn)!=1);
    t[*pcasemn]='O';
    adjp(a,t,pcasemn);
}

int verificationpair(int *t[],int *pcasemn)
{
    int R = 1;
    if (t[*pcasemn]=='#'||t[*pcasemn]=='x'||t[*pcasemn]=='X'||t[*pcasemn]=='O')
    {
        printf("         Coup NON AUTORISE!\n             Rejouez\n");
        R = 0;
    }
    return R;
}

void adjp(int a,int *t[],int *pcasemn)
{
  int doubleif = 0;
  *pcasemn = (*pcasemn)-1;
     if (t[*pcasemn] == 'x'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='o';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)-(a);
     if (t[*pcasemn] == 'x'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='o';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)+(a+2);
     if (t[*pcasemn] == 'x'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='o';
      }
  doubleif = 0;
  *pcasemn = (*pcasemn)+(a);
     if (t[*pcasemn] == 'x'||t[*pcasemn] == '#')
      {
        t[*pcasemn]='#';
        doubleif=1;
      }
     if (t[*pcasemn] == 'O')
      {
        doubleif=1;
      }
     if (doubleif!=1)
      {
        t[*pcasemn]='o';
      }
}

void imprimertableaufinal(int a,int b,int *t[])
{
    int i;
    int z;
    int j;
    int casemnrecalcule=0;
    imprimerligne0(a);
    for(i=0,z='A'; i<b; i++,z++)
    {
        imprimerbord(a);
        printf("%c ",z);
        for(j=0; j<a; j++)
        {
            casemnrecalcule=(i+1)*(a+1)+(j+2)-1;
            printf("| %c ",t[casemnrecalcule]);
        }
        printf("|\n");
    }
    imprimerbord(a);
}

int testerfindejeu(int a,int b,int t[],int *jeu,int vraisindices[],int parite)
{
  *jeu=0;
  int k;
  if(parite)
    {
      for(k=0; k<a*b; k++)
     {
      if((t[vraisindices[k]] == 'x') || (t[vraisindices[k]]==' '))
            {
                *jeu = 1;
            }
     }
    }
  else
    {

      for(k=0; k<a*b; k++)
     {
      if((t[vraisindices[k]] == 'o') || (t[vraisindices[k]]==' '))
            {
                *jeu = 1;
            }
     }
    }
 return *jeu;
 }

int points(int a,int b,int t[],int vraisindices[],int *resultsi,int *resultsp)
  {
      int k;
      for(k=0; k<a*b; k++)
     {
      if (t[vraisindices[k]] == 'x')
            {
                *resultsi=(*resultsi)+1;
            }
      if (t[vraisindices[k]] == 'X')
            {
                *resultsi=(*resultsi)+4;
            }
      if(t[vraisindices[k]] == 'o')
            {
                *resultsp=(*resultsp)+1;
            }
      if(t[vraisindices[k]] == 'O')
            {
                *resultsp=(*resultsp)+4;
            }
     }
  }

void Gagnant(int *resultsi,int *resultsp,int nbtour)
 {
  if(*resultsi>*resultsp)
   {
    printf("Le Joueur 1(X) gagne avec un score de %d a %d [%d tours]",*resultsi,*resultsp,nbtour);
   }
  if(*resultsi<*resultsp)
   {
    printf("Le Joueur 2(O) gagne avec un score de %d a %d [%d tours]",*resultsp,*resultsi,nbtour);
   }
   if(*resultsi==*resultsp)
   {
    printf("EGALITE : %d-%d [%d tours],vous pouvez rejouer.....",*resultsi,*resultsp,nbtour);
   }
 }

