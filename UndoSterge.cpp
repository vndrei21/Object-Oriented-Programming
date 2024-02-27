//
// Created by Andrei on 4/29/2023.
//

#include "UndoSterge.h"

void UndoSterge::DoUndo() {
    repo.store(v);
}
