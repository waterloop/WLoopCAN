import sys
import click
from lib import CANBus, CANFrame

CONTROLLER_COMMAND = 0x00
BMS_STATE_CHANGE_COMMAND = 0x0b
MC_STATE_CHANGE_COMMAND = 0x15

LV_READY_STATE = 0x01


def on_rx(state_acks):
    return (
        lambda frame, timestamp:
        print("Hi, {frame.arb_id}")
    )

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def script_name(interface):
    with CANBus(interface) as bus:
        bus.set_rx_callback(on_rx)
        
        frame = CANFrame(CONTROLLER_COMMAND, LV_READY_STATE)
        bus.put_frame(frame)

        


if __name__ == "__main__":
    try:
        script_name()
    except KeyboardInterrupt:
        sys.exit(0)

