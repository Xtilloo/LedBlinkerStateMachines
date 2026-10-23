// ======================================================================
// \title  LedStateMachine.cpp
// \author xtilloo
// \brief  cpp file for LedStateMachine component implementation class
// ======================================================================

#include "Ledblinkerstatemachine/Components/LedStateMachine/LedStateMachine.hpp"

namespace Ledblinkerstatemachine {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

LedStateMachine ::LedStateMachine(const char* const compName) : LedStateMachineComponentBase(compName) {}

LedStateMachine ::~LedStateMachine() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void LedStateMachine ::run_handler(FwIndexType portNum, U32 context) {

    // Logic states for the buttons
    Fw::Logic red_state;
    Fw::Logic yellow_state;
    Fw::Logic green_state;

    // GPIO reads for each button 
    // (make sure these are configured in topology.cpp to the correct file)
    this->gpioRead_out(0, red_state);
    this->gpioRead_out(1, yellow_state);
    this->gpioRead_out(2, green_state);

    // Send signals
    if (red_state == Fw::Logic::HIGH) {
        this->LedStateMachine_sendSignal_RED_BUTTON_PRESS();
    }
    else if (yellow_state == Fw::Logic::HIGH) {
        this->LedStateMachine_sendSignal_YELLOW_BUTTON_PRESS();
    }
    else if (green_state == Fw::Logic::HIGH) {
        this->LedStateMachine_sendSignal_GREEN_BUTTON_PRESS();
    }

    LedStateMachine_LedSMStateMachineBase::State state = this->LedStateMachine_getState();
    if (this->LedStateMachine_getState() == LedStateMachine_LedSMStateMachineBase::State::BLINK) {
        // Toggle the LED
        DoToggleLED();
    }

}

// ----------------------------------------------------------------------
// Implementations for internal state machine actions
// ----------------------------------------------------------------------

void LedStateMachine ::Ledblinkerstatemachine_LedStateMachine_LedSM_action_TURN_OFF(
    SmId smId,
    Ledblinkerstatemachine_LedStateMachine_LedSM::Signal signal) {
    // Turn off the GPIO line connected to the LED
    this->log_ACTIVITY_HI_BUTTON_PRESS(Fw::String("RED"));
    this->gpioWrite_out(0, Fw::Logic::LOW);
}

void LedStateMachine ::Ledblinkerstatemachine_LedStateMachine_LedSM_action_TURN_ON(
    SmId smId,
    Ledblinkerstatemachine_LedStateMachine_LedSM::Signal signal) {
    // Turn on the GPIO line connected to the LED
    this->log_ACTIVITY_HI_BUTTON_PRESS(Fw::String("GREEN"));
    this->gpioWrite_out(0, Fw::Logic::HIGH);
}

void LedStateMachine ::Ledblinkerstatemachine_LedStateMachine_LedSM_action_START_BLINK(
    SmId smId,
    Ledblinkerstatemachine_LedStateMachine_LedSM::Signal signal) {
    // Transition the GPIO line connected to toggle on an off every now and then
    this->log_ACTIVITY_HI_BUTTON_PRESS(Fw::String("YELLOW"));
}

void LedStateMachine::DoToggleLED() {
    if (this->LED_on){
        this->gpioWrite_out(0, Fw::Logic::LOW);
        this->LED_on = 0;
    }
    else{
        this->gpioWrite_out(0, Fw::Logic::HIGH);
        this->LED_on = 1;
    }
}

}  // namespace Ledblinkerstatemachine
