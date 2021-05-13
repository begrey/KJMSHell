#include "../srcs/minishell.h"

static char *get_word(char *s, int len)
{
    char    *p;
    char    *word;
    char    *word_p;
    if ((word = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
        return (NULL);
    word_p = word;
    p = s;
    while (len != 0)
    {
        *word++ = *p++;
        len--;
    }
    *word = '\0';
    return (word_p);
}
static int  word_len(char *s, char c)
{
    int     len;
    int     flag;
    flag = 0;
    len = 0;
    while (*s != '\0' && (*s != c || flag != 0)) // 공백이여도 flag가 켜저있는 상태에서는 계속 반복문 지속해야함
    {
        if (*s == '\"' || *s == '\'')
        {
			if (!(*(s - 1) != '\0' &&  *(s - 1) == '\\')) //escape문자가 붙어있는 상태는 그냥 일반 문자랑 동일취급
            {
				if (flag == 0)
					flag = *s;
				else if ((int)*s == flag) // 같은 syntax 일떄
					flag = 0; // '나 "가 닫힐 때 다시 플래그 초기화 시켜주기
			}
        }
        len++;
        s++;
    }
    return (len);
}

int			set_flag(char *s, int flag)
{
	if ((*s == '\"' || *s == '\''))
    {
		if (*(s - 1) != '\0' &&  *(s - 1) == '\\') // "나 '가 문자열 처음으로 들어왔을 때는 제외
			return (flag); //" 나 ' 자체를 반환해야하니 냅둔다.
        if (flag == 0) // 새로 '나 "를 만났을 때 플래그 세워주기
            flag = *s;
        else if ((int)*s == flag) // 같은 syntax 일떄
            flag = 0; // '나 "가 닫힐 때 다시 플래그 초기화 시켜주기
    }
	return (flag);
}

static int  count_len(char *s, char c, int flag)
{
    int     len;

    len = 0;
    if (!s)
        return (0);
    while (*s == c && *s != '\0')
        s++;
    while (*s != '\0')
    {
        if (*s != c)
        {
            len++;
            while (*s != '\0' && (*s != c || flag != 0)) // "거나 '인 경우는 닫힐때까지 공백 무시
            {
				flag = set_flag(s, flag);
                s++;
            }
            if (*s == '\0' && flag != 0)
			{
				write(1, "Syntax Error :(", 15);
                return (-1); // syntax error 
			}
        }
        else
            s++;
    }
    return (len);
}
static char **free_ans(char **a)
{
    int i;
    i = 0;
    while (a[i] != NULL)
        free(a[i++]);
    free(a);
    return (NULL);
}

char		*move_ptr(char *ptr, char c)
{
	char	*p;
	int		flag;

	flag = 0;
	p = ptr;
	if (*p == '\"' || *p == '\'')
        flag = *p;
    if (flag != 0)
    {
        flag = 0;
        p = ft_strchr(p + 1, *p); // 현재 " 위치 + 1부터 넣어줘야 다음 "위치를 찾음
    }
    else
	{
        p = ft_strchr(p, c);
	}

	if (p != NULL)
		p++;
	return (p);
}

char        **ft_split_syn(char const *s, char c)
{
    char    **word;
    char    **ans;
    char    *ptr;
	int		len;

    ptr = (char *)s;
	len = count_len((char *)s, c, 0);
    //printf("%d\n", len);
    if ((word = (char**)malloc(sizeof(char *) * (len + 1))) == NULL)
        return (NULL);
    ans = word;
    while (ptr != NULL && *ptr != '\0' && len > 0)
    {
        if (*ptr != c)
        {
            if ((*word = get_word(ptr, word_len(ptr, c))) == NULL)
                return (free_ans(ans));
			len--; // "3  3"'3   3'인 경우,   "3  3"'3  3'  과 '3  3' 두개로 스플릿 되기 때문에 단어수 체크해야함
            word++;
			ptr = move_ptr(ptr, c);
        }
        else
            ptr++;
    }
    *word = NULL;
    return (ans);
}
 int main()
 {
     char *s;
	 char c;
     char **line;
     int i;
     s = "D\"   o\'n '    fff\" be \'s\' o  \'s\"e   r\"\'i ous >a >b >c <d stringzz";
	 c = ' ';
	 printf("input str @@%s@@\ninput char :@@%c@@\n", s, c);
     line = ft_split_syn(s, c);
     for (int i = 0; line[i] != NULL; i++)
         printf("line[%d] :%s\n", i, line[i]);
     return 0;
 }
