#include 					<iostream>
#include 					"Analex.hh"

int 							main(int argc, char **argv)
{
	Analex 					a;

	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " [file name]" << std::endl;
		return (-1);
	}
	a.run(argv[1]);
	return (0);
}
