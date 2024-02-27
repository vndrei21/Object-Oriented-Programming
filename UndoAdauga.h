//
// Created by Andrei on 4/29/2023.
//

#ifndef ANDREI_UNDOADAUGA_H
#define ANDREI_UNDOADAUGA_H
#include "UndoActions1.h"

class UndoAdauga: public UndoActions1{
public:
    UndoAdauga(SongRepository& repo, Song & s): UndoActions1{repo, s}{}
    void DoUndo() override;
    ~UndoAdauga()=default;

};


#endif //ANDREI_UNDOADAUGA_H
