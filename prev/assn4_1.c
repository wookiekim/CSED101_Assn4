/*김승욱 기계공학과 20150630 */
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"//string.h 헤더파일을 대체하기위한 헤더파일입니다.

typedef struct{
int num; // 사전 파일 “word.txt”에서 단어의 위치(몇 번째 단어)
char *word; // 영어 단어
char *meaning; // 단어의 뜻(한글)
}WORDINFO;//구조체를 WORDINFO라는 data type으로 선언해줍니다.

void opt_help();//help를 입력 받았을때 실행하는 함수입니다.
void opt_quit(WORDINFO *recentTable);//quit을 입력받았을때 실행하는 함수입니다.
int opt_single(WORDINFO * recentTable);//single을 입력받았을때 실행하는 함수입니다.
int opt_multi(WORDINFO * recentTable);//multi를 입력받았을때 실행하는 함수입니다.
void add_table(WORDINFO recentTable[5],int line,char * term, char * def);//검색 성공시 recentTable에 단어를 추가하는 함수입니다.
void print_table(WORDINFO* recentTable);//recent를 입력받았을 때 실행하는 함수입니다.
int main()
{
	WORDINFO recentTable[5]={0};//recentTable을 선언과 같이 0으로 초기화해줍니다. 
	char opt[20];	

	opt_help();//초기 메뉴를 출력합니다.

	while(1){//명령어가 아닌 명령어를 받거나, quit외의 명령어를 받았을 시 무한으로 돌아가게 하기 위한 반복문입니다.

		printf(">>");
		scanf("%s",opt);//명령어를 입력받습니다.

		if(mystrcmp(mytolower(opt),"quit")==0){//명령어가 quit일시
			opt_quit(recentTable);//동적할당 받은 공간들을 free
			break;//반복문을 빠져나갑니다.
		}
		else if(mystrcmp(mytolower(opt),"help")==0)//명령어가 help일시
		{
			opt_help();//초기화면 출력(명령어 설명)
		}

		else if(mystrcmp(mytolower(opt),"single")==0)//명령어가 single일시
		{
			opt_single(recentTable);//single 실행
		}

		else if(mystrcmp(mytolower(opt),"multi")==0)//명령어가 multi일시
		{
			opt_multi(recentTable);//multi 실행
		}

		else if(mystrcmp(mytolower(opt),"recent")==0)//명령어가 recent일시
		{
			print_table(recentTable);//recentTable출력
		}
	}

	return 0;//프로그램 종료. Quit을 통해서야만 정상적인 종료가 가능합니다.
}

void opt_help()//명령어 설명 출력
{
	printf("------------------------------\n"); 
	printf("single: 한 단어 검색\n");
	printf("multi : 여러 단어 검색\n");
	printf("recent: 최근 검색 단어\n");
	printf("quit  : 프로그램 종료\n");
	printf("help  : 명령어 목록 보기\n");
	printf("------------------------------\n"); 
}

void add_table(WORDINFO recentTable[5],int line,char * term, char * def)
{
	int i,j,k;

	for(i=0;i<5;i++)	
		if(recentTable[i].num==line){//recentTable에 이미 단어가 있는지 확인합니다.
			if(i==0)//만일 같은 단어가 recentTable의 첫 칸에 있다면 바꿀 필요가 없기에, 바로 break문을 합니다.
				break;
			else{
				for(j=i;j>=1;j--){//같은 단어가 recentTable이 아닌 다른 칸에 있다면, 단어를 한 칸씩 밀어줍니다. 
					mystrcpy(recentTable[j].word=(char*)realloc(recentTable[j].word,mystrlen(recentTable[j-1].word)*sizeof(char)+1),recentTable[j-1].word);
					mystrcpy(recentTable[j].meaning=(char*)realloc(recentTable[j].meaning,mystrlen(recentTable[j-1].meaning)*sizeof(char)+1),recentTable[j-1].meaning);
					recentTable[j].num=recentTable[j-1].num;
				}		
				mystrcpy(recentTable[0].word=(char*)realloc(recentTable[0].word,mystrlen(term)*sizeof(char)+1),term);
				mystrcpy(recentTable[0].meaning=(char*)realloc(recentTable[0].meaning,mystrlen(def)*sizeof(char)+1),def);
				recentTable[0].num=line;//이후 첫 칸에 새롭게 찾은 단어의 정보를 추가합니다.
				break;
			}
		}
	if(i==5){//만일 recentTable에 같은 단어가 없을 시
		if(recentTable[0].num==0);//만일 recentTable에 아무 정보가 없을 시에는, else를 건너 뛴 뒤 맨 아래에 있는 작업만 수행합니다.
		else{//recentTable에 정보가 저장되어있을때
			for(j=1;j<5;j++)
				if(recentTable[j].num==0)//몇번째 칸까지 정보가 저장되어있는지 확인합니다.
					break;
			if(j==5){//모든 칸에 정보가 있을시4
			free(recentTable[j-1].word);//마지막 칸에 동적할당 되어있는 메모리들을 free해줍니다.
			free(recentTable[j-1].meaning);
			j=4;//이는 다음에 있는 반복문을 위하여, j가 5일때 4로 바꾸어줍니다.
			}
			for(k=j;k>=1;k--){
					mystrcpy(recentTable[k].word=(char*)malloc(mystrlen(recentTable[k-1].word)*sizeof(char)+1),recentTable[k-1].word);
					mystrcpy(recentTable[k].meaning=(char*)malloc(mystrlen(recentTable[k-1].meaning)*sizeof(char)+1),recentTable[k-1].meaning);
					recentTable[k].num=recentTable[k-1].num;
					free(recentTable[k-1].word);
					free(recentTable[k-1].meaning);
			}//한 칸씩 뒤로 밀어 준뒤, 밀리기 전의 칸을 free해줍니다.
		}
		mystrcpy(recentTable[0].word=(char*)malloc(mystrlen(term)*sizeof(char)+1),term);
		mystrcpy(recentTable[0].meaning=(char*)malloc(mystrlen(def)*sizeof(char)+1),def);
		recentTable[0].num=line;
	}//첫 칸에 받아온 단어의 정보를 저장합니다.
}

void print_table(WORDINFO* recentTable)
{
	int i;
	printf("최근 검색 단어 목록\n");

	for(i=0;i<5;i++)//recentTable내에 저장되어있는 정보들을 출력합니다.
		if(recentTable[i].num!=0)//정보가 없는 부분은 출력하지 않습니다.
		printf("%3d.%s : %s\n",recentTable[i].num,recentTable[i].word,recentTable[i].meaning);
}
void opt_quit(WORDINFO *recentTable)
{
	int i;
	for(i=0;i<5;i++)
				free(recentTable[i].word);//recentTable의 word에 할당되어있는 메모리를 모두 free해줍니다.
	for(i=0;i<5;i++)
				free(recentTable[i].meaning);//recentTable의 meaning에 할당되어있는 메모리를 모두 free해줍니다.
}
int opt_single(WORDINFO * recentTable)
{
	char search[100],term[100],def[100];//찾을 단어와 단어의 뜻, 그리고 입력받을 단어를 저장할 배열을 선언해줍니다.
	FILE* infile;//infile이라는 파일경로를 선언해줍니다.
	int line=0,found=0;//줄 수와 찾았는지 못찾았는지를 결정해주는 변수를 선언해줍니다.
	printf("검색할 단어: ");
			scanf("%s",search);//찾을 단어를 입력받습니다.

			infile=fopen("word.txt","r");//word.txt를 읽기형식으로 열어줍니다.
			if(infile==NULL){
				printf("word.txt를 찾을 수 없습니다\n");//만일 word.txt가 없을시에는 비정상적으로 single함수를 나와줍니다.
				return 1;
			}
			while(fscanf(infile,"%s %s",term,def)==2){//한 줄씩 읽으며, 단어 - 뜻 식으로 받아옵니다.
				line++;//한 줄을 읽을때마다 line의 값을 1씩 증가해줍니다.
				if(mystrcmp(term,search)==0){//만일 word.txt에서 입력받은 단어와 같은 단어를 찾았을 시
					found++;//found 를 1로 증가시켜줍니다.
					printf("[검색 성공] %3d.%s : %s\n",line,term,def);//결과를 출력합니다.
					add_table(recentTable,line,term,def);//찾은 단어를 recentTable로 옮겨줍니다
					fclose(infile);//파일경로를 닫아줍니다.
					break;//이미 찾았으니 더 이상 찾을 필요가 없으므로, 반복문을 나와줍니다.
				}
			}
			if(found==0){//만일 찾지 못했을시, found 는 0에서 증가하지 않습니다.
			printf("[검색 실패] %s 사전에 없는 단어\n",search);//결과출력
			}
			return 0;
}
int opt_multi(WORDINFO * recentTable)//multi를 입력받았을 시 실행합니다.
{
	int line=0,found=0;//줄 수와 찾았는지 못 찾았는지의 변수를 선언하여줍니다.
	FILE * infile, *infile2;//파일 경로를 2개 선언해줍니다.
	char search[100],term[100],def[100],filename[100];//입력받을 단어와 파일이름,그리고 word.txt에서의 단어와 뜻을 저장할 변수를 선언해줍니다.

	printf("파일명 입력 : ");
			scanf("%s",filename);//파일명을 입력받습니다.
			infile=fopen(filename,"r");//입력받은 파일명의 파일을 읽기형식으로 열어줍니다
			if(infile==NULL){
				printf("[%s] 파일을 찾을 수 없습니다\n",filename);//filename에 일치하는 파일이 없을 시에는 비정상적으로 종료하여줍니다.
				return 1;
			}
			infile2=fopen("word.txt","r");//word.txt를 읽기형식으로 열어줍니다.
			if(infile2==NULL){
				printf("word.txt를 찾을 수 없습니다\n");//word.txt가 없을 시에는 비정상적으로 종료하여줍니다.
				return 1;
			}
			while(fscanf(infile,"%s",search)==1)//infile 파일경로에서 읽어올 단어가 없을 때까지 도는 반복문입니다.
			{
				line=0;//줄 수
				found=0;//찾았는지 못 찾았는지에 대한 변수

				while(fscanf(infile2,"%s %s",term,def)==2){//word.txt에서 단어 - 뜻 식으로 읽어올 수 없을때까지
					line++;//줄 수 증가

					if(mystrcmp(term,search)==0){//infile에서 읽어온 단어가 word.txt에 있을 시에
						found++;//found == 1이됩니다
						printf("[검색 성공] %3d.%s : %s\n",line,term,def);//결과 출력
						add_table(recentTable,line,term,def);//recentTable에 추가
						rewind(infile2);//파일 포인터를 다시 파일의 시작부분으로 돌려줍니다.
						break;//이미 찾았으니, 반복문을 나와줍니다.
					}
				}
				if(found==0){//찾지 못했을 시
				printf("[검색 실패] %s 사전에 없는 단어\n",search);//결과 출력
				rewind(infile2);//마찬가지로 파일 포인터를 맨 위로 올려줍니다.
				}
			}
			fclose(infile);//infile경로를 닫아줍니다.
			fclose(infile2);//infile2경로를 닫아줍니다.
			return 0;
}