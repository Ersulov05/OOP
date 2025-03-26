#pragma once
#include <string>

struct IdentificatorValueData
{
	std::string identificatorName;
	double value;
	IdentificatorValueData()
		: identificatorName("")
		, value(NAN){};

	IdentificatorValueData(std::string identificatorName, double value)
		: identificatorName(identificatorName)
		, value(value)
	{
	}
};