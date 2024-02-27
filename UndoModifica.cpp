//
// Created by Andrei on 4/29/2023.
//

#include "UndoModifica.h"

void UndoModifica::DoUndo() {
    repo.modifica_oferta(v);
}
