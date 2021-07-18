#include <QGridLayout>
#include <QValidator>
#include <QBoxLayout>
#include <QGraphicsPathItem>
#include <QPolygonF>
#include <QPainterPath>
#include <cmath>

#include "baziercurve.h"

BazierCurve::BazierCurve(QWidget* parent): QWidget(parent)
{
    this->resize(800, 500);

    QIntValidator* ival_indig = new QIntValidator;

    msgb_erinp = new QMessageBox;
    msgb_erinp->setText("You input issue data or didn't input data");

    grscene_main = new QGraphicsScene;
    grview_main = new QGraphicsView(grscene_main);

    lne_px1 = new QLineEdit;
    lne_px1->setValidator(ival_indig);
    lne_px1->setPlaceholderText("x1");
    lne_py1 = new QLineEdit;
    lne_py1->setValidator(ival_indig);
    lne_py1->setPlaceholderText("y1");
    lne_px2 = new QLineEdit;
    lne_px2->setValidator(ival_indig);
    lne_px2->setPlaceholderText("x2");
    lne_py2 = new QLineEdit;
    lne_py2->setValidator(ival_indig);
    lne_py2->setPlaceholderText("y2");
    lne_px3 = new QLineEdit;
    lne_px3->setValidator(ival_indig);
    lne_px3->setPlaceholderText("x3");
    lne_py3 = new QLineEdit;
    lne_py3->setValidator(ival_indig);
    lne_py3->setPlaceholderText("y3");

    pbt_run = new QPushButton("Run");
    connect(pbt_run, SIGNAL(clicked()), this, SLOT(SlotPButtonRun()));
    pbt_erase = new QPushButton("Erase");
    connect(pbt_erase, SIGNAL(clicked()), this, SLOT(SlotPButtonErase()));

    QGridLayout* glay_work = new QGridLayout;
    glay_work->addWidget(lne_px1, 0, 0);
    glay_work->addWidget(lne_py1, 0, 1);
    glay_work->addWidget(lne_px2, 1, 0);
    glay_work->addWidget(lne_py2, 1, 1);
    glay_work->addWidget(lne_px3, 2, 0);
    glay_work->addWidget(lne_py3, 2, 1);
    glay_work->addWidget(pbt_run, 3, 0);
    glay_work->addWidget(pbt_erase, 3, 1);

    lstwdg_xint = new QListWidget;
    lbl_lstwdg_xint = new QLabel("X Integer");

    QVBoxLayout* vlay_work = new QVBoxLayout;
    vlay_work->addLayout(glay_work);
    vlay_work->addWidget(lbl_lstwdg_xint);
    vlay_work->addWidget(lstwdg_xint);


    QHBoxLayout* hlay_main = new QHBoxLayout;
    hlay_main->addLayout(vlay_work);
    hlay_main->addWidget(grview_main);

    this->setLayout(hlay_main);
}

BazierCurve::~BazierCurve() {}

void BazierCurve::SlotPButtonRun()
{
    if (checkLineEdit()){
        this->getPoints();
        this->calculate();
        this->printXintPoints();
        this->paint();
    } else {
        msgb_erinp->open();
    }
}

void BazierCurve::SlotPButtonErase()
{
    lne_px1->clear();
    lne_py1->clear();
    lne_px2->clear();
    lne_py2->clear();
    lne_px3->clear();
    lne_py3->clear();
    vec_points.clear();
    lstwdg_xint->clear();
}

void BazierCurve::getPoints()
{
    point_start = {lne_px1->text().toFloat(), lne_py1->text().toFloat()};
    point_addit = {lne_px2->text().toFloat(), lne_py2->text().toFloat()};
    point_end = {lne_px3->text().toFloat(), lne_py3->text().toFloat()};
}

bool BazierCurve::checkLineEdit()
{
    if (lne_px1->text() == "")
        return false;
    if (lne_py1->text() == "")
        return false;
    if (lne_px2->text() == "")
        return false;
    if (lne_py2->text() == "")
        return false;
    if (lne_px3->text() == "")
        return false;
    if (lne_py3->text() == "")
        return false;

    return true;
}

void BazierCurve::calculate()
{
    vec_points.clear();
    int countPoints = 10;//кол-во точек
    double d_t = (double)1/countPoints;
    double t = 0 - d_t;
    for (int i = 0; i < countPoints + 1; ++i)
    {
        double n = t;
        t += d_t;
        vec_points.push_back(
                    {std::pow((1-t), 2) * point_start.x() + 2 * (1-t) * t * point_addit.x() + std::pow(t, 2) * point_end.x(),
                    std::pow((1-t), 2) * point_start.y() + 2 * (1-t) * t * point_addit.y() + std::pow(t, 2) * point_end.y()});
    }
}

void BazierCurve::printXintPoints()
{
    lstwdg_xint->clear();
    QString qstr;
    for (size_t i = 0; i < vec_points.size(); ++i){
        qstr.clear();
        int m = static_cast<int>(vec_points.at(i).x()) ;
        if (vec_points.at(i).x() == m || i == vec_points.size() - 1){
            qDebug() << "x: " <<vec_points.at(i).x() << "y: " << vec_points.at(i).y() << "\n";
            QString qstr_temp_x = QString("x: %1 ").arg(vec_points.at(i).x());
            QString qstr_temp_y = QString("y: %1 ").arg(vec_points.at(i).y());
            qstr.append(qstr_temp_x);
            qstr.append(qstr_temp_y);
            lstwdg_xint->addItem(qstr);
        }
    }
}

void BazierCurve::paint()
{
    QPainterPath ptpath;
    ptpath.cubicTo(point_start, point_addit, point_end);
    QPolygonF temp_polygon;
    QGraphicsPathItem* grpath = new QGraphicsPathItem(ptpath);
    grscene_main->addItem(grpath);
}


