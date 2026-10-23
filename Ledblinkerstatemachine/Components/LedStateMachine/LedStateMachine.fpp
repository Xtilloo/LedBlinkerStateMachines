module Ledblinkerstatemachine {
    @ Component that uses an FPP state machine to control the state of an LED
    active component LedStateMachine {

        @ Drives state machine transitions
        sync input port run: Svc.Sched

        state machine LedSM {
            initial enter OFF

            action TURN_OFF
            action TURN_ON
            action START_BLINK

            signal RED_BUTTON_PRESS
            signal YELLOW_BUTTON_PRESS
            signal GREEN_BUTTON_PRESS

            state OFF {
                entry do {TURN_OFF}
                on YELLOW_BUTTON_PRESS enter BLINK
                on GREEN_BUTTON_PRESS enter ON

            }

            state ON {
                entry do {TURN_ON}
                on YELLOW_BUTTON_PRESS enter BLINK
                on RED_BUTTON_PRESS enter OFF
            }

            state BLINK {
                entry do {START_BLINK}
                on GREEN_BUTTON_PRESS enter ON
                on RED_BUTTON_PRESS enter OFF
            }
        }

        state machine instance LedStateMachine: LedSM

        event BUTTON_PRESS(button: string) \
            severity activity high \
            format "The {} button was pressed"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        
        @ Port for requesting the current time
        time get port timeCaller

        @ Enables command handling
        import Fw.Command

        @ Enables event handling
        import Fw.Event

        @ Enables telemetry channels handling
        import Fw.Channel

        @ Port to return the value of a parameter
        param get port prmGetOut

        @Port to set the value of a parameter
        param set port prmSetOut

        @ GPIO Ports to read the button GPIOs
        output port gpioRead: [3] Drv.GpioRead

        @ GPIO port to write to LED
        output port gpioWrite: Drv.GpioWrite

    }
}