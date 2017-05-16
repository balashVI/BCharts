#include "categoryaxis.h"

CategoryAxis::CategoryAxis(QQuickItem *parent) :
    AbstractAxis(parent), pBarValueSpacing{3}, pBarDatasetSpacing{5}
{
}

int CategoryAxis::barDatasetSpacing() const
{
    return pBarDatasetSpacing;
}

void CategoryAxis::setBarDatasetSpacing(int value)
{
    pBarDatasetSpacing = value;
    emit barDatasetSpacingChanged();
}

int CategoryAxis::barValueSpacing() const
{
    return pBarValueSpacing;
}

void CategoryAxis::setBarValueSpacing(int value)
{
    pBarValueSpacing = value;
    emit barValueSpacingChanged();
}

const QList<QString> &CategoryAxis::labels() const
{
    return pLabels;
}

void CategoryAxis::setLabels(QList<QString> newLabels)
{
    pLabels = std::move(newLabels);
    calculateWidthOfLongestLabel();
    emit labelsChanged();
}
