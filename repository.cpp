#include "Repository.h"
#include <assert.h>
bool SongRepository::exists(const Song& s) {
    try {
        find(s.getTitlu(), s.getArtist());
        return true;
    }
    catch (RepoException) {
        return false;
    }
}
///
const Song& SongRepository::find(string titlu, string artist)
{
    for (const Song& s : this->allSongs) {
        if (s.getTitlu() == titlu && s.getArtist() == artist) {
            return s;
        }
    }
    throw RepoException("oferta cu denumirea "+titlu+" si destinatia "+artist +" nu exista in lista");
}
void SongRepository::store(const Song& s) {
    if (exists(s)) {
        throw RepoException("oferta cu denumirea " + s.getTitlu() + " si destinatia " + s.getArtist() + " exista in lista");
    }
    this->allSongs.push_back(s);
}

const vector<Song> SongRepository::getAllSongs() {
    vector<Song> songs;
    for (auto song : this->allSongs) {
        songs.push_back(song);
    }
    return songs;}

void SongRepository::sterge_oferta(Song s) {
    if (!exists(s))
        throw RepoException(
                "oferta cu denumirea " + s.getTitlu() + " si destinatia " + s.getArtist() + " nu exista in lista");
    vector<Song> lst = getAllSongs();
    int i= 0 ;
    for (auto l: lst)
    {
        if (s.getTitlu() == l.getTitlu() && s.getArtist() == l.getArtist())
        {
            allSongs.erase(allSongs.begin()+i);
            break;
        }
        ++i;
}
    }

Song SongRepository::modifica_oferta(Song s) {
    if (!exists(s))
        throw RepoException("oferta cu denumirea " + s.getTitlu() + " si destinatia " + s.getArtist() + " nu exista in lista");
    vector<Song> lst = getAllSongs();
    int i = 0;
    Song aux;
        for (auto l:lst){
            if (s.getTitlu() == l.getTitlu() && s.getArtist() == l.getArtist())
            {
                this->allSongs[i] = s;
                aux = l;
            }
            i++;
        }

        return aux;
}

void testAddRepo() {
    SongRepository testRepo;
    Song song1{ "Yamasha", "Alex Velea","pop",3.45 };
    testRepo.store(song1);
    assert(testRepo.getAllSongs().size() == 1);

    Song song2{ "Raisa", "Fly Project", "pop", 3.42 };
    Song song3{ "Yamasha", "Alex Velea", "rock", 4.32 };
    try {
        testRepo.store(song3);
        //assert(false);
    }
    catch (RepoException) {
        assert(true);
    }


}
void testFindRepo() {
    SongRepository testRepo;

    Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
    Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
    Song song3{ "Holy Diver","Dio", "rock", 4.45 };
    testRepo.store(song1);
    testRepo.store(song2);

    assert(testRepo.exists(song1));
    assert(!testRepo.exists(song3));

    auto foundSong = testRepo.find("Pictures of Home", "Deep Purple");
    assert(foundSong.getArtist() == "Deep Purple");
    assert(foundSong.getDurata() == 3.24);
    assert(foundSong.getGen() == "rock");


    try {
        testRepo.find("Baba O'riley", "The Who");
        //assert(false);
    }
    catch (RepoException& ve) {
        assert(ve.getErrorMessage()== "oferta cu denumirea Baba O'riley si destinatia The Who nu exista in lista");
    }
}

void testDeletRepo()
{
    SongRepository test_repo;
    Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
    Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
    Song song3{ "Holy Diver","Dio", "rock", 4.45 };
    test_repo.store(song1);
    test_repo.store(song2);
    test_repo.store(song3);
    assert(test_repo.getAllSongs().size() == 3);
    test_repo.sterge_oferta(song1);
    assert(test_repo.getAllSongs().size() == 2);
    test_repo.sterge_oferta(song2);
    test_repo.sterge_oferta(song3);
    assert(test_repo.getAllSongs().size() == 0);
    Song song5("Baba O'riley", "The Who","asds",12);

    try {
        test_repo.sterge_oferta(song5);
        //assert(false);
    }
    catch (RepoException& ve) {
        assert(ve.getErrorMessage()== "oferta cu denumirea Baba O'riley si destinatia The Who nu exista in lista");
    }


}
void testModificarepo()
{
    SongRepository test_repo;
    Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
    Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
    Song song3{ "Holy Diver","Dio", "rock", 4.45 };
    Song song4{ "Holy Diver","Dio", "city", 3};

    test_repo.store(song1);
    test_repo.store(song2);
    test_repo.store(song3);
    test_repo.modifica_oferta(song4);
    vector<Song> lst = test_repo.getAllSongs();
    assert(lst[lst.size()-1].getGen() == "city");
    assert(lst[lst.size()-1].getDurata() == 3);
    //cout << lst[lst.size()-1].getGen() << endl << lst[lst.size()-1].getDurata();
    Song song5("Baba O'riley", "The Who","asds",12);
    try {
        test_repo.modifica_oferta(song5);
        //assert(false);
    }
    catch (RepoException& ve) {
        assert(ve.getErrorMessage()== "oferta cu denumirea Baba O'riley si destinatia The Who nu exista in lista");
    }

}

void testeRepo() {
    testAddRepo();
    testFindRepo();
    testDeletRepo();
    testModificarepo();
}