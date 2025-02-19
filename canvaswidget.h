#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include <QImage>
#include <QColor>
#include <QPoint>

class CanvasWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanvasWidget(QWidget *parent = nullptr);
    void setPenColor(const QColor &newColor);
    QColor getPenColor() const;
    void setPenSize(int newSize);
    int getPenSize() const;
    void clearCanvas();
    void setBackgroundColor(const QColor &color);
    QColor getBackgroundColor() const;
    void resizeCanvas(int width, int height);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QImage canvas;
    QColor penColor;
    int penSize;
    QPoint lastPoint;
    bool drawing;
};

#endif // CANVASWIDGET_H
