/****************************************************************************
 *                                                JeeLab J-Guider ver Zero
 *--------------------------------------------------------------------------------------------------------*
 *
 *  - lisence -
 * 'JeeLab J-Guider' represents the best 'FREE Guider' for tiny microcomputer currently available on the market.
 * This code is 'FREE OF CHARGE' for non-commercial & individual developer only. Both of these conditions should be met!
 * If you are not a individual developer or if you want to use your computer for business purposes,
 * we offer a wide range of more suitable verison providing higher speed and more efficient processing.
 * If you use more infomation, contact us using e-mail or visit our site.
 *
 * e-mail: 
 *              info@jeelab.com
 *  
 * web site:    
 *               http://www.jeelab.com
 *               http://jeelab.tistory.com
 *
 ****************************************************************************/

#include "init.h"
#include "types.h"
#include "uart.h"

#if (KERNEL_DEBUG == ENABLED)
#include <ctype.h>
#include <string.h>
#include <stdarg.h>


static int do_padding;
static int left_flag;
static int len;
static int num1;
static int num2;
static char pad_character;


void out_char (int ch );

static void padding( const int l_flag)
{
	int i;

	if (do_padding && l_flag && (len < num1))
		for (i=len; i<num1; i++)
			out_char( pad_character);
}


static void outs( char * lp)
{
	/* pad on left if needed                          */
	len = strlen((const char *)lp);
	padding( !left_flag);

	/* Move string to the buffer                      */
	while (*lp && num2--)
		out_char( *lp++);

	/* Pad on right if needed                         */
	len = strlen((const char *)lp);
	padding( left_flag);
}


static void outnum( long num, const  long base)
{
	char * cp;
	int negative;
	char outbuf[32];
	const char digits[] = "0123456789ABCDEF";

	/* Check if number is negative                    */
	if ((num < 0L)&&(base!=16L)) {
		negative = 1;
		num = -num;
	}
	else
		negative = 0;

	/* Build number (backwards) in outbuf             */
	cp = outbuf;
	do {
		if (negative)
			*cp++ = digits[(int)(num % base)];
		else
			*cp++ = digits[(int)(num % base)];
	} while ((num /= base) > 0);
	
	if (negative)
		*cp++ = '-';
	*cp-- = 0;

	/* Move the converted number to the buffer and    */
	/* add in the padding where needed.               */
	len = strlen((const char *)outbuf);
	padding( !left_flag);
	while (cp >= outbuf)
		out_char( *cp--);
	padding( left_flag);
}


static U16 getnum( char ** linep)
{
	int n;
	char * cp;

	n = 0;
	cp = *linep;
	while (isdigit(*cp))
		n = n*10 + ((*cp++) - '0');
	*linep = cp;
	return(n);
}


void xprintf( char * ctrl, ...)
{
   int long_flag;
   int dot_flag;

   char  ch;
   va_list argp;
   va_start( argp, ctrl);

   for ( ; *ctrl; ctrl++) {
			RstWatchdog();
      if (*ctrl != '%') {
         out_char(*ctrl);
         continue;
         }

      /* initialize all the flags for this format.   */
      dot_flag   =
      long_flag  =
      left_flag  =
      do_padding = 0;
      pad_character = ' ';
      num2=32767; //0x7ffff

try_next:
      ch = *(++ctrl);

      if (isdigit(ch)) {
         if (dot_flag)
            num2 = getnum(&ctrl);
         else {
            if (ch == '0')
               pad_character = '0';

            num1 = getnum(&ctrl);
            do_padding = 1;
         }
         ctrl--;
         goto try_next;
      }

      switch (tolower(ch)) {
         case '%':
              out_char( '%');
              continue;

         case '-':
              left_flag = 1;
              break;

         case '.':
              dot_flag = 1;
              break;

         case 'l':
              long_flag = 1;
              break;

         case 'd':
              if (long_flag || ch == 'D') {
                 outnum( va_arg(argp, long), 10L);
                 continue;
                 }
              else {
                 outnum( va_arg(argp, int), 10L);
                 continue;
                 }
         case 'x':
              outnum( (U32)va_arg(argp, int), 16L);
              continue;

         case 's':
              outs( va_arg( argp, char *));
              continue;

         case 'c':
              out_char( va_arg( argp, int));
              continue;

         case '\\':
              switch (*ctrl) {
                 case 'a':
                      out_char( 0x07);
                      break;
                 case 'h':
                      out_char( 0x08);
                      break;
                 case 'r':
                      out_char( 0x0D);
                      break;
                 case 'n':
                      out_char( 0x0D);
                      out_char( 0x0A);
                      break;
                 default:
                      out_char( *ctrl);
                      break;
                 }
              ctrl++;
              break;

         default:
              continue;
         }
      goto try_next;
      }

   va_end( argp);
   
}


void out_char (int ch ) 
{

	Uart0SendByte((U8)ch);
	if(ch == '\n') 
		Uart0SendByte('\r');

}

#endif
