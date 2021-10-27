from dataclasses import dataclass

@dataclass
class CANFrame():
    arb_id: int
    payload: list

    def to_dict(self):
        return {
            "arb_id": "{:03x}".format(self.arb_id),
            "payload": ["{:02x}".format(i) for i in self.payload]
        }

