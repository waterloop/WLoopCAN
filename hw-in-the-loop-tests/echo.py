import sys
import click
from lib import CANBus, CANFrame

def on_rx(frame, timestamp):
    print(f"received {frame.to_dict()} at {str(timestamp)}\n")

@click.command()
@click.option("--interface", help = "ex. can0", required = True)
def echo(interface):
    bus = CANBus(interface)
    bus.set_rx_callback(on_rx)

    while (1):
        # user input
        id_ = int(input("enter id: "), 16)
        pld = [int(i, 16) for i in input("enter payload: ").split(" ")]

        frame = CANFrame(arb_id = id_, payload = pld)
        bus.put_frame(frame)

if __name__ == "__main__":
    try:
        echo()
    except KeyboardInterrupt:
        sys.exit(0)

