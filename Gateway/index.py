from bluepy import btle

class MyDelegate(btle.DefaultDelegate):
    def __init__(self):
        btle.DefaultDelegate.__init__(self)

    def handleNotification(self, cHandle, data):
        print(data)
        print(data[0])
        
# Initialisation  -------
address = "YOUR_ADDRESS"

services_uuid_read = [
    "0000fe40cc7a482a984a7f2ed5b3e58f",
    "0000fe41cc7a482a984a7f2ed5b3e58f",
    "0000fe42cc7a482a984a7f2ed5b3e58f"
]
char_uuid_read = [
    "0x0000fe438e2245419d4c21edae82ed19",
    "0x0000fe448e2245419d4c21edae82ed19",
    "0x0000fe458e2245419d4c21edae82ed19"
]

services_uuid_control = [
    "0000fe38cc7a482a984a7f2ed5b3e58f"
]
char_uuid_control = [
    "0000fe398e2245419d4c21edae82ed19"
]

p = btle.Peripheral(address)
p.setDelegate(MyDelegate())

# Setup to turn notifications on, e.g.

counter = 0
for x in services_uuid_read:
    svc[counter] = p.getServiceByUUID(x)
    counter = counter + 1

counter = 0

for x in char_uuid_read:
    ch[counter] = svc.getCharacteristics(x)
    counter = counter + 1

"""
setup_data for bluepy noification-
"""
setup_data = b"\x01\x00"
counter = 0

for x in char_uuid_read:
    p.writeCharacteristic(ch[counter].valHandle + 1, setup_data)
    counter = counter + 1

counter = 0

for x in char_uuid_read:
    ch_data = p.readCharacteristic(ch[counter].valHandle + 1)
    print(type(ch_data))
    print(ch_data)
    counter = counter + 1

print("=== Main Loop ===")

while True:
    if p.waitForNotifications(1.0):
        continue