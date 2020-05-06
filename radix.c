#include "radix.h"
#include "print_bytes.h"

void print_numbers(int count, int nums_array[])
{
//register the Bytes printf function
  if (register_printf_byte())
    exit(EXIT_FAILURE);
  
  //print as bin,oct,dec,hex
  //actually, couldnt print bin yet.
  
  //print the table colums at top
  printf("%15s%15s%15s%15s\n","Binary","Octal","Decimal","Hex");
  for ( int i = 0; i < count; i++)
  {
	int n = nums_array[i];
  	printf("%#15B"
	       "%#15o"
		   "%15d"
	       "%#15x\n",n,n,n,n);
  }
}

// int hex is a flag.
// If it is 1 then it means print the index numbers in hex.
// Else print in decimal
void print_ascii_table(int hex)
{
  //mod handles the modulus, it makes sure newlines come at the right time
  //i keeps track of 
  int mod = 10;

  if(hex)
  {
	mod = 16;
	printf("%5s"," ");
	for(int i = 0; i < 16; i++)
	  printf("%3x",i);
  }
  else
  {
	printf("%5s"," ");
	for(int i = 0; i < 10; i++)
	  printf("%3d",i);
  }
  
  printf("\n\t");
  for ( char i = ( hex ? 32 : 30 ); i < 126; i++ )
  {
	if( (i % mod) == 0 )
	{
	  //this enters a newline and a tab to keep everything aligned.
	  //It uses an implicit if statement to handle the formatting
	  //for hex and decimal separately.
	  printf(hex ? "\n%2x   " : "\n%2d   ",i/mod);
	}
	printf("%3c",i);
  }
  //enter 2 newlines to make it more readable
  //puts prints 1 newline on top of the newline already in there
  puts("\n");
}
