//
// Created by Andrei on 4/29/2023.
//

#ifndef ANDREI_UNDOACTIONS1_H
#define ANDREI_UNDOACTIONS1_H

#include "Domain.h"
#include "Repository.h"
#include "repo_file.h"
class UndoActions1 {
protected:
    SongRepository& repo;
    Song  v;
public:
    //ActiuneUndo()=default;
    UndoActions1(SongRepository& r, Song& v):repo{r}, v{v}{};
    virtual void DoUndo() = 0;
    ~UndoActions1()=default;
};



#endif //ANDREI_UNDOACTIONS1_H
