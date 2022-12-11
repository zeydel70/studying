#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {
	String(const char *str = "");
	String(size_t n, char c);
	~String();

    String(const String &other);
    String &operator=(const String &other);

	void append(const String &other);
    
    	struct Substring
	{
		Substring(const char* _substr = "", unsigned _left = 0) : subsize(strlen(_substr)), substr(strcpy(new char[strlen(_substr) + 1], _substr)), left(_left) 
		{}

		~Substring() { delete[] this->substr; }

		// 2й оператор [] 
		String operator[](unsigned right) const
		{
			if ((this->left == right) || (this->substr == ""))  return String{};

			size_t new_size = right - left;
			char* tempStr = new char[new_size+1];

			for (unsigned i = 0; i != new_size; ++i) { tempStr[i] = this->substr[i]; }
			tempStr[new_size] = '\0';
			String Res_Op2{ tempStr };
			delete[] tempStr;
			tempStr = nullptr;
			return Res_Op2; 
		}
		
		char* substr;
		size_t subsize;
		unsigned left;
	};


	// 1й оператор []
	Substring operator[](unsigned left) const {	return String::Substring{ str+left, left}; }


	size_t size;
	char *str;
};


int main()
{
	String const hello("hello");
	String const hell = hello[0][4]; // теперь в hell хранится подстрока "hell"
	String const ell  = hello[1][4]; // теперь в ell хранится подстрока "ell"
	return 0;
}