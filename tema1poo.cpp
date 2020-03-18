#include <iostream>
#include "string_tema.h"



/*Program care citeste doua stringuri s1 si s2 si
afisaza stringul obtinut prin eliminarea tuturor 
aparitiilor lui s2 in s1 ca subcuvant (exemplu:  
s1="abcbabab", s2="ab" ===> "cb")*/


	int main()
	{
		string_tema s1 = "abcbabab";
		string_tema s2 = "ab";
		int poz;
		poz = s1.pos(s2);
		while (poz != -1)
		{
			s1.delete1(poz, s2.length());
			poz = s1.pos(s2);
		}
		cout << s1;
	}
		
	
