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

    def updateDeviceList(self):
        self.deviceList.clear()
        self.sock.sendto("ID;".encode(), self.multicastData)
