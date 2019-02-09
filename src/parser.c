////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "parser.h"
#include <string.h>
#include <stdio.h>

int pareser_check(char *str)
{
    int len = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            len++;
        }
    }

    char *s = malloc(len + 1);
    for (int i = 0, j = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            s[j++] = str[i];
        }
    }

    for (int i = 0; i < strlen(s); i++)
    {
        char c = s[i];
        if (c != '(' && c != ')' && c != '-' && c != '+' && c != '*' && c != '/')
        {
            if (!(c >= '0' && c <= '9'))
            {
                return 0;
            }
        }

        if (c == '*' || c == '/')
        {
            if (i > 0 && (s[i - 1] == '*' || s[i - 1] == '/' || s[i - 1] == '(' || s[i - 1] == ')'))
                return 0;
            if (i + 1 < strlen(s) && (s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '(' || s[i + 1] == ')'))
                return 0;
        }

        if (c == '(' && i > 0)
        {
            if (s[i - 1] >= '0' && s[i - 1] <= '9')
                return 0;
        }

        if (c == ')' && i + 1 < strlen(s))
        {
            if (s[i + 1] >= '0' && s[i + 1] <= '9')
                return 0;
        }
    }

    int bracket_balance = 0;
    for (int i = 0; i < strlen(s); i++)
    {
        if (s[i] == '(')
            bracket_balance++;
        else if (s[i] == ')')
            bracket_balance--;
    }

    if (bracket_balance != 0)
        return 0;

    return 1;
}

Bigint *parse(char *str)
{
    int len = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            len++;
        }
    }

    char *s = malloc(len + 1);
    for (int i = 0, j = 0; i < strlen(str); i++)
    {
        if (str[i] != ' ')
        {
            s[j++] = str[i];
        }
    }

    return parse_expression(s);
}

Bigint *parse_expression(char *str)
{
    // printf("%s\n", str);
    if (strlen(str) == 0)
        return bigint_constructori(0);

    // +
    int bracket_balance = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(')
            bracket_balance++;
        else if (str[i] == ')')
            bracket_balance--;

        if (str[i] == '+' && bracket_balance == 0)
        {
            if (i > 0 && (str[i - 1] == '*' || str[i - 1] == '/'))
                continue;

            if (i + 1 < strlen(str) && (str[i + 1] == '*' || str[i + 1] == '/'))
                continue;

            int size_l = i;
            int size_p = strlen(str) - 1 - i;
            char *l = malloc(size_l + 1);
            char *p = malloc(size_p + 1);
            memcpy(l, str, size_l);
            memcpy(p, str + i + 1, size_p);

            Bigint *bl = parse_expression(l);
            Bigint *bp = parse_expression(p);
            free(l);
            free(p);
            return bigint_add(bl, bp);
        }
    }

    // -
    bracket_balance = 0;
    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == '(')
            bracket_balance++;
        else if (str[i] == ')')
            bracket_balance--;

        if (str[i] == '-' && bracket_balance == 0)
        {
            if (i > 0 && (str[i - 1] == '*' || str[i - 1] == '/'))
                continue;

            if (i < strlen(str) && (str[i + 1] == '*' || str[i + 1] == '/'))
                continue;

            int size_l = i;
            int size_p = strlen(str) - 1 - i;
            char *l = malloc(size_l + 1);
            char *p = malloc(size_p + 1);
            memcpy(l, str, size_l);
            memcpy(p, str + i + 1, size_p);

            Bigint *bl = parse_expression(l);
            Bigint *bp = parse_expression(p);
            free(l);
            free(p);
            return bigint_sub(bl, bp);
        }
    }

    // * and /
    bracket_balance = 0;
    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == '(')
            bracket_balance++;
        else if (str[i] == ')')
            bracket_balance--;

        if (str[i] == '*' && bracket_balance == 0)
        {
            int size_l = i;
            int size_p = strlen(str) - 1 - i;
            char *l = malloc(size_l + 1);
            char *p = malloc(size_p + 1);
            memcpy(l, str, size_l);
            memcpy(p, str + i + 1, size_p);

            Bigint *bl = parse_expression(l);
            Bigint *bp = parse_expression(p);
            free(l);
            free(p);
            return bigint_mult(bl, bp);
        }
        else if (str[i] == '/' && bracket_balance == 0)
        {
            int size_l = i;
            int size_p = strlen(str) - 1 - i;
            char *l = malloc(size_l + 1);
            char *p = malloc(size_p + 1);
            memcpy(l, str, size_l);
            memcpy(p, str + i + 1, size_p);

            Bigint *bl = parse_expression(l);
            Bigint *bp = parse_expression(p);
            free(l);
            free(p);
            return bigint_div(bl, bp);
        }
    }

    // ( )
    int pl = -1, pr = -1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '(')
        {
            pl = i;
            break;
        }
    }

    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] == ')')
        {
            pr = i;
            break;
        }
    }

    if (pl != -1 && pr != -1 && pl < pr)
    {
        char *s = malloc(pr - pl - 1 + 1);
        memcpy(s, str + pl + 1, pr - pl - 1);
        return parse_expression(s);
    }

    // number
    pl = -1, pr = -1;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            pl = i;
            break;
        }
    }

    for (int i = strlen(str) - 1; i >= 0; i--)
    {
        if (str[i] >= '0' && str[i] <= '9')
        {
            pr = i;
            break;
        }
    }

    if (pl != -1 && pr != -1 && pl <= pr)
    {
        char *s = malloc(pr - pl + 1 + 1);
        memcpy(s, str + pl, pr - pl + 1);
        return bigint_constructorstr(s);
    }

    return bigint_constructori(0);
}