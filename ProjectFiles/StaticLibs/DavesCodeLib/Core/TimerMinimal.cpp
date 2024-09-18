#include "TimerMinimal.h"
#include "Logging.h"

namespace DCL
{
    CTimerMinimal::CTimerMinimal()
    {
        LOG("Constructor called.");;
        reset();
    }

    double CTimerMinimal::getSecondsPast(void) const
    {
        return _mdDeltaSec;
    }

    void CTimerMinimal::update(void)
    {
        _mdTimePointNew = std::chrono::steady_clock::now();
        _mdTimeDeltaSec = _mdTimePointNew - _mdTimePointOld;
        _mdTimePointOld = _mdTimePointNew;
        _mdDeltaSec = _mdTimeDeltaSec.count();
    }

    void CTimerMinimal::reset(void)
    {
        _mdTimePointNew = std::chrono::steady_clock::now();
        _mdTimePointOld = _mdTimePointNew;
        _mdTimeDeltaSec = _mdTimePointNew - _mdTimePointOld;
        _mdDeltaSec = _mdTimeDeltaSec.count();
    }
}   // namespace DCL