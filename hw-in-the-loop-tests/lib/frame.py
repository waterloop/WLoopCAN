from dataclasses import dataclass

@dataclass
class CANFrame():
    arb_id: int
    payload: list

    def to_dict(self):
        ret = {
            "id": self.arb_id,
            "payload": self.payload
        }
        return ret

