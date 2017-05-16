#ifndef CATEGORYAXIS_H
#define CATEGORYAXIS_H

#include "abstractaxis.h"

class CategoryAxis : public AbstractAxis
{
    Q_OBJECT
public:
    explicit CategoryAxis(QQuickItem *parent = 0);

    ///Містить список даних
    Q_PROPERTY(QList<QString> labels READ labels WRITE setLabels NOTIFY labelsChanged)

    ///Містить відстань між стовпцями
    Q_PROPERTY(int barValueSpacing READ barValueSpacing WRITE setBarValueSpacing NOTIFY barValueSpacingChanged)

    ///Містить відстань між категоріями
    Q_PROPERTY(int barDatasetSpacing READ barDatasetSpacing WRITE setBarDatasetSpacing NOTIFY barDatasetSpacingChanged)

    int barDatasetSpacing() const;
    void setBarDatasetSpacing(int value);

    int barValueSpacing() const;
    void setBarValueSpacing(int value);

    const QList<QString> &labels() const;
    void setLabels(QList<QString> newLabels);

private:
    QList<QString> pLabels;
    int pBarValueSpacing, pBarDatasetSpacing;

signals:
    void labelsChanged();
    void barValueSpacingChanged();
    void barDatasetSpacingChanged();

public slots:

};

#endif // CATEGORYAXIS_H
