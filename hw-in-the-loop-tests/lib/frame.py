from dataclasses import dataclass

@dataclass
class CANFrame():
    arb_id: int
    payload: list

    def to_dict(self):
        return {
            "arb_id": int("{:03x}".format(self.arb_id)),
            "payload": [int("{:02x}".format(i)) for i in self.payload]
        }

