#pragma once
#include <regex>
#include <string>
#include <unordered_set>
// TODO: Переименовать
class Identificator
{
public:
	virtual ~Identificator() = default;
	virtual double GetValue() = 0;
	virtual void SetValue(double value) {};
	virtual std::string GetName() const = 0;
	virtual void ResetCache() = 0;
	virtual void AddDependent(Identificator* dependent) = 0;
	virtual bool IsCacheValid() = 0;
	virtual std::unordered_set<Identificator*> GetSubscribes() = 0;

protected:
	static void ValidateName(const std::string& name)
	{
		static const std::regex identifier_regex("^[a-zA-Z][a-zA-Z0-9_]*$");

		if (!std::regex_match(name, identifier_regex))
		{
			throw std::invalid_argument(
				"Identifier must start with a letter and contain only letters, digits and underscores");
		}
	}
};