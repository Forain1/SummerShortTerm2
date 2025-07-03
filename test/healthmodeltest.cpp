#include "healthmodeltest.h"
#include "../model/topmodel.h"
#include "../model/characterstate.h"
#include <QtTest/QTest>

HealthModelTest::HealthModelTest(QObject *parent)
    : QObject{parent}
{
}

void HealthModelTest::testAttackWidthAndSingleHit()
{
    TopModel model;
    model.initCharacter();
    auto c0 = model.getCharacter0();
    auto c1 = model.getCharacter1();

    // 设置角色重叠
    c0->setX(100);
    c0->setY(200);
    c0->setWidth(50);
    c0->setHeight(50);
    c0->setIdleWidth(50);
    c0->setIdleHeight(50);
    c1->setX(120); // 100+50>120，重叠
    c1->setY(200);
    c1->setWidth(50);
    c1->setHeight(50);
    c1->setIdleWidth(50);
    c1->setIdleHeight(50);

    // 设置c1为攻击状态，c0为防御状态
    c1->setCharacterState(new AttackingState());
    c0->setCharacterState(new IdleState());
    c1->setHasHit(false);
    int baseWidth = c1->getIdleWidth();
    int attackInc = c1->getAttackWidthInc();
    int maxFrame = AttackingState().getMaxFrame();

    int health0 = c0->getCurrentHealth();
    int health1 = c1->getCurrentHealth();

    // 攻击动画逐帧推进，width逐渐变宽，只能扣一次血
    bool hitHappened = false;
    for(int frame=0; frame<=maxFrame+2; ++frame) {
        int prevWidth = c1->getWidth();
        model.nextFrame();
        int curWidth = c1->getWidth();
        // width应该逐渐变宽，最后恢复
        if(frame < maxFrame) {
            QVERIFY(curWidth >= prevWidth);
            QVERIFY(curWidth <= baseWidth + attackInc);
        } else {
            // 动画结束后width恢复
            QCOMPARE(curWidth, baseWidth);
        }
        // 只会扣一次血
        if(c0->getCurrentHealth() < health0) {
            if(!hitHappened) {
                hitHappened = true;
                QCOMPARE(c0->getCurrentHealth(), health0 - 5); // Idle被攻击-5
            } else {
                // 后续帧不能再扣血
                QCOMPARE(c0->getCurrentHealth(), health0 - 5);
            }
        }
    }
    QVERIFY(hitHappened);
    // c1血量不变
    QCOMPARE(c1->getCurrentHealth(), health1);
}

QTEST_MAIN(HealthModelTest)
#include "healthmodeltest.moc"
