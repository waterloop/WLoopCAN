import sys
import click
from lib import CANBus, CANFrame

def on_rx(frame, timestamp):
    pass

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def script_name(interface):
    with CANBus(interface) as bus:
        bus.set_rx_callback(on_rx)


if __name__ == "__main__":
    try:
        script_name()
    except KeyboardInterrupt:
        sys.exit(0)

