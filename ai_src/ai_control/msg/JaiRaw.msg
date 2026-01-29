# The data needed for JAI learning paper
Header header
uint64 time_usec    # Timestamp (UNIX Epoch time or time since system boot)
float32 rol         # Roll (rad)
float32 pit         # Pitch (rad)
float32 yaw         # Yaw (rad)
float32 drol        # Dot Roll (rad/s)
float32 dpit        # Dot Pitch (rad/s)
float32 dyaw        # Dot Yaw (rad/s)
float32 xa          # Delta Wheel Rate (rad/s)
float32 ya          # Dot Dot Pitch (rad/s)
float32 za          
float32 ur          # Wheel output right (unit)
float32 ul          # Wheel output left (unit)
float32 disired_pit # Desired dot dot pitch (rad)
float32 desired_dpit # PWM1 (rad/s)
float32 beta        # Beta
float32 Thr_out     # Throttle output
