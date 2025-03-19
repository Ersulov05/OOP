#include "../Entity/Identificator.h"
#include <string>
#include <unordered_map>
#include <vector>

class IdentificatorRepository
{
public:
	void AddIdentificator(Identificator identificator);
	void EditIdentificator(Identificator identificator);
	Identificator GetIdentificatorByName(const std::string& identificatorName);
	std::unordered_map<std::string, Identificator> GetVariableIdentificators();
	std::unordered_map<std::string, Identificator> GetFunctionIdentificators();
	std::unordered_map<std::string, Identificator> GetAllIdentificators();

private:
	std::unordered_map<std::string, Identificator> identificators;
};