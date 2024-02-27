#include "UI.h"
#include <iostream>
#include "repo_cos.h"
#include "service_cos.h"
#include "repo_file.h"
#include "ProductGui.h"
#include <QApplication>
#include "Domain.h"

#include "service.h"

using std::cout;
using std::endl;
void testAll() {
    testeDomain();
    cout << "Finished domain tests." << endl;
    testeRepo();
    cout << "Finished repo tests." << endl;
    testeService();
    cout << "Finished service tests." << endl;
    test_repo_cos();
    cout << "Finished whishlist tests" << endl;
    test_srv_cos();
    tests_file();
    cout << "Finished all file tests" << endl;
}
void startApp() {
    SongRepository repo;
    SongValidator val;
    repo_cos repo_bag;
    repo_file repoFile{"fisier_main.txt"};
    service_cos srv_cos{repo_bag,repo};
    vector<UndoActions1*> undo;
    SongStore srv{ repo,val, undo };
    ConsoleUI ui{ srv , srv_cos};
    ui.run();
}
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
   //testAll();
   //startApp();
    SongRepository repo;
    SongValidator val;
    repo_cos repo_bag;
    repo_file repoFile{"fisier_main.txt"};
    service_cos srv_cos{repo_bag,repo};
    vector<UndoActions1*> undo;
    SongStore srv{ repo,val, undo };
    ConsoleUI ui{ srv , srv_cos};
    //ui.run();
    ProductGuy p{srv, srv_cos};
    p.show();
    return QApplication::exec();

}
