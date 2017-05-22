#ifndef POLAR_GRID_H
#define POLAR_GRID_H

#include <QObject>

class PolarGrid : public QObject
{
    Q_OBJECT
public:
    explicit PolarGrid(QObject *parent = 0);

signals:

public slots:
};

#endif // POLAR_GRID_H