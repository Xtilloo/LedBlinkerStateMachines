// ======================================================================
// \title  LedStateMachine.hpp
// \author xtilloo
// \brief  hpp file for LedStateMachine component implementation class
// ======================================================================

#ifndef Ledblinkerstatemachine_LedStateMachine_HPP
#define Ledblinkerstatemachine_LedStateMachine_HPP

#include "Ledblinkerstatemachine/Components/LedStateMachine/LedStateMachineComponentAc.hpp"

namespace Ledblinkerstatemachine {

class LedStateMachine final : public LedStateMachineComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct LedStateMachine object
    LedStateMachine(const char* const compName  //!< The component name
    );

    //! Destroy LedStateMachine object
    ~LedStateMachine();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    //! Drives state machine transitions
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

  private:
    // ----------------------------------------------------------------------
    // Implementations for internal state machine actions
    // ----------------------------------------------------------------------

    //! Implementation for action TURN_OFF of state machine Ledblinkerstatemachine_LedStateMachine_LedSM
    void Ledblinkerstatemachine_LedStateMachine_LedSM_action_TURN_OFF(
        SmId smId,                                                   //!< The state machine id
        Ledblinkerstatemachine_LedStateMachine_LedSM::Signal signal  //!< The signal
        ) override;

    //! Implementation for action TURN_ON of state machine Ledblinkerstatemachine_LedStateMachine_LedSM
    void Ledblinkerstatemachine_LedStateMachine_LedSM_action_TURN_ON(
        SmId smId,                                                   //!< The state machine id
        Ledblinkerstatemachine_LedStateMachine_LedSM::Signal signal  //!< The signal
        ) override;

    //! Implementation for action START_BLINK of state machine Ledblinkerstatemachine_LedStateMachine_LedSM
    void Ledblinkerstatemachine_LedStateMachine_LedSM_action_START_BLINK(
        SmId smId,                                                   //!< The state machine id
        Ledblinkerstatemachine_LedStateMachine_LedSM::Signal signal  //!< The signal
        ) override;

    //! Simple helper function to toggle the LED
    void DoToggleLED();

    // Little helper variable to track LED state while blinking
    bool LED_on = 0;
};

}  // namespace Ledblinkerstatemachine

#endif
