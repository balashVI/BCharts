#include "textlayout.h"

#include <QPainter>

TextLayout::TextLayout(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    QFontMetrics metrics(mFont);
    mLabelHeight = metrics.height();
}

void TextLayout::clear()
{
    mTextItems.clear();
}

void TextLayout::add(QString text, QPointF position)
{
    QFontMetrics metrics(mFont);
    double width = metrics.width(text);

    QRectF rect;
    rect.setX(position.x() - 0.5 * width);
    rect.setY(position.y() - 0.5 * mLabelHeight);
    rect.setWidth(width);
    rect.setHeight(mLabelHeight);

    TextItem ti;
    ti.text = text;
    ti.rect = rect;
    mTextItems.append(ti);
}

void TextLayout::setFont(const QFont &font)
{
    mFont = font;

    QFontMetrics metrics(mFont);
    mLabelHeight = metrics.height();
}

void TextLayout::paint(QPainter *painter)
{
    painter->setFont(mFont);
    for (TextItem &item : mTextItems)
    {
        painter->drawText(item.rect, Qt::AlignCenter, item.text);
    }
}
