#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <map>

using namespace std;

class Person
{
private:
    string name;
    string role;

    // Functie de creat figuranti
    void createExtras()
    {
        ifstream file1;
        file1.open("Membrii.csv");

        if (!file1)
            throw "File does not exist!";
        
        // Testez daca deja i-am creat sa nu ii mai adaug inca o data
        string extra = "figurant";
        bool found_record = false;
        string field_one, field_two;

        while (getline(file1, field_one, ',') && !found_record)
        {
            getline(file1, field_two, '\n');

            if (field_two == extra)
                found_record = true;
        }

        file1.close();

        if (found_record == false)
        {
            int extras = 132;

            // Baza de date pentru nume
            string last_name[15] = {
                "Tanase", "Chitu", "Subtirica", "Onea", "Rosu", "Ungureanu", "Mironescu", "Rusu", "Neagu", "Mazilu", "Sivriu", "Titiriga",
                "Filip", "Mustafa", "Burtoiu"
            };

            // Baza de date pentru prenume
            string first_name[15] = {
                "Theodor", "Cosmin", "Vlad", "Maria", "Ionut", "Cristian", "David", "Sergiu", "Alexandru", "Gabriela", "Bianca", "Tiberiu",
                "Dragos", "Georgiana", "Alina"
            };

            srand(time(0));

            int random_last_name, random_first_name, i;

            ofstream file;
            file.open("Membrii.csv", ios::out | ios::app);

            if (!file)
                throw "File does not exist!";

            // Generare numar random de la 0 la 14 pentru a lua din vectorii de string un nume si un prenume si a-i adauga in fisierul cu toti membrii cast-ului
            for (i = 0; i < extras; i++)
            {
                random_last_name = rand()%15;
                random_first_name = rand()%15;

                file<<last_name[random_last_name]<<' '<<first_name[random_first_name]<<","<<"figurant"<<"\n";
            }

            file.close();
        }
    }

    // Functie de asignat tip de monstru si de a calcula pretul pentru machiaje
    long assignMonster()
    {
        ifstream file1;
        file1.open("Membrii.csv");

        if (!file1)
            throw "File does not exist!";

        // Baza de date pentru monstri
        string monster[5] = {
            "Vampir", "Varcolac", "Sirena", "Clarvazatori", "Om"
        };

        // Vector de frecventa pentru tip de monstru pe care il initializez cu 0
        int number_of_monsters[5], i;
        for (i = 0; i < 5; i++)
            number_of_monsters[i] = 0;

        srand(time(0));

        int nr;

        // Asignare tip monstru random si doar pentru actori, cascadori si figuranti
        while (getline(file1, name, ','))
        {
            getline(file1, role, '\n');

            if (role == "actor" || role == "cascador" || role == "figurant")
            {
                nr = rand()%5;
                number_of_monsters[nr]++;
            }
        }

        // Calcul pret machiaje
        int preturi[5] = {230, 555, 345, 157, 55};

        int pret_monstrii[5];
        long pret_total = 0;

        for (i = 0; i < 5; i++)
        {
            pret_monstrii[i] = preturi[i] * number_of_monsters[i];
            pret_total += pret_monstrii[i];
        }

        return pret_total;
    }

    // Functie pentru asignat diete si de calculat pretul meselor in functie de dieta
    long assignDiet()
    {
        ifstream file1;
        file1.open("Membrii.csv");

        if (!file1)
            throw "File does not exist!";

        // Baza de date pentru dieta
        string diet[3] = {
            "Omnivorous", "Vegetarian", "Flexitarian"
        };

        // Vector de frecventa pentru tip de dieta pe care il initializez cu 0
        int number_of_people[3];
        int i;
        for (i = 0; i < 3; i++)
            number_of_people[i] = 0;

        srand(time(0));

        int nr;

        // Asignare tip dieta random si contorizat fiecare persoana ce fel de dieta are
        while (getline(file1, name, ','))
        {
            getline(file1, role, '\n');

                nr = rand()%3;
                number_of_people[nr]++;
        }

        // Calcul pret mese
        int pret_per_dieta[3] = {40, 33, 46};
        long pret_total = 0;

        for (i = 0; i < 3; i++)
            pret_total += pret_per_dieta[i] * number_of_people[i];

        return pret_total;
    }

    // Functie pentru calculat pretul pentru camerele din hotel
    long camere()
    {
        ifstream file;
        file.open("Membrii.csv");

        if (!file)
            throw "File does not exist!";

        // Contorizare figuranti si cast initial
        int nr_figuranti = 0;
        int nr_cast_initial = 0;

        while (getline(file, name, ','))
        {
            getline(file, role, '\n');

            if (role == "figurant")
                nr_figuranti++;
            else nr_cast_initial++;
        }

        // Calcul impartire pe camere
        int nr_camere_de_2;
        int nr_camere_de_3;

        nr_camere_de_2 = nr_cast_initial/2;
        if (nr_cast_initial%2 != 0)
            nr_camere_de_2++;

        nr_camere_de_3 = nr_figuranti/3;
        if (nr_figuranti%3 != 0)
            nr_camere_de_3++;

        // Calcul pret camere
        int pret_camera_de_2 = 350;
        int pret_camera_de_3 = 420;

        int pret_final_camera_de_2 = pret_camera_de_2 * nr_camere_de_2;
        int pret_final_camera_de_3 = pret_camera_de_3 * nr_camere_de_3;

        long pret_total = pret_final_camera_de_2 + pret_final_camera_de_3;

        return pret_total;

        file.close();
    }

public:
    // Constructor pentru a crea caracterele extra
    Person()
    {
        try
        {
            createExtras();
        }
        catch(string msg)
        {
            cerr<<msg<<endl;
        }
    }

    // Functii get pentru preturi
    long getMakeup()
    {
        return assignMonster();
    }

    long getFood()
    {
        return assignDiet();
    }

    long getRooms()
    {
        return camere();
    }
};

class TVShow
{
private:
    int places_per_bus = 50;
    int price_per_trip = 0;
    int number_of_people = numarPersoane();
    int cost_of_a_bus = 5680;

    // Contorizare numar de persoane totale participante
    int numarPersoane()
    {
        ifstream file;
        file.open("Membrii.csv");

        if (!file)
            throw "File does not exist!";

        int nr_persoane = 0;
        string line;

        while(getline(file, line))
            nr_persoane++;

        return nr_persoane;
    }

    // Functie pentru calcul drum dus-intors cu autocarul
    long busCost()
    {
        int number_of_buses = number_of_people/places_per_bus;

        if (number_of_people%places_per_bus != 0)
            number_of_buses++;

        price_per_trip = number_of_buses * cost_of_a_bus;

        return 2*price_per_trip;
    }

    // Functie de creare meniu pe 3 zile pentru fiecare tip de dieta
    void menu()
    {
        // Baza de date pentru fiecare fel de mancare la fiecare dieta
        string supa_omnivori[3] = {
            "Ciorba radauteana", "Supa cu galuste", "Supa de pui a la grec"
        };
        string supa_vegetarieni[3] = {
            "Supa crema de legume", "Ciorba de legume", "Ciorba de loboda"
        };
        string supa_flexitarieni[3] = {
            "Supa de cartofi cu ardei copt", "Ciorba de rosii", "Ciorba de peste"
        };

        string fel_omnivori[3] = {
            "Musaca", "Pui cu lamaie si cartofi la cuptor", "Penne quatro formaggi"
        };
        string fel_vegetarieni[3] = {
            "Tocana de cartofi", "Legume la cuptor cu halloumi la gratar", "Ciuperci sote"
        };
        string fel_flexitarieni[3] = {
            "Peste la gratar", "Pastrav la cuptor", "Legume tempura si branza la gratar"
        };

        string desert_omnivori[3] = {
            "Lava cake", "Cheesecake cu lamaie", "Alba ca zapada"
        };
        string desert_vegetarieni[3] = {
            "Placinta de mere", "Salam de biscuiti", "Prajitura cu gem"
        };
        string desert_flexitarieni[3] = {
            "Cornulete cu nuca", "Clatite", "Galuste cu prune"
        };

        ofstream file("Meniu.csv");

        file<<"Omnivori"<<","<<"Vegetarieni"<<","<<"Flexitarieni"<<"\n";

        // Afisare in fisier
        int i;
        for (i = 0; i < 3; i++)
            file<<"Ziua "<<i+1<<","<<"Ziua "<<i+1<<","<<"Ziua "<<i+1<<"\n"<<supa_omnivori[i]<<","<<supa_vegetarieni[i]<<","<<supa_flexitarieni[i]
            <<"\n"<<fel_omnivori[i]<<","<<fel_vegetarieni[i]<<","<<fel_flexitarieni[i]<<"\n"<<desert_omnivori[i]<<","<<desert_vegetarieni[i]
            <<","<<desert_flexitarieni[i]<<"\n";

        file.close();
    }

    // Functie pentru calculat pretul bauturii (apa, cafea, suc)
    float bautura()
    {
        ifstream file;
        file.open("Membrii.csv");

        if (!file)
            throw "File does not exist!";

        // Contorizare numar persoane
        int nr_persoane = 0;
        string line;
        while (getline(file, line))
            nr_persoane++;

        // Calcul bautura (apa, cafea, suc)
        float litrii_apa = nr_persoane * 1;
        float litrii_cafea = nr_persoane * 0.5;
        float litrii_suc = nr_persoane * 0.8;

        float pret_apa = 3;
        float pret_cafea = 30;
        float pret_suc = 4;

        float pret_final_apa = pret_apa * litrii_apa;
        float pret_final_cafea = pret_cafea * litrii_cafea;
        float pret_final_suc = pret_suc * litrii_suc;

        float pret_total = pret_final_apa + pret_final_cafea + pret_final_suc;

        return pret_total;
    }

    // Functie de calculat pretul pentru inchirierea castelului
    long inchiriereSpatiu(int zile)
    {
        // Calcul
        int cost_per_zi = 10000;
        int numar_de_reduceri = zile/10;
        int reducere = 2;

        reducere *= numar_de_reduceri;

        return (numar_de_reduceri*cost_per_zi*10-cost_per_zi*10*reducere/100);
    }

public:
    // Constructor pentru creare meniu
    TVShow()
    {
        try
        {
            menu();
        }
        catch(string msg)
        {
            cerr<<msg<<endl;
        }
    }

    // Functii get pentru preturi
    long getBus()
    {
        return busCost();
    }

    float getDrinks()
    {
        return bautura();
    }

    long getInchiriere(int zile)
    {
        return inchiriereSpatiu(zile);
    }
};

// Dictionar roman-englez pentru rolurile fiecarui membru
map<string, string> translations {
        {"director", "director"},
        {"scriitor", "writer"},
        {"actor", "actor"},
        {"producator", "producer"},
        {"muzica", "music"},
        {"cinematografie", "cinematography"},
        {"editor", "editor"},
        {"distribuitor", "caster"},
        {"productie", "production"},
        {"artist", "artist"},
        {"set", "set"},
        {"costum", "costume"},
        {"makeup", "makeup"},
        {"asistentDirector", "directorAssistant"},
        {"sunetist", "sound"},
        {"efecte", "effects"},
        {"cascador", "stunt"},
        {"electrician", "electrical"},
        {"animator", "animation"},
        {"asistentCast", "castAssistant"},
        {"imbracaminte", "wardrobe"},
        {"editorial", "editorial"},
        {"locatie", "location"},
        {"script", "script"},
        {"transport", "transport"},
        {"aditional", "additional"},
        {"figurant", "extra"}
};

// Functie de traducere in functie de dictionar
string translate(string word)
{
    if (translations.count(word))
        return translations[word];
    return word;
}

// Functie de tradus csv numit Membrii
void translateMembrii()
{
    ifstream file;
    file.open("Membrii.csv");

    if (!file)
        throw "File does not exist!";

    ofstream file1;
    file1.open("Members.csv");

    if (!file1)
        throw "File does not exist!";

    string name, role;

    while (getline(file, name, ','))
    {
        getline(file, role, '\n');

        file1<<name<<","<<translate(role)<<"\n";
    }

    file.close();
    file1.close();
}

// Functie de tradus csv numit Meniu
void translateMeniu()
{
    ofstream file;
    file.open("Menu.csv");

    if (!file)
        throw "File does not exist!";

    file<<"Omnivorous"<<","<<"Vegetarian"<<","<<"Flexitarian"<<"\n";
    file<<"Day 1"<<","<<"Day 1"<<","<<"Day 1"<<"\n";
    file<<"Sour chicken soup with garlic and cream"<<","<<"Creamy vegetable soup"<<","<<"Potato soup with roasted pepper"<<"\n";
    file<<"Moussaka"<<","<<"Stewed potatoes"<<","<<"Grilled fish"<<"\n";
    file<<"Lava cake"<<","<<"Apple pie"<<","<<"Walnut horn pastries"<<"\n";
    file<<"Day 2"<<","<<"Day 2"<<","<<"Day 2"<<"\n";
    file<<"Dumpling soup"<<","<<"Vegetable soup"<<","<<"Tomato soup"<<"\n";
    file<<"Chicken with lemon and baked potatoes"<<","<<"Baked vegetables with grilled halloumi"<<","<<"Baked trout"<<"\n";
    file<<"Lemon cheesecake"<<","<<"Cookie salami"<<","<<"Pancakes"<<"\n";
    file<<"Day 3"<<","<<"Day 3"<<","<<"Day 3"<<"\n";
    file<<"Greek-style chicken soup"<<","<<"Nettle soup"<<","<<"Fish soup"<<"\n";
    file<<"Penne quatro formaggi"<<","<<"Sauteed mushrooms"<<","<<"Tempura vegetables and grilled cheese"<<"\n";
    file<<"Snow white"<<","<<"Cake with jame"<<","<<"Plum dumplings"<<"\n";

    file.close();
}

// Functie de tradus csv numit Costuri
void translateCosturi()
{
    ofstream file;
    file.open("Costs.csv");

    if (!file)
        throw "File does not exist!";

    file<<"30 days"<<","<<"45 days"<<","<<"60 days"<<","<<"100 days"<<"\n";
    file<<"Transport - 44164.144531$"<<","<<"Transport - 44164.144531$"<<","<<"Transport - 44164.144531$"<<","<<"Transport - 44164.144531$"<<"\n";
    file<<"Accommodation - 970172.750000$"<<","<<"Accommodation - 1455259.125000$"<<","<<"Accommodation - 1940345.500000$"<<","<<"Accommodation - 3233909.250000$"<<"\n";
    file<<"Makeup - 356572.343750$"<<","<<"Makeup - 534858.500000$"<<","<<"Makeup - 713144.687500$"<<","<<"Makeup - 1188574.500000$"<<"\n";
    file<<"Food and drinks - 347403.875000$"<<","<<"Food and drinks - 521105.812500$"<<","<<"Food and drinks - 694807.750000$"<<","<<"Food and drinks - 1158012.875000$"<<"\n";
    file<<"Space rental - 63498.917969$"<<","<<"Space rental - 84665.226562$"<<","<<"Space rental - 126997.835938$"<<","<<"Space rental - 211663.062500$"<<"\n";

    file.close();
}

int main()
{
    TVShow tv;
    Person p;

    ofstream file;
    file.open("Costuri.csv");

    try
    {
        if (!file)
        throw "File does not exist!";
    }
    catch(string msg)
    {
        cerr<<msg<<endl;
    }

    // Calcul pentru perioade diferite si conversie din lei in dolari
    long mancare = p.getFood();
    long bautura = tv.getDrinks();

    float dolar = 4.63;

    file<<"30 de zile"<<","<<"45 de zile"<<","<<"60 de zile"<<","<<"100 de zile"<<"\n";
    try{file<<fixed<<"Transport - "<<tv.getBus()/dolar<<"$"<<","<<"Transport - "<<tv.getBus()/dolar<<"$"<<","<<"Transport - "<<tv.getBus()/dolar<<"$"<<","<<"Transport - "<<tv.getBus()/dolar<<"$"<<"\n";} catch(string msg) {cerr<<msg<<endl;}
    try{file<<fixed<<"Cazare - "<<30 * p.getRooms()/dolar<<"$"<<","<<"Cazare - "<<45 * p.getRooms()/dolar<<"$"<<","<<"Cazare - "<<60 * p.getRooms()/dolar<<"$"<<","<<"Cazare - "<<100 * p.getRooms()/dolar<<"$"<<"\n";} catch(string msg) {cerr<<msg<<endl;}
    try{file<<fixed<<"Machiaj - "<<30 * p.getMakeup()/dolar<<"$"<<","<<"Machiaj - "<<45 * p.getMakeup()/dolar<<"$"<<","<<"Machiaj - "<<60 * p.getMakeup()/dolar<<"$"<<","<<"Machiaj - "<<100 * p.getMakeup()/dolar<<"$"<<"\n";} catch(string msg) {cerr<<msg<<endl;}
    try{file<<fixed<<"Mancare si apa - "<<30 * (mancare + bautura)/dolar<<"$"<<","<<"Mancare si apa - "<<45 * (mancare + bautura)/dolar<<"$"<<","<<"Mancare si apa - "<<60 * (mancare + bautura)/dolar<<"$"<<","<<"Mancare si apa - "<<100 * (mancare + bautura)/dolar<<"$"<<"\n";} catch(string msg) {cerr<<msg<<endl;}
    try{file<<fixed<<"Inchiriere spatiu - "<<tv.getInchiriere(30)/dolar<<"$"<<","<<"Inchiriere spatiu - "<<tv.getInchiriere(45)/dolar<<"$"<<","<<"Inchiriere spatiu - "<<tv.getInchiriere(60)/dolar<<"$"<<","<<"Inchiriere spatiu - "<<tv.getInchiriere(100)/dolar<<"$"<<"\n";} catch(string msg) {cerr<<msg<<endl;}

    file.close();

    translateMembrii();
    translateMeniu();
    translateCosturi();

    return 0;
}
