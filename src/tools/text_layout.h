#ifndef TEXT_LAYOUT_H
#define TEXT_LAYOUT_H

#include <QQuickPaintedItem>

struct TextItem {
    QString text;
    QRectF rect;
};

class TextLayout : public QQuickPaintedItem
{
    Q_OBJECT
public:
    explicit TextLayout(QQuickItem *parent = 0);

    void clear();
    void add(QString text, QPointF position);

public slots:
    void setFont(const QFont &font);
    void setColor(QColor color);

protected:
    void virtual paint(QPainter *painter) override;

private:
    QList<TextItem> mTextItems;
    QFont mFont;
    QColor mColor;

    double mLabelHeight;
};

#endif // TEXT_LAYOUT_H
