#ifndef LABEL_CONFIGS_H
#define LABEL_CONFIGS_H

#include <QObject>

class LabelConfigs : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool drawBackground READ drawBackground WRITE setDrawBackground NOTIFY drawBackgroundChanged)
public:
    explicit LabelConfigs(QObject *parent = 0);

    bool drawBackground() const;
    void setDrawBackground(bool draw);

signals:
    void drawBackgroundChanged(bool draw);

protected:
    bool pDrawBackground;
};

#endif // LABEL_CONFIGS_H
