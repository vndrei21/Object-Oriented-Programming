//
// Created by Andrei on 4/29/2023.
//

#ifndef ANDREI_UNDOMODIFICA_H
#define ANDREI_UNDOMODIFICA_H
#include "UndoActions1.h"

class UndoModifica: public UndoActions1{

public:
    UndoModifica(SongRepository& repo, Song&s): UndoActions1{repo,s}{}
    void DoUndo() override;
    ~UndoModifica()=default;

};


#endif //ANDREI_UNDOMODIFICA_H
