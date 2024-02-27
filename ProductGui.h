#ifndef ANDREI_PRODUCTGUI_H
#define ANDREI_PRODUCTGUI_H
#endif
//ANDREI_PRODUCTGUI_H
#include "Domain.h"
#include <QWidget>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QLineEdit>
#include <QFormLayout>
#include "service.h"
#include <QString>
#include <QDebug>
#include <QMessageBox>
#include <QLineEdit>
#include "repo_cos.h"
#include "service_cos.h"
#include "Repository.h"
#include "Validators.h"
#include "QGroupBox"
#include <QRadioButton>
#include <QButtonGroup>
#include <algorithm>
#include <random>
#include <chrono>
#include "Observer.h"
#include <QPushButton>
#include <QTableView>
#include "BagGui.h"
#include "paint.h"
#include "TabelView.h"
class ProductGuy:public QWidget, public Observer{
public:
    ProductGuy(SongStore& s,service_cos& cos):srv{s},srv_cos{cos}{
        populate_srv();
        init_gui();
        connect_button();
        bag_init();
        load_data(srv.getAllSongs());
       // init_read_only();

        /*auto *wnd = new QWidget;
    auto *list = new QListWidget;
    auto *mainly = new QHBoxLayout;
    wnd->setLayout(mainly);
    mainly->addWidget(list);
    auto *secondly = new QVBoxLayout;
    auto *btnly = new QHBoxLayout;
    auto *add = new QPushButton{"adauga"};
    auto *deletee = new QPushButton{"sterge"};
    auto *modify =new QPushButton{"modifica"};
    auto *exit = new QPushButton{"exit"};
    auto *denumire = new QLineEdit{};
    auto *destinatie = new QLineEdit{};
    auto *tip = new QLineEdit{};
    auto *pret = new QLineEdit{};
    auto *formly = new QFormLayout;
    secondly->addWidget(denumire);
    secondly->addWidget(destinatie);
    secondly->addWidget(tip);
    secondly->addWidget(pret);

    formly->addRow("Denumire", denumire);
    formly->addRow("Destinatie",destinatie);
    formly->addRow("Tip", tip);
    formly->addRow("Pret", pret);
    secondly->addLayout(formly);
     btnly->addWidget(add);
    btnly->addWidget(modify);
    btnly->addWidget(deletee);
    btnly->addWidget(exit);
    secondly->addLayout(btnly);
    mainly->addLayout(secondly);
     */

    }

    void update()override{
        load_data_to_bag();
    }

private:
    QTableView* tv = new QTableView();

    SongStore& srv;
    TabelView* t;
    vector<Song> s5;
    service_cos& srv_cos;
    painter* p = new painter{srv_cos};
    QListWidget *list = new QListWidget;
    QPushButton *add = new QPushButton{"adauga"};
    QPushButton *deletee = new QPushButton{"sterge"};
    QPushButton *modify =new QPushButton{"modifica"};
    QPushButton *exit = new QPushButton{"exit"};
    QPushButton *sortbydenumire = new QPushButton{"Sort by name"};
    QPushButton *sortbydestinatie = new QPushButton{"Sort by Destination"};
    QPushButton *sortbytypeandprice = new QPushButton{"Sort by type and price"};
    QLineEdit* denumire = new QLineEdit{};
    QLineEdit *destinatie = new QLineEdit{};
    QLineEdit *tip = new QLineEdit{};
    QLineEdit *pret = new QLineEdit{};
    QFormLayout *formly = new QFormLayout;
    QPushButton *undo = new QPushButton{"Undo"};
    QPushButton *filterdestinatie = new QPushButton{"Filtrare destinatie"};
    QPushButton *filterprice = new QPushButton{"Filtrare pret"};
    QWidget* wfilter = new QWidget;
    QFormLayout* formfilter = new QFormLayout;
    QLineEdit* desti = new QLineEdit;
    QVBoxLayout* filterly =new QVBoxLayout;
    QPushButton* exitfilter = new QPushButton{"exit"};
    QPushButton* filterbtn = new QPushButton{"filter"};
    QPushButton* filterpricebtn = new QPushButton{"filter"};
    QPushButton* exitfilterprice =new QPushButton{"exit"};
    QWidget* wfilterprice = new QWidget;
    QVBoxLayout* pricefilterly = new QVBoxLayout;
    QFormLayout* formpricely =new QFormLayout;
    QLineEdit* min_price = new QLineEdit;
    QLineEdit* max_price = new QLineEdit;
    QPushButton* afisare=  new QPushButton{"Afiseaza"};
    QPushButton* show_painter = new QPushButton{"Afiseaza desen"};


    //aici am declarat tot ce am nevoie pentru cos
    QPushButton* addtobag = new QPushButton{"Adauga in cos"};
    QWidget* cos = new QWidget;
    QPushButton* stergebag = new QPushButton{"sterge din cos"};
    QFormLayout* form = new QFormLayout;
    QListWidget* coslist = new QListWidget;
    QLineEdit* denumire_bag = new QLineEdit;
    QLineEdit* destinatie_bag = new QLineEdit;
    QLineEdit* tip_bag = new QLineEdit;
    QLineEdit* nr_of_ntt_bag = new QLineEdit;
    QPushButton* afisare_aleator = new QPushButton{"afisare aleator"};
    QPushButton* Exp = new QPushButton{"Export"};
    QLineEdit* exp_line = new QLineEdit;
    QRadioButton* cvs = new QRadioButton(tr("CVS"));
    QRadioButton* html = new QRadioButton(tr("HTML"));
    [[maybe_unused]] QWidget* read_only_cos = new QWidget;
    QVBoxLayout* mainread= new QVBoxLayout;
    QPushButton* read_only = new QPushButton{"Cos(read only)"};
    BagGui read_only1{srv_cos};
    QPushButton* addtobagmain = new QPushButton{"Adauga in cos"};
    QPushButton* stergebagmain = new QPushButton{"sterge din cos"};
    QPushButton* afisare_aleatormain = new QPushButton{"afisare aleator"};
    QHBoxLayout* cosly = new QHBoxLayout;
    QLineEdit* line = new QLineEdit;


    [[maybe_unused]] void init_read_only()
    {
        mainread->addWidget(coslist);

    }



    void populate_srv()
    {
        srv.addSong("vacanta1", "Paris", "cultural", 1100);
        srv.addSong("vacanta2", "Madrid", "city_break",800);
        srv.addSong("vacanta3", "Londra", "Cultural",950);
        srv.addSong("vacanta4", "Amsterdam", "city_break", 600);
        srv.addSong("vacanta5", "Barcelona", "Relax", 900);
        srv.addSong("vacanta6", "Praga", "city_break", 450);
        srv.addSong("vacanta7", "Roma", "cultural", 880);
        srv.addSong("vacanta8", "Torino", "cultural", 680);
    }

    void load_data(const vector<Song> lst)
    {
        list->clear();
        for(const auto& s : lst)
        {
            auto *item = new QListWidgetItem(QString::fromStdString(s.getArtist()));
            item->setData(Qt::UserRole,QString::fromStdString(s.getTitlu()));
            list->addItem(item);
        }
        t->setPets(lst);
    }
   void init_gui(){
       auto *mainly = new QHBoxLayout;
       this->setLayout(mainly);
       auto first = new QVBoxLayout;
       first->addWidget(list);
       first->addWidget(afisare);
       auto sort = new QHBoxLayout;
       sort->addWidget(sortbydenumire);
       sort->addWidget(sortbydestinatie);
       sort->addWidget(sortbytypeandprice);
       first->addLayout(sort);
       //mainly->addWidget(list);
       mainly->addLayout(first);
       auto *secondly = new QVBoxLayout;
       auto *btnly = new QHBoxLayout;
       /*auto *add = new QPushButton{"adauga"};
       auto *deletee = new QPushButton{"sterge"};
       auto *modify =new QPushButton{"modifica"};
       auto *exit = new QPushButton{"exit"};
       auto *denumire = new QLineEdit{};
       auto *destinatie = new QLineEdit{};
       auto *tip = new QLineEdit{};
       auto *pret = new QLineEdit{};
       auto *formly = new QFormLayout;
       secondly->addWidget(denumire);
       secondly->addWidget(destinatie);
       secondly->addWidget(tip);
       secondly->addWidget(pret);
       */
        denumire->QLineEdit::setPlaceholderText(QString("Denumire"));
       destinatie->QLineEdit::setPlaceholderText(QString("Destinatie"));
       tip->QLineEdit::setPlaceholderText(QString("Tip"));
       pret->QLineEdit::setPlaceholderText(QString("pret"));
       formly->addRow("Denumire", denumire);
       formly->addRow("Destinatie",destinatie);
       formly->addRow("Tip", tip);
       formly->addRow("Pret", pret);
       secondly->addLayout(formly);
       secondly->addWidget(addtobag);
       secondly->addWidget(read_only);
       secondly->addWidget(line);
       btnly->addWidget(add);
       btnly->addWidget(modify);
       btnly->addWidget(deletee);
       btnly->addWidget(exit);
       btnly->addWidget(undo);
       cosly->addWidget(addtobagmain);
       cosly->addWidget(stergebagmain);
       cosly->addWidget(afisare_aleatormain);
       secondly->addLayout(cosly);
       secondly->addLayout(btnly);
       secondly->addWidget(filterdestinatie);
       secondly->addWidget(filterprice);
       mainly->addLayout(secondly);
        mainly->addWidget(show_painter);
       srv_cos.add_obs(p);
       s5 = srv.getAllSongs();
       this->t = new TabelView{s5};
       t->setPets(srv.getAllSongs());
       t->add_list(srv.getAllSongs());
       this->tv->setModel(t);
        mainly->addWidget(tv);





   }
    void connect_button()
    {

        QObject::connect(show_painter,&QPushButton::clicked,[&](){
            p->show();
        });
        QObject::connect(afisare,&QPushButton::clicked,[&](){
            load_data(srv.getAllSongs());
        });
        QObject::connect(add,&QPushButton::clicked,[&](){
            //qDebug() << "adauga!";
            try {
                AddVacanta();
                load_data(srv.getAllSongs());
            }catch (ValidationException& v)
            {
                QMessageBox::warning(this,"Warning",QString::fromStdString(v.getErrorMessages()));
            }
        });
        QObject::connect(deletee, &QPushButton::clicked, [&](){
            //qDebug() << "sterge!";
            try {
                sterge_vacanta();
                load_data(srv.getAllSongs());
            }catch(ValidationException& v)
            {
                QMessageBox::warning(this,"Warning",QString::fromStdString(v.getErrorMessages()));

            }
        });
        QObject::connect(modify,&QPushButton::clicked,[&](){
            //qDebug() << "Modifica!";
            try {
                modifica_vacanta();
                load_data(srv.getAllSongs());
            }catch(ValidationException& v)
            {
                QMessageBox::warning(this,"Warning",QString::fromStdString(v.getErrorMessages()));
            }
            });
        QObject::connect(exit,&QPushButton::clicked,[&](){
            qDebug() << "Exit!";
            wfilter->close();
            close();
            wfilterprice->close();
            cos->close();

        });
        QObject::connect(sortbydenumire,&QPushButton::clicked,[&](){
            load_data(srv.sortByDurata());
        });
        QObject::connect(sortbydestinatie, &QPushButton::clicked,[&](){
            load_data(srv.sortbyDestinatie());
        });
        QObject::connect(sortbytypeandprice,&QPushButton::clicked,[&](){
            load_data(srv.sortByArtistSong());
        });

        QObject::connect(list,&QListWidget::itemSelectionChanged,[&](){
            auto sel = list->selectedItems();
            if(sel.isEmpty())
            {
                denumire->setText("");
                destinatie->setText("");
                tip->setText("");
                pret->setText("");
            }
            else
            {
                auto selItem = sel.at(0);
                auto dest = selItem->text();
                auto den = selItem->data(Qt::UserRole).toString();
                auto s = srv.find(den.toStdString(),dest.toStdString());
                denumire->setText(QString::fromStdString(s.getTitlu()));
                destinatie->setText(QString::fromStdString(s.getArtist()));
                tip->setText(QString::fromStdString(s.getGen()));
                pret->setText(QString::number(s.getDurata()));
            }
        });
        QObject::connect(undo,&QPushButton::clicked,[&](){
            srv.doUndo();
            load_data(srv.getAllSongs());
        });
        QObject::connect(filterbtn,&QPushButton::clicked,[&](){
            load_data(srv.filtrareGen(desti->text().toStdString()));
        });
        QObject::connect(exitfilter,&QPushButton::clicked,[&](){wfilter->close();
        });
        QObject::connect(filterdestinatie,&QPushButton::clicked,[&](){


            formfilter->addRow("Destinatie",desti);
            desti->QLineEdit::setPlaceholderText(QString("Destinatie"));
            //load_data(srv.filtrareGen(dest->text().toStdString()));

            wfilter->setLayout(filterly);
            filterly->addLayout(formfilter);
            filterly->addWidget(desti);
            filterly->addWidget(filterbtn);
            filterly->addWidget(exitfilter);
            wfilter->show();
        });
        QObject::connect(filterprice,&QPushButton::clicked,[&](){
            wfilterprice->setLayout(pricefilterly);
            min_price->QLineEdit::setPlaceholderText(QString("pret Minim"));
            max_price->QLineEdit::setPlaceholderText(QString("Pret Maxim"));
            formpricely->addRow("Pretul minim",min_price);
            formpricely->addRow("Pretul maxim", max_price);
            pricefilterly->addLayout(formpricely);
            pricefilterly->addWidget(filterpricebtn);
            pricefilterly->addWidget(exitfilterprice);
            wfilterprice->show();
        });
        QObject::connect(filterpricebtn,&QPushButton::clicked,[&](){
            load_data(srv.filtrareDurata(min_price->text().toDouble(),max_price->text().toDouble()));
        });

        //butonul care adauga in cos si deschide fereastra
        QObject::connect(addtobag,&QPushButton::clicked,[&](){
            add_to_bag();

            cos->show();
        });
        QObject::connect(addtobagmain,&QPushButton::clicked,[&](){
            add_to_bag();

        });
        //asta e in plus
        QObject::connect(coslist,&QListWidget::itemSelectionChanged,[&](){
            auto sel =coslist->selectedItems();
            if(sel.empty())
            {
                denumire_bag->setText("");
                destinatie_bag->setText("");
                tip_bag->setText("");
                //pret_bag->setText("");

            }else
            {
                auto bag_item = sel.at(0);
                auto dest = bag_item->text().toStdString();
                auto den = bag_item->data(Qt::UserRole).toString().toStdString();
                auto v = srv_cos.find(den,dest);
                denumire_bag->setText(QString::fromStdString(v.getTitlu()));
                destinatie_bag->setText(QString::fromStdString(v.getArtist()));
                tip_bag->setText(QString::fromStdString(v.getGen()));
                //pret_bag->setText(QString::number(v.getDurata()));
            }
        });
        //aici e butonul care imi sterge din cos
        QObject::connect(stergebag,&QPushButton::clicked,[&](){
            srv_cos.srv_delete();
            load_data_to_bag();
        });
        QObject::connect(stergebagmain,&QPushButton::clicked,[&](){
            srv_cos.srv_delete();
            load_data_to_bag();
        });
        QObject::connect(afisare_aleator,&QPushButton::clicked,[&](){
            Shuffle();
            load_data_to_bag();
        });
        QObject::connect(afisare_aleatormain,&QPushButton::clicked,[&](){
            Shuffle1();
            load_data_to_bag();
        });
        QObject::connect(Exp,&QPushButton::clicked,[&](){
           exp_bag();
           load_data_to_bag();
        });
        QObject::connect(read_only,&QPushButton::clicked,[&](){
            auto a = new BagGui{srv_cos};
            srv_cos.add_obs(a);
            a->show();
        });

    }
    void AddVacanta()
    {
        try
        {
            srv.addSong(denumire->text().toStdString(),destinatie->text().toStdString(),tip->text().toStdString(),pret->text().toDouble());
        }
        catch (RepoException& re)
        {
            QMessageBox::warning(this,"warning",QString::fromStdString(re.getErrorMessage()));
        }
    }

    void sterge_vacanta()
    {
        try
        {
            srv.deleteSong(denumire->text().toStdString(),destinatie->text().toStdString(),tip->text().toStdString(),pret->text().toDouble());
        }
        catch (RepoException& re)
        {
            QMessageBox::warning(this,"warnning",QString::fromStdString(re.getErrorMessage()));
        }
    }

    void modifica_vacanta()
    {
        try
        {
            srv.modificaSong(denumire->text().toStdString(),destinatie->text().toStdString(),tip->text().toStdString(),pret->text().toDouble());

        }
        catch (RepoException& re)
        {
            QMessageBox::warning(this,"warning",QString::fromStdString(re.getErrorMessage()));
        }
    }

    //aici am creat fereastra efectiva
    void bag_init()
    {
        srv_cos.add_obs(this);
        srv_cos.add_obs(&read_only1);
        auto primbag = new QHBoxLayout;
        auto mainlybag = new QVBoxLayout;
        mainlybag->addWidget(coslist);
        auto secondlybag = new QVBoxLayout;
        denumire_bag->setPlaceholderText(QString::fromStdString("Denumire"));
        destinatie_bag->setPlaceholderText(QString::fromStdString("Destinatie"));
        tip_bag->setPlaceholderText(QString::fromStdString("tip"));
        //pret_bag->setPlaceholderText(QString::fromStdString("pret"));
        auto secondbagly = new QVBoxLayout;
        secondbagly->addLayout(form);
        mainlybag->addWidget(stergebag);
        //mainlybag->addWidget(afisare_aleator);
        mainlybag->addLayout(secondbagly);
        cos->setLayout(primbag);
        nr_of_ntt_bag->setPlaceholderText("numar de entitati");
        secondlybag->addWidget(nr_of_ntt_bag);
        secondlybag->addWidget(afisare_aleator);
        exp_line->setPlaceholderText("Adaugati numele fisierului");
        secondlybag->addWidget(exp_line);

        cvs->setChecked(true);
        auto buttonly = new QHBoxLayout;
        buttonly->addWidget(cvs);
        buttonly->addWidget(html);
        secondlybag->addLayout(buttonly);
        secondlybag->addWidget(Exp);
        primbag->addLayout(mainlybag);
        primbag->addLayout(secondlybag);
        load_data_to_bag();
    }

    //functie care afiseaza lista de vacante din cos
    void load_data_to_bag()
    {
        coslist->clear();
        for(const auto elem:srv_cos.srv_get_all_bag())
        {
            auto item =  new QListWidgetItem(QString::fromStdString(elem.getArtist()));
            item->setData(Qt::UserRole,QString::fromStdString(elem.getTitlu()));
            coslist->addItem(item);
        }
    }
    //functia care adauga in cos
    void add_to_bag()
    {
        try
        {
            srv_cos.srv_add(denumire->text().toStdString(),destinatie->text().toStdString());
            load_data_to_bag();
        }
        catch (RepoException& re)
        {
            QMessageBox::warning(this,"Warning",QString::fromStdString(re.getErrorMessage()));
        }
    }
    void Shuffle()
    {
        vector<Song> lst = srv.getAllSongs();
        auto n = nr_of_ntt_bag->text().toInt();
        while(n) {
            mt19937 mt{random_device{}()};
            uniform_int_distribution<> dist(0, lst.size() - 1);
            int randomNr = dist(mt);
            auto seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle(lst.begin(),lst.end(),default_random_engine(seed));
            srv_cos.srv_add(lst[randomNr].getTitlu(),lst[randomNr].getArtist());
            n--;
        }
    }
    void Shuffle1()
    {
        vector<Song> lst = srv.getAllSongs();
        auto n = line->text().toInt();
        while(n) {
            mt19937 mt{random_device{}()};
            uniform_int_distribution<> dist(0, lst.size() - 1);
            int randomNr = dist(mt);
            auto seed = chrono::system_clock::now().time_since_epoch().count();
            shuffle(lst.begin(),lst.end(),default_random_engine(seed));
            srv_cos.srv_add(lst[randomNr].getTitlu(),lst[randomNr].getArtist());
            n--;
        }
    }
    void exp_bag()
    {
        auto fisier = exp_line->text().toStdString();
        int mod = 0;
        if(cvs->isChecked())
            mod = 1;
        srv_cos.Bag_Export(fisier,mod);
    }

};

