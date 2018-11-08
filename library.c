#include<stdio.h>
#include<stdlib.h>

#define N 100
#define S 30

int library(char **, char *, int);
int comparisonAlpha(char, char);
void mallocLibWords(char **);
void freeLibWords(char **);
int readLib(FILE *, char **, char *);
void searchWord(char **, int, char *);
void addLib(char *,char *);

void main(){
  FILE *fp;
  char *libWords[N], libName[S]="library.txt";
  searchWord(libWords, readLib(fp, libWords, libName), libName);
}

int library(char *libWords[], char searchWord[], int wordsCount){
  int i,j=0,findCount[N];

  for(i=0;i<wordsCount;i++){
    if(comparisonAlpha(libWords[i][0],searchWord[0])){
      findCount[j]=i;
      j++;
    }
  }
  if(j==0)return -1;

  printf("Which word is your search?\n");
  for(i=0;i<j;i++){
    printf("%d: %s\n",i,libWords[findCount[i]]);
  }

  scanf("%d",&i);

  if(i<0)return -1;
  return findCount[i];  
}

int comparisonAlpha(char c1, char c2){
  int diff = 'a'-'A';
  
  if(c1==c2)return 1;

  if(c1>='a'&&c1<='z'){
    c1 -= diff;
    if(c1==c2)return 1;
  }

  if(c2>='a'&&c2<='z'){
    c2 -= diff;
    if(c1==c2)return 1;
  }

  return 0;
}

void mallocLibWords(char *libWords[]){
  int i;

  for(i=0;i<N;i++){
    libWords[i]=malloc(S);
  }
}

void freeLibWords(char *libWords[]){
  int i;

  for(i=0;i<N;i++){
    free(libWords[i]);
  }
}

int readLib(FILE *fp, char *libWords[], char libName[]){
  int i=0;
  
  if ((fp = fopen(libName, "r")) == NULL) {
    fprintf(stderr, "Fail to open file.\n");
  }

  mallocLibWords(libWords);
  
  while(1){
    if(fscanf(fp,"%s",libWords[i])==EOF)break;
    i++;
  }

  fclose(fp);

  return i;
}

void searchWord(char *libWords[], int i, char libName[]){
  char searchWord[S],com;
  int findNum;
  
  printf("input search word\n");
  scanf("%s",searchWord);

  findNum = library(libWords, searchWord, i);

  if(findNum<0){
    printf("%s is not found.\n",searchWord);
    printf("Add this word? input y or n.\n");

    scanf("%c",&com);
    if(com=='y')addLib(libName,searchWord);
  }
  
  else printf("%s is found.\n",libWords[findNum]);
  
  freeLibWords(libWords);
}

void addLib(char libName[],char searchWord[]){
  if ((fp = fopen(libName, "a")) == NULL) {
    fprintf(stderr, "Fail to open file.\n");
  }

  fprintf(fp,"%s",searchWord);

  close(fp);
}
