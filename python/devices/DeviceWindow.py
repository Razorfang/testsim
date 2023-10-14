from PyQt5.QtWidgets import QWidget, QPushButton, QVBoxLayout, QListWidget, QListWidgetItem

import socket
import struct

def createMulticastSocket(group, port):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 1)
    sock.bind((group, port))
    mreq = struct.pack('4sl', socket.inet_aton(group), socket.INADDR_ANY)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
    sock.settimeout(5)
    return sock

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
        self.sock = createMulticastSocket(mcastGroup, mcastPort)

        self.discoverButton = DeviceDiscoveryButton()
        self.discoverButton.clicked.connect(self.updateDeviceList)

        self.deviceList = DeviceList()

        layout = QVBoxLayout()
        layout.addWidget(self.discoverButton)
        layout.addWidget(self.deviceList)
        self.setLayout(layout)

    def getSelectedDevice(self):
        return self.deviceList.currentItem()

    def updateDeviceList(self):
        message = "ID;"
        self.deviceList.clear()
        self.sock.sendto(message.encode(), self.multicastData)
        while True:
            try:
                data = self.sock.recv(4096)
                if not data:
                    break
                data = data.decode('ISO-8859-1')
                # Covers loopback case
                if message != data:
                    self.deviceList.addItem(QListWidgetItem(data))
            except socket.timeout:
                print("Timeout occurred")
                break
