import sys

from PyQt5.QtWidgets import QWidget, QApplication, QHBoxLayout

from devices.DeviceWindow import DeviceWindow
from tests.TestWindow import TestWindow

if __name__ == "__main__":
    # Set up the app
    app = QApplication(sys.argv)
    mainWindow = QWidget()
    
    # Title
    mainWindow.setWindowTitle('Please hire me')

    # Split window into two parts; one for device selection and one for test selection
    windowLayout = QHBoxLayout()
    windowLayout.addWidget(DeviceWindow("224.3.11.15", 31115))
    windowLayout.addWidget(TestWindow())

    mainWindow.setLayout(windowLayout)

    # Run the app
    mainWindow.show()
    sys.exit(app.exec())

