//
// Created by Andrei on 4/20/2023.
//

#ifndef ANDREI_REPO_COS_H
#define ANDREI_REPO_COS_H
#include <vector>
#include "Domain.h"
using namespace std;
class repo_cos{

private:
    vector<Song> bag;
public:
    void repo_add(Song s);
    void repo_delete();
    vector<Song> get_bag();

};

void test_repo_cos();


#endif //ANDREI_REPO_COS_H
