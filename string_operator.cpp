#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {
	String(const char *str = "") {
		this-> size = strlen(str);
		char* str_n = new char[this->size+1];
		this->str = strcpy(str_n, str);
    }
	
	String(size_t n, char c) {
		this->size = n;
		char* str_n = new char[n+1];
		for (int i = 0; i < n; i++) {
			str_n[i] = c;
		}
		str_n[n] = '\0';
		this->str = str_n;
	}

	/* и деструктор */
	~String() {
		delete[] str;
		str = 0;
	}


    String(const String& other): size(other.size), str(new char[size+1]) {
		for (size_t i = 0; i != size; i++) { this->str[i] = other.str[i]; }
		this->str[size] = '\0';
	}
	
    String& operator=(const String& other) {
		if (this != &other)
		{
			delete[] str;
			size = other.size;
			str = new char[size + 1];
			for (size_t i = 0; i != size; i++) { str[i] = other.str[i]; }
			str[size] = '\0';
		}
		return *this;
	}

	void append(String &other) {
       	size_t new_size =  this->size + other.size + 1;
		char* str2 = new char[new_size];
		for (int i = 0; i < this->size && i < new_size; i++) {
			str2[i] = this->str[i];
		}
		for (int i = this->size; i < new_size; i++) {
			str2[i] = other.str[i - this->size];
		}
		delete [] this->str;
		this->str = str2;
		this->size = new_size-1; 
    }
    
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