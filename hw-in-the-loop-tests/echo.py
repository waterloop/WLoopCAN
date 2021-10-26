import csv
import sys
import time
import click
from lib import CANBus, CANFrame

def on_rx(frame, timestamp):
    frame_dict = frame.to_dict()
    print(f"received {frame_dict} at {str(timestamp)}\n")

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def echo(interface):
    with CANBus(interface) as bus:
        bus.set_rx_callback(on_rx)

        while (1):
            try:
                # user input
                id_ = int(input("enter id: "), 16)
                pld = [int(i, 16) for i in input("enter payload: ").split(" ")]
                print()

                # send frame
                frame = CANFrame(arb_id = id_, payload = pld)
                bus.put_frame(frame)

                time.sleep(0.5)

            except ValueError:
                print("Error: inavlid input\n")


if __name__ == "__main__":
    try:
        echo()
    except KeyboardInterrupt:
        sys.exit(0)

