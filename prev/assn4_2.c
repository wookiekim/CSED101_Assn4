/* ��¿� �����а� 20150630*/
#include <stdio.h>
#include <stdlib.h>//malloc�� realloc�� ����ϱ� ���� ����Դϴ�.
#include "mystring.h"//string.h�� ��ü�ϴ� ����� ���� ��������Դϴ�.

typedef struct{
int num; // ���� ���� ��word.txt������ �ܾ��� ��ġ(�� ��° �ܾ�)
char *word; // ���� �ܾ�
char *meaning; // �ܾ��� ��(�ѱ�)
}WORDINFO;

void opt_help();//help�� �Է¹޾��� �ÿ� �����ϴ� �Լ��Դϴ�.
void opt_quit(WORDINFO *recentTable,WORDINFO* hashTable[][4]);//quit�� �Է¹޾��� �ÿ� �����ϴ� �Լ��Դϴ�.
int opt_single(WORDINFO * recentTable,WORDINFO * hashTable[][4]);//single�� �Է¹޾��� �ÿ� �����ϴ� �Լ��Դϴ�.
int opt_multi(WORDINFO * recentTable,WORDINFO * hashTable[][4]);//multi�� �Է¹޾��� �ÿ� �����ϴ� �Լ��Դϴ�.
void add_table(WORDINFO recentTable[5],int line,char * term, char * def);//recentTable�� �ܾ������� �߰��ϴ� �Լ��Դϴ�.
void print_table(WORDINFO* recentTable);//recentTable�� ����ϴ� �Լ��Դϴ�.
void add_hash(int line, char* term, char* def, WORDINFO * hashTable[][4]);//hashTable�� �ܾ������� �߰��ϴ� �Լ��Դϴ�.
void print_hash(WORDINFO* hashTable[][4]);//hashTable�� ����Ǿ��ִ� �������� ����ϴ� �Լ��Դϴ�.
int check_hash(char*word,WORDINFO*recentTable, WORDINFO * hashTable[][4]);//hashTable�� ã����� �ܾ �ִ��� Ȯ���ϴ� �Լ��Դϴ�.
int get_key(char* word);//�Է¹��� �ܾ��� ���ĺ����� ASCII�ڵ� ���� ���Ͽ� ��ȯ���ִ� �Լ��Դϴ�.
int main()
{
	WORDINFO recentTable[5]={0}; //recentTable�� �������ݴϴ�.
	WORDINFO * hashTable[7][4]={0};//hashTable�� �������ݴϴ�.

	char opt[20];//��ɾ �Է¹��� �迭�� �����Ͽ��ݴϴ�.

	opt_help();//�ʱ�ȭ���� ����մϴ�.(��ɾ� ����)

	while(1){//quit�� �Է¹ޱ� ������ ���α׷��� ������� �ʵ��� ���ѹݺ����� ����մϴ�.

		printf(">>");
		scanf("%s",opt);

		if(mystrcmp(mytolower(opt),"quit")==0){//quit�� �Է¹޾�����
			opt_quit(recentTable,hashTable);//�Ҵ�� �޸𸮵��� free���ݴϴ�.
			break;//�ݺ����� ���������ϴ�.
		}
		else if(mystrcmp(mytolower(opt),"help")==0)//help�� �Է¹޾��� ��
		{
			opt_help();//��ɾ� ������ ����Ͽ��ݴϴ�.
		}

		else if(mystrcmp(mytolower(opt),"single")==0)//single�� �Է¹޾��� ��
		{
			opt_single(recentTable,hashTable);//word.txt���� �Է¹��� �ܾ ã���ݴϴ�.
		}

		else if(mystrcmp(mytolower(opt),"multi")==0)//multi�� �Է¹޾��� ��
		{
			opt_multi(recentTable,hashTable);//word.txt���� ���ϴ� ���Ͽ� �ִ� �ܾ���� ���� ã���ݴϴ�.
		}

		else if(mystrcmp(mytolower(opt),"recent")==0)//recent�� �Է¹޾��� ��
		{
			print_table(recentTable);//recentTable�� ����Ͽ��ݴϴ�.
		}

		else if(mystrcmp(mytolower(opt),"print")==0)//print�� �Է¹޾��� ��
		{
			print_hash(hashTable);//hashTable�� ����Ͽ��ݴϴ�.
		}
	}
	return 0;//���α׷��� �����մϴ�.
}

void opt_help()//��ɾ���� ������ ����Ͽ��ݴϴ�.
{
	printf("------------------------------\n"); 
	printf("single: �� �ܾ� �˻�\n");
	printf("multi : ���� �ܾ� �˻�\n");
	printf("recent: �ֱ� �˻� �ܾ�\n");
	printf("print : �ؽ� ���̺� ���\n");
	printf("quit  : ���α׷� ����\n");
	printf("help  : ��ɾ� ��� ����\n");
	printf("------------------------------\n"); 
}

void add_table(WORDINFO recentTable[5],int line,char * term, char * def)//recentTable�� �ܾ������� �Է��Ͽ��ݴϴ�.
{
	int i,j,k;

	for(i=0;i<5;i++)//recentTable�� �Է¹��� �ܾ�� ���� �ܾ �ִ��� Ȯ���մϴ�.
		if(recentTable[i].num==line){//���� �ִٸ�
			if(i==0)//���� ù �ڸ��� ���� �ܾ �ִٸ� ���� ���������ݴϴ�. recentTable�� ��ȭ�� �� �ʿ䰡 �����ϴ�.
				break;
			else{//���� ���� �ڸ��� ���� �ʴٸ�
				for(j=i;j>=1;j--){//��� �ܾ������� ��ĭ�� �ڷ� �о� �� ��
					mystrcpy(recentTable[j].word=(char*)realloc(recentTable[j].word,mystrlen(recentTable[j-1].word)*sizeof(char*)+1),recentTable[j-1].word);
					mystrcpy(recentTable[j].meaning=(char*)realloc(recentTable[j].meaning,mystrlen(recentTable[j-1].meaning)*sizeof(char*)+1),recentTable[j-1].meaning);
					recentTable[j].num=recentTable[j-1].num;
				}		
				mystrcpy(recentTable[0].word=(char*)realloc(recentTable[0].word,mystrlen(term)*sizeof(char*)+1),term);
				mystrcpy(recentTable[0].meaning=(char*)realloc(recentTable[0].meaning,mystrlen(def)*sizeof(char*)+1),def);
				recentTable[0].num=line;//ù��° ĭ�� �ܾ������� �����մϴ�.
				break;
			}
		}
	if(i==5){//���� ���� �ܾ ���� ��
		if(recentTable[0].num==0);//recentTable�� �ƹ� ������ ����Ǿ����� �ʴٸ� else�� �ǳʶݴϴ�.
		else{//recentTable�� ������ ���� ��
			for(j=1;j<5;j++)
				if(recentTable[j].num==0)
					break;//recentTable�� ������ �ܾ������� �����ϰ� �ִ��� �˾Ƴ��ϴ�
			if(j==5){//��� ĭ�� ������ ���� ��
			free(recentTable[j-1].word);//������ ĭ�� �Ҵ�Ǿ��ִ� ������ free���ݴϴ�.
			free(recentTable[j-1].meaning);
			j=4;
			}
			for(k=j;k>=1;k--){//��� ������ �� ĭ�� �ڷ� �о��ݴϴ�.
					mystrcpy(recentTable[k].word=(char*)malloc(mystrlen(recentTable[k-1].word)*sizeof(char*)+1),recentTable[k-1].word);
					mystrcpy(recentTable[k].meaning=(char*)malloc(mystrlen(recentTable[k-1].meaning)*sizeof(char*)+1),recentTable[k-1].meaning);
					recentTable[k].num=recentTable[k-1].num;
					free(recentTable[k-1].word);
					free(recentTable[k-1].meaning);//������ �� ��, ����Ǿ��ִ� ���� �Ҵ�� �޸𸮸� free���ݴϴ�.
			}
		}
		mystrcpy(recentTable[0].word=(char*)malloc(mystrlen(term)*sizeof(char*)+1),term);
		mystrcpy(recentTable[0].meaning=(char*)malloc(mystrlen(def)*sizeof(char*)+1),def);
		recentTable[0].num=line;
	}//ù ĭ�� �ܾ������� �߰��մϴ�.
}
void print_table(WORDINFO* recentTable)
{
	int i;
	printf("�ֱ� �˻� �ܾ� ���\n");

	for(i=0;i<5;i++)//recentTable�� ����Ǿ��ִ� ������ �����մϴ�
		if(recentTable[i].num!=0)
		printf("%3d.%s : %s\n",recentTable[i].num,recentTable[i].word,recentTable[i].meaning);
}
void opt_quit(WORDINFO *recentTable,WORDINFO* hashTable[][4])
{
	int i,j;
	for(i=0;i<5;i++){//recentTable�� �����Ҵ� �Ǿ��ִ� �޸𸮸� ���free���ݴϴ�.
				free(recentTable[i].word);
				free(recentTable[i].meaning);
	}
	for(j=0;j<7;j++)
		for(i=0;i<4;i++){//hashTable�� �����Ҵ� �Ǿ��ִ� �޸𸮸� ��� free���ݴϴ�.
			if(hashTable[j][i]!=0){//hashTable�� �����͵��� ����Ű�� word�� meaning�켱 free���ݴϴ�.
			free(hashTable[j][i]->word);
			free(hashTable[j][i]->meaning);
			}
			free(hashTable[j][i]);//�� �Ŀ� hashTable�� free���ݴϴ�.
		}
}
int opt_single(WORDINFO * recentTable,WORDINFO * hashTable[][4])
{
	char search[100],term[100],def[100];//�ʿ��� ĳ���͹迭 ����
	FILE* infile;//���ϰ�� ����
	int line=0,found=0,key=0;
	printf("�˻��� �ܾ�: ");
			scanf("%s",search);//�ܾ� �Է¹ޱ�

			if(check_hash(search,recentTable,hashTable));//�Է¹��� �ܾ hashTable�� �ִ��� Ȯ��
			else{//hashTable�� ���� ��
				infile=fopen("word.txt","r");//word.txt.������ �б��������� ����
				if(infile==NULL){//word.txt�� ���� �� ������������ single�Լ� ��������
					printf("word.txt�� ã�� �� �����ϴ�\n");
					return 1;
				}
				while(fscanf(infile,"%s %s",term,def)==2){//word.txt���� �ܾ� - �� �������� �޾ƿü� ������
					line++;
					if(mystrcmp(term,search)==0){//���� �ܾ ã�´ٸ�
						found++;
						printf("[�˻� ����(����)] %3d.%s : %s\n",line,term,def);//��� ���
						add_table(recentTable,line,term,def);//recentTable�� �ܾ� ���� �߰�
						add_hash(line,term,def,hashTable);//hashTable�� �ܾ� ���� �߰�
						fclose(infile);//���� ��� �ݱ�
						break;//�̹� ã������ �ݺ��� Ż��
					}
				}
				if(found==0){//�� ã������
				printf("[�˻� ����] %s ������ ���� �ܾ�\n",search);//������
				}
			}
			return 0;//������ single����������
}
int opt_multi(WORDINFO * recentTable,WORDINFO* hashTable[][4])
{
	int line=0,found=0,key=0;//�ʿ� ���� ����
	FILE * infile, *infile2;//���� ��� ����
	char search[100],term[100],def[100],filename[100];//�ʿ� ĳ������ �迭 ����

	printf("���ϸ� �Է� : ");
			scanf("%s",filename);//���ϸ� �Է¹ޱ�
			infile=fopen(filename,"r");//filename������ �б� �������� ����
			if(infile==NULL){//filename������ ���ٸ� ������ multi��������
				printf("[%s]������ ã�� �� �����ϴ�\n",filename);
				return 1;
			}
			infile2=fopen("word.txt","r");//word.txt������ �б� �������� ����
			if(infile2==NULL){//word.txt�� ���ٸ� ������ multi��������
				printf("word.txt�� ã�� �� �����ϴ�\n");
				return 1;
			}

			while(fscanf(infile,"%s",search)==1)//infile���� �ܾ �ϳ��� �ҷ���
			{
				line=0;
				found=0;//�ʿ亯�� ����
				
				if(check_hash(search,recentTable,hashTable));//�ҷ��� �ܾ hashTable�� �ִ��� Ȯ��
				else{//hashTable�� ���ٸ�

				while(fscanf(infile2,"%s %s",term,def)==2){//word.txt���� �ܾ�-�� �������� �ҷ��� �� ������
					line++;//�� �߰�

					if(mystrcmp(term,search)==0){//���� �ܾ �ִٸ�
						found++;
						printf("[�˻� ����(����)] %3d.%s : %s\n",line,term,def);//��� ���
						add_table(recentTable,line,term,def);//recentTable�� �ܾ����� �߰�
						add_hash(line,term,def,hashTable);//hashTable�� �ܾ����� �߰�
						rewind(infile2);//���� �����͸� ������ ������ġ�� ����
						break;//�ܾ ã������ �ݺ��� Ż��
					}
				}
				if(found==0){//ã�� �� �Ͽ�����
				printf("[�˻� ����] %s ������ ���� �ܾ�\n",search);//������
				rewind(infile2);//���� �����͸� ������ ������ġ�� ����
				}
				}				
			}

			fclose(infile);//infile���ϰ�� �ݱ�
			fclose(infile2);//infile2���ϰ�� �ݱ�
	
			return 0;//������ multi��������
}
int get_key(char *src)
{
	int i=0,key=0;

	while(src[i]!=0){//�Է¹��� �ܾ ������ �� NULL�� ����������
		key+=src[i];//ASCII�ڵ� ���� ���Ѵ�
		i++;
	}
	return key%7;//ASCII�ڵ� ���� mod 7�Ͽ� ��ȯ�Ѵ�.
}
int check_hash(char*src,WORDINFO*recentTable, WORDINFO * hashTable[][4])
{
	int key,i;
	key=get_key(src);//key�� �޾ƿ´�.

	for(i=0;i<4;i++)
		if(hashTable[key][i]!=0)//�ؽ����̺��� ������� �ʰ�
			if(mystrcmp(hashTable[key][i]->word,src)==0){//���� ���� �ܾ �ִٸ�
				printf("[�˻� ����(�ؽ�)] %2d.%s : %s\n",hashTable[key][i]->num,hashTable[key][i]->word,hashTable[key][i]->meaning);//������
				add_table(recentTable,hashTable[key][i]->num,hashTable[key][i]->word,hashTable[key][i]->meaning);//recentTable�� �����߰�
				return 1;//���������� 1 ��ȯ
			}
	if(i==4)//������ ���Ҵµ� hashTable�� ���� �ܾ ������
		return 0;//��ã������ 0 ��ȯ

}
void add_hash(int line, char* term, char* def, WORDINFO * hashTable[][4])
{
	int key,i;
	key=get_key(term);//key�޾ƿ���

	for(i=0;i<4;i++)
		if(hashTable[key][i]==0){//���� hashTableĭ�� ����ִٸ�
			hashTable[key][i]=(WORDINFO*)malloc(sizeof(WORDINFO));
			hashTable[key][i]->num=line;
			hashTable[key][i]->word=(char*)malloc(mystrlen(term)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->word,term);
			hashTable[key][i]->meaning=(char*)malloc(mystrlen(def)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->meaning,def);//ó�� ����ִ� ĭ�� �ܾ������� �߰�
			printf("[���� �Ϸ�(�ؽù��� %d.%d)] %3d.%s : %s\n",key,i,line,term,def);//����Ϸ� ���
			break;//�̹� ���������� �ݺ��� Ż��
		}
	if(i==4){//����ִ� ĭ�� ���� ��
		printf("[���� ����(�ؽ�)] overflow\n");//overflow ���
		printf("[���� �Ϸ�(�ؽ�)] %3d.%s : %s\n",hashTable[key][0]->num,hashTable[key][0]->word,hashTable[key][0]->meaning);//���� ���
		free(hashTable[key][0]->word);
		free(hashTable[key][0]->meaning);
		free(hashTable[key][0]);//ù ĭ�� �ִ� ���� free
		
		for(i=0;i<3;i++){//��� ������ �� ĭ�� ������ ����
			hashTable[key][i]=(WORDINFO*)malloc(sizeof(WORDINFO));
			hashTable[key][i]->word=(char*)malloc(mystrlen(hashTable[key][i+1]->word)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->word,hashTable[key][i+1]->word);
			hashTable[key][i]->meaning=(char*)malloc(mystrlen(hashTable[key][i+1]->meaning)*sizeof(char)+1);
			mystrcpy(hashTable[key][i]->meaning,hashTable[key][i+1]->meaning);
			hashTable[key][i]->num=hashTable[key][i+1]->num;
			free(hashTable[key][i+1]->word);
			free(hashTable[key][i+1]->meaning);
			free(hashTable[key][i+1]);//��� ��, ���� ������ �ִ� ĭ�� free���ش�.
		}

		hashTable[key][3]=(WORDINFO*)malloc(sizeof(WORDINFO));
			hashTable[key][3]->word=(char*)malloc(mystrlen(term)*sizeof(char)+1);
			mystrcpy(hashTable[key][3]->word,term);
			hashTable[key][3]->meaning=(char*)malloc(mystrlen(def)*sizeof(char)+1);
			mystrcpy(hashTable[key][3]->meaning,def);
			hashTable[key][3]->num=line;//������ ĭ�� ���ο� �ܾ��� ������ �Է�
			printf("[���� �Ϸ�(�ؽù��� %d.%d)] %3d.%s : %s\n",key,3,line,term,def);//����Ϸ� ��� 
	}

}
void print_hash(WORDINFO* hashTable[][4])
{
	int i,j;

	for(i=0;i<7;i++){
		printf("���� %d: ",i);

		for(j=0;j<4;j++)//�ؽ��� ĭ�� ������� �ʴٸ�, �ش� ĭ�� �����Ͱ� ����Ű�� �ִ� ������ ���
			if(hashTable[i][j]!=0)
				printf("%2d.%s : %s ",hashTable[i][j]->num,hashTable[i][j]->word,hashTable[i][j]->meaning);
		printf("\n");
	}
				
}