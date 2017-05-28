#include "text_layout.h"

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
    if (font != mFont)
    {
        mFont = font;

        QFontMetrics metrics(mFont);
        mLabelHeight = metrics.height();

        for (TextItem &i : mTextItems)
        {
            double width = metrics.width(i.text);

            QPointF center = i.rect.center();
            i.rect.setX(center.x() - 0.5 * width);
            i.rect.setY(center.y() - 0.5 * mLabelHeight);
            i.rect.setWidth(width);
            i.rect.setHeight(mLabelHeight);
        }

        update();
    }
}

void TextLayout::setColor(QColor color)
{
    if (color != mColor)
    {
        mColor = color;

        update();
    }
}

void TextLayout::paint(QPainter *painter)
{
    painter->setFont(mFont);
    painter->setPen(mColor);
    for (TextItem &item : mTextItems)
    {
        painter->drawText(item.rect, Qt::AlignCenter, item.text);
    }
}
