import sys

from PyQt5.QtWidgets import QWidget, QApplication, QHBoxLayout

from devices.DeviceWindow import DeviceWindow
from tests.TestWindow import TestWindow
from app.AppWindow import AppWindow

if __name__ == "__main__":
    # Set up the app
    app = QApplication(sys.argv)
    mainWindow = AppWindow("224.3.11.15", 31115)

    # Run the app
    mainWindow.show()
    sys.exit(app.exec())

