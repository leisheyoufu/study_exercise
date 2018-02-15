#!/usr/bin/env python
from __future__ import print_function

from pssh.pssh_client import ParallelSSHClient
from pssh.utils import enable_logger, logger
from gevent import joinall

enable_logger(logger)
hosts = ['9.114.120.103']
client = ParallelSSHClient(hosts, user='xxx', pkey='xxx')
cmds = client.copy_file('/tmp/test.txt', '/tmp/test.txt')
joinall(cmds, raise_error=True)