/// \file FiniteStateMachine.h
/// \brief Contains finite state machine stuff
/// 
/// 

#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <map>
#include <string>

namespace DCL
{
	class CFiniteStateMachine;

	/// \brief Finite state base class with which to derive our FSM state classes from for use with the CFiniteStateMachine class.
	///
	/// This represents a single state in a finite state machine and has several pure virtual methods which need to be 
	/// implemented within any class which is derived from this one.
	class CFiniteStateBase
	{
	public:
		/// \brief This is called when this state is first entered.
		virtual void onEnter(void) = 0;

		/// \brief This is called when this state is left.
		virtual void onExit(void) = 0;

		/// \brief This is called whilst the state is active.
		///
		/// \param pFSM A pointer to a CFiniteStateMachine which will manage this state.
		/// This is usefull to allow the state to change to another named state by calling pFSM->switchToState()
		virtual void onActive(CFiniteStateMachine* pFSM) = 0;
	};

	/// \brief This is a generic finite state machine used alongside classes derived from CFiniteStateBase.
	///
	/// Each state has three methods which need to be implemented (See CFiniteStateBase)
	/// First create one or more classes derived from the base class and implement each of the three methods,
	/// onEnter(), onExit() and onActive().
	/// We create an object of this class and objects of each of our classes derived from the CFiniteStateBase class.
	/// Then we add each of those objects to this one, specifying a unique name for each state.
	/// Initially, the state machine has no state and upon calling update() will do nothing.
	/// We need to call switchToState(std::string strStateName) to set the initial state.
	/// Upon doing so, the state's onEnter() method will be called, followed by it's onActive() method, until the
	/// state machine is asked to switch to another state with a call of switchToState() either externally, or from
	/// within a state itself.
	/// Usage example:
	/// First, create a couple of classes derived from the CFiniteStateBase class which will be used for the FSM's states
	/// \code
	/// class CMyFirstState : public CFiniteStateBase
	/// {
	/// public:
	///		void onEnter(void){	// Do stuff for when this state is entered	}
	///		void onExit(void){	// Do stuff for when this state is left	}
	///		void onActive(CFiniteStateMachine* pFSM){ pFSM->switchToState("MySecondState");	// Switch to the second state }
	/// };
	/// class CMySecondState : public CFiniteStateBase
	/// {
	/// public:
	///		void onEnter(void){	// Do stuff for when this state is entered	}
	///		void onExit(void){	// Do stuff for when this state is left	}
	///		void onActive(CFiniteStateMachine* pFSM){ // Do stuff in this state }
	/// };
	/// // Now that the two state classes have been created, we need to create the FSM itself and allocate memory for each of the state classes.
	/// CFiniteStateMachine fsm;
	/// CMyFirstState* pStateOne = new CMyFirstState;
	/// CMySecondState* pStateTwo = new CMySecondState;
	/// // Now we need to add each state to the FSM, giving them each a unique name...
	/// fsm.addState("state1", pStateOne);
	/// fsm.addState("state2", pStateTwo);
	/// // Note: There's no need to delete either of the states, as this is done for us
	/// // when the FSM is destroyed, or by calling either removeState() or removeAllStates() of the FSM object.
	/// // Now call fsm.update() to call the currently set state's onActive() method.
	/// \endcode
	class CFiniteStateMachine
	{
	public:

		/// \brief Frees the state pointers which have been added with a call to addState()
		///
		/// There's no need to delete the states given during a call to addState() as this is performed here.
		~CFiniteStateMachine();

		/// \brief Updates the state machine, calling the currently set state's onActive() method.
		///
		/// Remember that initially, no current state is set, so this will initially do nothing until switchToState() is called.
		void update(void);

		/// \brief Switches to the named state.
		///
		/// \param strStateName The name given to a previously added state.
		/// 
		/// This usually calls the currently set state's onExit() method, followed by the new state's onEnter() method.
		/// But the first time this is called, the FSM has no currently set state, so the call to onExit() is not performed.
		/// If the named state doesn't exist, then an exception occurs.
		void switchToState(const std::string& strStateName);

		/// \brief Adds a new uniquely named state
		///
		/// \param strStateName The name given to a previously added state.
		/// \param pState A pointer to a class object derived from the CFiniteStateBase class.
		/// 
		/// If the name already exists, an exception occurs.
		/// The CFiniteStateBase object has to be allocated yourself prior to calling this method.
		/// Once the state object has been added here, there's no need to keep it around for deletion later,
		/// as this class's removeState(), removeAllStates() and destructor will delete them for us.
		/// Also note that this method checks to see if the given state pointer is NULL and throws an exception if so.
		void addState(const std::string& strStateName, CFiniteStateBase* pState);

		/// \brief Removes a previously added state
		///
		/// \param strStateName The name given to a previously added state.
		/// 
		/// If the named state doesn't exist, an exception occurs
		/// The state given during a call to addState() is deleted for us here, no need to delete it ourselves.
		void removeState(const std::string& strStateName);

		/// \brief Returns whether a named state has already been added or not
		/// 
		/// \param strStateName The name given to a previously added state.
		/// \return Whether the named state exists (true) or not (false)
		bool getStateExists(const std::string& strStateName);

		/// \brief Removes all previously added states
		///
		/// The states given during calls to addState() are deleted for us here, no need to delete them ourselves.
		void removeAllStates(void);

		/// \brief Get the number of currently added states.
		///
		/// \return The current number of added states.
		int getNumberStates(void);

		/// \brief Returns pointer to the state at the given index.
		///
		/// \param uiIndex Index number of the state. Valid range is 0 to getNumberStates()-1 (If at least one state has been added)
		/// \return a pointer to the found state.
		/// 
		/// If an invalid index is given, an exception occurs
		CFiniteStateBase* getState(unsigned int uiIndex);

		/// \brief Returns pointer to the named state.
		///
		/// \param strStateName The name given to a previously added state.
		/// \return a pointer to the found state.
		/// 
		/// If the named state couldn't be found, an exception occurs.
		CFiniteStateBase* getState(const std::string strStateName);
	private:
		std::string _mstrCurrentState;							///< The name of the currently set state. This is initially empty, IE, there's no state.
		std::map<std::string, CFiniteStateBase*> _mmapStates;	///< Holds each uniquely named state and a pointer to the object.
	};

}	// namespace DCL

#endif	// #ifndef FILENAME_H
