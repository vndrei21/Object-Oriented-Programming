//
// Created by Andrei on 4/20/2023.
//

#include "repo_cos.h"
#include <cassert>
void repo_cos::repo_add(Song s) {
    bag.push_back(s);
}

void repo_cos::repo_delete() {
    bag.clear();
}

vector<Song> repo_cos::get_bag() {
    return bag;
}


void test_add_delete_get_all()
{
    repo_cos s;
    Song song1{ "Pictures of Home", "Deep Purple", "rock",3.24 };
    Song song2{ "Highway Star","Deep Purple", "rock",2.44 };
    Song song3{ "Holy Diver","Dio", "rock", 4.45 };
    Song song4{ "Holy Diver","Dio", "city", 3};
    s.repo_add(song1);
    s.repo_add(song2);
    s.repo_add(song3);
    s.repo_add(song4);
    assert(s.get_bag().size() == 4);
    s.repo_delete();
    assert(s.get_bag().empty());
}



void test_repo_cos() {
test_add_delete_get_all();
}
