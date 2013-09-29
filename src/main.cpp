#include 					<fstream>
#include 					<iostream>
#include 					"Analex.hh"

int 							main(int argc, char **argv)
{
	Analex 					a;
	t_state 				*currentState;
	std::ifstream 	readFile;
	std::vector<AAutomata *>::iterator 	iter;
	char 						currentChar;

	if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << " file" << std::endl;
		return (-1);
	}
	readFile.open(argv[0], std::ifstream::in);
	while (readFile.good())
	{
		currentChar = readFile.get();
		for (iter = a._automata.begin(); iter != a._automata.end(); ++iter)
		{
			currentState = (*iter)->getInitialState();
			while (!currentState->isFinal)
			{
				if ((currentState = (*iter)->transition(currentState, currentChar)) == NULL)
				{
					std::cerr << "Error in the chain with this automata" << std::endl;
					return (-1);
				}
				currentChar = readFile.get();
			}
		}
		std::cout << "chain acepted" << std::endl;
	}
	return (0);
}
