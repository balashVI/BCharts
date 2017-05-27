#ifndef TEXTLAYOUT_H
#define TEXTLAYOUT_H

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

    void setFont(const QFont &font);

protected:
    void virtual paint(QPainter *painter) override;

private:
    QList<TextItem> mTextItems;
    QFont mFont;

    double mLabelHeight;
};

#endif // TEXTLAYOUT_H
