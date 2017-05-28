#ifndef LABEL_CONFIGS_H
#define LABEL_CONFIGS_H

#include <QObject>
#include <QColor>
#include <QFont>

class LabelConfigs : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool visible READ visible WRITE setVisible NOTIFY visibleChanged)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(bool drawBackground READ drawBackground WRITE setDrawBackground NOTIFY drawBackgroundChanged)
public:
    explicit LabelConfigs(QObject *parent = 0);

    bool visible() const;
    void setVisible(bool visible);

    QFont font() const;
    void setFont(QFont f);

    QColor color() const;
    void setColor(QColor c);

    bool drawBackground() const;
    void setDrawBackground(bool draw);

signals:
    void visibleChanged(bool visible);
    void fontChanged(QFont font);
    void colorChanged(QColor c);
    void drawBackgroundChanged(bool draw);

private:
    bool pVisible;
    QFont pFont;
    QColor pColor;
    bool pDrawBackground;
};

#endif // LABEL_CONFIGS_H
