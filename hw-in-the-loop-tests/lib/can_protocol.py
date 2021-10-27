ARBITRATION_IDS = {
    "CONTROLLER_COMMAND": 0x00,
    "BMS_STATE_CHANGE": 0x0B,
    "MC_STATE_CHANGE": 0x15,
    "MANUAL_CONTROL": 0x08
}

STATE_IDS = {
    "RESTING": 0x00,
    "LV_READY": 0x01,
    "ARMED": 0x02,
    "AUTO_PILOT": 0x03,
    "BRAKING": 0x04,
    "EMERGENCY_BRAKE": 0x05,
    "SYSTEM_FAILURE": 0x06,
    "MANUAL_OPERATION_WAITING": 0x07,
    "ACCELERATING": 0x08,
    "AT_SPEED": 0x09,
    "DECELERATING": 0x0a,
    "INVALID": 0x0b,
    "NACK": 0xff
}

def get_state_name(state_id: int):
    for k in STATE_IDS:
        if STATE_IDS[k] == state_id:
            return k
    return "INVALID"