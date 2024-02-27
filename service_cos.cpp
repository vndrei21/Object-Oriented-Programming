//
// Created by Andrei on 4/20/2023.
//

#include "service_cos.h"
#include <cassert>
#include <fstream>
void service_cos::srv_add(string denumire, string destinatie) {
    bag_repo.repo_add(song_repo.find(denumire, destinatie));
    this->notify_all();

}

void service_cos::srv_delete() {
    bag_repo.repo_delete();
    this->notify_all();

}

vector<Song> service_cos::srv_get_all_bag() {
    return bag_repo.get_bag();
}

void service_cos::Bag_Export(string& fisier, int& option) {

    if(option == 1)
        fisier+=".cvs";
    else
        fisier+=".html";
    ofstream fout(fisier);
    for(auto item: srv_get_all_bag())
    {
        fout<<item.getArtist() <<"," << item.getTitlu() << "," << item.getGen() << ","<< item.getDurata() << endl;
    }
}

Song service_cos::find(string denumire, string destinatie) {
    for(const auto& s:bag_repo.get_bag())
    {
        if(s.getTitlu() == denumire && s.getArtist() == destinatie)
            return s;
    }
    return Song();
}


void test_add_delete_get_srv()
{
    SongRepository test_repo;
    Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
    Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
    Song song3{ "Holy Diver","Dio", "rock", 4.45 };
    test_repo.store(song1);
    test_repo.store(song2);
    test_repo.store(song3);
    repo_cos cos;
    service_cos srv{cos,test_repo};
    srv.srv_add("Pictures of Home", "Deep Purple" );
    srv.srv_add("Highway Star","Deep Purple");
    srv.srv_add("Holy Diver","Dio");
    assert(srv.srv_get_all_bag().size() == 3);
    srv.srv_delete();
    assert(srv.srv_get_all_bag().size() == 0);
}

void test_srv_cos() {
test_add_delete_get_srv();
}
