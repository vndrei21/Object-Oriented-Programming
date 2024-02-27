//
// Created by Andrei on 4/20/2023.
//

#ifndef ANDREI_SERVICE_COS_H
#define ANDREI_SERVICE_COS_H
#include "repo_cos.h"
#include "repository.h"
#include <vector>
#include <string>
#include "Observer.h"
using namespace std;
class service_cos: public observable{
private:
    repo_cos& bag_repo;
    SongRepository& song_repo;
public:
    service_cos(repo_cos& repo, SongRepository& songrepo):bag_repo{ repo }, song_repo { songrepo }{};
    void srv_add(string denumire, string destinatie);

    void srv_delete();
    vector<Song> srv_get_all_bag();
    void Bag_Export(string& fisier,int& option);
    Song find(string denumire, string destinatie);
};

void test_srv_cos();
#endif //ANDREI_SERVICE_COS_H
