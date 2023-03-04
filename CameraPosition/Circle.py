import pcbnew
import math

board = pcbnew.GetBoard()

# Define center position of circle
center_x = pcbnew.FromMM(50) # Change to desired center x-coordinate
center_y = pcbnew.FromMM(50) # Change to desired center y-coordinate

# Define radius of circle
radius = pcbnew.FromMM(30) # Change to desired radius

# Define LED parameters
led_width = pcbnew.FromMM(2) # Change to desired LED width
led_height = pcbnew.FromMM(2) # Change to desired LED height
led_spacing = pcbnew.FromMM(2) # Change to desired spacing between LEDs

# Calculate angle between LEDs
angle_between_leds = 360 / 20 # Change 20 to desired number of LEDs

# Loop through LEDs and position them in a circle
for i in range(20):
    angle = i * angle_between_leds
    x = center_x + radius * math.cos(math.radians(angle))
    y = center_y + radius * math.sin(math.radians(angle))
    module = board.FindFootprintByReference("LED" + str(i+1)) # Assumes LEDs are named LED1, LED2, etc.
    module.SetPosition(pcbnew.wxPoint(x - led_width/2, y - led_height/2))
