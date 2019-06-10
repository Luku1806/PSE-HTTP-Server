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

# ------------Simple valid stuff------------#

# Case 1
cannon += Beam(
    description='Valid request to index.html',
    request='GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 2
cannon += Beam(
    description="Valid request to debug",
    request='GET /debug HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# ------------Http method------------#

# Case 3
cannon += Beam(
    description='Invalid method "SHRED"',
    request='SHRED /index.html HTTP/1.1\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 4
cannon += Beam(
    description='get written in lowercase',
    request='get /index.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)

# ------------HTTP version------------#

# Case 5
cannon += Beam(
    description='Request with http version 1.0',
    request='GET /index.html HTTP/1.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 6
cannon += Beam(
    description='Request with http version 1.1',
    request='GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 7
cannon += Beam(
    description='Request with http version 2.0',
    request='GET /index.html HTTP/2.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)

# Case 8
cannon += Beam(
    description="HTTP not uppercase",
    request='GET / http/1.1\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 505']
)

# Case 9
cannon += Beam(
    description="HTTP version with comma",
    request='GET /index.html HTTP/1,1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 505']
)

# ------------File stuff------------#

# Case 10
cannon += Beam(
    description='Non existent file',
    request='GET /test/index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 404']
)

# Case 11
cannon += Beam(
    description='Out of document root with existing file',
    request='GET /../index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 403']
)

# Case 12
cannon += Beam(
    description='Out of document root whitout existing file',
    request='GET /../ HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 403']
)

# Case 13
cannon += Beam(
    description='Long input (<255)',
    request='GET /images/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 15
cannon += Beam(
    description='Spaces in request',
    request='         GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# ------------URL encoding------------#

# Case 16
cannon += Beam(
    description="Non hex charcter after %",
    request='GET /%keinhex HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Case 17
cannon += Beam(
    description="% as last character",
    request='GET /images% HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Case 18
cannon += Beam(
    description='Space in ressource that is not url encoded',
    request='GET /images/ein leerzeichen.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Case 19
cannon += Beam(
    description="Non ascii charcter",
    request='GET /👧 HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)

# ------------File extensions------------#

# Case 20
cannon += Beam(
    description="Access to existing picture without file ending",
    request='GET /images/tux HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 21
cannon += Beam(
    description="Access to existing .jpg picture",
    request='GET /images/tux.jpg HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 22
cannon += Beam(
    description="Access to existing .png picture",
    request='GET /images/tux.png HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 23
cannon += Beam(
    description="Access to existing .PNG picture",
    request='GET /images/TUX1.PNG HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 24
cannon += Beam(
    description='Try to read *.png',
    request='GET /*.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)

# ------------Host stuff------------#

# Case 25
cannon += Beam(
    description="host: extern",
    request='GET / HTTP/1.1\r\nHost: extern\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 26
cannon += Beam(
    description="host: intern",
    request='GET / HTTP/1.1\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 26.2
cannon += Beam(
    description="host: iNteRn",
    request='GET / HTTP/1.1\r\nHost: iNteRn\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 27
cannon += Beam(
    description="'host: extern ' (spaces behind extern)",
    request='GET / HTTP/1.1\r\nHost: extern  \r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 28
cannon += Beam(
    description="host: intern ' (spaces behind intern)",
    request='GET / HTTP/1.1\r\nHost: intern   \r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 29
cannon += Beam(
    description='Intern host with port',
    request='GET / HTTP/1.1\r\nHost: intern:{port}\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 30
cannon += Beam(
    description='Extern host with port',
    request='GET / HTTP/1.1\r\nHost: extern:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 31
cannon += Beam(
    description='Host header not at first',
    request='GET /index.html HTTP/1.1\r\nDies ist: kein host ¯\_(ツ)_/¯\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 32
cannon += Beam(
    description='Host with random case: hoST',
    request='GET / HTTP/1.1\r\n   hoSt:   {host}:{port}  \r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 33
cannon += Beam(
    description='Empty host header',
    request='GET / HTTP/1.1\r\nHost:\r\n\r\n',
    response=['HTTP/1.1 400']
)

# ------------Missing stuff in headerline------------#

# Case 34
cannon += Beam(
    description="No method",
    request='/ HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Case 35
cannon += Beam(
    description="No ressource",
    request='GET HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Case 36
cannon += Beam(
    description="No version",
    request='GET /\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

# ------------General syntax stuff------------#

# Case 37
cannon += Beam(
    description="Invalid header without :",
    request='GET / HTTP/1.1\r\n\r\nkein Doppelpunkt\r\n',
    response=['HTTP/1.1 200']
)

# Case 38
cannon += Beam(
    description="File extension uppercase",
    request='GET /index.HTML HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)

# Case 39
cannon += Beam(
    description='Try Content-Type Exploit',
    request='GET /index.html\';pkill%20-f%20pse\' HTTP/1.1\r\nHost: {host}:{port}  \r\n\r\n',
    response=['HTTP/1.1 404']
)

# ------------Linebreak stuff------------#

# Case 40
cannon += Beam(
    description='Valid request without any additional header',
    request='GET / HTTP/1.1\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 41
cannon += Beam(
    description='Invalid request, without second linebreak',
    request='GET /index.html HTTP/1.1\r\n',
    response=['HTTP/1.1 400']
)

# Case 42
cannon += Beam(
    description='Invalid request, without any linebreak',
    request='GET /index.html HTTP/1.1',
    response=['HTTP/1.1 400']
)

# Case 43
cannon += Beam(
    description="Second linebreak after headerline --> host in body and not processed",
    request='GET / HTTP/1.1\r\n\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 44
cannon += Beam(
    description="Invalid request with a return character only as linebreak",
    request='GET / HTTP/1.1\rkein Doppelpunkt\r\n\r\n',
    response=['HTTP/1.1 400']
)

# ------------Authentication stuff------------#

# Case 45
cannon += Beam(
    description='Authorization with existent base64 encoded username "test" and password "testtest"',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: Basic dGVzdDp0ZXN0dGVzdA==\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 46
cannon += Beam(
    description='Authorization with existent base64 encoded username "test1" and password "test1test1"',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: Basic dGVzdDE6dGVzdDF0ZXN0MQ==\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 47
cannon += Beam(
    description='Authorization with non existent base64 encoded username "invalid" and password "intruder"',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: Basic aW52YWxpZDppbnRydWRlcg==\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 48
cannon += Beam(
    description='Authorization with non existent base64 encoded username "invalid" and password "intruder"',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: Basic dGVzdDE6dG:VzdDF0ZXN0MQ==\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 49
cannon += Beam(
    description='Authorization with valid credentials and lowercase "basic"',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: basic dGVzdDp0ZXN0dGVzdA==\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 50
cannon += Beam(
    description='Authorization with valid credentials but authentication scheme "test"',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: test dGVzdDp0ZXN0dGVzdA==\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 51
cannon += Beam(
    description='Authorization with valid credentials missing scheme',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: dGVzdDp0ZXN0dGVzdA==\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 51
cannon += Beam(
    description='Authorization with Basic, but no credentials',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization: Basic\r\n\r\n',
    response=['HTTP/1.1 401']
)

# Case 52
cannon += Beam(
    description='Authorization without any content',
    request='GET / HTTP/1.1\r\nHost: intern\r\nAuthorization:\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Pew pew!
cannon.pewpew()
