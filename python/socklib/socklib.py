import socket
import struct

def createUDPClientSocket():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    return sock

def createUDPSocket(ip, port):
    sock = createUDPClientSocket()
    sock.bind((ip, port))
    return sock

def createMulticastSocket(group, port, recvTimeout):
    sock = createUDPClientSocket()
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_LOOP, 1)
    sock.bind((group, port))
    mreq = struct.pack('4sl', socket.inet_aton(group), socket.INADDR_ANY)
    sock.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP, mreq)
    sock.settimeout(recvTimeout)
    return sock

