#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int control;
    while(1)
    {
        control = fgetc(f);
        if (control == EOF)
            return -1;
        if(!isspace(control))
        {
            ungetc(control,f);
            break;
        }
    }
    return (0);
}

int match_char(FILE *f, char c)
{
    int control;
    control = fgetc(f);
    if (control == EOF)
        return -1;
    if (control == c)
        return 1;
    else 
        ungetc(control,f);
    return (0);
}

int scan_char(FILE *f, va_list ap)
{
    char *ptr = va_arg(ap,char*); // mesela bizim ap listemizde &c var biz charpointer aldık
    int control = fgetc(f);
    if (control == -1)
        return -1;
    *ptr = control;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int num = 0;
    int control;
    int negat = 1;
    int *ptr = va_arg(ap,int*); // mesela bizim ap listemizde  %d &x var biz integer pointer aldık

    control = fgetc(f);
    if (control == -1)
        return -1;
    if(control=='-' || control == '+')
    {
        if(control=='-')
            negat = -1;
        control = fgetc(f);
        if (control == -1)
            return -1;
    }
    if (!isdigit(control))
    {
        ungetc(control,f);
        return (-1); // harf falan gelmiş
    }
    while (isdigit(control))
    {
        num = num*10 + (control - '0');
        control = fgetc(f);
    }
    if (control != EOF)
        ungetc(control,f);
    num *=negat;
    *ptr = num;
    // You may insert code here
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int i;
    i = 0;
    char    *c = va_arg(ap,char *);
    int control = fgetc(f);
    if (control == EOF)
        return -1;
    while(!isspace(control) && control != EOF)
    {
        c[i] = control;
        i++;
        control = fgetc(f);
    }
    if (control != EOF)
        ungetc(control,f);
    c[i] = '\0';
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
			if (match_conv(f, &format, ap) != 1) //ft_scanf("%d-%d",&a,&b) dedik ap de 42-100 oldu - aynı mı diye bakar aynı ise geçer
				break;
			else
				nconv++;
		}
		else if (isspace(*format)) //ft_scanf("  %d    ",&a) dedik spaceleri geçiyor
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
    char a[100];
    ft_scanf("%s",a);
    printf("a %s",a);
}
