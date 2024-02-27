//
// Created by Andrei on 6/7/2023.
//

#ifndef ANDREI_PAINT_H
#define ANDREI_PAINT_H
#include <QWidget>
#include <Observer.h>
#include "QPainter"
#include "service_cos.h"
class painter:public QWidget,public Observer{

private:
    service_cos& srv;


public:
    void update()override{
        repaint();
    }
    painter(service_cos& s):srv{s}{};

    void paintEvent(QPaintEvent* ev) override {
        auto x = 10;
        QPainter p1{this};
        for (auto l: srv.srv_get_all_bag()) {
            p1.drawRect(x, 0, 20, l.getDurata()/25);
            x += 40;
        }
    }

};
#endif //ANDREI_PAINT_H
