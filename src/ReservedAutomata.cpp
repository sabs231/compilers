#include 	"ReservedAutomata.hh"


ReservedAutomata::ReservedAutomata()
	: AAutomata()
{
	this->_stateNum = 18;
	this->_symbolNum = 14;
	this->_stateIndex.insert(std::pair<char, int>('A', 0));
	this->_stateIndex.insert(std::pair<char, int>('B', 1));
	this->_stateIndex.insert(std::pair<char, int>('C', 2));
	this->_stateIndex.insert(std::pair<char, int>('D', 3));
	this->_stateIndex.insert(std::pair<char, int>('E', 4));
	this->_stateIndex.insert(std::pair<char, int>('F', 5)); // FINAL
	this->_stateIndex.insert(std::pair<char, int>('G', 6));
	this->_stateIndex.insert(std::pair<char, int>('H', 7));
	this->_stateIndex.insert(std::pair<char, int>('I', 8));
	this->_stateIndex.insert(std::pair<char, int>('J', 9));
	this->_stateIndex.insert(std::pair<char, int>('K', 10));
	this->_stateIndex.insert(std::pair<char, int>('L', 11));
	this->_stateIndex.insert(std::pair<char, int>('M', 12));
	this->_stateIndex.insert(std::pair<char, int>('N', 13));
	this->_stateIndex.insert(std::pair<char, int>('O', 14));
	this->_stateIndex.insert(std::pair<char, int>('P', 15));
	this->_stateIndex.insert(std::pair<char, int>('Q', 16));
	this->_stateIndex.insert(std::pair<char, int>('R', 17));
	
	this->_symbolIndex.insert(std::pair<char, int>('c', 0));
	this->_symbolIndex.insert(std::pair<char, int>('o', 1));
	this->_symbolIndex.insert(std::pair<char, int>('u', 2));
	this->_symbolIndex.insert(std::pair<char, int>('n', 3));
	this->_symbolIndex.insert(std::pair<char, int>('t', 4));
	this->_symbolIndex.insert(std::pair<char, int>('w', 5));
	this->_symbolIndex.insert(std::pair<char, int>('h', 6));
	this->_symbolIndex.insert(std::pair<char, int>('i', 7));
	this->_symbolIndex.insert(std::pair<char, int>('l', 8));
	this->_symbolIndex.insert(std::pair<char, int>('e', 9));
	this->_symbolIndex.insert(std::pair<char, int>('s', 10));
	this->_symbolIndex.insert(std::pair<char, int>('f', 11));
	this->_symbolIndex.insert(std::pair<char, int>('a', 12));
	this->_symbolIndex.insert(std::pair<char, int>('r', 13));

	this->_transitionTable = new t_state*[this->_stateNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
		this->_transitionTable[i] = new t_state[this->_symbolNum];
	for (unsigned int i = 0; i < this->_stateNum; i++)
	{
		for (unsigned int j = 0; j < this->_symbolNum; j++)
		{
			this->_transitionTable[i][j].name = '#';
			this->_transitionTable[i][j].isFinal = false;
		}
	}
	// Transiciones
	this->_transitionTable[0][0].name = 'O';
	this->_transitionTable[0][5].name = 'B';
	this->_transitionTable[0][9].name = 'H';
	this->_transitionTable[0][3].name = 'J';
	this->_transitionTable[0][7].name = 'L';
	this->_transitionTable[0][12].name = 'M';
	
	this->_transitionTable[14][1].name = 'P';
	this->_transitionTable[15][2].name = 'Q';
	this->_transitionTable[16][3].name = 'R';
	this->_transitionTable[17][4].name = 'F';
	this->_transitionTable[17][4].isFinal = true;
	
	this->_transitionTable[1][6].name = 'C';
	this->_transitionTable[2][7].name = 'D';
	this->_transitionTable[3][8].name = 'E';
	this->_transitionTable[4][9].name = 'F';
	this->_transitionTable[4][9].isFinal = true;
	
	this->_transitionTable[7][8].name = 'I';
	this->_transitionTable[8][10].name = 'E';
	
	this->_transitionTable[9][7].name = 'K';
	this->_transitionTable[10][8].name = 'F';
	this->_transitionTable[10][8].isFinal = true;

	this->_transitionTable[11][11].name = 'F';
	this->_transitionTable[11][11].isFinal = true;
	
	this->_transitionTable[12][13].name = 'N';
	this->_transitionTable[13][13].name = 'F';
	this->_transitionTable[13][13].isFinal = true;

}

ReservedAutomata::ReservedAutomata(t_state **transitionTable, unsigned int stateNum, unsigned int symbolNum)
	: AAutomata(transitionTable, stateNum, symbolNum)
{
}

ReservedAutomata::~ReservedAutomata()
{
	if (this->_transitionTable)
		delete [] this->_transitionTable;
}

char ReservedAutomata::simplifySymbol(char currentSymbol) const{
	return currentSymbol;
}
