#include<iostream>
#include <string>

class BigInteger
{
public:
	BigInteger(std::string value) :num(value) {}

	BigInteger(const BigInteger& other) //конструктор копирования
	{
		this->num = other.num;
	}

	BigInteger(BigInteger&& other) noexcept :num(std::exchange(other.num, nullptr))
	{} //конструктор перемещения

	BigInteger& operator= (const BigInteger& other)//оператор копирующего присваивания
	{
		this->num = other.num;
		return *this;
	}

	BigInteger& operator= (BigInteger&& other) noexcept//оператор перемещающего присваивания
	{
		this->num = std::move(other.num);
		return *this;
	}

	BigInteger operator+ (const BigInteger& other)
	{
		std::string answer = "";
		int residue = 0; // остаток
		int value1, value2, resolve;
		int i = this->num.size() - 1;
		int j = other.num.size() - 1;
		for (; i>=0 || j>=0 ; --i, --j)
		{
			value1 = (i>=0) ? static_cast<int>(this->num[i] - '0'):0;
			value2 = (j>=0) ? static_cast<int>(other.num[j] - '0'):0;
			resolve = value1 + value2 + residue;
			residue = (resolve >= 10) ? 1 : 0;
			resolve %= 10;
			answer = std::to_string(resolve) + answer;
		}
		if (residue > 0)
		{
			answer = std::to_string(residue) + answer;
		}
		return BigInteger(answer);
	}


	BigInteger operator*(const int value)
	{
		std::string answer;
		BigInteger tmpl("0");
		int value2,resolve;

		for (int i = this->num.size() - 1; i >= 0; --i)
		{
			answer = "";
			value2 = static_cast<int>(this->num[i] - '0');
			resolve = value * value2;
			answer = std::to_string(resolve) + answer;
			for (int j = this->num.size() - 1; j>i;--j)
			{
				answer = answer + '0';
			}
			tmpl = tmpl + BigInteger(answer);
		}
		return tmpl;
	}

	std::string get_num()
	{
		return num;
	}

private:
	std::string num;
};

std::ostream& operator<<(std::ostream& stream,BigInteger value)
{
	stream << value.get_num();
	return stream;
}

int main()
{
	auto number1 = BigInteger("114575");
	auto number2 = BigInteger("78524");
	auto result = number1 + number2;
	std::cout << result; // 193099
	std::cout << std::endl << std::endl;
	auto number3 = BigInteger("15");
	std::cout << number3 * 3;
	return 0;
}