int mystrlen(char *str)
{
	int length=0,i;
	for(i=0;;i++)
	{
		if(str[i]!=0)//str[i]�� null���ڰ� �ƴҶ����� 1�������ֱ�
			length+=1;
		else
			return length;//null���ڰ� �´ٸ� �׶������� length�� ��ȯ
	}
}

char *mystrcpy(char *toStr, char *fromStr)
{
	int i;

	for(i=0;;i++){
	if(fromStr[i]!=0)
		toStr[i]=fromStr[i];//null�� �ƴҽ� �� ���ھ� ����
	else{
		toStr[i]=fromStr[i];//null�Ͻ� null���� �����ϰ� toStr��ȯ
		return toStr;
	}
	}
}

int mystrcmp(char *str1, char *str2)
{
	int i;

	for(i=0;;i++)
	{
		if(str2[i]>str1[i])//str2�� ���ڰ�str1�� ���ں��� ascii�� ������
			return -1;
		else if(str2[i]<str1[i])//�� �ݴ��
			return 1;
		else if(str2[i]==str1[i] && str2[i]==0)//����str2�� ���ڿ� str1�� ���ڰ� ����, �Ѵ� �ι��ڶ��
			return 0;
	}

}

char *mytolower(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
		if(str[i]>64 && str[i]<91)//���� ���ڰ� �ƽ�Ű�ڵ�� 64�� 91�� ���̿� ������ (�빮�� ���ĺ�)
			str[i]=str[i]+32;//�ƽ�Ű�ڵ尪�� 32�߰� (���� ���ĺ������� �ҹ��ڷ� �ٲ�)

	return str;
}
