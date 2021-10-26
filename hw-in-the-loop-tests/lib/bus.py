from __future__ import annotations
import can
import threading
import os
from typing import Callable
from datetime import datetime
from frame import CANFrame

_BUSTYPE = "socketcan"

def _monitor_bus(bus_obj: CANBus):
    while (1):
        for msg in bus_obj._bus:
            frame = CANFrame(
                arb_id = msg.arbitration_id, payload = list(msg.data))

            # TODO: replace with python-can timestamps if
            #       this isn't goot enough
            bus_obj._log_file.write(f"[{datetime.now()}]: {frame.to_dict}")
            bus_obj._rx_callback(frame, datetime.now())

class CANBus():
    def __init__(self, interface):
        self._log_file = open(f"hw-in-the-loop-tests/bus_logging.txt", 'a')
        self._rx_callback = lambda *args: None
        self._bus = can.ThreadSafeBus(channel = interface, bustype = _BUSTYPE)
        self._monitor_bus_thread = threading.Thread(
            target = _monitor_bus, args = (self,), daemon = True)

        self._monitor_bus_thread.start()

    def __del__(self):
        self._log_file.close()

    def put_frame(self, frame: CANFrame):
        msg = can.Message(
            arbitration_id = frame.arb_id, data = frame.payload, is_extended_id = False)
        self._bus.send(msg)

    def set_rx_callback(self, callback: Callable):
        self._rx_callback = callback

