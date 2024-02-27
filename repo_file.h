//
// Created by Andrei on 5/5/2023.
//

#ifndef ANDREI_REPO_FILE_H
#define ANDREI_REPO_FILE_H
#include <fstream>
#include "repository.h"
#include "vector"
using namespace std;



class repo_file: public SongRepository {
private:
    vector<Song> file_song;
    string file_path;
public:
    repo_file()=default;
    repo_file(string file_path): file_path{file_path}{};
    void read_from_file();
    void write_to_file();
    void add(Song s);
    void dell(Song s);
    Song modify(Song s);
    vector<Song> get_all_offers();

};

void tests_file();
#endif //ANDREI_REPO_FILE_H
