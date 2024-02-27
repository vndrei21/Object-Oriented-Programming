#pragma once
#include "UI.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
void ConsoleUI::printMenu() {
    cout << "Comenzi disponibile:" << endl;
    cout << "1. Adauga oferta" << endl;
    cout << "2. Filtreaza oferta" << endl;
    cout << "3. Sorteaza oferta" << endl;
    cout << "4. Afiseaza toate ofertele" << endl;
    cout << "5.modifica" << endl;
    cout << "6.sterge" << endl;
    cout << "7.adauga in cos" << endl;
    cout << "8.sterge cos" << endl;
    cout << "9.vizualizare cos" << endl;
    cout << "10.adauga aleator in cos[r]" << endl;
    cout << "11.Export cos[e]"<<endl;
    cout << "12.Undo[u]" << endl;
    cout << "0.Exit" << endl;
}

void ConsoleUI::uiAdd() {
    string titlu, artist, gen;
    double durata;
    cout << "Introduce-ti denumirea:";
    getline(cin >> ws, titlu);
    while(titlu.size() < 2)
    {
        cout << "denumire incorecta!va rugam sa introduce-ti o denumire corecta:"<<endl;
        getline(cin >> ws, titlu);
    }
    cout << "Introduce-ti destinatia:";
    getline(cin >> ws, artist);
    while(artist.size()<1)
    {
        cout << "destinatie incorecta!va rugam sa introduce-ti o destinatie incorecta:"<<endl;
        getline(cin >> ws, artist);


    }
    cout << "introduce-ti tip-ul:";
    getline(cin >> ws, gen);
    while(gen.size()<1)
    {
        cout << "Tip incorect!va rugam sa introduce-ti un tip corect:"<<endl;
        getline(cin >> ws, gen);


    }

    cout << "introduce-ti pretul:";
    cin >> durata;
    if(durata < 0)
    {
        cout << "pretul introdus este incorect!Va rugam introduce-ti un pret corect:";
        cin >> durata;
    }
    try {
        srv.addSong(titlu, artist,gen, durata);
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationException& ve) {
        cout << "Oferta nu este valida!" << endl;
        cout << ve.getErrorMessages();
    }

}

void ConsoleUI::uiSort() {
    cout << "Criteriul de sortare este (denumire/destinatie/pret+tip):";
    string criteriu;
    cin >> criteriu;

    if (criteriu == "denumire")
        printSongs(srv.sortByDurata());
    else if (criteriu == "pret+tip")
        printSongs(srv.sortByArtistSong());
    else if(criteriu == "destinatie")
        printSongs(srv.sortbyDestinatie());
    else
        cout << "Nu se poate sorta dupa criteriul dat." << endl;

}

void ConsoleUI::uiFilter() {
    cout << "Criteriul de filtrare este (destinatie/pret):";
    string criteriu;
    cin >> criteriu;

    if (criteriu == "destinatie") {
        cout << "destinatia pentru care se afiseaza oferta:" << endl;
        string searchedGenre;
        cin >> searchedGenre;
        printSongs(srv.filtrareGen(searchedGenre));
    }
    else if (criteriu == "pret") {
        double durataStart, durataEnd;
        cout << "Limita inferioara a bugetului:" << endl;
        cin >> durataStart;
        cout << "Limita superioara a bugetului:" << endl;
        cin >> durataEnd;

        printSongs(srv.filtrareDurata(durataStart,durataEnd));
    }

    else
        cout << "Nu se poate filtra dupa criteriul dat." << endl;
}

void ConsoleUI::printSongs(const vector<Song>& allSongs) {

    if (allSongs.size() == 0)
        cout << "Nu exista oferte." << endl;
    else {
        cout << "DENUMIRE\t\tDESTINATIE\tTIP\t\t\tPRET\n";
        for (const auto &song: allSongs) {
            cout << song.getTitlu() << "\t\t" << song.getArtist();
            if(song.getArtist().length() > 7) {
                cout << "\t" << song.getGen();
                if (song.getGen().length() > 7)
                    cout << "\t\t" << song.getDurata() << endl;
                else
                    cout << "\t\t\t" << song.getDurata() << endl;
            }
            else
                cout<< "\t\t" << song.getGen() << "\t\t"<< song.getDurata()<< endl;

        }
    }
}


void ConsoleUI::addDefaultSongs() {
    srv.addSong("vacanta1", "Paris", "cultural", 1100);
    srv.addSong("vacanta2", "Madrid", "city_break",800);
    srv.addSong("vacanta3", "Londra", "Cultural",950);
    srv.addSong("vacanta4", "Amsterdam", "city_break", 600);
    srv.addSong("vacanta5", "Barcelona", "Relax", 900);
    srv.addSong("vacanta6", "Praga", "city_break", 450);
    srv.addSong("vacanta7", "Roma", "cultural", 880);
    srv.addSong("vacanta8", "Torino", "cultural", 680);

}

void ConsoleUI::run() {
    int running = 1;
    char cmd;
    addDefaultSongs();
    while (running) {
        printMenu();
        cout << "Comanda este:";
        cin >> cmd;
        switch (cmd)
        {
            case '1':
                uiAdd();
                break;
            case '2':
                uiFilter();
                break;
            case '3':
                uiSort();
                break;

            case '4':
                printSongs(srv.getAllSongs());
                break;
            case '0':
                running = 0;
                break;
            case '6':
                uiDelete();
                break;
            case '5':
                uiModify();
                break;
            case '7':
                uiAddtobag();
                break;
            case '8':
                uiDeleteBag();
                break;
            case '9':
                uiPrintBag();
                break;
            case 'r':
                addShuffletoBag();
                break;
            case 'e':
                ExportBag();
                break;
            case 'u':
                UNDO();
                break;
            default:
                cout << "introduce-ti o comanda valida!"<< endl;
                break;
        }
    }
}

void ConsoleUI::uiDelete() {
    string titlu, artist, gen;
    double durata;
    cout << "Introduce-ti denumirea:";
    getline(cin >> ws, titlu);

    cout << "Introduce-ti destinatia:";
    getline(cin >> ws, artist);
    cout << "introduce-ti tip-ul:";
    getline(cin >> ws, gen);

    cout << "introduce-ti pretul:";
    cin >> durata;
    try {
        srv.deleteSong(titlu, artist,gen, durata);
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationException& ve) {
        cout << "Oferta nu este valida!" << endl;
        cout << ve.getErrorMessages();
    }
}

void ConsoleUI::uiModify() {
    string titlu, artist, gen;
    double durata;
    cout << "Introduce-ti denumirea:";
    getline(cin >> ws, titlu);

    cout << "Introduce-ti destinatia:";
    getline(cin >> ws, artist);
    cout << "introduce-ti tip-ul:";
    getline(cin >> ws, gen);

    cout << "introduce-ti pretul:";
    cin >> durata;
    try {
        srv.modificaSong(titlu, artist,gen, durata);
    }
    catch (RepoException& re) {
        cout << re.getErrorMessage();
    }
    catch (ValidationException& ve) {
        cout << "Oferta nu este valida!" << endl;
        cout << ve.getErrorMessages();
    }

}

void ConsoleUI::uiAddtobag() {
    cout << "Introduce-ti denumirea:";
    string denumire;
    string destinatie;
    getline(cin >> ws, denumire);
    cout << "introduce-ti destinatia:";
    getline(cin >> ws, destinatie);
    try {
        bag_srv.srv_add(denumire,destinatie);
        cout <<"oferta adaugata!"<< endl;
    }catch (RepoException& re)
    {
        cout << re.getErrorMessage();
    }
}

void ConsoleUI::uiDeleteBag() {
    bag_srv.srv_delete();
}

void ConsoleUI::uiPrintBag() {
    cout << "Cosul dumneavoastra contine urmatoarele oferte:\n";
    printSongs(bag_srv.srv_get_all_bag());
}

void ConsoleUI::addShuffletoBag(){
    int n;
    cout << "introduce-ti numarul de entitati pe care doriti sa le adaugati:";
    cin >> n;
    vector<Song> lst = srv.getAllSongs();
    while(n) {
        mt19937 mt{random_device{}()};
        uniform_int_distribution<> dist(0, lst.size() - 1);
        int randomNr = dist(mt);
        auto seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(lst.begin(),lst.end(),default_random_engine(seed));
        bag_srv.srv_add(lst[randomNr].getTitlu(),lst[randomNr].getArtist());
        n--;
    }
}

void ConsoleUI::ExportBag() {
    string fisier;
    int optiune;
    cout << "Introduce-ti numele fisierului\n";
    getline(cin >> ws, fisier);
    cout << "Introduce-ti optiunea:";
    cin >> optiune;
    if(bag_srv.srv_get_all_bag().empty())
        cout << "Cosul este gol!\n";
    else
        bag_srv.Bag_Export(fisier, optiune);
}

void ConsoleUI::UNDO() {
    try{
        srv.doUndo();
    }catch (string &ex)
    {
        cout << ex;
    }

}

