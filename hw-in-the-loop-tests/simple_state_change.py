import sys
import click
from lib import CANBus, CANFrame, ARBITRATION_IDS, STATE_IDS

def watch_acks_on_rx(state_acks):
    def on_rx(frame, timestamp):
        if frame.arb_id == ARBITRATION_IDS["BMS_STATE_CHANGE"]:
            if frame.payload[0] == STATE_IDS["LV_READY"]:
                state_acks[0] = True
    return on_rx

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def simple_state_change(interface):
    with CANBus(interface) as bus:
        state_acks = [False]
        bus.set_rx_callback(watch_acks_on_rx(state_acks))

        frame = CANFrame(ARBITRATION_IDS["CONTROLLER_COMMAND"], STATE_IDS["LV_READY"])
        bus.put_frame(frame)

        print("Waiting for state machine")
        while not state_acks[0]:
            pass     

        print("ACK Received, transitioned from Resting -> LV Armed")


if __name__ == "__main__":
    try:
        simple_state_change()
    except KeyboardInterrupt:
        sys.exit(0)

