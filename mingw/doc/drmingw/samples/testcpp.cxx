/* test-c.c
 *
 * A sample C++ program to test Dr.MinGW.
 *
 * Jose Fonseca
 */

#include <stdio.h>

typedef char * cp;

void YetAnotherFunction( int i, double j, char * pszString )
{
	int k;

#if 0
	/* Other ways to cause a GPF */
	*(int *)i = 5;  
	__asm ("int $3");
	(*((void (*)(void)) 0x12345678))();
#endif

	sscanf("12345", "%i", (int *) (k=i));
}

void MyWonderfulFunction( int i, float j )
{
	YetAnotherFunction( i * 2, j, "Hello" );
}

int main()
{
	MyWonderfulFunction( 4, float(5.6) );

	return 0;
}
