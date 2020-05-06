#include "print_bytes.h"

//use this function to get the B modifier registered
int register_printf_byte(void)
{
  int ret;
  
  //ret = register_printf_specifier('B',printf_byte,printf_byte_arginfo);
  ret = register_printf_specifier('B',printf_byte,printf_arginf_sz_byte);

  if(ret)
  {
	printf("Error registering printf function.\n"
		"Maybe you have a problem with GLIBC.\n");
	exit(EXIT_FAILURE);
  }

  return 0;
}

//simple function to tell printf that arg is a general pointer type
int printf_byte_arginfo(const struct printf_info *info,
	size_t n, int *argtypes)
{
  //We always take 1 arg and it must be a pointer to the struct.
  if(n>0)
	argtypes[0] = PA_POINTER;
  return 1;
}

int printf_arginf_sz_byte(const struct printf_info *info,
	size_t n, int *argtypes, int *size)
{
  if(n>0)
  {
	argtypes[0] = PA_POINTER;
	size[0] = sizeof(void*);
  }
  return 1;
}

int printf_byte_output(FILE *stream, const struct printf_info *info,
	const void *const *args)
{
  return 0;
}

//this function handles the heavy lifting.
int printf_byte(FILE*stream, const struct printf_info *info,
	const void *const *args)
{
  char*byte; //holds byte as a string
  char*fmtstr; //hold the formatting string
  int len;

  if ( args[0] != NULL )
  {
	char *tmp = strdup(args[0]);
	byte = build_byte(tmp); //build the byte as string
  }

  //make fmtstr to hold correct formatting based on flags
  //asprintf works by making the string from the args and putting 
  //them into the first arg, fmtstr.
  if(info->width>0)
	asprintf(&fmtstr,"%%%s%ds",
		(info->left ? "-" : ""), info->width);
  else
	asprintf(&fmtstr,"%%s");

  if(info->alt)
  {
	char*b = strdup("0b");
	byte = strcat(b,byte);
  }

  //print it
  len = fprintf(stream,fmtstr,byte);

  //cleanup and return
  free(fmtstr);
  free(byte);

  if(len==-1)
	return -1;

  return len;
}

//this function takes a string, a decimal, and turns it into a byte 
//in the form of a string.
char *build_byte(char *arg)
{
  char*byte = malloc(sizeof(char)*9);
  int a = *(int*)(arg);

  for ( int i = 0; i<8; i++)
	byte[7-i] = ( (a>>i) & 1 )?'1':'0';
  //add a null at the end
  byte[8] = '\0';

  return byte;
}

//use this function to get the B modifier registered
//After executing this, the %B can be used for printing bytes
int register_printf_binary(void)
{
  int ret;
  
  ret = register_printf_specifier('b',printf_binary,printf_arginf_sz_binary);

  if(ret)
  {
	printf("Error registering binary printf function");
	exit(EXIT_FAILURE);
  }

  return 0;
}

//simple function to tell printf that arg is a general pointer type
int printf_arginf_sz_binary(const struct printf_info *info,
	size_t n, int *argtypes)
{
  //We always take 1 arg and it must be a general pointer
  if(n>0)
	argtypes[0] = PA_POINTER;
  return 1;
}

//this function handles the heavy lifting.
int printf_binary(FILE*stream, const struct printf_info *info,
	const void *const *args)
{
  char*bits; //holds byte as a string
  char*fmtstr; //hold the formatting string
  int len;

  if ( args[0] != NULL )
  {
	char *tmp = strdup(args[0]); //args[0] is a const so it cannot be 
								 // passed and changed to a function
	bits = build_bits(tmp); //build the byte as string
  }

  //make fmtstr to hold correct formatting based on flags
  //asprintf works by making the string from the args and putting 
  //them into the first arg, fmtstr.
  if(info->width>0)
	asprintf(&fmtstr,"%%%s%ds",
		(info->left ? "-" : ""), info->width);
  else
	asprintf(&fmtstr,"%%s");

  if(info->alt)
  {
	char*b = strdup("0b");
	bits = strcat(b,bits);
  }

  //print it
  len = fprintf(stream,fmtstr,bits);

  //cleanup and return
  free(fmtstr);
  free(bits);

  //If no arg was given then return -1to signal an error.
  if(len==-1)
	return -1;

  return len;
}

//this function takes a string, a decimal, and turns it into a byte 
//in the form of a string.
char *build_bits(char *arg)
{
  size_t size = (3 * (sizeof(arg) - 1));
  char*bits = malloc(size+1);
  //size of bits is number of digits in decimal times 3.
  int a = *(int*)(arg);

  for ( int i = 0; i<size; i++)
	bits[size-i-1] = ( (a>>i) & 1 )?'1':'0';
  //add a null at the end
  bits[size-1] = '\0';

  return bits;
}
