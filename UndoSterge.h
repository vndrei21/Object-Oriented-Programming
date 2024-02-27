//
// Created by Andrei on 4/29/2023.
//

#ifndef ANDREI_UNDOSTERGE_H
#define ANDREI_UNDOSTERGE_H
#include "UndoActions1.h"

class UndoSterge: public UndoActions1{
public:
    UndoSterge(SongRepository&r, Song& s): UndoActions1{r, s}{};
    void DoUndo() override;
    ~UndoSterge()=default;
};


#endif //ANDREI_UNDOSTERGE_H
