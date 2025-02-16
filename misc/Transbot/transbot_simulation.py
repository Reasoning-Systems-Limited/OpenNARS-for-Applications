import sys
import os
os.system("pkill NAR")
sys.path.append('../Python/')
import NAR
from time import sleep
import random

picked = False
frame = ""
going = False

def getPicked():
    return picked
    
def setPicked(value):
    picked = value

def detect_objects():
    global going
    if going:
        going = False
        return ([("person", 0, 480, 10, 10, 0.9)], "")
    return ([("bottle" if not picked else "person", random.choice([0,375,375]), 480, 10, 10, 0.9)], "")

def getLocation():
    return [(0,0,0),(0,0,0,0)]

def getCollision():
    return "free" if random.random() > 0.3 else random.choice(["front", "left", "right"])
#<(<gripper --> [holding]> &/ <({SELF} * person) --> ^goto>) =/> <person --> [left]>>.
def OpStop():
    None

def forward():
    None

def left():
    None

def right():
    None

def backward():
    None

def pick():
    None

def arm_down():
    None

def arm_up():
    None

def close_gripper():
    global picked
    picked = True
    return True

def open_gripper():
    None

def OpGo(x, y, z=0, w=1, frame_id = 'map'):
    global going
    if frame_id == 'map':
        going = True

def drop():
    global picked
    picked = False
    None

class FakeCV:
    def waitKey(self, wtf):
        return 0
    def imshow(self, frame, k):
        None
cv = FakeCV()

with open('transbot.py') as f:
    lines = f.readlines()

maxindex = 0
for i in range(len(lines)):
    if "import" in lines[i]:
        maxindex = i

code = "\n".join(lines[maxindex+1:])
exec(code)

