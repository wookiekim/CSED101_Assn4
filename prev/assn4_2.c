/* 김승욱 기계공학과 20150630*/
#include <stdio.h>
#include <stdlib.h>//malloc과 realloc을 사용하기 위한 헤더입니다.
#include "mystring.h"//string.h를 대체하는 사용자 정의 헤더파일입니다.

typedef struct{
int num; // 사전 파일 “word.txt”에서 단어의 위치(몇 번째 단어)
char *word; // 영어 단어
char *meaning; // 단어의 뜻(한글)
}WORDINFO;

void opt_help();//help를 입력받았을 시에 실행하는 함수입니다.
void opt_quit(WORDINFO *recentTable,WORDINFO* hashTable[][4]);//quit을 입력받았을 시에 실행하는 함수입니다.
int opt_single(WORDINFO * recentTable,WORDINFO * hashTable[][4]);//single을 입력받았을 시에 실행하는 함수입니다.
int opt_multi(WORDINFO * recentTable,WORDINFO * hashTable[][4]);//multi를 입력받았을 시에 실행하는 함수입니다.
void add_table(WORDINFO recentTable[5],int line,char * term, char * def);//recentTable에 단어정보를 추가하는 함수입니다.
void print_table(WORDINFO* recentTable);//recentTable을 출력하는 함수입니다.
void add_hash(int line, char* term, char* def, WORDINFO * hashTable[][4]);//hashTable에 단어정보를 추가하는 함수입니다.
void print_hash(WORDINFO* hashTable[][4]);//hashTable에 저장되어있는 정보들을 출력하는 함수입니다.
int check_hash(char*word,WORDINFO*recentTable, WORDINFO * hashTable[][4]);//hashTable에 찾고싶은 단어가 있는지 확인하는 함수입니다.
int get_key(char* word);//입력받은 단어의 알파벳들의 ASCII코드 합을 더하여 반환해주는 함수입니다.
int main()
{
	WORDINFO recentTable[5]={0}; //recentTable을 선언해줍니다.
	WORDINFO * hashTable[7][4]={0};//hashTable을 선언해줍니다.

	char opt[20];//명령어를 입력받을 배열을 선언하여줍니다.

	opt_help();//초기화면을 출력합니다.(명령어 설명)

	while(1){//quit을 입력받기 전에는 프로그램이 종료되지 않도록 무한반복문을 사용합니다.

		printf(">>");
		scanf("%s",opt);

		if(mystrcmp(mytolower(opt),"quit")==0){//quit을 입력받았을시
			opt_quit(recentTable,hashTable);//할당된 메모리들을 free해줍니다.
			break;//반복문을 빠져나갑니다.
		}
		else if(mystrcmp(mytolower(opt),"help")==0)//help를 입력받았을 시
		{
			opt_help();//명령어 설명을 출력하여줍니다.
		}

		else if(mystrcmp(mytolower(opt),"single")==0)//single을 입력받았을 시
		{
			opt_single(recentTable,hashTable);//word.txt에서 입력받은 단어를 찾아줍니다.
		}

		else if(mystrcmp(mytolower(opt),"multi")==0)//multi를 입력받았을 시
		{
			opt_multi(recentTable,hashTable);//word.txt에서 원하는 파일에 있는 단어들의 뜻을 찾아줍니다.
		}

		else if(mystrcmp(mytolower(opt),"recent")==0)//recent를 입력받았을 시
		{
			print_table(recentTable);//recentTable을 출력하여줍니다.
		}

		else if(mystrcmp(mytolower(opt),"print")==0)//print를 입력받았을 시
		{
			print_hash(hashTable);//hashTable을 출력하여줍니다.
		}
	}
	return 0;//프로그램을 종료합니다.
}

void opt_help()//명령어들의 설명을 출력하여줍니다.
{
	printf("------------------------------\n"); 
	printf("single: 한 단어 검색\n");
	printf("multi : 여러 단어 검색\n");
	printf("recent: 최근 검색 단어\n");
	printf("print : 해시 테이블 출력\n");
	printf("quit  : 프로그램 종료\n");
	printf("help  : 명령어 목록 보기\n");
	printf("------------------------------\n"); 
}

void add_table(WORDINFO recentTable[5],int line,char * term, char * def)//recentTable에 단어정보를 입력하여줍니다.
{
	int i,j,k;

	for(i=0;i<5;i++)//recentTable에 입력받은 단어와 같은 단어가 있는지 확인합니다.
		if(recentTable[i].num==line){//만일 있다면
			if(i==0)//만일 첫 자리에 같은 단어가 있다면 그저 빠져나와줍니다. recentTable에 변화를 줄 필요가 없습니다.
				break;
			else{//만일 같은 자리에 있지 않다면
				for(j=i;j>=1;j--){//모든 단어정보를 한칸씩 뒤로 밀어 준 뒤
					mystrcpy(recentTable[j].word=(char*)realloc(recentTable[j].word,mystrlen(recentTable[j-1].word)*sizeof(char*)+1),recentTable[j-1].word);
					mystrcpy(recentTable[j].meaning=(char*)realloc(recentTable[j].meaning,mystrlen(recentTable[j-1].meaning)*sizeof(char*)+1),recentTable[j-1].meaning);
					recentTable[j].num=recentTable[j-1].num;
				}		
				mystrcpy(recentTable[0].word=(char*)realloc(recentTable[0].word,mystrlen(term)*sizeof(char*)+1),term);
				mystrcpy(recentTable[0].meaning=(char*)realloc(recentTable[0].meaning,mystrlen(def)*sizeof(char*)+1),def);
				recentTable[0].num=line;//첫번째 칸에 단어정보를 저장합니다.
				break;
			}
		}
	if(i==5){//만일 같은 단어가 없을 시
		if(recentTable[0].num==0);//recentTable에 아무 정보도 저장되어있지 않다면 else를 건너뜁니다.
		else{//recentTable에 정보가 있을 시
			for(j=1;j<5;j++)
				if(recentTable[j].num==0)
					break;//recentTable이 어디까지 단어정보를 저장하고 있는지 알아냅니다
			if(j==5){//모든 칸에 정보가 있을 시
			free(recentTable[j-1].word);//마지막 칸에 할당되어있는 정보를 free해줍니다.
			free(recentTable[j-1].meaning);
			j=4;
			}
			for(k=j;k>=1;k--){//모든 정보를 한 칸씩 뒤로 밀어줍니다.
					mystrcpy(recentTable[k].word=(char*)malloc(mystrlen(recentTable[k-1].word)*sizeof(char*)+1),recentTable[k-1].word);
					mystrcpy(recentTable[k].meaning=(char*)malloc(mystrlen(recentTable[k-1].meaning)*sizeof(char*)+1),recentTable[k-1].meaning);
					recentTable[k].num=recentTable[k-1].num;
					free(recentTable[k-1].word);
					free(recentTable[k-1].meaning);//정보를 민 후, 저장되어있던 곳에 할당된 메모리를 free해줍니다.
			}
		}
		mystrcpy(recentTable[0].word=(char*)malloc(mystrlen(term)*sizeof(char*)+1),term);
		mystrcpy(recentTable[0].meaning=(char*)malloc(mystrlen(def)*sizeof(char*)+1),def);
		recentTable[0].num=line;
	}//첫 칸에 단어정보를 추가합니다.
}
void print_table(WORDINFO* recentTable)
{
	int i;
	printf("최근 검색 단어 목록\n");

	for(i=0;i<5;i++)//recentTable에 저장되어있는 정보를 저장합니다
		if(recentTable[i].num!=0)
		printf("%3d.%s : %s\n",recentTable[i].num,recentTable[i].word,recentTable[i].meaning);
}
void opt_quit(WORDINFO *recentTable,WORDINFO* hashTable[][4])
{
	int i,j;
	for(i=0;i<5;i++){//recentTable에 동적할당 되어있는 메모리를 모두free해줍니다.
				free(recentTable[i].word);
				free(recentTable[i].meaning);
	}
	for(j=0;j<7;j++)
		for(i=0;i<4;i++){//hashTable에 동적할당 되어있는 메모리를 모두 free해줍니다.
			if(hashTable[j][i]!=0){//hashTable의 포인터들이 가르키는 word와 meaning우선 free해줍니다.
			free(hashTable[j][i]->word);
			free(hashTable[j][i]->meaning);
			}
			free(hashTable[j][i]);//그 후에 hashTable을 free해줍니다.
		}
}
int opt_single(WORDINFO * recentTable,WORDINFO * hashTable[][4])
{
	char search[100],term[100],def[100];//필요한 캐릭터배열 선언
	FILE* infile;//파일경로 선언
	int line=0,found=0,key=0;
	printf("검색할 단어: ");
			scanf("%s",search);//단어 입력받기

			if(check_hash(search,recentTable,hashTable));//입력받은 단어가 hashTable에 있는지 확인
			else{//hashTable에 없을 시
				infile=fopen("word.txt","r");//word.txt.파일을 읽기형식으로 열기
				if(infile==NULL){//word.txt가 없을 시 비정상적으로 single함수 빠져나옴
					printf("word.txt를 찾을 수 없습니다\n");
					return 1;
				}
				while(fscanf(infile,"%s %s",term,def)==2){//word.txt에서 단어 - 뜻 형식으로 받아올수 있을때
					line++;
					if(mystrcmp(term,search)==0){//같은 단어를 찾는다면
						found++;
						printf("[검색 성공(파일)] %3d.%s : %s\n",line,term,def);//결과 출력
						add_table(recentTable,line,term,def);//recentTable에 단어 정보 추가
						add_hash(line,term,def,hashTable);//hashTable에 단어 정보 추가
						fclose(infile);//파일 경로 닫기
						break;//이미 찾았으니 반복문 탈출
					}
				}
				if(found==0){//못 찾았을시
				printf("[검색 실패] %s 사전에 없는 단어\n",search);//결과출력
				}
			}
			return 0;//정상적 single빠져나오기
}
int opt_multi(WORDINFO * recentTable,WORDINFO* hashTable[][4])
{
	int line=0,found=0,key=0;//필요 변수 선언
	FILE * infile, *infile2;//파일 경로 선언
	char search[100],term[100],def[100],filename[100];//필요 캐릭터형 배열 선언

	printf("파일명 입력 : ");
			scanf("%s",filename);//파일명 입력받기
			infile=fopen(filename,"r");//filename파일을 읽기 형식으로 열기
			if(infile==NULL){//filename파일이 없다면 비정상 multi빠져나옴
				printf("[%s]파일을 찾을 수 없습니다\n",filename);
				return 1;
			}
			infile2=fopen("word.txt","r");//word.txt파일을 읽기 형식으로 열기
			if(infile2==NULL){//word.txt가 없다면 비정상 multi빠져나옴
				printf("word.txt를 찾을 수 없습니다\n");
				return 1;
			}

			while(fscanf(infile,"%s",search)==1)//infile에서 단어를 하나씩 불러옴
			{
				line=0;
				found=0;//필요변수 선언
				
				if(check_hash(search,recentTable,hashTable));//불러온 단어가 hashTable에 있는지 확인
				else{//hashTable에 없다면

				while(fscanf(infile2,"%s %s",term,def)==2){//word.txt에서 단어-뜻 형식으로 불러올 수 있을때
					line++;//줄 추가

					if(mystrcmp(term,search)==0){//같은 단어가 있다면
						found++;
						printf("[검색 성공(파일)] %3d.%s : %s\n",line,term,def);//결과 출력
						add_table(recentTable,line,term,def);//recentTable에 단어정보 추가
						add_hash(line,term,def,hashTable);//hashTable에 단어정보 추가
						rewind(infile2);//파일 포인터를 파일의 시작위치로 돌림
						break;//단어를 찾았으니 반복문 탈출
					}
				}
				if(found==0){//찾지 못 하였을시
				printf("[검색 실패] %s 사전에 없는 단어\n",search);//결과출력
				rewind(infile2);//파일 포인터를 파일의 시작위치로 돌림
				}
				}				
			}

			fclose(infile);//infile파일경로 닫기
			fclose(infile2);//infile2파일경로 닫기
	
			return 0;//정상적 multi빠져나옴
}
int get_key(char *src)
{
	int i=0,key=0;

	while(src[i]!=0){//입력받은 단어를 저장한 에 NULL이 없을때까지
		key+=src[i];//ASCII코드 값을 더한다
		i++;
	}
	return key%7;//ASCII코드 합을 mod 7하여 반환한다.
}
int check_hash(char*src,WORDINFO*recentTable, WORDINFO * hashTable[][4])
{
	int key,i;
	key=get_key(src);//key를 받아온다.

	for(i=0;i<4;i++)
		if(hashTable[key][i]!=0)//해시테이블이 비어있지 않고
			if(mystrcmp(hashTable[key][i]->word,src)==0){//만일 같은 단어가 있다면
				printf("[검색 성공(해시)] %2d.%s : %s\n",hashTable[key][i]->num,hashTable[key][i]->word,hashTable[key][i]->meaning);//결과출력
				add_table(recentTable,hashTable[key][i]->num,hashTable[key][i]->word,hashTable[key][i]->meaning);//recentTable에 정보추가
				return 1;//성공했을시 1 반환
			}
	if(i==4)//끝까지 돌았는데 hashTable에 같은 단어가 없을때
		return 0;//못찾았을시 0 반환

}
void add_hash(int line, char* term, char* def, WORDINFO * hashTable[][4])
{
	int key,i;
	key=get_key(term);//key받아오기

	for(i=0;i<4;i++)
		if(hashTable[key][i]==0){//만일 hashTable칸이 비어있다면
			hashTable[key][i]=(WORDINFO*)malloc(sizeof(WORDINFO));
			hashTable[key][i]->num=line;
			hashTable[key][i]->word=(char*)malloc(mystrlen(term)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->word,term);
			hashTable[key][i]->meaning=(char*)malloc(mystrlen(def)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->meaning,def);//처음 비어있는 칸에 단어정보를 추가
			printf("[저장 완료(해시버켓 %d.%d)] %3d.%s : %s\n",key,i,line,term,def);//저장완료 출력
			break;//이미 저장했으니 반복문 탈출
		}
	if(i==4){//비어있는 칸이 없을 시
		printf("[저장 실패(해시)] overflow\n");//overflow 출력
		printf("[삭제 완료(해시)] %3d.%s : %s\n",hashTable[key][0]->num,hashTable[key][0]->word,hashTable[key][0]->meaning);//삭제 출력
		free(hashTable[key][0]->word);
		free(hashTable[key][0]->meaning);
		free(hashTable[key][0]);//첫 칸에 있는 정보 free
		
		for(i=0;i<3;i++){//모든 정보를 한 칸씩 앞으로 당긴다
			hashTable[key][i]=(WORDINFO*)malloc(sizeof(WORDINFO));
			hashTable[key][i]->word=(char*)malloc(mystrlen(hashTable[key][i+1]->word)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->word,hashTable[key][i+1]->word);
			hashTable[key][i]->meaning=(char*)malloc(mystrlen(hashTable[key][i+1]->meaning)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->meaning,hashTable[key][i+1]->meaning);
			hashTable[key][i]->num=hashTable[key][i+1]->num;
			free(hashTable[key][i+1]->word);
			free(hashTable[key][i+1]->meaning);
			free(hashTable[key][i+1]);//당긴 후, 원래 정보가 있던 칸을 free해준다.
		}

		hashTable[key][3]=(WORDINFO*)malloc(sizeof(WORDINFO));
			hashTable[key][3]->word=(char*)malloc(mystrlen(term)*sizeof(char)+1);
			mystrcpy(hashTable[key][3]->word,term);
			hashTable[key][3]->meaning=(char*)malloc(mystrlen(def)*sizeof(char)+1);
			mystrcpy(hashTable[key][3]->meaning,def);
			hashTable[key][3]->num=line;//마지막 칸에 새로운 단어의 정보를 입력
			printf("[저장 완료(해시버켓 %d.%d)] %3d.%s : %s\n",key,3,line,term,def);//저장완료 출력 
	}

}
void print_hash(WORDINFO* hashTable[][4])
{
	int i,j;

	for(i=0;i<7;i++){
		printf("버켓 %d: ",i);

		for(j=0;j<4;j++)//해시의 칸이 비어있지 않다면, 해당 칸의 포인터가 가르키고 있는 정보를 출력
			if(hashTable[i][j]!=0)
				printf("%2d.%s : %s ",hashTable[i][j]->num,hashTable[i][j]->word,hashTable[i][j]->meaning);
		printf("\n");
	}
				
}