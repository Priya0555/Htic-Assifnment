#include "canvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <QInputDialog>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
Canvas::Canvas(QWidget *parent) : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
}

void Canvas::loadImage(const QString &path)
{
    image.load(path);
    update();
}

void Canvas::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if (!image.isNull()) {
        QSize scaled = image.size() * scaleFactor;
        p.drawImage(QRect(QPoint(0,0), scaled), image);
    }

    p.setPen(QPen(Qt::green, 2));

    for (auto &ann : annotations) {
        QPolygonF poly;
        for (auto &pt : ann.polygon)
            poly << pt * scaleFactor;

        p.drawPolygon(poly);

        if (!ann.label.isEmpty())
            p.drawText(poly.first(), ann.label);
    }

    // current drawing
    if (!currentPolygon.isEmpty()) {
        QPolygonF temp;
        for (auto &pt : currentPolygon)
            temp << pt * scaleFactor;

        temp << currentMouse;
        p.drawPolyline(temp);
    }
}

void Canvas::mousePressEvent(QMouseEvent *e)
{
    QPointF pt = e->pos() / scaleFactor;

    if (e->button() == Qt::LeftButton) {
        currentPolygon << pt;
    }
    update();
}

void Canvas::mouseMoveEvent(QMouseEvent *e)
{
    currentMouse = e->pos();
    update();
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *)
{
    if (currentPolygon.size() < 3) return;

    bool ok;
    QString label = QInputDialog::getItem(this, "Label",
                                          "Select Label:",
                                          labels, 0, false, &ok);

    if (ok) {
        Annotation ann;
        ann.polygon = currentPolygon;
        ann.label = label;
        annotations.push_back(ann);
    }

    currentPolygon.clear();
    update();
}

void Canvas::keyPressEvent(QKeyEvent *e)
{
    if (e->key() == Qt::Key_Escape) {
        currentPolygon.clear();
        update();
    }

    if (e->key() == Qt::Key_Delete && !annotations.empty()) {
        annotations.pop_back();
        update();
    }

    if (e->key() == Qt::Key_Plus)
        scaleFactor *= 1.2;

    if (e->key() == Qt::Key_Minus)
        scaleFactor /= 1.2;

    update();
}

void Canvas::saveJson(const QString &file)
{
    QJsonArray arr;

    for (auto &ann : annotations) {
        QJsonObject obj;
        obj["label"] = ann.label;

        QJsonArray pts;
        for (auto &p : ann.polygon) {
            QJsonObject pt;
            pt["x"] = p.x();
            pt["y"] = p.y();
            pts.append(pt);
        }

        obj["points"] = pts;
        arr.append(obj);
    }

    QJsonDocument doc(arr);
    QFile f(file);
    if (!f.open(QIODevice::WriteOnly)) {
        qDebug() << "Error: Cannot open file for writing";
        return;
    }

    f.write(doc.toJson());
    f.close();
}

void Canvas::loadJson(const QString &file)
{
    QFile f(file);

    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Error: Cannot open file for reading";
        return;
    }
    QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    annotations.clear();

    for (auto v : doc.array()) {
        Annotation ann;
        QJsonObject obj = v.toObject();
        ann.label = obj["label"].toString();

        for (auto p : obj["points"].toArray()) {
            QJsonObject pt = p.toObject();
            ann.polygon << QPointF(pt["x"].toDouble(),
                                   pt["y"].toDouble());
        }

        annotations.push_back(ann);
    }

    update();
}