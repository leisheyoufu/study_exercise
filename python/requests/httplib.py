#!/usr/bin/env python
#coding=utf8

import urllib3

ca_certs = "/pcenter/ssl/ca.pem"  # Or wherever it lives.
#http = urllib3.PoolManager(cert_reqs='CERT_REQUIRED', ca_certs=ca_certs)
http = urllib3.PoolManager(10)
try:
    r = http.request('GET', 'https://x3650m4n03/pcenterws/nodes?userName=wsuser&password=pcenter')
    print r
except urllib3.exceptions.SSLError as e:
    print e

