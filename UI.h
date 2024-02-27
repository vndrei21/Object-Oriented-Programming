#pragma once
#include "service.h"
#include "service_cos.h"
class ConsoleUI {
private:
    SongStore& srv;
    service_cos& bag_srv;

public:
    ConsoleUI(SongStore& srv, service_cos& bag) :srv{ srv },bag_srv{bag}{};
    ConsoleUI(const ConsoleUI& ot) = delete;

    void printMenu();
    void uiAdd();
    void uiDelete();
    void uiModify();
    void uiSort();
    void uiFilter();
    void uiAddtobag();
    void uiDeleteBag();
    void uiPrintBag();
    void addDefaultSongs();
    void addShuffletoBag();
    void ExportBag();
    void printSongs(const vector<Song>& allSongs);
    void run();
    void UNDO();
};
