#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

int comision_retragere = 3;
using namespace std;


//         CLASA CONT BANCAR

class ContBancar {

public:
	static int nr_conturi;
	string nume_client;
	string data;
	double sold;

//public:
	int nr_gratis;

//public:
	ContBancar();
	ContBancar(string n, string d, double s);
	ContBancar(const ContBancar& obj);
	virtual ~ContBancar();


	void set_sold(double);
	double get_sold() const;
	string get_nume() const;

	virtual void retragere(double);
	virtual void depunere(double);
	virtual void afisare(ostream &out);

	friend ostream& operator >> (ostream &in,const ContBancar *obj);
	friend ostream& operator << (ostream &out,const ContBancar *obj);
	ContBancar& operator = (const ContBancar &obj);
};

int ContBancar::nr_conturi = 0;

ContBancar::ContBancar()
{
	nr_conturi++;
	sold = 0;
	nr_gratis = 3;
}

ContBancar::ContBancar(string n, string d, double s)
{
	nr_conturi += 1 ;
	nume_client = n;
	data = d;
	sold = s;
	nr_gratis = 3;
	comision_retragere = 3;
}

ContBancar :: ContBancar(const ContBancar& obj)
{
	nr_conturi ++ ;
	nume_client = obj.nume_client;
	data = obj.data;
	sold = obj.sold;
	nr_gratis = obj.nr_gratis;
}

ContBancar :: ~ContBancar()
{
	nr_conturi--;
}

void ContBancar::set_sold(double s)
{
	sold = s;
}

double ContBancar::get_sold() const
{
	return sold;
}

string ContBancar::get_nume() const
{
	return nume_client;
}

void ContBancar::depunere(double s)
{
	sold = sold + s;
}

istream& operator >> (istream &in, ContBancar &obj)
{
	cout << "Detinator cont: ";
	getline(in, obj.nume_client);
	cout << "Data deschiderii contului: ";
	getline(in, obj.data);
	cout << "Sold: ";
	in >> obj.sold;
	return in;
}


ostream& operator << (ostream &out, const ContBancar& obj)
{
	out << "Informatii despre cont:\n";
	out << "Detinator cont: " << obj.nume_client << endl;
	out << "Sold: " << obj.sold << endl;
	out << "Nr. tranzactii gratuite ramase: " << obj.nr_gratis << endl;
	return out;
}

ContBancar& ContBancar :: operator = (const ContBancar& obj)
{
	if (this != &obj)
	{
		nume_client = obj.nume_client;
		data = obj.data;
		sold = obj.sold;
		nr_gratis = obj.nr_gratis;
	}
	return (*this);
}

void ContBancar::retragere(double s)
{
	if (nr_gratis)
		try
	{
		if (s > sold)
			throw "Nu sunt destui bani in cont\n";
		nr_gratis--;
		sold = sold - s;
	}
	catch (int x)
	{
		cout << "Fonduri insuficiente. Retragerea nu se poate efectua \n";
	}
	else
		try
	{
		if (s + comision_retragere > sold)
			throw "Fonduri insuficiente";
		sold = sold - s - comision_retragere;
	}
	catch (int x)
	{
		cout << "Fonduri insuficiente. Retragerea nu se poate efectua \n";
	}
}


//          END CLASA CONT BANCAR



//           CLASA DERIVATA CONT DE ECONOMII

class ContDeEconomii : public ContBancar
{
public:
	int dobanda;
	double rata_dobanda;
	string istoric;

public:
	ContDeEconomii();
	ContDeEconomii(string n, string d, double s, double r, int dob);
	ContDeEconomii(const ContDeEconomii& obj);
	~ContDeEconomii();
	void retragere(double);
	void depunere(double);
	void afisare(ostream &out);

	friend istream& operator >> (istream &in, ContDeEconomii *obj);
	friend ostream& operator << (ostream &out, ContDeEconomii *obj);
	ContDeEconomii operator = (const ContDeEconomii &obj);
};

ContDeEconomii::ContDeEconomii() : ContBancar()
{
	dobanda = 0;
	rata_dobanda = 0;
	string s = to_string(get_sold());
	istoric += s;
}

ContDeEconomii::ContDeEconomii(string n, string d, double s, double r, int dob) : ContBancar(nume_client, data, sold)
{
	rata_dobanda = r;
	dobanda = dob;
	string aux = to_string(get_sold());
	istoric += aux;
}

ContDeEconomii::ContDeEconomii(const ContDeEconomii& obj) : ContBancar(obj){
	rata_dobanda = obj.rata_dobanda;
	dobanda = obj.dobanda;
	string s;
	istoric += " ";
	s = to_string(get_sold());
	istoric += s;
}

ContDeEconomii :: ~ContDeEconomii()
{

}

void ContDeEconomii::depunere(double s)
{
	set_sold(get_sold() + s);
	string aux;
	istoric += " ";
	aux = to_string(get_sold());
	istoric += aux;
}

void ContDeEconomii::retragere(double s)
{
	if (nr_gratis)
		try
	{
		if (s>(this->get_sold()))
			throw 0;

		nr_gratis--;
		set_sold(get_sold() - s);
		string aux;
		istoric += " ";
		aux = to_string(get_sold());
		istoric += aux;
	}
	catch (int a)
	{
		cout << "Fonduri insuficiente. Retragerea nu a fost aprobata!\n";
	}
	else
		try
	{
		if (s + comision_retragere>(this->get_sold()))
			throw 0;
		set_sold(get_sold() - s - comision_retragere);
		string aux;
		istoric += " ";
		aux = to_string(get_sold());
		istoric += aux;
	}

	catch (int a)
	{
		cout << "Fonduri insuficiente. Retragerea nu a fost aprobata!\n";
	}
}

istream& operator >> (istream &in, ContDeEconomii& obj)
{
	cout << "Rata:"; 
	in>>obj.rata_dobanda;
	cout << "Durata ratei:";
	in >> obj.dobanda;
	cout << "Istoricul soldului:";
	in >> obj.istoric;
	return in;
}

ContDeEconomii ContDeEconomii :: operator = (const ContDeEconomii& obj)
{
	if (this != &obj)
	{
		this->ContBancar::operator=(obj);
		rata_dobanda = obj.rata_dobanda;
		dobanda = obj.dobanda;
		istoric = obj.istoric;
	}
	return (*this);
}

void ContDeEconomii :: afisare(ostream &out)
{
	this->ContBancar::afisare(out);
	out << "Dobanda este pe " << dobanda << " luni \n";
	out << "Rata dobanzii este: " << rata_dobanda << endl;
	out << "Istoricul contului este: " << istoric << endl;


}


//            END CLASA CONT DE ECONOMII

//      CLASA TEMPLATE GESTIONARE CONTURI

template <class T>
class GestionareConturi
{
public:
	static int id_cont;
	int nr_conturi;
	vector<T*> ConturiDeschise;

public:
	GestionareConturi();
	GestionareConturi(const GestionareConturi<T> &obj);
	virtual ~GestionareConturi();

    void adaugare_cont()
	friend ostream &operator >> (istream &in, GestionareConturi<T>& obj);
	friend ostream &operator << (ostream &out, GestionareConturi<T>& obj);
	GestionareConturi<T>& operator = (const GestionareConturi<T>& obj);
	GestionareConturi<T>& operator += (const GestionareConturi<T>& obj);

};

template <class T> int GestionareConturi<T> ::id_cont = 1;

template <class T> GestionareConturi<T> ::GestionareConturi()
{
	id_cont += ;
}

template <class T> GestionareConturi<T> ::GestionareConturi(const GestionareConturi<T> &obj)
{
	id_cont = obj.id_cont;
	nr_conturi = obj.nr_conturi;
	for (int i = 0; i<obj.nr_conturi; i++)
		if (typeid(*obj.ConturiDeschise[i]) == typeid(ContDeEconomii))
		{
			ConturiDeschise.push_back(new ContDeEconomii);
			(*ConturiDeschise[i]) = (*obj.ConturiDeschise[i]);
		}
		else
			if (typeid(*obj.ConturiDeschise[i]) == typeid(T))
			{
				ConturiDeschise.push_back(new T());
				(*ConturiDeschise[i]) = (*obj.ConturiDeschise[i]);
			}
			else
				cout << "Nu exista acest tip de cont\n";
}

template <class T> GestionareConturi<T> :: ~GestionareConturi()
{
	id_cont--;
}

template<class T>void GestionareConturi<T>::adaugare_cont(istream&in)
{
    cout<<"Sunt disponibile urmatoarele tipuri de conturi: 1. Cont curent 2. Cont de economii. Ce optiune va interesaza?\n";
    cout<<"Tipul de cont dorit: ";
    string tip;
    getline(in,tip);
    if(tip=="Cont de economii")
    {
        nr_conturi++;
        ConturiDeschise.push_back(new ContDeEconomii());
        (*ConturiDeschise[nr_conturi-1]).citire(in);
    }
    else if(tip=="Cont curent")
    {
        nr_conturi++;
        ConturiDeschise.push_back(new T());
        (*ConturiDeschise[nr_conturi-1]).citire(in);
    }
    else
        cout<<"Tip de cont invalid.\n";
}

template<class T> void GestionareConturi<T>::afisare_cont(ostream&os,int nr_cont)
{
    (*vectConturi[nr_cont-1]).afisare(os);
    os<<"\n";
}


template <class T> istream& operator >> (istream &in, GestionareConturi<T> &obj)
{
	cout << "Alegeti tipul de cont: \n 1. ContBancar curent 2. ContBancar de economii \n";
	int x;
	in >> x;
	if (x == 1)
	{
		nr_conturi += 1;
		ConturiDeschise.push_back(new ContDeEconomii());
		
	}
	else
		if (x == 2)
		{
			nr_conturi += 1 ;
			ConturiDeschise.push_back(new T());
		}
		else
			cout << "Nu exista acest tip de cont!";
}

template <class T> ostream& operator << (ostream& out, const GestionareConturi<T>& obj)
{
	for (int i = 0; i<nr_conturi; i++)
	{
		(*ConturiDeschise[i]).afisare(out);
		out << "\n";
	}
}

//        END CLASA TEMPLATE GESTIONARE CONTURI


int main()

{
    GestionareConturi cont;
	cout<<"MyBank \n Alegeti una dintre optiunile de mai jos: \n 1. Deschidere cont \n 2. Retragere numerar \n 3. Depunere numerar \n 4. Afisare informatii cont ";
    int x;
    cin>>x;
    switch (x)
    {
        case 1:
            cont->adaugare_cont();
        case 2:
            cont->retragere();
        case 3:
            cont->depunere();
        case 4:
            cont->afisare();
        default:
            cout<<"Nu ati introdus o optiune valida";
    }
}   