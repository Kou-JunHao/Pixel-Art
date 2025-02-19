#include "canvaswidget.h"
#include <QPainter>
#include <QMouseEvent>

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent),
    penColor(Qt::black), penSize(1), drawing(false)
{
    setBackgroundColor(Qt::white);
    resizeCanvas(800, 600);
}

void CanvasWidget::setPenColor(const QColor &newColor)
{
    penColor = newColor;
}

void CanvasWidget::setPenSize(int newSize)
{
    penSize = newSize;
}

QColor CanvasWidget::getPenColor() const
{
    return penColor;
}

int CanvasWidget::getPenSize() const
{
    return penSize;
}

void CanvasWidget::clearCanvas()
{
    canvas.fill(Qt::white);
    update();
}

void CanvasWidget::setBackgroundColor(const QColor &color)
{
    canvas.fill(color);
    update();
}

QColor CanvasWidget::getBackgroundColor() const
{
    return canvas.pixelColor(0, 0);
}

void CanvasWidget::resizeCanvas(int width, int height)
{
    QImage newCanvas(width, height, QImage::Format_ARGB32);
    newCanvas.fill(Qt::white);
    
    QPainter painter(&newCanvas);
    painter.drawImage(0, 0, canvas);
    
    canvas = newCanvas;
    update();
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing) {
        QPainter painter(&canvas);
        painter.setPen(QPen(penColor, penSize, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        painter.drawLine(lastPoint, event->pos());
        lastPoint = event->pos();
        update();
    }
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
    }
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, canvas);
}
