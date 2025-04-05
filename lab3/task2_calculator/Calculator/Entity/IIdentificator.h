#pragma once
#include <regex>
#include <string>
#include <unordered_set>

class IIdentificator
{
public:
	virtual ~IIdentificator() = default;
	virtual double GetValue() = 0;
	virtual void SetValue(double value) {};
	virtual std::string GetName() const = 0;
	virtual void ResetCache() = 0;
	virtual void AddDependent(IIdentificator* dependent) = 0;
	virtual void RemoveDependencies() = 0;
	virtual bool IsCacheValid() = 0;
	virtual std::unordered_set<IIdentificator*> GetSubscribes()
	{
		return {};
	};

protected:
	static void ValidateIdentifier(const std::string& name)
	{
		static const std::regex identifier_regex("^[a-zA-Z][a-zA-Z0-9_]*$");

		if (!std::regex_match(name, identifier_regex))
		{
			throw std::invalid_argument(
				"Identifier must start with a letter and contain only letters, digits and underscores");
		}
	}
};