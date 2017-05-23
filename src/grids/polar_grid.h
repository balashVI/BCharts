#ifndef POLAR_GRID_H
#define POLAR_GRID_H

#include "base_grid.h"

class PolarGrid : public BaseGrid
{
    Q_OBJECT
public:
    explicit PolarGrid(QObject *parent = 0);

    QSGNode *updatePaintNode(QSGNode *oldNode, QRectF boundingRect, bool force) override;

protected:
    QSGNode *updateGridLines(QSGNode *oldNode, QRectF boundingRect, bool force);
};

#endif // POLAR_GRID_H
