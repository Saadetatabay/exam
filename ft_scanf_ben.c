#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c = fgetc(f);
    if (c == EOF)
        return (-1);
    while(isspace(c))
        c = fgetc(f);
    if (c != EOF)
        ungetc(c,f);
        // You may insert code here
    return (1);
}

int match_char(FILE *f, char c)
{
    int co = fgetc(f);
    if (co == EOF)
        return (-1);
    if (co == c)
        return (1);
    ungetc(co,f);
    return (0);
        // You may insert code here
}

int scan_char(FILE *f, va_list ap)
{
    char *c = va_arg(ap,char *);
    int control = fgetc(f);
    if (control == EOF)
        return (-1);
    *c = control;
        // You may insert code here
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int digit_found = 0;
    int num = 0;
    int *d = va_arg(ap,int *);
    int negat = 1;
    int control = fgetc(f);
    if (control == EOF)
        return(-1);
    if (control == '-' || control == '+')
    {
        if (control == '-')
            negat = -1;
        control = fgetc(f);
        if (control == EOF)
            return (-1);
    }
    while( control !=EOF && isdigit(control))
    {
        digit_found  = 1;
        num = num*10 + (control - '0');
        control = fgetc(f);
    }
    if (control != EOF)
        ungetc(control,f);
    if(!digit_found)
        return (0);
    *d = num*negat;
        // You may insert code here
    return (1);
}

int scan_string(FILE *f, va_list ap)
{
    int i = 0;
    char *s = va_arg(ap,char *);
    int control = fgetc(f);
    if ( control == EOF)
        return (-1);
    while(control != EOF && !isspace(control))
    {
        s[i] = control;
        control =fgetc(f);
        i++;
    }
    s[i] = '\0';
    if (control != EOF)
        ungetc(control,f);
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
int main(void)
{
    int     num;
    char    str[100]; // String için yeterli yer ayırıyoruz
    char    c;
    int     ret;

    // Kullanıcıya ne girmesi gerektiğini söyleyelim
    printf("Test icin sunu yazip Enter'a basin:\n");
    printf("   -42   merhaba   :   Z\n\n");
    printf("Girdinizi bekliyorum: ");

    // TEST:
    // 1. Baştaki boşlukları atlamalı (%d öncesi)
    // 2. Negatif sayıyı okumalı
    // 3. Stringi okumalı
    // 4. ':' karakterini ve etrafındaki boşlukları geçmeli
    // 5. Son karakteri okumalı
    ret = ft_scanf(" %d %s : %c", &num, str, &c);

    printf("\n\n======== SONUCLAR ========\n");
    printf("Return Degeri (nconv) : %d  (Beklenen: 3)\n", ret);
    printf("Okunan Tamsayi (d)    : %d\n", num);
    printf("Okunan String (s)     : |%s|\n", str);
    printf("Okunan Karakter (c)   : |%c|\n", c);

    return (0);
}