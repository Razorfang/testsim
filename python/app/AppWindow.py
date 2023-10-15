from PyQt5.QtWidgets import QWidget, QHBoxLayout

from devices.DeviceWindow import DeviceWindow
from tests.TestWindow import TestWindow
from socklib.socklib import createUDPSocket

class AppWindow(QWidget):
    def __init__(self, mcastGroup, mcastPort):
        super().__init__()

        self.setWindowTitle("Project W4114C3")

        self.deviceWindow = DeviceWindow(mcastGroup, mcastPort)
        self.testWindow = TestWindow(self.onStartEvent, self.onStopEvent)

        windowLayout = QHBoxLayout()
        windowLayout.addWidget(self.deviceWindow)
        windowLayout.addWidget(self.testWindow)
        
        self.setLayout(windowLayout)

    def onStartEvent(self):
        testDuration = self.testWindow.getTestDuration()
        if testDuration:
            testDeviceData = self.deviceWindow.getSelectedDeviceData()
            if testDeviceData:
                msg = f"TEST;CMD=START;DURATION={testDuration};RATE=100;"
                unisock = createUDPSocket('192.168.1.145', 12345)
                unisock.sendto(msg.encode(), testDeviceData)
                print(f"Message sent: {msg}")
                reply = unisock.recv(4096)
                print(f"Reply received: {reply}")
            else:
                print("Select a device to test!")
        else:
            print("Enter a test duration!")

    def onStopEvent(self):
        print("Stop clicked")

