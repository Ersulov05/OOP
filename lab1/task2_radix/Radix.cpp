#include <iostream>
#include <algorithm>
#include <climits>

const int MIN_RADIX = 2;
const int MAX_RADIX = 36;

bool isNumeric(const std::string& str) {
    return std::all_of(str.begin(), str.end(), ::isdigit);
}

bool assertBasisWithLimits(int radix)
{
    return radix >= MIN_RADIX && radix <= MAX_RADIX;
}

int StringToInt(const char & ch, int radix, bool & wasError)
{
    if (!assertBasisWithLimits(radix))
    {
        wasError = true;
        return 0;
    }
    int result = 0;

    if (std::isdigit(ch)) {
        result = ch - '0';
    } else if (std::isalpha(ch)) {
        char upperCh = std::toupper(ch);
        result = upperCh - 'A' + 10;
    } else {
        wasError = true;
        return 0;
    }

    if (result < 0 || result >= radix) {
        wasError = true;
        return 0;
    }
    return result;
}

std::string IntToString(int n, int radix, bool &wasError) 
{
    if (!assertBasisWithLimits(radix) || n < 0 || n >= radix) {
        wasError = true;
        return "";
    }

    if (n < 10) {
        return std::string(1, '0' + n);
    } else {
        return std::string(1, 'A' + n - 10);
    }
}

int ConvertRadixToDecimal(const std::string& str, int radix, bool & wasError)
{
    if (!assertBasisWithLimits(radix) || str.empty()) {
        wasError = true;
        return 0;
    }

    int result = 0;
    size_t start = 0;
    int sign = 1;
    if (str[0] == '-') {
        start = 1;
        sign = -1;
    }

    for (size_t i = start; i < str.length(); ++i) {
        int digit = StringToInt(str[i], radix, wasError);
        if ((result > (INT_MAX - digit) / radix) || wasError) {
           wasError = true;
           return 0;
        }
        
        result = result * radix + digit;
    }
    return sign * result;
}

std::string ConvertDecimalToRadix(int value, int radix, bool & wasError)
{
    if (!assertBasisWithLimits(radix)) {
        wasError = true;
        return "";
    }

    if (value == 0) {
        return "0";
    }

    std::string result = "";
    std::string sign = "";

    if (value < 0) {
        sign = "-";
        value = -value;
    }

    while (value > 0) {
        int digit = value % radix;
        value /= radix;
        result = IntToString(digit, radix, wasError) + result;
    }

    return sign + result;
}

std::string ConvertSourceToDestinationNotation(const std::string& value, int sourceNotation, int destinationNotation, bool & wasError) 
{
    int decimalValue = ConvertRadixToDecimal(value, sourceNotation, wasError);
    return ConvertDecimalToRadix(decimalValue, destinationNotation, wasError);
}

struct Arg
{
	int sourceNotation;
    int destinationNotation;
	std::string value;
};

Arg ParseArgs(int argc, char* argv[])
{
    if (argc != 4) {
        std::cout << "ERROR\n";
        exit(1);
    }
    Arg arg;

    if (!isNumeric(argv[1]) || !isNumeric(argv[2])) {
        std::cout << "ERROR\n";
        exit(1);
    }
    
    arg.sourceNotation = std::stoi(argv[1]);
    arg.destinationNotation = std::stoi(argv[2]);
    arg.value = argv[3];
    return arg;
}

int main(int argc, char* argv[]) 
{   
    Arg arg = ParseArgs(argc, argv);
    bool error = false;

    std::string convertedValue = ConvertSourceToDestinationNotation(arg.value, arg.sourceNotation, arg.destinationNotation, error);
    if (error) {
        std::cout << "ERROR\n";
    } else {
        std::cout << convertedValue << std::endl;
    }

    return 0;
}