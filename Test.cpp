#include "Interface.h"

using namespace std;

int main() 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Interface* I = new Interface();

	I->work();

	delete I;
	
	return 0;
}