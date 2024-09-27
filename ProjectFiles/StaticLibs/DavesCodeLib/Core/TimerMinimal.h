#ifndef TIMERMINIMAL_H
#define TIMERMINIMAL_H

#include <chrono>

namespace DCL
{
    /// \brief Deals with time related concepts with minimal features compared to CTimer.
    /// 
    /// Create an object of this class, keep it around and call update() between the code which you wish to measure the time difference.
    /// Then call getSecondsPast() to obtain the time passed since the two calls to update()
    /// This class is similar to CTimer, but with less features and is slightly faster to compute.
    /// It also returns the time delta as a double instead of float for more precision.
    ////
    class CTimerMinimal
    {
    public:
        /// \brief Constructor
        CTimerMinimal();

        /// \brief Call this to compute time difference between the last two calls to this method.
        void update(void);

        /// \brief Returns the time passed in seconds between the last two calls to update() method.
        /// \return Time passed in seconds between the last two calls to the update() method.
        double getSecondsPast(void) const;

        /// \brief Resets all values to sane values
        void reset(void);

    private:
        std::chrono::duration<double> _mdTimeDeltaSec;
        std::chrono::time_point<std::chrono::steady_clock> _mdTimePointOld, _mdTimePointNew;
        double _mdDeltaSec;                                                                     ///< Holds time delta since last call to update() method in seconds.
    };

}   // namespace DCL

#endif // #ifndef FILENAME_H
