#!/usr/bin/python
# -*- coding: utf-8 -*-
#
# This script makes a HTTP request to a specific server and compares
# responses with user-defined expected responses.
from __future__ import unicode_literals

import sys

from pewpewlaz0rt4nk import (
    Beam,
    Laz0rCannon,
)

__version__ = '2.0.0'

# Set host and port.
# Read the target IP address and port from the command line arguments.
# If there are no command line arguments, use the following default values.
host = 'localhost'
port = 31337

# Overwrite host and port (if specified)
if len(sys.argv) == 3:
    _, host, port = sys.argv
    port = int(port)

# Initialise Laz0rCannon
cannon = Laz0rCannon(host=host, port=port)

# Laz0r Beams (Tests to fire against the server).

# Case 1:
cannon += Beam(
    request='GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 2:
cannon += Beam(
    request='HEAD /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 3:
cannon += Beam(
    description='Not implemented request',
    request='POST /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 4:
cannon += Beam(
    description='Invalid method "SHRED"',
    request='SHRED /index.html HTTP/1.1\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 5:
cannon += Beam(
    description='Request with http version 2.0',
    request='GET /index.html HTTP/2.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/2.0 200']
)

# Case 6:
cannon += Beam(
    description='Request with http version 1.0',
    request='GET /index.html HTTP/1.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.0 200']
)

# Case 7:
cannon += Beam(
    description='Request with http version 1.1',
    request='GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 8:
cannon += Beam(
    description='Request with http version 1.5 (Not Supported)',
    request='GET /index.html HTTP/1.5\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)

# Case 9:
cannon += Beam(
    description='Wrong directory',
    request='GET /test/index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 404']
)

# Case 9:
cannon += Beam(
    description='Out of document root',
    request='GET /../index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 403']
)

# Pew pew!
cannon.pewpew()