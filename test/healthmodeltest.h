#ifndef HEALTHMODELTEST_H
#define HEALTHMODELTEST_H

#include <QObject>

class HealthModelTest : public QObject
{
    Q_OBJECT
public:
    explicit HealthModelTest(QObject *parent = nullptr);

signals:
private slots:
    void testAttackWidthAndSingleHit();
};

#endif // HEALTHMODELTEST_H
