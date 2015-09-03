#!/usr/bin/python

from mininet.node import *
from mininet.topo import Topo
from mininet.net import Mininet
from mininet.util import dumpNodeConnections
from mininet.log import setLogLevel
from mininet.link import TCLink
import sys

class YSwitchXHostTopo(Topo):
	def __init__(self, hosts,switches, **opts):
		Topo.__init__(self, **opts)
		hosts = int(hosts)
		switches = int(switches)
		for i in range(switches):
			switch = self.addSwitch('s%s' % (i + 1))
		for i in range(hosts):
			host = self.addHost('h%s' % (i + 1))
		for j in range(switches):
			for i in range(switches):
				if i > j:
					self.addLink('s%s' % (j + 1),'s%s' % (i + 1))
		start = 0
		end = 2
		for j in range(switches):
			if len(range(hosts)) == 1:
				if ((j+1)%2) == 0:
					self.addLink('s%s' % (j+1),'h1',bw=2)
				else:
					self.addLink('s%s' % (j+1),'h1',bw=1)
				end = end +2
				break
			for i in range(start,end):
				if ((i+1)%2) == 0:
					self.addLink('s%s' % (j+1),'h%s' % (i+1),bw=2)
				else:
					self.addLink('s%s' % (j+1),'h%s' % (i+1),bw=1)
			start = start + 2
			end = end + 2
			if end > int(sys.argv[1]) or j+1 == len(range(switches)):
			 	break		
		if len(range(switches)) < len(range(hosts))/2:
			if j+1 == len(range(switches)):
				i=j
			if end > int(sys.argv[1]) or i+1 < len(range(hosts)):
			   	for k in range(end-2,hosts):
					if ((k+1)%2) == 0:
						self.addLink('s%s' % (i+1),'h%s' % (k+1),bw=2)
					else:
						self.addLink('s%s' % (i+1),'h%s' % (k+1),bw=1)

def init(hosts,switches):
	topo = YSwitchXHostTopo(hosts,switches)
	net = Mininet(topo = topo, link = TCLink, controller = OVSController)
	net.start()
	for x in xrange(int(hosts)):
		for y in xrange(int(hosts)):
			if x%2==0 and y%2==1:
				net.nameToNode["h"+str(x+1)].cmd("iptables -A OUTPUT -o h"+str(x+1)+"-eth0 -d 10.0.0."+ str(y+1)+" -j DROP")
	dumpNodeConnections(net.hosts)
	net.pingAll()
	net.stop()

if __name__ == '__main__':
	setLogLevel('info')
	init(sys.argv[1],sys.argv[2])
