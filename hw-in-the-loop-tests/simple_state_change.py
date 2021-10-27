import sys
import click
from lib import CANBus, CANFrame

CONTROLLER_COMMAND = 0x00
BMS_STATE_CHANGE_COMMAND = 0x0b
MC_STATE_CHANGE_COMMAND = 0x15

LV_READY_STATE = 0x01


def watch_acks_on_rx(state_acks):
    def on_rx(frame, timestamp):
        if frame.arb_id == BMS_STATE_CHANGE_COMMAND and frame.payload[0] == LV_READY_STATE:
            state_acks[0] = True
    return on_rx

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def script_name(interface):
    with CANBus(interface) as bus:
        state_acks = [False]
        bus.set_rx_callback(watch_acks_on_rx(state_acks))

        frame = CANFrame(CONTROLLER_COMMAND, LV_READY_STATE)
        bus.put_frame(frame)

        print("Waiting for state machine", end="")
        while not state_acks[0]:
            pass     

        print("ACK Received, transitioned from Resting -> LV Armed")


if __name__ == "__main__":
    try:
        script_name()
    except KeyboardInterrupt:
        sys.exit(0)

