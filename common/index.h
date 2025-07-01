#ifndef INDEX_H
#define INDEX_H
#define BATTLEWIDTH 1600
#define BATTLEHEIGHT 900
namespace Index{
enum PageIndex{
    MenuIndex,CastIndex,BattleIndex,SettlementIndex
};
enum StateIndex{
    IdleState,WalkingState,JumpingState,FallingState,AttackingState,DefendingState,StunnedState
};
}
#endif // INDEX_H
