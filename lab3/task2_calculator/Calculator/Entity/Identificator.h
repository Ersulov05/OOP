#include <cmath>
#include <string>

enum class IdentificatorType
{
	FUNCTION,
	VARIABLE
};

enum class Operation
{
	PLUS,
	MINUS,
	MULTIPLY,
	DIVIDING,
	NONE
};

struct Function
{
	Operation operation = Operation::NONE;
	Identificator identificator1;
	Identificator identificator2;
};

struct Identificator
{
	std::string name;
	IdentificatorType type = IdentificatorType::VARIABLE;
	union
	{
		Function* function;
		double value = NAN;
	} data;
};