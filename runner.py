import os
import sys

A = 100
W = 10
L = 500
maxN = 20
name = 's1'
argc = len(sys.argv)

if argc > 1 and (sys.argv[1][:2] == '-h' or sys.argv[1][:1] == 'h'):
    print 'Usage: python runner.py file_name, A, W, L, max_N'
    exit()

if argc > 1:
    name = sys.argv[1]
if argc > 2:
    A = sys.argv[2]
if argc > 3:
    W = sys.argv[3]
if argc > 4:
    L = sys.argv[4]
if argc > 5:
    maxN = int(sys.argv[5])

f = open('%s.csv' % name, 'w')

for N in range(1, maxN + 1):
    cmd = './Simulation {0} {1} {2} {3}'.format(N, A, W, L)
    print cmd

    output = os.popen(cmd, 'r')
    result = output.read()
    delay = result.split('delay time: ')[1].split(' secs')[0]
    throughput = result.split('Throughput: ')[1].split(' Mbps')[0]
    msg = "%d, %s, %s\n" % (N, delay, throughput)

    print "\t%s" % msg,
    f.write(msg)
