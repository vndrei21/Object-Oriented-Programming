//
// Created by Andrei on 6/7/2023.
//

#ifndef ANDREI_TABELVIEW_H
#define ANDREI_TABELVIEW_H
#include <QAbstractTableModel>
#include "Domain.h"
#include "vector"
#include "string"
#include "Domain.h"
int rows = 10;
int cols = 1;
class TabelView: public QAbstractTableModel{
private:

    std::vector<Song> vacante;
public:
    TabelView(const std::vector<Song>& s): vacante{s}{};
/**
* number of rows
*/
    int rowCount(const QModelIndex &parent = QModelIndex()) const override
    {
        return vacante.size();
    }
/**
* number of columns
*/
    int columnCount(const QModelIndex &parent = QModelIndex()) const override{
        return 4;
    }
/**
* Value at a given position
*/
    void add_list(vector<Song> s)
    {
        vacante = s;
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override
    {


        if (role == Qt::DisplayRole) {
            cout <<"asdadsfdasfdsa\n";
            Song p = vacante[index.row()];
            qDebug() << p.getTitlu()<<'\n';
            if (index.column() == 0) {
                return QString::fromStdString(p.getTitlu());
            }
            else if (index.column() == 1) {
                return QString::fromStdString(p.getArtist());
            }
            else if (index.column() == 2) {
                return QString::fromStdString(p.getGen());
            }
            else if (index.column() == 3) {
                return QString::number(p.getDurata());
            }
        }

          /*  if(index.column() == 0)
                return QString::fromStdString("ASsadas");
            //return QString::fromStdString(s.getTitlu());
            //auto s = vacante.begin()+index.row();
            //for(int i =0; i < strlen(s.getTitlu().);)
            //return QString(r).arg(index.row());

        }
            //return QString("row%1").arg(index.row()).arg(index.column());
        */
          return QVariant();
    }
    /**
  * Invoked on edit
  */
  void setPets(const vector<Song> s)
    {
        this->vacante = s;
        auto topleft = createIndex(0,0);
        auto bottor = createIndex(rowCount(), columnCount());
        emit dataChanged(topleft,bottor);
    }

};


#endif //ANDREI_TABELVIEW_H
