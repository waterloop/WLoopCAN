import csv
import sys
import time
import click
from lib import CANBus

def on_rx(frame, timestamp):
    frame_dict = frame.to_dict()
    print(f"received {frame_dict} at {str(timestamp)}\n")

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def data_logging(interface):
    with CANBus(interface) as bus:
        bus.set_rx_callback(on_rx)

        while (1):
            pass


if __name__ == "__main__":
    try:
        data_logging()
    except KeyboardInterrupt:
        sys.exit(0)

