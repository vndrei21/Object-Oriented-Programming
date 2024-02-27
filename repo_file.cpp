#include "repo_file.h"
#include <cassert>
#include <sstream>
ifstream infile;
fstream write;
istringstream iss;

void repo_file::read_from_file() {
    infile.open(file_path);
    string denumire, destinatie, tip,line;
    double pret;

    while(getline(infile, line))
    {

        iss.clear();
        iss.str(line);
        iss >> denumire >> destinatie >> tip >> pret;
        //cout << denumire << " " << destinatie << " " << tip << " " << pret << "\n";
        Song s{denumire,destinatie,tip, pret};
        store(s);
    }
    infile.close();
}

void repo_file::write_to_file() {
    write.open (file_path, std::fstream::out);
    for(auto s:getAllSongs())
    {
        write << s.getTitlu()<< "  "  << s.getArtist()<< " " << s.getGen()<< " " <<s.getDurata() <<'\n';
        sterge_oferta(s);
    }
    write.close();
}


void repo_file::add(Song s) {
    this->read_from_file();
    //cout << this->get_all_offers().size() << "\n";
    store(s);
    this->write_to_file();
}


void repo_file::dell(Song s) {

    this->read_from_file();
    sterge_oferta(s);
    this->write_to_file();
}


Song repo_file::modify(Song s) {
    this->read_from_file();
    Song s1 = modifica_oferta(s);
    this->write_to_file();
    return s1;
    }

vector<Song> repo_file::get_all_offers() {
    read_from_file();
    auto l = getAllSongs();
    write_to_file();
    return l;


}




void test_add() {

    repo_file File{"Repo.txt"};
    assert(File.get_all_offers().size() == 0);
    //cout <<File.get_all_offers().size();
    Song s1{"vacanta10", "Lisabona", "Cultural", 900};
    File.add(s1);
    Song s2{"vacanta10", "Lisabona", "city_break", 1900};
    File.modify(s2);
    assert(File.get_all_offers().size() == 1);
    File.dell(s2);
    assert(File.get_all_offers().size() == 0);

    /*
     * vacanta1  Paris cultural 1100
vacanta2  Madrid city_break 800
vacanta3  Londra Cultural 950
vacanta4  Amsterdam city_break 600
vacanta5  Barcelona Relax 900
vacanta6  Praga city_break 450
vacanta7  Roma cultural 880
vacanta8  Torino cultural 680
vacanta10  Lasasas Cultural 900
vacanta10  Lisabona Cultural 900
*/
}


void tests_file(){
    test_add();
}