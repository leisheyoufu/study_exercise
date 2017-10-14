#!/usr/bin/env python
# -*- encoding: utf-8 -*-
from __future__ import print_function

import os
import sys
import jinja2
import subprocess
import traceback


BASEDIR = os.path.abspath(os.path.dirname(__file__))
CONSERVER_CFG_PATH = '/etc/conserver.cf'

class Utils(object):
    @staticmethod
    def execute(cmd, **kwargs):
        try:
            p = subprocess.Popen(cmd, stdout=subprocess.PIPE,
                                 stderr=subprocess.PIPE, **kwargs)
            out, err = p.communicate()
            if err:
                print('Running command %s out: %s err: %s' % (
                    ' '.join(cmd), out, err))
        except subprocess.CalledProcessError, OSError:
            print('Error to running command: %s err: %s' % (
                ' '.join(cmd), traceback.format_exc()))

def gen_global_config():
    template = os.path.join(BASEDIR, 'conserver.cf.tmpl')
    with open(template, 'r') as f:
        return f.read()


def write_to_file(path, contents):
    with open(path, 'w') as f:
        f.write(contents)


def gen_node_config(tmpl, nodes, ip):
    """Generate node configuration from jinja2 template
    :param templ: jinja2 template
    :param nodes: the names of nodes
    :param ip: the ip address to ssh
    """
    return [tmpl.render({'node': node, 'ip': ip}) for node in nodes]


def build_template(nodes, ip):
    template = os.path.join(BASEDIR, 'conserver_node.tmpl')
    tmpl_path, tmpl_name = os.path.split(template)
    loader = jinja2.FileSystemLoader(tmpl_path)
    env = jinja2.Environment(loader=loader)
    tmpl = env.get_template(tmpl_name)
    buffer = gen_global_config() + '\n' + '\n'.join(gen_node_config(tmpl, nodes, ip))
    write_to_file(CONSERVER_CFG_PATH, buffer)

def restart_conserver():
    cmd = ['service', 'conserver', 'restart']
    Utils.execute(cmd)

if __name__ == "__main__":
    count = 3
    ip = "10.5.102.73"
    if len(sys.argv) > 1:
        count = int(sys.argv[1])
    if len(sys.argv) > 2:
        ip = str(sys.argv[2])
    if count > 5000:
        print("The max count is 5000")
        count = 5000
    nodes = ["fake_console_node%d" % i for i in range(count)]
    build_template(nodes, ip)
    restart_conserver()

