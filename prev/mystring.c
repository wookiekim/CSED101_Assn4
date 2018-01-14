int mystrlen(char *str)
{
	int length=0,i;
	for(i=0;;i++)
	{
		if(str[i]!=0)//str[i]가 null문자가 아닐때까지 1씩더해주기
			length+=1;
		else
			return length;//null문자가 맞다면 그때까지의 length를 반환
	}
}

char *mystrcpy(char *toStr, char *fromStr)
{
	int i;

	for(i=0;;i++){
	if(fromStr[i]!=0)
		toStr[i]=fromStr[i];//null이 아닐시 한 글자씩 복사
	else{
		toStr[i]=fromStr[i];//null일시 null까지 복사하고 toStr반환
		return toStr;
	}
	}
}

int mystrcmp(char *str1, char *str2)
{
	int i;

	for(i=0;;i++)
	{
		if(str2[i]>str1[i])//str2의 글자가str1의 글자보다 ascii상 높으면
			return -1;
		else if(str2[i]<str1[i])//그 반대면
			return 1;
		else if(str2[i]==str1[i] && str2[i]==0)//만일str2의 글자와 str1의 글자가 같고, 둘다 널문자라면
			return 0;
	}

}

char *mytolower(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
		if(str[i]>64 && str[i]<91)//만일 글자가 아스키코드상 64와 91의 사이에 있으면 (대문자 알파벳)
			str[i]=str[i]+32;//아스키코드값에 32추가 (같은 알파벳이지만 소문자로 바꿈)

	return str;
}
