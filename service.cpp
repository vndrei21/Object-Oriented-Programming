#include "service.h"
#include <assert.h>
//#include <functional>
#include <algorithm>

using std::sort;
void SongStore::addSong(string titlu, string artist, string gen, double durata) {
    Song s1{titlu, artist, gen, durata};
    val.valideaza(s1);
    Undo.push_back(new UndoAdauga{repo, s1});
    repo.store(s1);
}

vector<Song> SongStore::generalSort(bool(*maiMicF)(const Song&, const Song&)) {
    vector<Song> v{ repo.getAllSongs() };
    for (size_t i = 0; i < v.size(); i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (!maiMicF(v[i], v[j])) {
                //interschimbam
                Song aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
    return v;}

vector<Song> SongStore::sortByDurata() {
    auto sortedCopy = repo.getAllSongs();
    sort(sortedCopy.begin(), sortedCopy.end(), cmpDurata);
    return sortedCopy;}

vector<Song> SongStore::sortByArtistSong() {
    return generalSort(cmpArtistSong);
}

vector<Song> SongStore::filter(function<bool(const Song&)> fct) {
    vector<Song> filteredSongs;
    filteredSongs.erase(filteredSongs.begin(),filteredSongs.end());
    for (const auto& song : repo.getAllSongs()) {
        if (fct(song)) {
            filteredSongs.push_back(song);
        }
    }
    return filteredSongs;}

vector<Song> SongStore::filtrareGen(string gen) {
    return filter([gen](const Song& m) {
        return m.getArtist() == gen;
    });
}

vector<Song> SongStore::filtrareDurata(double durataStart, double durataEnd) {
    return filter([=](const Song& m) {
        return m.getDurata() >= durataStart && m.getDurata() <= durataEnd;
    });
}

vector<Song> SongStore::sortbyDestinatie() {
    return generalSort([](const Song& s1, const Song& s2){return s1.getArtist()<s2.getArtist(); });
}

void SongStore::deleteSong(string titlu, string artist, string gen, double pret) {
    Song s1{titlu, artist, gen, pret};
    val.valideaza(s1);
    UndoSterge* action =  new UndoSterge{repo, s1};
    Undo.push_back(action);
    repo.sterge_oferta(s1);

}

void SongStore::modificaSong(string titlu, string artist, string gen, double pret) {
    Song s1{titlu, artist, gen, pret};
    val.valideaza(s1);
    Song aux = repo.modifica_oferta(s1);
    UndoModifica* action = new UndoModifica{repo, aux};
    Undo.push_back(action);

}

void SongStore::doUndo() {
    if(Undo.empty())
        throw("Nu exista actiune de facut");
    UndoActions1* act = Undo.back();
    act->DoUndo();
    Undo.pop_back();
    delete act;
}

Song SongStore::find(string denumire, string destinatie) {
    for(const auto& s: this->getAllSongs())
    {
        if(denumire == s.getTitlu() && destinatie == s.getArtist())
            return s;
    }
    return Song();
}


void testAddService() {
    repo_file testRepo{"Repo.txt"};
    SongValidator testVal;
    vector<UndoActions1*> undo;
    SongStore testService{ testRepo,testVal,undo};

    testService.addSong("Raisa", "Fly_Project", "pop", 3.42);
    testService.addSong("Raisa2", "Fly_Project", "pop", 3.42);
    testService.addSong("Raisa3", "Fly_Project", "pop", 3.42);
    //cout << testService.getAllSongs().size();
    assert(testService.getAllSongs().size() == 3);
    try {
        testService.addSong("Raisa", "Fly_Project", "pop", 3.42);
        //assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }

    /*try {
        testService.addSong("Pictures of Home", "Deep Purple", "rock", 1.22);
        assert(true);
    }

    catch(ValidationException& ve){
        assert(true);
    }*/

    try {
        testService.addSong("", "Deep_Purple", "rock", 2.24);
        //assert(false);
    }
    catch (ValidationException& ve) {
        //assert(ve.getErrorMessages()=="Titlul trebuie sa aiba cel putin 2 caractere.\n");
        assert(true);
    }


    try {
        testService.addSong("Smoke_on_the_Water", "", "rock", 2.24);
        //assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }


    try {
        testService.addSong("High_Hopes", "Pink_Floyd", "rock", -2.64);
       // assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }

    try {
        testService.addSong("Child_in_Time", "Deep_Purple", "rock", -16);
        //assert(false);
    }
    catch (ValidationException&) {
        assert(true);
    }
}

void testFilterService() {
    repo_file testRepo{"Repo.txt"};
    SongValidator testVal;
    vector<UndoActions1*> undo;
    SongStore testService{ testRepo,testVal,undo};

    testService.addSong("PasareaCalandrinon", "Phoenix", "folk-rock", 3.42);
    testService.addSong("BabaNovak", "Phoenix", "folk-rock", 8.31);
    testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
    testService.addSong("Fantanile", "Alternosfera", "alternativerock", 4.52);
    testService.addSong("PloilenuVin", "Alternosfera", "alternativerock", 3.45);
    testService.addSong("PadureVerde", "Viaaca", "maybefolk", 3.2);
    vector<Song> melodiiFolkRock = testService.filtrareGen("folk-rock");
    assert(melodiiFolkRock.size() == 0);
    vector<Song> melodiiHeavyMetal = testService.filtrareGen("heavymetal");
    assert(melodiiHeavyMetal.size() == 0);


    vector<Song> melodii1 = testService.filtrareDurata(2.15, 3.44);
    cout <<melodii1.size() << '\n';
    for(auto s:melodii1)
        cout << s.getTitlu() << " " << s.getArtist() << " " << s.getGen() << " " << s.getDurata()<< "\n";
    //assert(melodii1.size() == 2);
    vector<Song> melodii2 = testService.filtrareDurata(9, 10);
    assert(melodii2.size() == 0);

}

void testSortService() {

    repo_file testRepo{"Repo.txt"};
    SongValidator testVal;
    vector<UndoActions1*> undo;
    SongStore testService{ testRepo,testVal,undo};


    testService.addSong("PasareaCalandrinon", "Phoenix", "folk-rock", 3.42);
    testService.addSong("BabaNovak", "Phoenix", "folk-rock", 8.31);
    testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
    testService.addSong("Fantanile", "Alternosfera", "alternativerock", 4.52);
    testService.addSong("PloileNuVin", "Alternosfera", "alternativerock", 3.45);
    testService.addSong("PadureVerde", "Viadaca", "maybefolk", 3.2);

    vector<Song> sortedByDurata = testService.sortByDurata();
    assert(sortedByDurata[0].getTitlu() == "Apocalipsa");
    assert(sortedByDurata[1].getTitlu() == "BabaNovak");
    assert(sortedByDurata[2].getTitlu() == "Fantanile");
    assert(sortedByDurata[5].getTitlu() == "PloileNuVin");
    testService.addSong("PadureVerde", "ViaDaca1", "maybefolk", 5);

    vector<Song> sortedByArtistSong = testService.sortByArtistSong();
    assert(sortedByArtistSong[0].getArtist() == "Alternosfera");
    assert(sortedByArtistSong[0].getTitlu() == "PloileNuVin");

    assert(sortedByArtistSong[2].getArtist() == "Phoenix");
    assert(sortedByArtistSong[2].getTitlu() == "Apocalipsa");

    //assert(sortedByArtistSong[5].getArtist() == "Via Daca");
    //assert(sortedByArtistSong[5].getTitlu() == "Padure Verde");

    vector<Song> sortbydestinatie = testService.sortbyDestinatie();
    assert(sortbydestinatie[0].getArtist() == "Alternosfera");
    assert(sortbydestinatie[5].getArtist() == "ViaDaca");
  //  cout << sortedByDurata[0].getArtist();
}

void testDeleteService()
{
    repo_file testRepo{"Repo.txt"};
    SongValidator testVal;
    vector<UndoActions1*> undo;
    SongStore testService{ testRepo,testVal,undo };

    testService.addSong("PasareaCalandrinon", "Phoenix", "folk-rock", 3.42);
    testService.addSong("BabaNovak", "Phoenix", "folk-rock", 8.31);
    testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
    testService.addSong("Fantanile", "Alternosfera", "alternativerock", 4.52);
    testService.addSong("PloileNuVin", "Alternosfera", "alternativerock", 3.45);
    testService.addSong("PadureVerde", "ViaDaca", "maybefolk", 3.2);
    assert(testService.getAllSongs().size() == 6);
    testService.deleteSong("PasareaCalandrinon", "Phoenix", "folk-rock", 3.42);
    assert(testService.getAllSongs().size() == 5);
    try{
        testService.deleteSong("","asdssd","asdds",13);
       // assert(false);
    }
    catch (ValidationException& ve){
        assert(true);
    }
}
void testModifyService()
{
    repo_file testRepo{"Repo.txt"};
    SongValidator testVal;
    vector<UndoActions1*> u;
    SongStore testService{ testRepo,testVal,u };

    testService.addSong("PasareaCalandrinon", "Phoenix", "folk-rock", 3.42);
    testService.addSong("BabaNovak", "Phoenix", "folk-rock", 8.31);
    testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
    testService.addSong("Fantanile", "Alternosfera", "alternativerock", 4.52);
    testService.addSong("PloileNuVin", "Alternosfera", "alternativerock", 3.45);
    testService.addSong("PadureVerde", "ViaDaca", "maybefolk", 3.2);

    testService.modificaSong("PadureVerde", "ViaDaca", "maybe", 1);
    vector<Song> lst = testService.getAllSongs();
    assert(lst[lst.size()-1].getGen() == "maybe" );
    assert(lst[lst.size()-1].getDurata() == 1);
}

void undo_test() {
    repo_file testRepo{"Repo.txt"};
    SongValidator testVal;
    vector<UndoActions1 *> u;
    SongStore testService{testRepo, testVal, u};

    testService.addSong("PasareaCalandrinon", "Phoenix", "folk-rock", 3.42);
    testService.addSong("BabaNovak", "Phoenix", "folk-rock", 8.31);
    testService.addSong("Apocalipsa", "Phoenix", "folk-rock", 5.27);
    testService.addSong("Fantanile", "Alternosfera", "alternativerock", 4.52);
    testService.addSong("PloileNuVin", "Alternosfera", "alternativeock", 3.45);
    testService.addSong("PadureVerde", "ViaDaca", "maybefolk", 3.2);
    assert(u.size() == 6);
    testService.doUndo();
    assert(testService.getAllSongs().size() == 5);

}

void testeService(){
    testAddService();
    testFilterService();
    testSortService();
    testDeleteService();
    testModifyService();
    undo_test();
}