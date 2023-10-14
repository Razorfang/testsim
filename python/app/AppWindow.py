from PyQt5.QtWidgets import QWidget, QHBoxLayout

from devices.DeviceWindow import DeviceWindow
from tests.TestWindow import TestWindow
from socklib.socklib import createUDPClientSocket

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
            msg = f"TEST;CMD=START;DURATION={testDuration};RATE=100;"
            unisock = createUDPClientSocket()
            unisock.sendto(msg.encode(), ('127.0.0.1', 12345))

    def onStopEvent(self):
        print("Stop clicked")

