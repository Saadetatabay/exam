#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

/* boşlukları geç */
int match_space(FILE *f)
{
    int c;

    while (1)
    {
        c = fgetc(f);
        if (c == EOF)
            return -1;
        if (!isspace(c))
        {
            ungetc(c, f);
            return 1;
        }
    }
}

/* format karakteri ile input karakteri aynı mı */
int match_char(FILE *f, char c)
{
    int x = fgetc(f);

    if (x == EOF)
        return -1;
    if (x == c)
        return 1;
    ungetc(x, f);
    return 0;
}

/* %c */
int scan_char(FILE *f, va_list ap)
{
    char *c = va_arg(ap, char *);
    int x = fgetc(f);

    if (x == EOF)
        return -1;
    *c = x;
    return 1;
}

/* %d */
int scan_int(FILE *f, va_list ap)
{
    int *n = va_arg(ap, int *);
    int c = fgetc(f);
    int sign = 1;
    int num = 0;

    if (c == EOF)
        return -1;

    if (c == '-' || c == '+')
    {
        if (c == '-')
            sign = -1;
        c = fgetc(f);
        if (c == EOF)
            return -1;
    }

    if (!isdigit(c))
    {
        ungetc(c, f);
        return 0;
    }

    while (isdigit(c))
    {
        num = num * 10 + (c - '0');
        c = fgetc(f);
    }

    if (c != EOF)
        ungetc(c, f);

    *n = num * sign;
    return 1;
}

/* %s */
int scan_string(FILE *f, va_list ap)
{
    char *s = va_arg(ap, char *);
    int i = 0;
    int c;

    match_space(f);
    c = fgetc(f);
    if (c == EOF)
        return -1;

    while (c != EOF && !isspace(c))
    {
        s[i++] = c;
        c = fgetc(f);
    }

    if (c != EOF)
        ungetc(c, f);
    s[i] = '\0';
    return 1;
}
