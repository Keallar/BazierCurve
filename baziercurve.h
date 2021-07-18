#pragma once
#include <iostream>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QVector>
#include <QListWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>

class BazierCurve: public QWidget
{
    Q_OBJECT
public:
    explicit BazierCurve(QWidget* parent = nullptr);
    virtual ~BazierCurve();
    void getPoints();
    bool checkLineEdit();
    void calculate();
    void printXintPoints();
    void paint();
private:
    QPointF point_start;
    QPointF point_addit;
    QPointF point_end;
    QPushButton* pbt_run;
    QPushButton* pbt_erase;
    QLineEdit* lne_px1;
    QLineEdit* lne_py1;
    QLineEdit* lne_px2;
    QLineEdit* lne_py2;
    QLineEdit* lne_px3;
    QLineEdit* lne_py3;
    QLabel* lbl_lstwdg_xint;
    QListWidget* lstwdg_xint;
    QMessageBox* msgb_erinp;
    QVector<QPointF> vec_points;
    QGraphicsView* grview_main;
    QGraphicsScene* grscene_main;
public slots:
    void SlotPButtonRun();
    void SlotPButtonErase();
};
