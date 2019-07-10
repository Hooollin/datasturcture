#include <stdio.h>

#define bool int
#define true 1
#define false 0
#define Status int
#define OK 1
#define ERR 0
#define MAXSTRLEN 255

typedef unsigned char String[MAXSTRLEN + 1]; // 0号下标存放串长

int min(int a, int b)
{
    return a < b ? a : b;
}

Status strAssign(String *t, char *s)
{
    char *tmp = s;
    int len = 0;
    while (*tmp != '\0')
    {
        len += 1;
        *(*t + len) = *tmp;
        tmp += 1;
    }
    **t = (unsigned char)len;
    return OK;
}

// 由s串复制得到t串
Status strCopy(String *t, String s)
{
    int len = s[0]; //实际长度为len + 1
    for (int i = 0; i <= len; i++)
    {
        *(*t + i) = s[i];
    }
    return OK;
}

//判断字符串是否为空
bool strEmpty(String s)
{
    return s[0] == 0;
}
// 比较s和t的大小，如果s > t，返回值>0,如果等于t，返回值=0，否则返回值<0
int strCompare(String s, String t)
{
    int sLen = s[0], tLen = t[0], idx = 1, res = 0;

    while (idx <= min(sLen, tLen) && res == 0)
    {
        res = s[idx] - t[idx];
        idx += 1;
    }

    if (res == 0 && sLen != tLen)
    {
        if (sLen > tLen)
        {
            res = s[idx];
        }
        else
        {
            res = -t[idx];
        }
    }
    return res;
}

//返回串长
int strLength(String s)
{
    return s[0];
}

//将s清为空船
Status clearString(String *s)
{
    **s = 0;
    return OK;
}

// 连接串s1, s2到串t
Status concat(String *t, String s1, String s2)
{
    **t = s1[0] + s2[0];
    int idx = 1;
    while (idx <= s1[0])
    {
        *(*t + idx) = s1[idx];
        idx += 1;
    }
    while (idx <= s1[0] + s2[0])
    {
        *(*t + idx) = s2[idx - s1[0] + 1];
        idx += 1;
    }
    return OK;
}

//返回字串
Status substring(String *sub, String s, int pos, int len)
{
    int sLen = s[0];
    if (pos + len > sLen)
    {
        printf("index out of range. \n");
        return ERR;
    }
    **sub = (unsigned char)len;
    for (int i = 1; i <= len; i++)
    {
        *(*sub + i) = s[pos + i];
    }
    return OK;
}

// t在主串s第pos后相同的子串
int index(String s, String t, int pos)
{
    int sLen = s[0];
    int tLen = t[0];
    int res = -1;
    for (int i = pos + 1; i <= sLen; i++)
    {
        if (sLen - i + 1 < tLen)
        {
            break;
        }
        int j = 0;
        while (j < tLen && s[j + i] == t[j + 1])
        {
            j++;
        }
        if (j == tLen)
        {
            res = i - 1;
            break;
        }
    }
    return res;
}
//打印字符串
void printStr(String s)
{
    int len = s[0];
    for (int i = 1; i <= len; i++)
    {
        printf("%c", s[i]);
    }
    printf("\n");
}

//用v替换所有在s中出现过的字串t
//代码太难看了。。。
Status replace(String *s, String t, String v)
{
    int sLen = **s;
    int tLen = t[0];
    int vLen = v[0];
    int i = 1;
    while (i < sLen)
    {
        int tIndex = index(*s, t, i - 1);
        if (tIndex == -1)
        {
            **s = sLen;
            return OK;
        }
        i = tIndex + 1;
        if (tLen < vLen)
        {
            int move = vLen - tLen;
            sLen += move;
            if (sLen + 1 + move > MAXSTRLEN)
            {
                printf("overflow");
                return ERR;
            }
            while (move-- > 0)
            {
                for (int k = sLen + 1; k >= i + tLen; k--)
                {
                    *(*s + k) = *(*s + k - 1);
                }
            }
        }
        else if (tLen > vLen)
        {
            int move = tLen - vLen;
            sLen -= move;
            for (int k = i + vLen; k < 1 + sLen - vLen; k++)
            {
                *(*s + k) = *(*s + k + move);
            }
        }
        int j = 0;
        while (j < vLen)
        {
            *(*s + i + j) = v[j + 1];
            j += 1;
        }
        i += j;
    }
    **s = sLen;
    return OK;
}

void main()
{
    String s, t, q;
    char testStr[20] = "hellllo";
    strAssign(&s, testStr);
    strAssign(&t, "ll");
    strAssign(&q, "kkk");
    replace(&s, t, q);
    printStr(s);
}
