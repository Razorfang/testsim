from PyQt5.QtWidgets import QWidget, QPushButton, QVBoxLayout, QListWidget, QListWidgetItem

import socket
from socklib.socklib import createMulticastSocket

class DeviceDiscoveryButton(QPushButton):
    def __init__(self):
        super().__init__("Discover devices")
        self.setToolTip("Discover all devices on this network")

class DeviceList(QListWidget):
    def __init__(self):
        super().__init__()

class DeviceWindow(QWidget):
    def __init__(self, mcastGroup, mcastPort):
        super().__init__()

        self.multicastData = (mcastGroup, mcastPort)
        self.sock = createMulticastSocket(mcastGroup, mcastPort, 5)

        self.discoverButton = DeviceDiscoveryButton()
        self.discoverButton.clicked.connect(self.updateDeviceList)

        self.deviceList = DeviceList()
        self.deviceData = {}

        layout = QVBoxLayout()
        layout.addWidget(self.discoverButton)
        layout.addWidget(self.deviceList)
        self.setLayout(layout)

    def addDevice(serial, ip, port):
        self.deviceList.addItem(QListWidgetItem(data))
        self.deviceData[serial] = (ip, port)

    def getSelectedDevice(self):
        return self.deviceList.currentItem()

    def getSelectedDeviceData(self):
        selectedDevice = self.getSelectedDevice()
        if selectedDevice:
            return self.deviceData[selectedDevice.text()]
        return None

    def updateDeviceList(self):
        message = "ID;"
        self.deviceList.clear()
        self.sock.sendto(message.encode(), self.multicastData)
        while True:
            try:
                data, sender = self.sock.recvfrom(4096)
                if not data:
                    break
                data = data.decode('ISO-8859-1')
                # Covers loopback case
                if message != data:
                    self.addDevice(data, sender, 12345)
            except socket.timeout:
                print("Timeout occurred")
                break
