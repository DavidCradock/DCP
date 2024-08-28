/// \file Timer.h
/// \brief Contains the CTimer class.
/// 
/// 

#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <string>

namespace DCL
{
    /// \brief Deals with time related concepts with additional features compared to CTimerMinimal.
    ///
    /// Create an object of this class, keep it around and call update() between the code which you wish to measure the time difference.
    /// Then call getSecondsPast() to obtain the time passed since the two calls to update()
    /// There are also two framerate methods which return what the framerate is, based on the time passed between the last two calls to update().
    /// There's getFPS() which simply returns the current frames per second and then there's...
    /// getFPSAveraged() which returns the frames per second which have been averaged over a certain amount of time.
    /// This "certain amount of time" is, by default, set to be 1 update per second, but can be changed with a call to setAveragedFPSRate()
    class CTimer
    {
    public:

        /// \brief Constructor
        CTimer();

        /// \brief Call this to compute time difference between last call to this method.
        void update(void);

        /// \brief Pause this timer, preventing any updates and making it so getSecondsPast() returns zero.
        ///
        /// Call Resume() to unpause.
        /// Only getSecondsPast is affected, all other methods still return normal values.
        void pause(void);

        /// \brief If the timer was paused with a call to pause(), this resumes business as normal.
        void resume(void);

        /// \brief Returns time passed in seconds since last call to update() method.
        ///
        /// \return Time passed in seconds since last call to update() method.
        float getSecondsPast(void) const;

        /// \brief Suspends execution of the calling thread for the parsed number of milliseconds.
        /// 
        /// \param uiMilliseconds The number of milliseconds to sleep for.
        /// 
        /// The sleep may be lengthened slightly by any system activity or by the time spent processing the call or by the granularity of system timers. 
        void sleep(unsigned int uiMilliseconds) const;

        /// \brief Sets the delay in seconds at which the getFPSAveraged() method's return value will be updated.
        /// 
        /// \param fSecondsBetweenUpdates How much time in seconds before the FPSS value is updated.
        /// 
        /// For example, parsing a value of 3.0 for fSecondsBetweenUpdates will update once every 3 seconds which is the default
        void setAveragedFPSRate(float fSecondsBetweenUpdates);

        /// \brief Returns the currently set rate at which the getFPSAveraged() method's return value will be updated per second.
        ///
        /// \return The currently set rate at which the getFPSAveraged() method's return value will be updated per second.
        float getAveragedFPSRate(void) const;

        /// \brief Returns computed Frames Per Second current value.
        ///
        /// \return The computed Frames Per Second current value.
        float getFPS(void) const;

        /// \brief Returns computed Frames Per Second averaged value.
        ///
        /// \return Computed Frames Per Second averaged value.
        float getFPSAveraged(void) const;

        /// \brief Returns the number of seconds until the next time the FPSAveraged value is updated.
        ///
        /// \return The number of seconds until the next time the FPSAveraged value is updated.
        float getFPSAveragedTimeUntilNextUpdate(void) const;

        /// \brief Resets all values to sane values, including the member set by setAveragedFPSRate()
        /// 
        /// Also, if this timer has been paused, it is unpaused.
        void reset(void);

        /// \brief Returns amount of seconds that we've been calling update()
        ///
        /// \return The amount of seconds that we've been calling update()
        float getRuntimeSeconds(void) const;

        /// \brief Based on current runtime, sets parsed values to seconds, minutes, hours, days and weeks
        ///
        /// \param fSeconds Will hold the runtime's seconds past
        /// \param iMinutes Will hold the runtime's minutes past
        /// \param iHours Will hold the runtime's hours past
        /// \param iDays Will hold the runtime's days past
        /// \param iWeeks Will hold the runtime's weeks past
        void getClock(float& fSeconds, int& iMinutes, int& iHours, int& iDays, int& iWeeks) const;

        /// \brief Based on current runtime, returns current runtime as a string holding seconds, minutes, hours, days and weeks
        ///
        /// \return The current runtime as a string holding seconds, minutes, hours, days and weeks
        std::string getClock(void) const;
    private:
        std::chrono::duration<double> _mdTimeDeltaSec;
        std::chrono::time_point<std::chrono::steady_clock> _mdTimePointOld, _mdTimePointNew;

        double _mdDeltaSec;                     ///< Holds time delta since last call to update() method in seconds.
        bool _mbPaused;                         ///<  pause() and resume()

        // Members for FPS
        double _mdFPS;                          ///<  Holds computed current frames per second value
        double _mdFPSFrameTime;                 ///<  Used to compute FPS stuff
        unsigned int _muiNumFrames;             ///<  Used to compute FPS stuff

        // Members for FPS averaged
        double _mdFPSAveraged;                  ///<  Holds computed averaged frames per second value
        double _mdFPSAveragedRate;              ///<  Number of times per second in which is the delay until unpdating the value returned by getFPSAveraged() method.
        double _mdFPSAveragedTimeCount;         ///<  Used to compute FPSAveraged stuff
        int _miFPSAveragedNumCallsPerSec;       ///<  Used to compute FPSAveraged stuff
        double _mdFPSAveragedAccum;             ///<  Used to compute FPSAveraged stuff
        double _mdRuntimeInSeconds;             ///<  Number of seconds we've been calling update()
    };

}   // namespace DCL

#endif // #ifndef FILENAME_H
