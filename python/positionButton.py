import pygame
from math import pi
import numpy as np

def scale(n):
    return int(n*50 + 200)

def scaleZ(n):
    return int(10*(1.1-n))

pygame.init()

pygame.joystick.init()

# Define the colors we will use in RGB format
BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
BLUE =  (  0,   0, 255)
GREEN = (  0, 255,   0)
RED =   (255,   0,   0)

# Set the height and width of the screen
sizex = 400
sizey = 400
size = [sizex, sizey]
screen = pygame.display.set_mode(size)

pygame.display.set_caption("Example code for draw module")

joystick = pygame.joystick.Joystick(0)

done = False
clock = pygame.time.Clock()

lastx = 0
lasty = 0
wasPressed = False

dotx = lastx
doty = lasty
fudgex = 0
fudgey = 0

while not done:
    clock.tick(60)
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    screen.fill(WHITE)
    joystick.init()
    button = joystick.get_button(0)
    dotz = joystick.get_axis(2)

    if button == True:
        if not wasPressed:
            wasPressed = True
            fudgex = joystick.get_axis(0)
            fudgey = joystick.get_axis(1)
        dotx = joystick.get_axis(0) - fudgex + lastx
        doty = joystick.get_axis(1) - fudgey + lasty
        dotz = joystick.get_axis(2)
        pygame.draw.circle(screen, BLUE, [scale(dotx), scale(doty)], scaleZ(dotz))
    else: # button == False
        if wasPressed:
            lastx = dotx
            lasty = doty
            wasPressed = False
        dotz = joystick.get_axis(2)
        pygame.draw.circle(screen, BLUE, [scale(dotx), scale(doty)], scaleZ(dotz))
    pygame.display.flip()

pygame.quit()
