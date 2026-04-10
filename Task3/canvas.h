#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QImage>
#include <QPolygonF>
#include <vector>

struct Annotation {
    QPolygonF polygon;
    QString label;
    bool selected = false;
};

class Canvas : public QWidget
{
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    void loadImage(const QString &path);
    void saveJson(const QString &file);
    void loadJson(const QString &file);

protected:
    void paintEvent(QPaintEvent *) override;
    void mousePressEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void mouseDoubleClickEvent(QMouseEvent *) override;
    void keyPressEvent(QKeyEvent *) override;

private:
    QImage image;
    double scaleFactor = 1.0;

    std::vector<Annotation> annotations;
    QPolygonF currentPolygon;
    QPointF currentMouse;

    QStringList labels = {"Car", "Tree", "Person"};
};
#endif // CANVAS_H
