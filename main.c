#include "print_bytes.h"
#include "radix.h"

void help(char**argv);

int main(int argc, char**argv)
{
  //if no options then print help msg
  if ( argc == 1 )
	help(argv);
  
  //these 2 guys keep track of the numbers that should be converted
  //and printed.
  //the array to store the numbers will always be at least big enough to handle 
  //numbers even if every single option is a number. Basically every time you 
  //give the program a number you have to also give it the radix as well.
  //That means if we also include the 1st argument (the program name itself
  // there will be 2*N+1 arguments, where N is the number of numbers to print.
  int numbers_array[ argc ];
  int numbers_count = 0;

  int c, digit_optind = 0;

  while (1)
  {
	int this_option_optind = optind ? optind : 1,
		option_index = 0;

	static struct option long_options[] = {
	  {"hex", 1, NULL, 'x'},
	  {"bin", 1, NULL, 'b'},
	  {"oct", 1, NULL, 'o'},
	  {"dec", 1, NULL, 'd'},
	  {"ascii", 0, NULL, 'a'},
	  {"ascii-hex", 0, NULL, 'A'},
	  {"help", 0, NULL, 'h'},
	  {0,0,0,0},
	};

	c = getopt_long(argc,argv,":aAx:b:o:d:h",long_options,&option_index);

	if ( c == -1 )
	  break;

	//make an array to hold all numbers, max amount of numbers is half of (argc-1)
	//since 1 arg is the program name
	//and each number is accompanied by a type i.e. -b -d -o 

	switch(c)
	{
	  case 'b':
		numbers_array[numbers_count++] = strtol(optarg,NULL,2);
		break;
	  case 'o':
		numbers_array[numbers_count++] = strtol(optarg,NULL,8);
		break;
	  case 'd':
		numbers_array[numbers_count++] = strtol(optarg,NULL,10);
		break;
	  case 'x':
		numbers_array[numbers_count++] = strtol(optarg,NULL,16);
		break;
	  case 'A':
		print_ascii_table(1);
		break;
	  case 'a':
		print_ascii_table(0);
		break;
	  case '?':
		fprintf(stderr,"You made some error with this option: %s\n",argv[optind-1]);
		exit(EXIT_FAILURE);
	  default:
		help(argv);
		break;
	}
  }

  if ( optind < argc )
	while ( optind < argc )
	{
	  numbers_array[numbers_count] = strtol(argv[optind],NULL,10);
	  numbers_count++;
	  optind++;
	}

  if ( numbers_count > 0 )
	print_numbers(numbers_count, numbers_array);

  exit(EXIT_SUCCESS);
}

void help(char**argv)
{
  printf("Usage: %s [-h help] [-b bin] [-o oct] [-d dec] [-x hex] [dec]\n"
	  "Print numbers in the 4 major radices.\n"
	  "Each option needs to be accompanied by a number in the radix you specify.\n"
	  "You can specify as many numbers as you want.\n"
	  "Any numbers that are passed without an option will be considered a decimal.\n"
	  "\n"
	  "  -b, --bin\t\tpass binary number\n"
	  "  -o, --oct\t\tpass octal number\n"
	  "  -d, --dec\t\tpass decimal number\n"
	  "  -x, --hex\t\tpass hex number\n"
	  "\n"
	  "  -a, --ascii\t\tprint an ascii table with decimal index\n"
	  "  -A, --ascii-hex\tprint an ascii table with hex index\n"
	  "  -h, --help\t\tprint this help message\n",argv[0]);
  exit(EXIT_FAILURE);
}
