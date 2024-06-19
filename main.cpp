#include <iostream>
#include <windows.h>
#include <algorithm>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>

using namespace std;

struct Adresat
{
    int id;
    string imie,nazwisko,nrTelefonu,email,adres;
};



int zliczIloscLiniWPliku();

void pobierzDaneDoWektora(vector <Adresat> &adresaci);

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst);

void dodajAdresataDoKsiazki (vector <Adresat> &adresaci);

void przeslijJednegoAdresataDoPliku(Adresat adresat);

void wyszukajAdresataPoNazwisku(vector <Adresat> adresaci);

void wyszukajAdresataPoImieniu(vector <Adresat> adresaci);

void wyswietlWszystkichAdresatow(vector <Adresat> adresaci);

void nadpiszListeAdresatowWPliku (vector <Adresat> &adresaci);

void usunAdresata(vector <Adresat> &adresaci);

void edytujAdresata(vector <Adresat> &adresaci);

int main()
{

    vector <Adresat> adresaci;
    pobierzDaneDoWektora(adresaci);
    char wybor;

    while(1)
    {
        system("cls");
        cout << "----------KSIAZKA ADRESOWA----------" << endl << endl;
        cout << "1. Dodaj Adresata do Ksiazki" << endl;
        cout << "2. Wyszukaj Adresata w Ksiazce" << endl;
        cout << "3. Wyswietl wszystkich Adresatow" << endl;
        cout << "4. Usun adresata" << endl;
        cout << "5. Edytuj adresata" << endl;
        cout << "9. Zamknij program" << endl;
        cin>>wybor;

        if (wybor == '1')
        {
            dodajAdresataDoKsiazki(adresaci);

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
        if (wybor == '9')
        {
            cout << "Do widzenia!";
            Sleep(200);
            exit(0);
        }
    }
    return 0;
}

int zliczIloscLiniWPliku()
{
    string line;
    int count = 0;
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::in);
    while(getline(plik, line))
        count++;
    plik.close();
    return count;
}

void pobierzDaneDoWektora(vector <Adresat> &adresaci)
{
    int iloscRekordow = 0;
    Adresat adresat;
    string pomocID;
    iloscRekordow = (zliczIloscLiniWPliku());
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::in);
    if(plik.good() == false)
    {
        cout << "Plik nie istnieje!" << endl;
    }
    for (int i=0; i<iloscRekordow; i++)
    {
        getline(plik,pomocID,'|');
        adresat.id=stoi(pomocID);
        getline(plik,adresat.imie,'|');
        getline(plik,adresat.nazwisko,'|');
        getline(plik,adresat.email,'|');
        getline(plik,adresat.nrTelefonu,'|');
        getline(plik,adresat.adres,'|');
        adresaci.push_back(adresat);
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
    plik.open("ksiazkaAdresowa.txt",ios::out|ios::app);
    if (plik.good() == true)
    {
        plik << adresat.id << '|' << adresat.imie << '|' << adresat.nazwisko << '|' << adresat.email << '|' << adresat.nrTelefonu << '|' << adresat.adres << '|'  << '\n';
        plik.close();
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku, dane nie zostaly zapisane" << endl;
        system("pause");
    }
}

void dodajAdresataDoKsiazki (vector <Adresat> &adresaci)
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
        adresat.id = adresaci.back().id + 1;
    }
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
            cout << endl << "Nie znaleziono w Ksiazce nikogo o podanym nazwisku" << endl;
            Sleep(1000);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
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
            cout << adresat.id << endl;
            cout << adresat.imie << endl;
            cout << adresat.nazwisko << endl;
            cout << adresat.email << endl;
            cout << adresat.nrTelefonu << endl;
            cout << adresat.adres << endl << endl;
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    cout << "Nacisnij dowolny klawisz aby wrocic do menu glownego" << endl;
    system("pause");
}

void nadpiszListeAdresatowWPliku (vector <Adresat> &adresaci)
{
    fstream plik;
    plik.open("ksiazkaAdresowa.txt",ios::out);
    if (plik.good() == true)
    {
        for (auto adresat : adresaci)
            plik << adresat.id<< '|' << adresat.imie << '|' << adresat.nazwisko << '|' << adresat.email << '|' << adresat.nrTelefonu << '|' << adresat.adres << '|' << '\n';
        plik.close();
    }
    else
    {
        cout << endl << "Nie udalo sie otworzyc pliku, dane nie zostaly zapisane" << endl;
        system("pause");
    }
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
            nadpiszListeAdresatowWPliku (adresaci);
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
        cout << "Wybrano adresata o Id : " << idAdresataDoEdycji << ", jakie dane chcesz zmienic?" << endl;
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
                cin >> wybor;
                switch (wybor)
                {
                case '1':
                {
                    cout << "Podaj nowe imie: ";
                    cin >> nowaWartoscEdytowanegoPola;
                    itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nowaWartoscEdytowanegoPola);
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '2':
                {
                    cout << "Podaj nowe nazwisko: ";
                    cin >> nowaWartoscEdytowanegoPola;
                    itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nowaWartoscEdytowanegoPola);
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
                    czyEdytowanoAdresata = true;
                    break;
                }
                case '4':
                {
                    cout << "Podaj nowy email: ";
                    cin >> nowaWartoscEdytowanegoPola;
                    itr->email = nowaWartoscEdytowanegoPola;
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
            nadpiszListeAdresatowWPliku (adresaci);
            cout << endl << "Kontakt pomyslnie edytowany!";
            Sleep(1000);
        }
    }
    else
    {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
}
