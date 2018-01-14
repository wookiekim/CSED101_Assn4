/*��¿� �����а� 20150630 */
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"//string.h ��������� ��ü�ϱ����� ��������Դϴ�.

typedef struct{
int num; // ���� ���� ��word.txt������ �ܾ��� ��ġ(�� ��° �ܾ�)
char *word; // ���� �ܾ�
char *meaning; // �ܾ��� ��(�ѱ�)
}WORDINFO;//����ü�� WORDINFO��� data type���� �������ݴϴ�.

void opt_help();//help�� �Է� �޾����� �����ϴ� �Լ��Դϴ�.
void opt_quit(WORDINFO *recentTable);//quit�� �Է¹޾����� �����ϴ� �Լ��Դϴ�.
int opt_single(WORDINFO * recentTable);//single�� �Է¹޾����� �����ϴ� �Լ��Դϴ�.
int opt_multi(WORDINFO * recentTable);//multi�� �Է¹޾����� �����ϴ� �Լ��Դϴ�.
void add_table(WORDINFO recentTable[5],int line,char * term, char * def);//�˻� ������ recentTable�� �ܾ �߰��ϴ� �Լ��Դϴ�.
void print_table(WORDINFO* recentTable);//recent�� �Է¹޾��� �� �����ϴ� �Լ��Դϴ�.
int main()
{
	WORDINFO recentTable[5]={0};//recentTable�� ����� ���� 0���� �ʱ�ȭ���ݴϴ�. 
	char opt[20];	

	opt_help();//�ʱ� �޴��� ����մϴ�.

	while(1){//��ɾ �ƴ� ��ɾ �ްų�, quit���� ��ɾ �޾��� �� �������� ���ư��� �ϱ� ���� �ݺ����Դϴ�.

		printf(">>");
		scanf("%s",opt);//��ɾ �Է¹޽��ϴ�.

		if(mystrcmp(mytolower(opt),"quit")==0){//��ɾ quit�Ͻ�
			opt_quit(recentTable);//�����Ҵ� ���� �������� free
			break;//�ݺ����� ���������ϴ�.
		}
		else if(mystrcmp(mytolower(opt),"help")==0)//��ɾ help�Ͻ�
		{
			opt_help();//�ʱ�ȭ�� ���(��ɾ� ����)
		}

		else if(mystrcmp(mytolower(opt),"single")==0)//��ɾ single�Ͻ�
		{
			opt_single(recentTable);//single ����
		}

		else if(mystrcmp(mytolower(opt),"multi")==0)//��ɾ multi�Ͻ�
		{
			opt_multi(recentTable);//multi ����
		}

		else if(mystrcmp(mytolower(opt),"recent")==0)//��ɾ recent�Ͻ�
		{
			print_table(recentTable);//recentTable���
		}
	}

	return 0;//���α׷� ����. Quit�� ���ؼ��߸� �������� ���ᰡ �����մϴ�.
}

void opt_help()//��ɾ� ���� ���
{
	printf("------------------------------\n"); 
	printf("single: �� �ܾ� �˻�\n");
	printf("multi : ���� �ܾ� �˻�\n");
	printf("recent: �ֱ� �˻� �ܾ�\n");
	printf("quit  : ���α׷� ����\n");
	printf("help  : ��ɾ� ��� ����\n");
	printf("------------------------------\n"); 
}

void add_table(WORDINFO recentTable[5],int line,char * term, char * def)
{
	int i,j,k;

	for(i=0;i<5;i++)	
		if(recentTable[i].num==line){//recentTable�� �̹� �ܾ �ִ��� Ȯ���մϴ�.
			if(i==0)//���� ���� �ܾ recentTable�� ù ĭ�� �ִٸ� �ٲ� �ʿ䰡 ���⿡, �ٷ� break���� �մϴ�.
				break;
			else{
				for(j=i;j>=1;j--){//���� �ܾ recentTable�� �ƴ� �ٸ� ĭ�� �ִٸ�, �ܾ �� ĭ�� �о��ݴϴ�. 
					mystrcpy(recentTable[j].word=(char*)realloc(recentTable[j].word,mystrlen(recentTable[j-1].word)*sizeof(char)+1),recentTable[j-1].word);
					mystrcpy(recentTable[j].meaning=(char*)realloc(recentTable[j].meaning,mystrlen(recentTable[j-1].meaning)*sizeof(char)+1),recentTable[j-1].meaning);
					recentTable[j].num=recentTable[j-1].num;
				}		
				mystrcpy(recentTable[0].word=(char*)realloc(recentTable[0].word,mystrlen(term)*sizeof(char)+1),term);
				mystrcpy(recentTable[0].meaning=(char*)realloc(recentTable[0].meaning,mystrlen(def)*sizeof(char)+1),def);
				recentTable[0].num=line;//���� ù ĭ�� ���Ӱ� ã�� �ܾ��� ������ �߰��մϴ�.
				break;
			}
		}
	if(i==5){//���� recentTable�� ���� �ܾ ���� ��
		if(recentTable[0].num==0);//���� recentTable�� �ƹ� ������ ���� �ÿ���, else�� �ǳ� �� �� �� �Ʒ��� �ִ� �۾��� �����մϴ�.
		else{//recentTable�� ������ ����Ǿ�������
			for(j=1;j<5;j++)
				if(recentTable[j].num==0)//���° ĭ���� ������ ����Ǿ��ִ��� Ȯ���մϴ�.
					break;
			if(j==5){//��� ĭ�� ������ ������4
			free(recentTable[j-1].word);//������ ĭ�� �����Ҵ� �Ǿ��ִ� �޸𸮵��� free���ݴϴ�.
			free(recentTable[j-1].meaning);
			j=4;//�̴� ������ �ִ� �ݺ����� ���Ͽ�, j�� 5�϶� 4�� �ٲپ��ݴϴ�.
			}
			for(k=j;k>=1;k--){
					mystrcpy(recentTable[k].word=(char*)malloc(mystrlen(recentTable[k-1].word)*sizeof(char)+1),recentTable[k-1].word);
					mystrcpy(recentTable[k].meaning=(char*)malloc(mystrlen(recentTable[k-1].meaning)*sizeof(char)+1),recentTable[k-1].meaning);
					recentTable[k].num=recentTable[k-1].num;
					free(recentTable[k-1].word);
					free(recentTable[k-1].meaning);
			}//�� ĭ�� �ڷ� �о� �ص�, �и��� ���� ĭ�� free���ݴϴ�.
		}
		mystrcpy(recentTable[0].word=(char*)malloc(mystrlen(term)*sizeof(char)+1),term);
		mystrcpy(recentTable[0].meaning=(char*)malloc(mystrlen(def)*sizeof(char)+1),def);
		recentTable[0].num=line;
	}//ù ĭ�� �޾ƿ� �ܾ��� ������ �����մϴ�.
}

void print_table(WORDINFO* recentTable)
{
	int i;
	printf("�ֱ� �˻� �ܾ� ���\n");

	for(i=0;i<5;i++)//recentTable���� ����Ǿ��ִ� �������� ����մϴ�.
		if(recentTable[i].num!=0)//������ ���� �κ��� ������� �ʽ��ϴ�.
		printf("%3d.%s : %s\n",recentTable[i].num,recentTable[i].word,recentTable[i].meaning);
}
void opt_quit(WORDINFO *recentTable)
{
	int i;
	for(i=0;i<5;i++)
				free(recentTable[i].word);//recentTable�� word�� �Ҵ�Ǿ��ִ� �޸𸮸� ��� free���ݴϴ�.
	for(i=0;i<5;i++)
				free(recentTable[i].meaning);//recentTable�� meaning�� �Ҵ�Ǿ��ִ� �޸𸮸� ��� free���ݴϴ�.
}
int opt_single(WORDINFO * recentTable)
{
	char search[100],term[100],def[100];//ã�� �ܾ�� �ܾ��� ��, �׸��� �Է¹��� �ܾ ������ �迭�� �������ݴϴ�.
	FILE* infile;//infile�̶�� ���ϰ�θ� �������ݴϴ�.
	int line=0,found=0;//�� ���� ã�Ҵ��� ��ã�Ҵ����� �������ִ� ������ �������ݴϴ�.
	printf("�˻��� �ܾ�: ");
			scanf("%s",search);//ã�� �ܾ �Է¹޽��ϴ�.

			infile=fopen("word.txt","r");//word.txt�� �б��������� �����ݴϴ�.
			if(infile==NULL){
				printf("word.txt�� ã�� �� �����ϴ�\n");//���� word.txt�� �����ÿ��� ������������ single�Լ��� �����ݴϴ�.
				return 1;
			}
			while(fscanf(infile,"%s %s",term,def)==2){//�� �پ� ������, �ܾ� - �� ������ �޾ƿɴϴ�.
				line++;//�� ���� ���������� line�� ���� 1�� �������ݴϴ�.
				if(mystrcmp(term,search)==0){//���� word.txt���� �Է¹��� �ܾ�� ���� �ܾ ã���� ��
					found++;//found �� 1�� ���������ݴϴ�.
					printf("[�˻� ����] %3d.%s : %s\n",line,term,def);//����� ����մϴ�.
					add_table(recentTable,line,term,def);//ã�� �ܾ recentTable�� �Ű��ݴϴ�
					fclose(infile);//���ϰ�θ� �ݾ��ݴϴ�.
					break;//�̹� ã������ �� �̻� ã�� �ʿ䰡 �����Ƿ�, �ݺ����� �����ݴϴ�.
				}
			}
			if(found==0){//���� ã�� ��������, found �� 0���� �������� �ʽ��ϴ�.
			printf("[�˻� ����] %s ������ ���� �ܾ�\n",search);//������
			}
			return 0;
}
int opt_multi(WORDINFO * recentTable)//multi�� �Է¹޾��� �� �����մϴ�.
{
	int line=0,found=0;//�� ���� ã�Ҵ��� �� ã�Ҵ����� ������ �����Ͽ��ݴϴ�.
	FILE * infile, *infile2;//���� ��θ� 2�� �������ݴϴ�.
	char search[100],term[100],def[100],filename[100];//�Է¹��� �ܾ�� �����̸�,�׸��� word.txt������ �ܾ�� ���� ������ ������ �������ݴϴ�.

	printf("���ϸ� �Է� : ");
			scanf("%s",filename);//���ϸ��� �Է¹޽��ϴ�.
			infile=fopen(filename,"r");//�Է¹��� ���ϸ��� ������ �б��������� �����ݴϴ�
			if(infile==NULL){
				printf("[%s] ������ ã�� �� �����ϴ�\n",filename);//filename�� ��ġ�ϴ� ������ ���� �ÿ��� ������������ �����Ͽ��ݴϴ�.
				return 1;
			}
			infile2=fopen("word.txt","r");//word.txt�� �б��������� �����ݴϴ�.
			if(infile2==NULL){
				printf("word.txt�� ã�� �� �����ϴ�\n");//word.txt�� ���� �ÿ��� ������������ �����Ͽ��ݴϴ�.
				return 1;
			}
			while(fscanf(infile,"%s",search)==1)//infile ���ϰ�ο��� �о�� �ܾ ���� ������ ���� �ݺ����Դϴ�.
			{
				line=0;//�� ��
				found=0;//ã�Ҵ��� �� ã�Ҵ����� ���� ����

				while(fscanf(infile2,"%s %s",term,def)==2){//word.txt���� �ܾ� - �� ������ �о�� �� ����������
					line++;//�� �� ����

					if(mystrcmp(term,search)==0){//infile���� �о�� �ܾ word.txt�� ���� �ÿ�
						found++;//found == 1�̵˴ϴ�
						printf("[�˻� ����] %3d.%s : %s\n",line,term,def);//��� ���
						add_table(recentTable,line,term,def);//recentTable�� �߰�
						rewind(infile2);//���� �����͸� �ٽ� ������ ���ۺκ����� �����ݴϴ�.
						break;//�̹� ã������, �ݺ����� �����ݴϴ�.
					}
				}
				if(found==0){//ã�� ������ ��
				printf("[�˻� ����] %s ������ ���� �ܾ�\n",search);//��� ���
				rewind(infile2);//���������� ���� �����͸� �� ���� �÷��ݴϴ�.
				}
			}
			fclose(infile);//infile��θ� �ݾ��ݴϴ�.
			fclose(infile2);//infile2��θ� �ݾ��ݴϴ�.
			return 0;
}