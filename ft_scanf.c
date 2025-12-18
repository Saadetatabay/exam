#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int control = fgetc(f);
    if (control == EOF)
        return (-1);
    while (control != EOF && isspace(control))
        control = fgetc(f);
    if (control == EOF)
        return (-1);
    ungetc(control,f);
        // You may; inert code here
    return (1);
}

int match_char(FILE *f, char c)
{
    int control = fgetc(f);
    if (control == EOF)
        return (-1);
    if (control == c)
        return (1);
    ungetc(control,f);
        // You may insert code here
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    char *c = va_arg(ap,char *);
    int control = fgetc(f);
    if (control == EOF)
        return (-1);
    *c =  control;
        // You may insert code here
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int found = 0;
    int sum = 0;
    int sign = 1;
    int *a = va_arg(ap,int*);
    int control = fgetc(f);
    if (control == EOF)
        return (-1);   
    if (control == '-' || control == '+')
    {
        if (control == '-')
            sign = -1;
        control = fgetc(f);
        if (control == EOF)
            return -1;
    }
    while (control != EOF && isdigit(control))
    {
        sum = sum*10 + (control - '0');
        control = fgetc(f);
    }
    if (control == EOF)
        return -1;
    if (!isdigit(control))
        ungetc(control,f);
    *a = sum * sign;
        // You may insert code here
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    char *s = va_arg(ap,char *);
    int control = fgetc(f);
    if (control == EOF)
        return (-1);

    int i = 0;
    while (control != EOF && isalpha(control))  
    {
        s[i] = control;
        control = fgetc(f);
        i++;
    }
    s[i] = 0;
    if (control == EOF)
        return (-1);
    // You may insert code here
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}
int main()
{
    char a[50];
    char c;
    int m;
    ft_scanf("%s %d %c",a,&m,&c);
    printf("%d",m);
    printf("char %c",c);
    printf("%s",a);
}