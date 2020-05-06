#include <iostream>
#include <istream>
#include <string>
#include <vector>

using namespace std;




//               CLASA CLIENT


class Client
{
    public:
    int id_client;
    string comanda;
    double nota;
    
    Client();
    // Constructor
    Client(Client &);

    // Destructor
    ~Client();

    void set_id_client (int id) { id_client = id;};
    int get_id_client () { return id_client;};

    void set_comanda(string s) { comanda = s;};
    string get_comanda () { return comanda;};

    double get_nota () { return nota; }

    void adauga_nota(double x);
    void adauga_comanda (string s);

    friend ostream& operator<< (ostream &out,  const Client &client);
    friend istream& operator>> (istream &in, Client &client);
    Client operator = (const Client &);
};


Client :: Client()

{

    nota = 0;
    comanda = "";
}

Client :: Client(Client &client)
{   
    id_client = client.id_client;
    comanda = client.comanda;
    nota = client.nota;
}

Client :: ~Client()

{
    nota = 0;
    comanda = "";
}

ostream& operator << (ostream& out, const Client& client)
{
    out << client.id_client;
    return out;
}

istream& operator >> (istream &in, Client &client)

{ 
    in>>client.id_client;
    return in;
}  

Client Client ::operator=(const Client &ob)
{
    if(this!=&ob)
    {
        id_client = ob.id_client;
        comanda = ob.comanda;
        nota = ob.nota;
    }
    return *this;
}

void Client :: adauga_nota(double x)
    {nota = get_nota() + x;}

void Client :: adauga_comanda(string s)
    {if (comanda == "")
        comanda = s;
    else
        comanda = get_comanda() + ", " +s;
    }

//               END CLASA CLIENT


//              CLASA MASA 

class Masa
{   
//private:
public:
    static int id;
    Client *clienti_masa;
    bool ocupata = false;
    int nrlocuri;
    int nrclienti;

public:
    Masa(int nr_locuri = 0);
    Masa(const Masa&);
    ~Masa();

    friend ostream& operator<< (ostream &out,  const Masa &masa);
    friend istream& operator>> (istream &in, Masa &masa);
    Masa operator=(const Masa &);

    void set_nr_clienti(int nr) { nrclienti = nr;};
    int get_nr_clienti() {return nrclienti;};
    void set_nr_locuri(int nr) {nrlocuri = nr;};
    int get_nr_locuri() {return nrlocuri;};

    void comanda_pt_client (string s, int id) { clienti_masa[id].adauga_comanda(s); };
    void adauga_nota_client (double pret, int id) { clienti_masa[id].adauga_nota(pret);};

    string get_comanda_client(int id) { return clienti_masa[id].get_comanda();};
};
int Masa:: id = 1;

Masa :: Masa(int nr_locuri) : nrlocuri(nr_locuri)
{
    clienti_masa = new Client[nr_locuri];
}

Masa::Masa(const Masa &ob):clienti_masa(ob.clienti_masa)
{
    nrlocuri = ob.nrlocuri;
    nrclienti = ob.nrclienti;
    for(int i=0; i<nrlocuri; i++)
    {
        clienti_masa[i] = ob.clienti_masa[i];
    }
}

Masa::~Masa()
{
    nrlocuri = nrclienti = 0;
    delete []clienti_masa;
}

Masa Masa::operator=(const Masa &ob)
{
    if(this!=&ob)
    {
        nrclienti = ob.nrclienti;
        nrlocuri = ob.nrlocuri;
        for(int i=0; i<nrlocuri; i++)
    {
        clienti_masa[i] = ob.clienti_masa[i];
    }

    }
    return *this;
}

ostream& operator<< (ostream &out, const Masa &masa)
{   if (masa.nrclienti != 0)
        {if (masa.nrclienti <= masa.nrlocuri)
        {out<<"Masa are "<<masa.nrclienti<<" clienti"<<endl;
        out<<"Id-urile clientilor sunt: ";
        for (int i = 0; i<masa.nrclienti ; i++)
        {
            out<<masa.clienti_masa[i].get_id_client()<<" ";
        }
        out<<endl;
        }
        else
        out<<"Masa nu are clienti\n";}
    else
    out<<"Masa nu are clienti\n";
    return out;
    
}

istream& operator>>(istream &in, Masa &masa)
{
    cout<<"Setati nr. de locuri al mesei: ";
    in>>masa.nrlocuri;
    cout<<"Cati clienti se aseaza la masa?\n";
    in>>masa.nrclienti;
    if (masa.nrclienti != 0)
        {if (masa.nrclienti <= masa.nrlocuri)
            {cout<<"Clientii s-au asezat.\n";
            for (int i=0;i<masa.nrclienti;i++)
                {masa.clienti_masa[i].set_id_client(masa.id);
                masa.id++;}}
        else
            cout<<"Masa nu este destul de mare\n";}
    else
    cout<<"Nu s-a asezat niciun client\n";
    

    return in;
}

//                CLASA VIRTUALA PURA MENIU

class Meniu 
{
public:
//protected: 
    double pret;

public:
    Meniu();
    Meniu(double);
    Meniu(const Meniu&);
    virtual ~Meniu();
    friend istream& operator >> (istream&, Meniu&);
    friend ostream& operator << (ostream&, const Meniu&);
    Meniu& operator = (const Meniu&);

    virtual void set_pret(double);
    virtual void get_pret() = 0;
    
};

Meniu :: Meniu()
{
    pret = 0;

}

Meniu :: Meniu(double pret) : pret(pret)
{

}

Meniu :: Meniu(const Meniu &meniu)
{
    pret = meniu.pret;
}

Meniu :: ~Meniu()
{
    pret = 0;
}

void Meniu:: set_pret(double x)
{
    pret = x;
}



//           END CLASA VIRTUALA PURA MENIU 



//          CLASA CIORBA (DERIVATA MENIU)

class Ciorba: public Meniu
{
public:
//protected:
    string denumire_ciorba;
    bool smantana;
    bool ardei;

public:
    
    Ciorba(double pret = 0, string denumire_ciorba ="", bool smantana = false, bool ardei = false);
    Ciorba(const Ciorba&);
    ~Ciorba();
    void set_denumire_ciorba(string, bool, bool);
    string get_denumire_ciorba();

    void get_pret() override
    {
        cout<<pret;
    }
    void set_pret(double x) override
    {
    if (denumire_ciorba == "ciorba de legume")
        x = 10;
    else if (denumire_ciorba == "ciorba de burta")
        x = 12;
    else if (denumire_ciorba == "ciorba de ciuperci")
        x = 15;

    if (smantana == true)
        x += 3;
    if (ardei == true)
        x += 2;

    Meniu :: set_pret(x);
    }

    friend istream& operator >> (istream&, Ciorba&);
    friend ostream& operator << (ostream&, const Ciorba&);
    Ciorba& operator = (const Ciorba&);
};

Ciorba :: Ciorba (double pret, string denumire_ciorba, bool smantana, bool ardei) : Meniu (pret), denumire_ciorba(denumire_ciorba), smantana(smantana), ardei(ardei)
{

}

Ciorba :: Ciorba(const Ciorba &ciorba)
{
    pret = ciorba.pret;
    denumire_ciorba = ciorba.denumire_ciorba;
    smantana = ciorba.smantana;
    ardei = ciorba.ardei;
}

Ciorba :: ~Ciorba()
{
    denumire_ciorba = "";
    smantana = false;
    ardei = false;
}

ostream& operator<< (ostream &out, Ciorba &ciorba)
{
    out<<"Pretul pentru "<<ciorba.denumire_ciorba;
    if(ciorba.smantana == true)
        out<<" cu smantana ";
    
    if(ciorba.ardei == true)
        out<<" cu ardei ";
    out<<"este ";
    out<<ciorba.pret;
    out<<" lei \n";
    return out;
}

istream& operator>> (istream &in, Ciorba &ciorba)
{   
    cout<<"Doriti ciorba?\n";   
    string s;
    in>>s;
    if (s=="da")
    {
    cout<<"Ce fel de ciorba? (legume, burta, ciuperci)\n ";
    in>>ciorba.denumire_ciorba;
    if (ciorba.denumire_ciorba == "legume")
        ciorba.denumire_ciorba = "ciorba de legume";
    else if (ciorba.denumire_ciorba == "burta")
        ciorba.denumire_ciorba = "ciorba de burta";
    else if (ciorba.denumire_ciorba == "ciuperci")
        ciorba.denumire_ciorba = "ciorba de ciuperci";
    cout<<"Doriti smantana?\n";
    in>>s;
    if(s=="da")
        ciorba.smantana = true;
    else
        ciorba.smantana = false;

    cout<<"Doriti ardei?\n";
    in>>s;
    if(s=="da")
        ciorba.ardei = true;
    else
        ciorba.ardei = false;  
    ciorba.set_pret(0);}

    return in;
}

Ciorba& Ciorba :: operator=(const Ciorba &ob)
{
    if(this!=&ob)
    {

        pret = ob.pret;
        denumire_ciorba = ob.denumire_ciorba;
        smantana = smantana;
        ardei = ardei;
    }
    return *this;
}

void Ciorba :: set_denumire_ciorba(string denumire, bool smantana, bool ardei)
{
    denumire_ciorba = denumire;
    this->smantana = smantana;
    this->ardei = ardei;
}

string Ciorba:: get_denumire_ciorba()
{
    return denumire_ciorba;
}


//            END CLASA CIORBA

//             CLASA FEL PRINCIPAL

class FelPrincipal : public Meniu
{
// private:
    public:
    string denumire_fel;
    bool garnitura;
    string denumire_garnitura;

public:
    FelPrincipal();
    FelPrincipal(double, string denumire_fel, bool garnitura=false, string denumire_garnitura=""); 
    FelPrincipal(const FelPrincipal&);
    virtual ~FelPrincipal();

    friend istream& operator >> (istream&, FelPrincipal&);
    friend ostream& operator << (ostream&, const FelPrincipal&);
    FelPrincipal& operator = (const FelPrincipal&);

    void get_pret() override
    {
        cout<<pret;
    }

    void set_pret(double x) override
    {
        if (denumire_fel=="frigarui de pui")
            x = 18;
        else if (denumire_fel == "tocana de pui")
            x = 17;
        else if (denumire_fel == "vita Chateaubriand")
            x = 40;
        else if (denumire_fel == "vita Stroganoff")
            x = 35;
        else if (denumire_fel == "file de vita")
            x = 30;
        
        if (garnitura == true)
            if (denumire_garnitura == "cartofi prajiti")
                x += 7;
            else if (denumire_garnitura == "piure")
                x += 7;
            else if (denumire_garnitura == "orez sarbesc")
                x += 10;
        
        Meniu :: set_pret(x);
    }

    void set_denumire_fel(string denumire, bool garnitura, string den_garnitura);
    string get_denumire_fel ();


};
FelPrincipal :: FelPrincipal()
{

}

FelPrincipal :: FelPrincipal(double pret, string denumire_fel, bool garnitura, string denumire_garnitura) : Meniu (pret), denumire_fel(denumire_fel), garnitura(garnitura), denumire_garnitura(denumire_garnitura)
{

}

FelPrincipal :: FelPrincipal(const FelPrincipal &fel)
{
    pret = fel.pret;
    denumire_fel = fel.denumire_fel;
    garnitura = fel.garnitura;
    denumire_garnitura = fel.denumire_garnitura;
}

FelPrincipal :: ~FelPrincipal()
{
    pret = 0;
    denumire_fel = "";
    garnitura = false;
    denumire_garnitura = "";
}

FelPrincipal& FelPrincipal :: operator=(const FelPrincipal &ob)
{
    if(this!=&ob)
    {

        pret = ob.pret;
        denumire_fel = ob.denumire_fel;
        garnitura = garnitura;
        denumire_garnitura = ob.denumire_garnitura;
    }
    return *this;
}

ostream& operator<< (ostream &out, FelPrincipal &fel)
{
    out<<"Pentru "<<fel.denumire_fel;
    if(fel.garnitura == true)
        out<<" cu "<<fel.denumire_garnitura<<",";
    
    out<<"pretul este ";
    out<<fel.pret;
    out<<" lei \n";
    return out;
}

istream& operator>> (istream &in, FelPrincipal &fel)
{   cout<<"Doriti fel principal?\n";
    string s; int ok=1;
    in>>s;
    if (s=="da")
    {cout<<"Ce fel principal?\n ";
    in>>fel.denumire_fel;
    if (fel.denumire_fel=="frigarui_de_pui")
            fel.denumire_fel = "frigarui de pui";
    else if (fel.denumire_fel == "tocana_de_pui")
            fel.denumire_fel = "tocana de pui";
    else if (fel.denumire_fel == "vita_Chateaubriand")
            fel.denumire_fel = "vita Chateaubriand";
    else if (fel.denumire_fel == "vita_Stroganoff")
            fel.denumire_fel = "vita Stroganoff";
    else if (fel.denumire_fel == "file_de_vita")
            fel.denumire_fel = "file de vita";
    else {cout<<"Nu exista acest fel principal in meniu\n;";
         ok=0;}
    if (ok!=0)

    cout<<"Doriti garnitura?:\n";
    in>>s;
    if(s=="da")
        fel.garnitura = true;
    else
        fel.garnitura = false;

    cout<<"Ce garnitura?\n";
    in>>s;
    if(s=="cartofi_prajiti")
        fel.denumire_garnitura = "cartofi prajiti";
    else if (s=="piure")
        fel.denumire_garnitura = "piure";
    else if (s=="orez_sarbesc")
        fel.denumire_garnitura = "orez sarbesc";
    else cout<<"Garnitura nu exista in meniu\n";}
    fel.set_pret(0);
    return in;
}

void FelPrincipal :: set_denumire_fel(string denumire, bool garni, string den_garnitura)
{
    denumire_fel = denumire;
    garnitura = garni;
    denumire_garnitura = den_garnitura;
}

string FelPrincipal :: get_denumire_fel()
{
    return denumire_fel;
}

//                END CLASA FEL PRINCIPAL


//                  CLASA DESERT

class Desert : public Meniu
{
//private:
public:
    int nr_cupe=0;
    string denumire_desert;

public:
    Desert();
    Desert(double pret, string denumire_desert);
    Desert(const Desert&);
    ~Desert();
    void get_pret() override {cout<<pret;};
    void set_pret(double x) override
    {
        if (denumire_desert=="Inghetata")
            x = 4*nr_cupe;
        else if (denumire_desert=="tort Krantz")
            x = 15;
        Meniu :: set_pret(x);
    }
    void set_denumire_desert(string s) { denumire_desert = s;};
    string get_denumire_desert() {return denumire_desert;};

    friend ostream& operator<< (ostream &out, Desert &desert);
    friend istream& operator>> (istream &in, Desert &desert);
    Desert& operator=(const Desert &);
};
Desert :: Desert()
{

}
Desert :: Desert(double pret, string denumire_desert) : Meniu (pret), denumire_desert(denumire_desert)
{

}

Desert :: Desert(const Desert &desert)
{
    pret = desert.pret;
    denumire_desert = desert.denumire_desert;
    nr_cupe = desert.nr_cupe;

}

Desert :: ~Desert()
{   
    pret = 0;
    denumire_desert = "";
}

Desert& Desert::operator=(const Desert &ob)
{
    if(this!=&ob)
    {

        pret = ob.pret;
        denumire_desert = ob.denumire_desert;
      
    }
    return *this;
}

ostream& operator<< (ostream &out, Desert &desert)
{
    out<<"Pentru "<<desert.denumire_desert<<" pretul este ";
    out<<desert.pret<<" lei";
    if(desert.denumire_desert == "inghetata")
        out<<" pentru "<<desert.nr_cupe<<" cupe";
    return out;
}

istream& operator>> (istream &in, Desert &desert)
{
    cout<<"Doriti desert?\n ";
    string s;
    in>>s;
    if (s=="da")
    {
    cout<<"Ce desert?\n";
    in>>desert.denumire_desert;
    if(desert.denumire_desert == "inghetata")
    {   desert.denumire_desert= "Inghetata";
        cout<<"Cate cupe?\n ";
        int i=0;
        while (i<3 or i>5)
        {in>>i;
        if (i>=3 and i<=5)
            desert.nr_cupe = i;
        else
        cout<<"Trebuie sa alegeti intre 3 si 5 cupe\n";}
        }
    else if (desert.denumire_desert == "krantz")
        desert.denumire_desert = "tort Krantz";
    else
        cout<<"Acest desert nu exista in meniu \n";}
    
    desert.set_pret(0);

    return  in;
}

//                    END CLASA DESERT


//                      CLASA BAUTURI

class Bauturi : public Meniu
{
//private:
public:
    string denumire_bautura;
    string culoare="";
    string sticla="";
    bool pahar= false;
    bool alcool = false;
    int nr_ml = 0;

public:
    Bauturi();
    Bauturi(double pret, string denumire_bautura);
    Bauturi(const Bauturi&);
    ~Bauturi();
    void get_pret() override {cout<<pret;};
    void set_pret(double x) override
    {
        if (denumire_bautura=="vin" and pahar == true) 
            {if (culoare == "rosu")
                x = 6 * nr_ml/100.0;
            else if (culoare =="alb" )
                x = 7 * nr_ml/100.0;}

        else if (denumire_bautura =="vin" and pahar == false)
            {
                if (sticla == "Bordeaux")
                    x = 30;
                else if (sticla == "Bolovanu")
                    x = 25;
            }
        
        else if (denumire_bautura == "bere")
            {
                if (alcool == true)
                    x = 12;
                else
                    x = 10;
            }
        
        else if (denumire_bautura == "apa")
            x = 7;
        Meniu :: set_pret(x);
    }

    void set_denumire_bautura(string s) { denumire_bautura = s;};
    string get_denumire_bautura() {return denumire_bautura;};

    friend ostream& operator<< (ostream &out, Bauturi &bautura);
    friend istream& operator>> (istream &in, Bauturi &bautura);
    Bauturi& operator=(const Bauturi &);

};

Bauturi :: Bauturi()
{

}
Bauturi :: Bauturi(double pret, string denumire_bautura) : Meniu (pret), denumire_bautura(denumire_bautura)
{

}

Bauturi :: Bauturi(const Bauturi &bautura)
{
    pret = bautura.pret;
    denumire_bautura = bautura.denumire_bautura;
    sticla = bautura.sticla;
    pahar = bautura.pahar;
    culoare = bautura.culoare;
    nr_ml = bautura.nr_ml;
    alcool = bautura.alcool;
}

Bauturi :: ~Bauturi()
{   
    pret = 0;
    denumire_bautura = "";
    sticla = "";
    culoare = "";
    pahar = false;
    nr_ml = 0;
    alcool = false;
}

Bauturi& Bauturi::operator=(const Bauturi &ob)
{
    if(this!=&ob)
    {

        pret = ob.pret;
        denumire_bautura = ob.denumire_bautura;
        
      
    }
    return *this;
}

ostream& operator<< (ostream &out, Bauturi &bautura)
{   if (bautura.denumire_bautura != "")
    {
    out<<"Pentru "<<bautura.denumire_bautura<<" pretul este ";
    out<<bautura.pret<<" lei";
    if(bautura.denumire_bautura == "vin" and bautura.pahar == true)
        out<<" pentru "<<bautura.nr_ml<<" ml";}
    return out;
}

istream& operator>> (istream &in, Bauturi &bautura)
{
    cout<<"Va aduc ceva de baut?\n ";
    string s;
    in>>s;
    if (s=="da")
    {
    cout<<"Vin, bere sau apa?\n";
    in>>bautura.denumire_bautura;
    if(bautura.denumire_bautura == "vin")
    {
        cout<<"La pahar sau sticla?\n ";
        int i;
        in>>s;
        if (s == "pahar")
        {   bautura.pahar == true;
            cout<<"Rosu sau alb?\n";
            in>>s;
            bautura.culoare = s;
            cout<<"Cati ml?\n";
            in>>i;
            bautura.nr_ml = i;
        }
        else if (s=="sticla")
            {  
                cout<<"Bordeaux sau Bolovanu?\n";
                in>>s;
                if (s=="Bordeaux")
                    bautura.sticla = "Bordeaux";
                else
                    bautura.sticla = "Bolovanu";

            }}
    else if (bautura.denumire_bautura == "bere")
        {
            cout<<"Cu alcool sau fara?\n";
            string s;
            in>>s;
            if (s== "cu alcool")
                bautura.alcool = true;
            else
                bautura.alcool = false;
        }
    }
    bautura.set_pret(0);
    return  in;
}

void comanda(Client c)
{
    Ciorba ciorba;
    cin>>ciorba;

}
int main()

{
    int i,x,n,nr;
    cout<<"Cate mese sunt in restaurant?\n";
    cin>>n;
    for (int i=1; i<=n;i++)
    {
        Masa m;
        cout<<"Masa "<<i<<endl;
        cin>>m;

      
        cout<<"Doreste cineva de la aceasta masa sa comande? (Introduceti id-ul persoanei) \n";
        bool comanda = true;
        while ( comanda == true)
        {for(i=0;i<m.nrclienti;i++)
        {cin>>nr;
        if (nr != 0)
            for(i=0;i<m.nrclienti;i++)
                if (m.clienti_masa[i].get_id_client() == nr)
                    {Ciorba c; 
                    cin>>c;
                    string s;
                    s = c.denumire_ciorba;
                    if (c.smantana == true)
                    s = s+ " cu smantana";
                    if (c.ardei ==true)
                    s = s+ " cu ardei";
                    if (c.denumire_ciorba != "") 
                    {m.clienti_masa[i].adauga_comanda(s);
                    m.clienti_masa[i].adauga_nota(c.pret);}
                    
                    FelPrincipal f; 
                    
                    cin>>f;
                    if (f.denumire_fel!="")

                    {
                    m.clienti_masa[i].adauga_comanda(f.denumire_fel);
                    m.clienti_masa[i].adauga_nota(f.pret);}

                    Desert d; 
                    
                    cin>>d;
                    if (d.denumire_desert != "")
                        if (d.denumire_desert=="tort Krantz" or d.denumire_desert=="Inghetata")
                        {m.clienti_masa[i].adauga_comanda(d.denumire_desert);
                        m.clienti_masa[i].adauga_nota(d.pret);}

                    Bauturi b;
                    cin>>b;
                    if (b.denumire_bautura!="")
                    {m.clienti_masa[i].adauga_comanda(b.denumire_bautura);
                    m.clienti_masa[i].adauga_nota(b.pret);}
                    
                    }
                    break; }
                cout<<"Mai doreste cineva sa comande? da/nu\n";
                string s;
                cin>>s;
                if (s=="nu")
                    {comanda = false; break;}
                else cout<<"Introduceti id: ";}
            
        cout<<"Doreste cineva de la aceasta masa nota? \n";
        bool nota = true; int total = 0;
        while (nota == true)
        {string s;
        cin>>s;
        if (s=="da")
        {cout<<"Doriti nota individuala sau pentru toata masa? 0-individuala / 1-totala\n";
            int k;
            cin>>k;
            if (k==0)
            {
            for(i=0;i<m.nrclienti;i++)
            {int nr; cout<<"Introduceti id-ul clientului:";
            cin>>nr;
            if (nr != 0)
            for(i=0;i<m.nrclienti;i++)
                if (m.clienti_masa[i].get_id_client() == nr)
                    {cout<<"Clientul cu id-ul "<<nr<<" a comandat "<<m.clienti_masa[i].get_comanda()<<endl;
                    cout<<"Totalul de plata este: "<<m.clienti_masa[i].get_nota()<<endl;
                    m.clienti_masa[i].set_id_client(0);
                    }}}
            else 
            for(i=0;i<m.nrclienti;i++)
            {
                if (m.clienti_masa[i].get_id_client() <= m.id )
                    total = total + m.clienti_masa[i].get_nota();
            }
        cout<<"Mai doreste cineva nota? da/nu\n";
                string s;
                cin>>s;
                if (s=="nu")
                    {nota = false; cout<<"Va multumesc!\n";break;}
                else cout<<"Introduceti id: ";}
                    
    }}
    
    
}

