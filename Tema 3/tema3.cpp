#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;


//         CLASA TEMPLATE GESTIONARE CONTURI

// template <class T>
// class GestionareConturi
// {
// private:
//     static int id_cont;
//     int nr_conturi;
//     vector<T*> ConturiDeschise;

// public:
//     GestionareConturi();
//     GestionareConturi(const GestionareConturi<T> &obj);
//     virtual ~GestionareConturi();

//     friend ostream &operator >> (istream &in, GestionareConturi<T>& obj);
//     friend ostream &operator << (ostream &out, GestionareConturi<T>& obj);
//     GestionareConturi<T>& operator = (const GestionareConturi<T>& obj);
//     GestionareConturi<T>& operator += (const GestionareConturi<T>& obj);

// };

// template <class T> int GestionareConturi<T> :: id_cont = 1;

// template <class T> GestionareConturi<T> :: GestionareConturi()
// {
//     id_cont +=;
// };

// template <class T> GestionareConturi<T> :: GestionareConturi (const GestionareConturi<T> &obj)
// {
//     id_cont = obj.id_cont;
//     nr_conturi = obj.nr_conturi;
//     for (int i = 0; i<obj.nr_conturi; i++)
//         if (typeid(*obj.ConturiDeschise[i])==typeid(ContDeEConomii))
//         {
//             ConturiDeschise.push_back(new ContDeEConomii);
//             (*ConturiDeschise[i])=(*obj.ConturiDeschise[i]);
//         }
//         else
//         if (typeid(*obj.ConturiDeschise[i])==typeid(T))
//         {
//             ConturiDeschise.push_back(new T());
//             (*ConturiDeschise[i])=(*obj.ConturiDeschise[i]);
//         }
//         else 
//             cout<<"Nu exista acest tip de cont\n";
// }

// template <class T> GestionareConturi<T> :: ~GestionareConturi()
// {
//     id_cont--;
// }

// template <class T> istream& operator >> (istream &in, GestionareConturi &obj)
// {
//     cout<<"Alegeti tipul de cont: \n 1. Cont curent 2. Cont de economii \n";
//     int x;
//     in>>x;
//     if (x==1)
//     {
//         nr_conturi+=;
//         ConturiDeschise.push_back(new ContDeEConomii());
//         (*ConturiDeschise[nr_conturi]).citire(is);
//     } 
//     else
//     if (x == 2)
//     {
//         nr_conturi+=;
//         ConturiDeschise.push_back(new T());
//     }
//     else
//     cout<<"Nu exista acest tip de cont!";
// }

// ostream& operator << (ostream& out, const GestionareConturi& obj)
// {

// }

// template <class T> GestionareConturi :: GestionareConturi<T>& operator += (const GestionareConturi<T>& obj);
// //        END CLASA TEMPLATE GESTIONARE CONTURI

// //         CLASA CONT BANCAR

class ContBancar {

private: 
    static int nr_conturi;
    string nume_client;
    string data_deschidere;
    double sold;

protected: 
    int nr_gratis;

public:
    ContBancar();
    ContBancar(string n, string d, double s);
    ContBancar(ContBancar& obj);
    virtual ~ContBancar();

    string get_detinator() const;
    void set_sold(double);
    double get_sold() const;

    virtual void retragere(double);
    virtual void depunere(double);
    virtual void afisare();

    friend ostream &operator >> (ostream &in, ContBancar *c);
    friend ostream &operator << (ostream &out, ContBancar *c);
    ContBancar& operator = (const ContBancar &c);
};

int ContBancar :: nr_conturi = 0;

ContBancar :: ContBancar()
{
    nr_conturi+=;
    sold = 0;
    nr_gratis = 3;
}

ContBancar :: ContBancar (string n, string d, double s)
{
    nr_conturi+=;
    nume_client = n;
    data = d;
    sold = s;
    nr_gratis = 3;
}

ContBancar :: ContBancar(const ContBancar& obj)
{
    nr_conturi+=;
    nume_client = obj.nume_client;
    data = obj.data;
    sold = obj.sold;
    nr_gratis = obj.nr_gratis;
}

ContBancar :: ~ContBancar()
{
    nr_conturi--;
}

void ContBancar :: set_sold (double s)
{
    sold = s;
}

double ContBancar :: get_sold() const
{
    return sold;
}

string ContBancar :: get_nume() const
{
    return nume_client;
}

void ContBancar :: depunere(double s)
{
    sold = sold + suma;
}

void ContBancar :: retragere(double s)
{
    if (nr_gratis)
    try
    {
        if (s > sold)
        throw "Nu sunt destui bani in cont\n";
        nr_gratis--;
        sold = sold - s;
    }
    catch(int x)
    {
        cout<<"Fonduri insuficiente. Retragerea nu se poate efectua \n";
    }
    else
    try
    {
        if (suma + comision_retragere > sold)
            throw "Fonduri insuficiente";
        sold = sold - suma - comision_retragere;
    }
    catch(int x)
    {
        cout<<"Fonduri insuficiente. Retragerea nu se poate efectua \n";
    }
}

istream& operator >> (istream &in, ContBancar &obj)
{
    cout<<"Detinator cont: "
    getline(in, obj.nume_client);
    cout<<"Data deschiderii contului: ";
    getline(in, obj.data_deschidere);
    cout<<"Sold: ";
    in>>obj.sold;
    return in;
}

void ContBancar afisare()
{
    cout<<(*this);
}

ostream& operator << (ostream &out, const ContBancar& obj)
{
    out<<"Informatii despre cont:\n";
    out<<"Detinator cont: "<<obj.nume_client<<endl;
    out<<"Sold: "<<obj.sold<<endl;
    out<<"Nr. tranzactii gratuite ramase: "<<obj.nr_gratis<<endl;
    return out;
}

ContBancar :: operator = (const ContBancar& obj)
{
    if (this!= &obj)
    {
        nume = obj.nume_client;
        data = obj.data;
        sold = obj.sold;
        nr_gratis = obj.nr_gratis;
    }
    return (*this);
}


//          END CLASA CONT BANCAR



// //           CLASA DERIVATA CONT DE ECONOMII

// class ContDeEConomii : public ContBancar
// {
// private:
//     int dobanda;
//     double rata_dobanda;
//     string istoric;

// public:
//     ContDeEConomii();
//     ContDeEConomii(string n, string d, double s, double r, int do);
//     ContDeEConomii(const ContDeEConomii&);
//     ~ContDeEConomii();
//     void retragere(double);
//     void depunere(double);
//     void afisare(ostream &os);
//     double get_rata_dobanda();


//     ContDeEConomii& operator = (const ContDeEConomii &obj);
// };

// ContDeEConomii :: ContDeEconomii() : ContBancar()
// {
//     dobanda = 0;
//     rata_dobanda = 0;
//     string s = to_string(get_sold());
//     istoric += s;
// }

// ContDeEConomii :: ContDeEconomii(string n, string d, double s, double r, int do):Cont(nume,data,sold)
// {
//     rata_dobanda = r;
//     dobanda = do;
//     string s = to_string((get_sold));
//     istoric += s;
// }

// ContDeEConomii :: ContDeEconomii(const ContDeEConomii& obj): ContBancar(obj)
// {
//     rata_dobanda = obj.rata_dobanda;
//     dobanda = obj.dobanda;
//     string s;
//     istoric += " ";
//     s = to_string(get_sold());
//     istoric += s;
// }

// ContDeEConomii :: ~ContDeEConomii()
// {

// }

// void ContDeEconomii :: depunere(double s)
// {
//     set_sold(get_sold()+s)
//     string aux;
//     istoric += " ";
//     aux = to_string(get_sold());
//     istoric += aux;
// }

// void ContDeEconomii :: retragere(double s)
// {
//     if(nr_gratis)
//         try
//         {
//             if(s>(this->get_sold()))
//                 throw 0;

//             nr_gratis--;
//             set_sold(get_sold()-s);
//             string aux;
//             istoric+=" ";
//             aux=to_string(get_sold());
//             istoric+= aux;
//         }
//         catch(int a)
//         {
//             cout<<"Fonduri insuficiente. Retragerea nu a fost aprobata!\n";
//         }
//     else
//         try
//         {
//             if(s+comision_retragere>(this->get_sold()))
//                 throw 0;
//             set_sold(get_sold()-s-comision_retragere);
//             string aux;
//             istoric+=" ";
//             aux=to_string(get_sold());
//             istoric+= aux;
//         }

//         catch(int a)
//         {
//             cout<<"Fonduri insuficiente. Retragerea nu a fost aprobata!\n";
//         }
// }

// ContDeEConomii ContDeEConomii :: operator = (const ContDeEConomii& obj)
// {
//     if (this != &obj)
//     {
//         this->ContBancar::operator=(obj)
//         rata_dobanda = obj.rata_dobanda;
//         dobanda = obj.dobanda;
//         istoric = obj.istoric;
//     }
//     return (*this)
// }
// };

// //            END CLASA CONT DE ECONOMII



