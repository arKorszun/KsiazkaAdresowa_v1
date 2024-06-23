#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <cstdio>

using namespace std;

struct Adresat
{
    int id, idUzytkownika;
    string imie, nazwisko, nrTelefonu, email, adres;
};

struct Uzytkownik
{
    int id;
    string login, haslo;
};

int zliczIloscLiniWPliku();

bool sprawdzCzyLoginJestWBazie (vector <Uzytkownik> uzytkownicy, string login);

void pobierzDaneUzytkownikowDoWektora(vector <Uzytkownik> &uzytkownicy);

void zapiszUzytkownikaDoPliku(Uzytkownik uzytkownik);

void rejestrujNowegoUzytkownika (vector <Uzytkownik> &uzytkownicy);

int zalogujUzytkownika (vector <Uzytkownik> uzytkownicy);

void nadpiszUzytkownikowWPliku(vector <Uzytkownik> &uzytkownicy);

void zmienHasloUzytkownika(vector <Uzytkownik> &uzytkownicy, int zalogowanyUzytkownik);

void pobierzDaneAdresatowDoWektora(vector <Adresat> &adresaci, int zalogowanyUzytkownik);

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);

void dodajAdresataDoKsiazki (vector <Adresat> &adresaci, int zalogowanyUzytkownik);

void przeslijJednegoAdresataDoPliku(Adresat adresat);

int pobierzIdOstatniegoAdresataZPliku ();

void wyszukajAdresataPoNazwisku(vector <Adresat> adresaci);

void wyszukajAdresataPoImieniu(vector <Adresat> adresaci);

void wyswietlWszystkichAdresatow(vector <Adresat> adresaci);

void nadpiszListeAdresatowWPlikuPoEdycjiAdresata (Adresat adresatPoEdycji, int idAdresataDoEdycji);

bool czyAdresatIstniejeWBazie (vector <Adresat> adresaci, int idAdresata);

void wyswietlWybranegoAdresata (vector <Adresat> adresaci, int idAdresata);

void usunAdresata(vector <Adresat> &adresaci);

void edytujAdresata(vector <Adresat> &adresaci);

int main()
{

    vector <Adresat> adresaci;
    vector <Uzytkownik> uzytkownicy;
    char wybor;
    int zalogowanyUzytkownik = 0;

    pobierzDaneUzytkownikowDoWektora(uzytkownicy);

    while(1)
    {
        cout << "     >>> MENU GLOWNE <<<     " << endl;
        cout << "-----------------------------" << endl;
        cout << "1. Rejestracja" << endl;
        cout << "2. Logowanie" << endl;
        cout << "9. Zamknij program" << endl;
        cout << "-----------------------------" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;
        system("cls");

        if (wybor == '1')
        {
            rejestrujNowegoUzytkownika(uzytkownicy);
        }
        else if (wybor == '2')
        {
            zalogowanyUzytkownik = zalogujUzytkownika(uzytkownicy);
            while(1)
            {
                pobierzDaneAdresatowDoWektora(adresaci, zalogowanyUzytkownik);
                system("cls");
                cout << "----------MENU UZYTKOWNIKA----------" << endl << endl;
                cout << "1. Dodaj Adresata do Ksiazki" << endl;
                cout << "2. Wyszukaj Adresata w Ksiazce" << endl;
                cout << "3. Wyswietl wszystkich Adresatow" << endl;
                cout << "4. Usun adresata" << endl;
                cout << "5. Edytuj adresata" << endl;
                cout << "6. Zmien haslo" << endl;
                cout << "9. Wyloguj sie" << endl;
                cin>>wybor;

                if (wybor == '1')
                {
                    dodajAdresataDoKsiazki(adresaci, zalogowanyUzytkownik);

                }
                if (wybor == '2')
                {
                    system("cls");
                    cout<<"Wyszukiwanie"<<endl;
                    cout<<"1. Wyszukaj po nazwisku"<<endl;
                    cout<<"2. Wyszukaj po imieniu"<<endl;
                    cout<<"9. Wroc do menu glownego"<<endl;
                    cin>>wybor;
                    if (wybor == '1')
                    {
                        wyszukajAdresataPoNazwisku(adresaci);
                    }
                    if (wybor == '2')
                    {
                        wyszukajAdresataPoImieniu(adresaci);
                    }
                    if (wybor == '9')
                    {
                        continue;
                    }
                }
                if (wybor == '3')
                {
                    wyswietlWszystkichAdresatow(adresaci);
                }
                if (wybor == '4')
                {
                    usunAdresata(adresaci);
                }
                if (wybor == '5')
                {
                    edytujAdresata(adresaci);
                }
                if (wybor == '6')
                {
                    zmienHasloUzytkownika(uzytkownicy,zalogowanyUzytkownik);
                }
                if (wybor == '9')
                {
                    cout << "Do widzenia!" ;
                    Sleep(500);
                    system("cls");
                    break;
                }
            }
        }
        else if (wybor == '9')
        {
            cout << "Do widzenia!" ;
            Sleep(500);
            exit(0);
        }
    }
    return 0;
}

int zliczIloscLiniWPliku(string nazwaPliku)
{
    string line;
    int count = 0;
    fstream plik;
    plik.open(nazwaPliku,ios::in);
    while(getline(plik, line))
        count++;
    plik.close();
    return count;
}

bool sprawdzCzyLoginJestWBazie (vector <Uzytkownik> uzytkownicy, string login)
{
    for (Uzytkownik uzytkownik : uzytkownicy )
    {
        if (uzytkownik.login == login )
        {
            return true;
        }
    }
    return false;
}

void pobierzDaneUzytkownikowDoWektora(vector <Uzytkownik> &uzytkownicy)
{
    int iloscRekordow = 0;
    Uzytkownik uzytkownik;
    string pomocID;
    string nazwaPliku = "Uzytkownicy.txt";
    iloscRekordow = (zliczIloscLiniWPliku(nazwaPliku));
    fstream plik;
    plik.open(nazwaPliku,ios::in);
    if(plik.good() == false)
    {
        cout << "Plik nie istnieje!" << endl;
    }
    for (int i=0; i<iloscRekordow; i++)
    {
        getline(plik,pomocID,'|');
        uzytkownik.id=stoi(pomocID);
        getline(plik,uzytkownik.login,'|');
        getline(plik,uzytkownik.haslo,'|');
        uzytkownicy.push_back(uzytkownik);
    }
    plik.close();
}

void zapiszUzytkownikaDoPliku(Uzytkownik uzytkownik)
{
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out|ios::app);
    if (plik.good() == true)
    {
        plik << uzytkownik.id << '|' << uzytkownik.login << '|' << uzytkownik.haslo << '|' << '\n';
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku, dane nie zostaly zapisane" << endl;
        system("pause");
    }
}

void rejestrujNowegoUzytkownika (vector <Uzytkownik> &uzytkownicy)
{
    string login="", haslo="";
    Uzytkownik uzytkownik;
    bool czyLoginJestZajety = false;

    do
    {
        cout << "------Rejestracja------" << endl << endl;
        cout << "Podaj login: ";
        cin >> login;
        czyLoginJestZajety = sprawdzCzyLoginJestWBazie(uzytkownicy, login);
        if (czyLoginJestZajety == false)
        {
            uzytkownik.login = login;
            czyLoginJestZajety = false;
        }
        else
        {
            cout << "Podany login jest zajety, podaj inne dane!" << endl << endl;
            Sleep(800);
            system("cls");
        }
    }
    while (czyLoginJestZajety == true);
    cout << "Podaj haslo: ";
    cin >> haslo;
    uzytkownik.haslo = haslo;
    if (uzytkownicy.empty())
    {
        uzytkownik.id = 1;
    }
    else
    {
        uzytkownik.id = uzytkownicy.back().id + 1;
    }
    uzytkownicy.push_back(uzytkownik);
    zapiszUzytkownikaDoPliku(uzytkownik);
    cout << endl << "Rejestracja pomyslna!" << endl;
    Sleep(800);
    system("cls");
}

int zalogujUzytkownika (vector <Uzytkownik> uzytkownicy)
{
    string login="", haslo="";
    int licznikProb = 3;
    int zalogowanyUzytkownik;
    bool czyLoginJestPoprawny = false;
    bool czyDaneLogowaniaSaPoprawne = false;

    do
    {
        cout << endl << "Podaj login: ";
        cin >> login;
        czyLoginJestPoprawny = sprawdzCzyLoginJestWBazie(uzytkownicy, login);
        if (czyLoginJestPoprawny == false)
        {
            cout << "Brak takiego uzytkownika, podaj prawidlowy login" << endl;
            Sleep(800);
            system("cls");
        }
    }
    while (czyLoginJestPoprawny == false);

    do
    {
        cout << "Podaj haslo: ";
        cin >> haslo;
        for (Uzytkownik uzytkownik : uzytkownicy )
        {
            if (uzytkownik.login == login && uzytkownik.haslo == haslo)
            {
                czyDaneLogowaniaSaPoprawne = true;
                zalogowanyUzytkownik = uzytkownik.id;
                cout << endl << "Witaj " << login << "!" << endl;
                Sleep(1000);
                system("cls");
                return zalogowanyUzytkownik;
            }
        }
        if (czyDaneLogowaniaSaPoprawne == false)
        {
            licznikProb-=1;
            cout << "Podales bledne haslo! Pozostala ilosc prob: " << licznikProb << endl;
        }
    }
    while ( licznikProb != 0);
    system("cls");
    cout << endl << "Trzykrotnie podales bledne haslo! nastapi powrot do Menu Glownego" << endl;
    Sleep(1000);
    return 0;

}

void nadpiszUzytkownikowWPliku(vector <Uzytkownik> &uzytkownicy)
{
    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out);
    if (plik.good() == true)
    {
        for (auto uzytkownik : uzytkownicy)
            plik << uzytkownik.id<< '|' << uzytkownik.login << '|' << uzytkownik.haslo << '|' << '\n';
        plik.close();
    }
    else
    {
        cout << endl << "Nie udalo sie otworzyc pliku, dane nie zostaly zapisane" << endl;
        system("pause");
    }
}

void zmienHasloUzytkownika(vector <Uzytkownik> &uzytkownicy, int zalogowanyUzytkownik)
{
    string haslo;
    bool czyHasloJestPoprawne = false;

    cout << "Podaj stare haslo: ";
    cin >> haslo;
    for (Uzytkownik uzytkownik : uzytkownicy )
    {
        if (uzytkownik.id == zalogowanyUzytkownik && uzytkownik.haslo == haslo)
        {
            czyHasloJestPoprawne = true;
        }
    }
    if (czyHasloJestPoprawne)
    {
        cout << "Podaj nowe haslo: ";
        cin >> haslo;


        for(vector <Uzytkownik> :: iterator itr = uzytkownicy.begin() ; itr != uzytkownicy.end() ; itr++)
        {
            if (itr->id == zalogowanyUzytkownik)
            {
                itr->haslo = haslo;
            }
        }
        nadpiszUzytkownikowWPliku(uzytkownicy);
        cout << "Haslo pomyslnie zmienione!";
        Sleep(800);
    }
    else
    {
        cout << "Haslo niepoprawne!" << endl;
        cout << "Powrot do Menu Uzytkownika" << endl;
        Sleep(800);
    }


}

void pobierzDaneAdresatowDoWektora(vector <Adresat> &adresaci, int zalogowanyUzytkownik)
{
    int iloscRekordow = 0, idUzytkownikaLiczba = 0;
    Adresat adresat;
    string idAdresata, idUzytkownika, imie, nazwisko, email, nrTelefonu, adres ;
    string nazwaPliku = "Adresaci.txt";
    iloscRekordow = (zliczIloscLiniWPliku(nazwaPliku));
    fstream plik;
    adresaci.clear(); // czysci wektor aby pobrac tylko adresatow zalogowanego uzytkownika
    plik.open(nazwaPliku,ios::in);
    if(plik.good() == false)
    {
        cout << "Plik nie istnieje!" << endl;
    }
    for (int i=0; i<iloscRekordow; i++)
    {
        getline(plik,idAdresata,'|');
        getline(plik,idUzytkownika,'|');
        getline(plik,imie,'|');
        getline(plik,nazwisko,'|');
        getline(plik,email,'|');
        getline(plik,nrTelefonu,'|');
        getline(plik,adres,'|');
        idUzytkownikaLiczba = stoi(idUzytkownika);

        if (idUzytkownikaLiczba == zalogowanyUzytkownik)
        {
            adresat.id = stoi(idAdresata);
            adresat.idUzytkownika = idUzytkownikaLiczba;
            adresat.imie = imie;
            adresat.nazwisko = nazwisko;
            adresat.email = email;
            adresat.nrTelefonu = nrTelefonu;
            adresat.adres = adres;
            adresaci.push_back(adresat);
        }
    }
    plik.close();
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst)
{
    if (!tekst.empty())
    {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

void przeslijJednegoAdresataDoPliku(Adresat adresat)
{
    fstream plik;
    plik.open("Adresaci.txt",ios::out|ios::app);
    if (plik.good() == true)
    {
        plik << adresat.id << '|' << adresat.idUzytkownika << '|' << adresat.imie << '|' << adresat.nazwisko << '|' << adresat.email << '|' << adresat.nrTelefonu << '|' << adresat.adres << '|'  << '\n';
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku, dane nie zostaly zapisane" << endl;
        system("pause");
    }
}

int pobierzIdOstatniegoAdresataZPliku ()
{
    int nrOstatniejLini = 0;
    string pobranaWartosc = "", idOstatniegoAdresataTekst = "";
    int idOstatniegoAdresata;
    string nazwaPliku = "Adresaci.txt";
    nrOstatniejLini = zliczIloscLiniWPliku (nazwaPliku);
    fstream plik;
    plik.open(nazwaPliku,ios::in);
    for (int i = 0; i < nrOstatniejLini; i++)
    {
        getline(plik, pobranaWartosc);
    }
    plik.close();

    for (size_t i = 0; i < pobranaWartosc.length(); i++)
    {
        if (pobranaWartosc[i] == '|') break;
        idOstatniegoAdresataTekst+=pobranaWartosc[i];
    }
    idOstatniegoAdresata = stoi(idOstatniegoAdresataTekst);
    return idOstatniegoAdresata;
}

void dodajAdresataDoKsiazki (vector <Adresat> &adresaci, int zalogowanyUzytkownik)
{
    string imie,nazwisko,nrTelefonu,email,adres;
    Adresat adresat;

    system("cls");
    cout << "Dodawanie nowej osoby do ksiazki"<<endl;
    cout << "Podaj imie: ";
    cin >> imie;
    cout << "Podaj nazwisko: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu: ";
    cin.sync();
    getline(cin,nrTelefonu);
    cout << "Podaj email: ";
    cin >> email;
    cout << "Podaj adres: ";
    cin.clear();
    cin.sync();
    getline(cin,adres);
    if (adresaci.empty())
    {
        adresat.id = 1;
    }
    else
    {
        int idOstatniegoAdresata = pobierzIdOstatniegoAdresataZPliku();
        adresat.id = idOstatniegoAdresata + 1;
    }
    adresat.idUzytkownika = zalogowanyUzytkownik;
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imie);
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwisko);
    adresat.email = email;
    adresat.nrTelefonu = nrTelefonu;
    adresat.adres = adres;
    adresaci.push_back(adresat);

    przeslijJednegoAdresataDoPliku(adresat);

    cout << "Dodano nowy wpis do ksiazki!";
    Sleep(1000);
}

void wyszukajAdresataPoNazwisku(vector <Adresat> adresaci)
{
    string szukaneNazwisko;
    bool czyAdresatIstnieje = false;
    if (!adresaci.empty())
    {
        cout << "Podaj nazwisko: ";
        cin >> szukaneNazwisko;
        system("cls");
        cout << "Adresaci o nazwisku: "<<szukaneNazwisko<<endl<<endl;

        for (Adresat adresat : adresaci)
        {
            if (adresat.nazwisko == szukaneNazwisko)
            {
                cout << adresat.id << endl;
                cout << adresat.imie << endl;
                cout << adresat.nazwisko << endl;
                cout << adresat.email << endl;
                cout << adresat.nrTelefonu << endl;
                cout << adresat.adres << endl << endl;
                czyAdresatIstnieje = true;
            }
        }
        if (czyAdresatIstnieje == false)
        {
            cout << endl << "Nie znaleziono w ksiazce nikogo o podanym nazwisku" << endl;
            Sleep(1000);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
        Sleep(1000);
    }
    cout <<"Nacisnij dowolny klawisz aby wrocic do menu glownego" << endl;
    system("pause");
}

void wyszukajAdresataPoImieniu(vector <Adresat> adresaci)
{
    string szukaneImie;
    bool czyAdresatIstnieje = false;

    if (!adresaci.empty())
    {
        cout << "Podaj imie: ";
        cin >> szukaneImie;
        system("cls");
        cout << "Adresaci o imieniu: "<<szukaneImie << endl << endl;
        for (Adresat adresat : adresaci)
        {
            if (adresat.imie == szukaneImie)
            {
                cout << adresat.id << endl;
                cout << adresat.imie << endl;
                cout << adresat.nazwisko << endl;
                cout << adresat.email << endl;
                cout << adresat.nrTelefonu << endl;
                cout << adresat.adres << endl << endl;
                czyAdresatIstnieje = true;
            }
        }
        if (czyAdresatIstnieje == false)
        {
            cout << endl << "Nie znaleziono w Ksiazce nikogo o podanym imieniu" << endl;
            Sleep(1000);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
        Sleep(1000);
    }
    cout<<"Nacisnij dowolny klawisz aby wrocic do menu glownego" << endl;
    system("pause");
}

void wyswietlWszystkichAdresatow(vector <Adresat> adresaci)
{
    system("cls");


    cout << "                  Ksiazka Adresowa" << endl;
    cout << "--------------------------------------------------------" << endl << endl;

    if (!adresaci.empty())
    {
        for (Adresat adresat : adresaci)
        {
            cout << "Id             " << adresat.id << endl;
            cout << "Imie           " << adresat.imie << endl;
            cout << "Nazwisko       " << adresat.nazwisko << endl;
            cout << "Email          " << adresat.email << endl;
            cout << "Nr.telefonu    " << adresat.nrTelefonu << endl;
            cout << "Adres          " << adresat.adres << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    cout << "Nacisnij dowolny klawisz aby wrocic do menu glownego" << endl;
    system("pause");
}

void nadpiszListeAdresatowWPlikuPoEdycjiAdresata (Adresat adresatPoEdycji, int idAdresataDoEdycji)
{
    string nazwaPliku = "Adresaci.txt";
    Adresat adresat;
    string idAdresata, idUzytkownika, imie, nazwisko, email, nrTelefonu, adres ;
    int iloscRekordow, idAdresataLiczba;
    fstream plikAdresaci, plikTymczasowy;

    iloscRekordow = (zliczIloscLiniWPliku(nazwaPliku));
    plikAdresaci.open("Adresaci.txt",ios::in);
    plikTymczasowy.open("Adresaci_tymczasowy.txt",ios::out);
    if (plikAdresaci.good() == true && plikTymczasowy.good())
    {
        for (int i=0; i<iloscRekordow; i++)
        {
            getline(plikAdresaci,idAdresata,'|');
            getline(plikAdresaci,idUzytkownika,'|');
            getline(plikAdresaci,imie,'|');
            getline(plikAdresaci,nazwisko,'|');
            getline(plikAdresaci,email,'|');
            getline(plikAdresaci,nrTelefonu,'|');
            getline(plikAdresaci,adres,'|');
            idAdresataLiczba = stoi(idAdresata);

            if (idAdresataLiczba == idAdresataDoEdycji)
            {
                plikTymczasowy << '\n' << adresatPoEdycji.id << '|' << adresatPoEdycji.idUzytkownika << '|' << adresatPoEdycji.imie << '|' << adresatPoEdycji.nazwisko << '|' << adresatPoEdycji.email << '|' << adresatPoEdycji.nrTelefonu << '|' << adresatPoEdycji.adres << '|';
            }
            else
            {
                plikTymczasowy << idAdresata << '|' << idUzytkownika << '|' << imie << '|' << nazwisko << '|' << email << '|' << nrTelefonu << '|' << adres << '|';
            }
        }
        plikAdresaci.close();
        plikTymczasowy.close();
    }
    else
    {
        cout << endl << "Nie udalo sie otworzyc pliku, dane nie zostaly zapisane" << endl;
        system("pause");
    }
    remove("Adresaci.txt");
    rename("Adresaci_tymczasowy.txt","Adresaci.txt");

}

bool czyAdresatIstniejeWBazie (vector <Adresat> adresaci, int idAdresata)
{
    for(vector <Adresat> :: iterator itr = adresaci.begin() ; itr != adresaci.end() ; itr++)
    {
        if (itr->id == idAdresata)
        {
            return true;
            if(itr == adresaci.end())break;
        }
    }
    return false;
}

void wyswietlWybranegoAdresata (vector <Adresat> adresaci, int idAdresata)
{
    for (Adresat adresat : adresaci)
        {
            if (adresat.id == idAdresata)
            cout << endl;
            cout << "Id             " << adresat.id << endl;
            cout << "Imie           " << adresat.imie << endl;
            cout << "Nazwisko       " << adresat.nazwisko << endl;
            cout << "Email          " << adresat.email << endl;
            cout << "Nr.telefonu    " << adresat.nrTelefonu << endl;
            cout << "Adres          " << adresat.adres << endl << endl;
        }
}

void usunAdresata(vector <Adresat> &adresaci)
{
    int idAdresataDoUsuniecia;
    char wybor;
    bool czyWskazanyAdresatIstnieje = false;

    if (!adresaci.empty())
    {
        while (czyWskazanyAdresatIstnieje == false)
        {
            system("cls");
            cout << "Podaj numer Id adresata do usuniecia: ";
            cin >> idAdresataDoUsuniecia;
            czyWskazanyAdresatIstnieje = czyAdresatIstniejeWBazie(adresaci,idAdresataDoUsuniecia);
            if (czyWskazanyAdresatIstnieje == false)
            {
                cout << endl << "Brak w bazie adresata z podanym Id, podaj poprawny numer!";
                Sleep(1000);
            }
        }
        cout << "Czy napewno chcesz usunac adresata? Wcisnij klawisz t aby potwierdzic";
        wybor = getch();
        switch (wybor)
        {
        case 't':
        {
            for(vector <Adresat> :: iterator itr = adresaci.begin() ; itr != adresaci.end() ; itr++)
            {
                if (itr->id == idAdresataDoUsuniecia)
                {
                    adresaci.erase(itr);
                    if(itr == adresaci.end())break;
                }
            }
            //nadpiszListeAdresatowWPliku (adresaci);
            cout << endl << "Kontakt pomyslnie usuniety!";
            Sleep(1000);
            break;
        }
        default:
            cout << endl << "Usuniecie anulowane";
            Sleep(1000);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
}

void edytujAdresata(vector <Adresat> &adresaci)
{
    int idAdresataDoEdycji;
    char wybor;
    Adresat adresatPoEdycji;
    string nowaWartoscEdytowanegoPola = "";
    bool czyWskazanyAdresatIstnieje = false;
    bool czyEdytowanoAdresata = false;
    if (!adresaci.empty())
    {
        while (czyWskazanyAdresatIstnieje == false)
        {
            system("cls");
            cout << "Podaj numer Id adresata do edycji: ";
            cin >> idAdresataDoEdycji;
            czyWskazanyAdresatIstnieje = czyAdresatIstniejeWBazie(adresaci,idAdresataDoEdycji);
            if (czyWskazanyAdresatIstnieje == false)
            {
                cout << endl << "Brak w bazie adresata z podanym Id, podaj poprawny numer!";
                Sleep(1000);
            }
        }
        system("cls");
        cout << "Aktualne dane wybranego adresata" << endl;
        wyswietlWybranegoAdresata (adresaci,idAdresataDoEdycji);
        cout << endl <<"Co chcesz poprawic?" << endl;
        cout << "1. imie" << endl;
        cout << "2. nazwisko" << endl;
        cout << "3. numer telefonu" << endl;
        cout << "4. email" << endl;
        cout << "5. adres" << endl;
        cout << "9. powrot do menu glownego" << endl;

        for(vector <Adresat> :: iterator itr = adresaci.begin() ; itr != adresaci.end() ; itr++)
        {
            if (itr->id == idAdresataDoEdycji)
            {
                adresatPoEdycji.id = itr-> id;
                adresatPoEdycji.idUzytkownika = itr-> idUzytkownika;
                adresatPoEdycji.imie = itr-> imie;
                adresatPoEdycji.nazwisko = itr-> nazwisko;
                adresatPoEdycji.nrTelefonu = itr-> nrTelefonu;
                adresatPoEdycji.email = itr-> email;
                adresatPoEdycji.adres = itr-> adres;

                cin >> wybor;

                cout << endl << "Aktualne dane wybranego adresata" << endl;
                cout << "Id             " << adresatPoEdycji.id << endl;
                cout << "Imie           " << adresatPoEdycji.imie << endl;
                cout << "Nazwisko       " << adresatPoEdycji.nazwisko << endl;
                cout << "Email          " << adresatPoEdycji.email << endl;
                cout << "Nr.telefonu    " << adresatPoEdycji.nrTelefonu << endl;
                cout << "Adres          " << adresatPoEdycji.adres << endl << endl;

                switch (wybor)
                {
                case '1':
                {
                    cout << "Podaj nowe imie: ";
                    cin >> nowaWartoscEdytowanegoPola;
                    itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nowaWartoscEdytowanegoPola);
                    adresatPoEdycji.imie = itr-> imie;
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '2':
                {
                    cout << "Podaj nowe nazwisko: ";
                    cin >> nowaWartoscEdytowanegoPola;
                    itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nowaWartoscEdytowanegoPola);
                    adresatPoEdycji.nazwisko = itr-> nazwisko;
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '3':
                {
                    cout << "Podaj nowy numer telefonu: ";
                    cin.clear();
                    cin.sync();
                    getline(cin,nowaWartoscEdytowanegoPola);
                    itr->nrTelefonu = nowaWartoscEdytowanegoPola;
                    adresatPoEdycji.nrTelefonu = itr-> nrTelefonu;
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '4':
                {
                    cout << "Podaj nowy email: ";
                    cin >> nowaWartoscEdytowanegoPola;
                    itr->email = nowaWartoscEdytowanegoPola;
                    adresatPoEdycji.email = itr-> email;
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '5':
                {
                    cout << "Podaj nowy adres: ";
                    cin.clear();
                    cin.sync();
                    getline(cin,nowaWartoscEdytowanegoPola);
                    itr->adres = nowaWartoscEdytowanegoPola;
                    adresatPoEdycji.adres = itr-> adres;
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '9':
                {
                    cout << endl << "Edycja anulowana";
                    Sleep(1000);
                    break;
                }
                }
            }
        }
        if (czyEdytowanoAdresata)
        {
            nadpiszListeAdresatowWPlikuPoEdycjiAdresata (adresatPoEdycji,idAdresataDoEdycji);
            cout << endl << "Kontakt pomyslnie edytowany!";
            Sleep(1000);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
        Sleep(1000);
    }
}
