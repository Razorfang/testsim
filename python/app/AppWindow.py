from PyQt5.QtWidgets import QWidget, QHBoxLayout

from devices.DeviceWindow import DeviceWindow
from tests.TestWindow import TestWindow

class AppWindow(QWidget):
    def __init__(self, mcastGroup, mcastPort):
        super().__init__()

        self.setWindowTitle("Project W4114C3")

        windowLayout = QHBoxLayout()
        windowLayout.addWidget(DeviceWindow(mcastGroup, mcastPort))
        windowLayout.addWidget(TestWindow())
        
        self.setLayout(windowLayout)

