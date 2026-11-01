// STAND-IN virtual interface prefix. Burn names the slots below; CD2 ApplyLeftHanded
// invokes SetActionMap at +0x1C, matching Burn's order. Object fields remain unmodelled.
#ifndef INPUT_CGAMECONTROLLER_H
#define INPUT_CGAMECONTROLLER_H
namespace Input
{
    class cActionMap;
    class cControlInput;
    class cGameController
    {
    public:
        virtual ~cGameController();
        virtual const cControlInput &RetActionInput(int actionID) const;
        virtual void SetActionInput(int actionID, float input);
        virtual bool CanActivateAction(int actionID) const;
        virtual bool CanReleaseAction(int actionID) const;
        virtual void DebounceAction(int actionID);
        virtual void DebounceControls();
        virtual void SetActionMap(cActionMap *map, unsigned char id);
    };
}
#endif
