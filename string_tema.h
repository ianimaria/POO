#include <iostream>
using namespace std;
class string_tema
{
	char * sir;
	int lungime;

public:
	string_tema();
	string_tema(const string_tema &);
	string_tema(const char *);
	~string_tema();
	void set_lungime(int num);
	void set_sir(string_tema s);
	int& get_lungime();
	char* get_sir();

	// metoda publica citire
	friend istream& operator >> (iostream& is, const string_tema)
	{
		for (int i = 0; i < s.lungime; i++)
		{
			is >> s.sir[i];
		}
		return is;
	}

	// metoda publica afisare
	friend ostream& operator<<(ostream& os, const string_tema)
	{
		for (int i = 0; i < s.lungime; i++)
		{
			os << s.sir[i];
		}
		return os;
	}

	// metode de atribuire
	void operator =(const string_tema &);
	void operator =(char *);

	// metoda-operator publica []
	char & string_tema::operator[] (unsigned int x)
	{
		return sir[x];
	}

	int length();
	// testarea egalitatii
	friend int operator==(const string_tema, const string_tema);
	friend int operator==(const string_tema, char*);
	friend int operator==(char*, const string_tema);
	// testarea neegalitatii
	friend int operator!=(const string_tema, const string_tema);
	friend int operator!=(const string_tema, char*);
	friend int operator!=(char*, const string_tema);
	// comparare lexicografica
	friend int operator<(const string_tema, const string_tema);
	friend int operator<(const string_tema, char*);
	friend int operator<(char*, const string_tema);

	friend int operator<=(const string_tema, const string_tema);
	friend int operator<=(const string_tema, char*);
	friend int operator<=(char*, const string_tema);

	friend int operator>(const string_tema, const string_tema);
	friend int operator>(const string_tema, char*);
	friend int operator>(char*, const string_tema);

	friend int operator>=(const string_tema, const string_tema);
	friend int operator>=(const string_tema, char*);
	friend int operator>=(char*, const string_tema);

	// functii din Turbo Pascal

	int pos(string_tema);
	char* copy(string_tema, int a, int b);
	char* insert(string_tema, int a);
	char* delete1(int a, int b);


}s;

string_tema::string_tema()
{
	sir = nullptr;
	lungime = 0;
}

string_tema::string_tema(const string_tema&s)
{
	sir = new char[lungime];
	for (int i = 0; i < lungime; i++) {
		sir[i] = s.sir[i];
	}
}

string_tema::string_tema(const char *p)
{
	int i = 0;
	const char * t = p;

	while (*p++)
	{
		i++;
	}

	sir = new char[i];
	int j = 0;

	for (j; *t; t++, j++)
	{
		sir[j] = *t;
	}
	lungime = j;
}

string_tema::~string_tema()
{
	delete[] sir;
}

void string_tema::set_lungime(int num)
{
	lungime = num;
}

void string_tema::set_sir(string_tema s)
{
	for (int i = 0; i < s.length(); i++)
		s[i] = '\0';
}

int &string_tema::get_lungime()
{
	return lungime;
}

char* string_tema::get_sir()
{
	return sir;
}


void string_tema::operator =(const string_tema &s)
{
	sir = s.sir;
}
void string_tema::operator =(char * t)
{
	t = s.sir;
}


int string_tema::length()
{
	if (sir == nullptr)
		return 0;
	else
		return lungime;
}

int operator==(string_tema s, string_tema t)
{
	if (s.length() != t.length())
		return 0;

	else
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s.sir[i] != t.sir[i])
				return 0;
		}
	}
	return 1;
}
int operator==(const string_tema, char *t)
{
	int i = 0;
	int length = 0;
	while (t[i] != '\0')
		length++;
	if (s.length() != length)
		return 0;

	else
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s.sir[i] != t[i])
				return 0;
		}
	}
	return 1;
}
int operator==(char *t, const string_tema)
{
	int i = 0;
	int length = 0;
	while (t[i] != '\0')
		length++;
	if (length != s.length())
		return 0;

	else
	{
		for (int i = 0; i < length; i++)
		{
			if (t[i] != s.sir[i])
				return 0;
		}
	}
	return 1;
}

int operator!=(string_tema, string_tema t)
{
	if (s.length() != t.length())
		return 1;

	else
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s.sir[i] != t.sir[i])
				return 1;
		}
	}
	return 0;
}

int operator!=(const string_tema, char *t)
{
	int i = 0;
	int length = 0;
	while (t[i] != '\0')
		length++;
	if (s.length() != length)
		return 1;

	else
	{
		for (int i = 0; i < s.length(); i++)
		{
			if (s.sir[i] != t[i])
				return 1;
		}
	}
	return 0;
}

int operator!=(char *t, const string_tema)
{
	int i = 0;
	int length = 0;
	while (t[i] != '\0')
		length++;
	if (length != s.length())
		return 1;

	else
	{
		for (int i = 0; i < length; i++)
		{
			if (t[i] != s.sir[i])
				return 1;
		}
	}
	return 0;
}

int operator<(const string_tema, const string_tema t)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s.sir[i] < t.sir[i])
			return 1;
		else
			return 0;
	}
}

int operator<(const string_tema, char *t)
{
	for (int i = 0; i < s.length(); i++)
		if (s.sir[i] < t[i])
			return 1;
		else
			return 0;
}

int operator<(char *t, const string_tema)
{
	for (int i = 0; i < s.length(); i++)
		if (t[i] < s.sir[i])
			return 1;
		else
			return 0;
}

int operator<=(string_tema s, string_tema t)
{
	for (int i = 0; i < s.length(); i++)
	{
		if (s.sir[i] <= t.sir[i])
			return 1;
		else
			return 0;
	}
}

int operator<=(const string_tema, char *t)
{
	for (int i = 0; i < s.length(); i++)
		if (s.sir[i] <= t[i])
			return 1;
		else
			return 0;
}

int operator<=(char *t, const string_tema)
{
	for (int i = 0; i < s.length(); i++)
		if (t[i] <= s.sir[i])
			return 1;
		else
			return 0;
}

int operator>(string_tema, string_tema t)
{
	for (int i = 0; i < s.length(); i++)
		if (s.sir[i] > t.sir[i])
			return 1;
		else
			return 0;
}

int operator>(const string_tema, char *t)
{
	for (int i = 0; i < s.length(); i++)
		if (s.sir[i] > t[i])
			return 1;
		else
			return 0;
}

int operator>(char *t, const string_tema)
{
	for (int i = 0; i < s.length(); i++)
		if (t[i] > s.sir[i])
			return 1;
		else
			return 0;
}

int operator>= (string_tema, string_tema t)
{
	for (int i = 0; i < s.length(); i++)
		if (s.sir[i] >= t.sir[i])
			return 1;
		else
			return 0;
}

int operator>=(const string_tema, char *t)
{
	for (int i = 0; i < s.length(); i++)
		if (s.sir[i] >= t[i])
			return 1;
		else
			return 0;
}

int operator>=(char *t, const string_tema)
{
	for (int i = 0; i < s.length(); i++)
		if (t[i] >= s.sir[i])
			return 1;
		else
			return 0;
}

// Functii din Turbo Pascal

int string_tema::pos(string_tema t)
{
	int i = 0, j = 0, poz = -1;
	while ((sir[i] != '\0') || (t.sir[j] != '\0'))
	{
		if (t.sir[j] != sir[i])
		{
			j++;
			i = 0;
			poz = 0;
		}
		else
		{
			poz = i;
			i++;
			j++;

		}
	}
	if (t.sir[j] == '\0' && poz >= 0)
		return poz;
	else
		return poz;
}
char* string_tema::copy(string_tema s, int poz, int nr)
{
	char* s2 = "";
	int j = 0;
	if (poz > s.length())
		return s2;
	else
	{
		for (int i = 0; i < s.length(); i++)
			while (nr != 0)
			{
				s2[j] = s.sir[i];
				j++;
			}

	}
	return s2;
}
char* string_tema::insert(string_tema s, int poz)
{

	for (int i = poz; i < poz + s.length(); i++)
		s.sir[i + s.length()] = sir[i];
	for (int i = poz; i < poz + s.length(); i++)
		s.sir[i] = sir[i - poz];
	return s.sir;
}

char* string_tema::delete1(int poz, int nr)
{
	for (int i = poz; i < length(); i++)
	{
		while (nr != 0)
		{
			sir[i] = sir[i + 1];
			nr--;
		}
		sir[length() - 1 - nr] = '\0';
	}
	return sir;
}
