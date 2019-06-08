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
    description='Not implemented method POST',
    request='POST /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 4:
cannon += Beam(
    description='Not implemented method PUT',
    request='PUT /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 5:
cannon += Beam(
    description='Invalid method HEAD',
    request='HEAD /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 6:
cannon += Beam(
    description='Invalid method "SHRED"',
    request='SHRED /index.html HTTP/1.1\r\nHost: {host}\r\n\r\n',
    response=['HTTP/1.1 501']
)

# Case 7:
cannon += Beam(
    description='Request with http version 2.0',
    request='GET /index.html HTTP/2.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)

# Case 8:
cannon += Beam(
    description='Request with http version 1.0',
    request='GET /index.html HTTP/1.0\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 9:
cannon += Beam(
    description='Request with http version 1.1',
    request='GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 10:
cannon += Beam(
    description='Request with http version 1.5 (Not Supported)',
    request='GET /index.html HTTP/1.5\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 505']
)

# Case 11:
cannon += Beam(
    description='Wrong directory',
    request='GET /test/index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 404']
)

# Case 12:
cannon += Beam(
    description='Out of document root with existing file',
    request='GET /../index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 403']
)

# Case 13:
cannon += Beam(
    description='Out of document root whitout existing file',
    request='GET /../ HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 403']
)

# Case 14:
cannon += Beam(
    description='Long input (<255)',
    request='GET /images/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Case 15:
#cannon += Beam(
#    description='Long input (>255)',
#    request='GET /testfile/default/images/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}\r\n\r\n',
#    response=['HTTP/1.1 200']
#)

# Case 16:
cannon += Beam(
    description='Spaces in request',
    request='         GET /index.html HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)

# Append beams to the cannon
#01 korrekter Request index.html
cannon += Beam(
    description= "korrekter Request index.html",
    request='GET /index.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
#02 falsche Methode
cannon += Beam(
    description= "falsche Methode",
    request='SHRED /index.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)
#03 Not found
cannon += Beam(
    description= "Not found",
    request='GET /notfound.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)
#04 korrekter Request debug
cannon += Beam(
    description= "korrekter Request debug",
    request='GET /debug HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
#05 korrekter Request
cannon += Beam(
    description= "korrekter Request",
    request='GET / HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
#06 kein Hex
cannon += Beam(
    description= "kein Hex",
    request='GET /%keinhex HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)
#07 kein ASCII
cannon += Beam(
    description= "kein ASCII",
    request='GET /👧 HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)
#08 /../
cannon += Beam(
    description= "/../",
    request='GET /debug/../../../debug HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 200']
)
#09 tux
cannon += Beam(
    description= "tux",
    request='GET /images/tux HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
#10 tux.jpg
cannon += Beam(
    description= "tux.jpg",
    request='GET /images/tux.jpg HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
    response=['HTTP/1.1 200']
)
#11 tux.png
cannon += Beam(
    description= "tux.png",
    request='GET /images/tux.png HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
    response=['HTTP/1.1 200']
)
#12 TUX1.PNG
cannon += Beam(
    description= "TUX1.PNG",
    request='GET /images/TUX1.PNG HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
    response=['HTTP/1.1 200']
)
#13 host: extern
cannon += Beam(
    description= "host: extern",
    request='GET / HTTP/1.1\r\nHost: extern\r\n\r\n',
    response=['HTTP/1.1 200']
)
#14 host: intern
cannon += Beam(
    description= "host: intern",
    request='GET / HTTP/1.1\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 401']
)
#15 falsche Methode get
cannon += Beam(
    description= "falsche Methode get",
    request='Get / HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 501']
)
#16 keine Ressource
cannon += Beam(
    description= "keine Ressource",
    request='GET HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)

#17 aaaaaa......image
cannon += Beam(
    description= "aaaaa.... image",
    request='GET /images/aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
#18 Leerzeichen Image
cannon += Beam(
    description= "ein Leerzeichen",
    request='GET /images/ein%20leerzeichen.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
#19 auf einen Ordner zugreifen
#cannon += Beam(
#    description= "auf einen Ordner zugreifen",
#    request='GET /images HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
#    response=['HTTP/1.1 403']
#)
#20
cannon += Beam(
    description= "request ungueltig",
    request='GET / HTTP/1.1\r\n\r\nkein Doppelpunkt\r\n',
    response=['HTTP/1.1 200']
)

#21 HTTP nicht Uppercase
cannon += Beam(
    description= "HTTP nicht Uppercase",
    request='GET / http/1.1\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 505']
)
cannon += Beam(
    description= "HTTP Protokoll wird nicht unterstüzt",
    request='GET / HTTP/0.9\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 505']
)

#22 Dateiendung großgeschrieben

cannon += Beam(
    description= "HTML groß Geschrieben",
    request='GET /index.HTML HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)

#23 HTTP Version mit Komma
cannon += Beam(
    description= "HTTP version mit Komma",
    request='GET /index.html HTTP/1,1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 505']
)

#24 host: intern mit Port
cannon += Beam(
    description= "host: intern",
    request='GET / HTTP/1.1\r\nHost: intern:31337\r\n\r\n',
    response=['HTTP/1.1 401']
)

#25 URL zu lang
#cannon += Beam(
#    description= "Url zu lang",
#    request='GET /bbbbbbbbccccccccccddddddddddeeeeeeeeeeddddddddddeeeeeeeeeeffffaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeaaaaaaaaaabbbbbbbbbbccccccccccddddddddddeeeeeeeeeeddddddddddeeeeeeeeeeffff/images/TUX1.PNG HTTP/1.1\r\nHost: {host}:{port} \r\n\r\n',
#    response=['HTTP/1.1 200']
#)

#26 http klein Geschrieben
cannon += Beam(
    description= "http klein Geschrieben",
    request='GET / http/1.1\r\nHost: intern:31337 \r\n\r\n',
    response=['HTTP/1.1 505']
)

#27 falsches Zeichen
cannon += Beam(
    description= "falsches Zeichen",
    request='GET /d$e&bug HTTP/1.1\r\nHost: {host}\r\nConnection: close\r\n\r\n',
    response=['HTTP/1.1 404']
)







#Test Gruppe 07
cannon += Beam(
    description='Schön-Wetter Http-Request zum Aufwärmen',
    request='GET / HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Ungültiges Http-Verb "POST"',
    request='POST /index.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)
cannon += Beam(
    description='Http-Verb in Kleinbuchstaben (get)',
    request='get /index.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)
cannon += Beam(
    description='Keine Ressource angegeben',
    request='GET  HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='Keine Http-Version angegeben',
    request='GET /\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='Datei mit nicht unterstützter Http-Version anfordern',
    request='GET /index.html HTTP/0.9\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 505']
)
cannon += Beam(
    description='Leerer Host',
    request='GET / HTTP/1.1\r\nHost:\r\n\r\n',
    response=['HTTP/1.1 400']
)

cannon += Beam(
    description='Versuch eine Datei zu erstellen',
    request='PUT /XSS.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 501']
)
cannon += Beam(
    description='Datei anfordern, die nicht existiert',
    request='GET /abc.html HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='Datei anfordern, die außerhalb des DocumentRoot liegt und nicht existiert',
    request='GET /../blablabla123.txt HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 403']
)
cannon += Beam(
    description='Versuch aus Doc Root auszubrechen und echo_server.c zu lesen',
    request='GET /../cmake-build-debug/echo_server.c HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 403']
)
cannon += Beam(
    description='Internen Bereich anfordern',
    request='GET / HTTP/1.1\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Internen Bereich anfordern mit Port',
    request='GET / HTTP/1.1\r\nHost: intern:31337\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Externen Bereich anfordern',
    request='GET / HTTP/1.1\r\nHost: extern\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Externen Bereich anfordern mit Port',
    request='GET / HTTP/1.1\r\nHost: extern:31337\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Externen Bereich und Intern zugleich anfordern',
    request='GET / HTTP/1.1\r\nHost: intern:extern\r\n\r\n',
    response=['HTTP/1.1 401']
)
cannon += Beam(
    description='Debug anfordern',
    request='GET /debug HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='Überprüfe Content-Type Exploit',
    request='GET /index.html\';pkill%20-f%20pse\' HTTP/1.1\r\nHost: {host}:{port}  \r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='tux anforden',
    request='GET /images/tux HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='tux.png anforden',
    request='GET /images/tux.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='TUX1.PNG anforden',
    request='GET /images/TUX1.PNG HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description='ein leerzeichen.png anfordern ohne %20',
    request='GET /images/ein leerzeichen.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 400']
)
cannon += Beam(
    description='Versuch png mit sehr langem nahmen zu lesen',
    request='GET /aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='Versuch *.png zu lesen',
    request='GET /*.png HTTP/1.1\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 404']
)
cannon += Beam(
    description='Aufruf ohne Header',
    request='GET / HTTP/1.1\r\n\r\n',
    response=['HTTP/1.1 200']
)

cannon += Beam(
    description='Host header nicht an erster Stelle',
    request='GET /index.html HTTP/1.1\r\nDies ist: kein host ¯\_(ツ)_/¯\r\nHost: {host}:{port}\r\n\r\n',
    response=['HTTP/1.1 200']
)

cannon += Beam(
    description='Host muss mit anderer Groß-/Kleinschreibung, padding glücken',
    request='GET / HTTP/1.1\r\n   hoSt:   {host}:{port}  \r\n\r\n',
    response=['HTTP/1.1 200']
)

cannon += Beam(
    description='nur eine Zeile + Zeilenumbrüche',
    request='GET /index.html HTTP/1.1\r\n\r\n',
    response=['HTTP/1.1 200']
)

cannon += Beam(
    description='nur eine Zeile ein Zeilenumbruch',
    request='GET /index.html HTTP/1.1\r\n',
    response=['HTTP/1.1 400']
)

cannon += Beam(
    description='Keine HTTP-Version, aber 2 Zeilenumbrüche',
    request='GET /index.html \r\n\r\n',
    response=['HTTP/1.1 400']
)

cannon += Beam(
    description='nur eine Zeile ohne Zeilenumbrüche',
    request='GET /index.html HTTP/1.1',
    response=['HTTP/1.1 400']
)

cannon += Beam(
    description= "request ungueltig",
    request='GET / HTTP/1.1\r\n\r\nHost: intern\r\n\r\n',
    response=['HTTP/1.1 200']
)
cannon += Beam(
    description= "request ungueltig",
    request='GET / HTTP/1.1\rkein Doppelpunkt\r\n\r\n',
    response=['HTTP/1.1 400']
)

# Pew pew!
cannon.pewpew()