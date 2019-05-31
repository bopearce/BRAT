from http.server import HTTPServer, SimpleHTTPRequestHandler
import ssl
import os

web_root = 'PUT WEB ROOT HERE'
os.chdir(web_root)

server_address = ('127.0.0.1', 443)
httpd = HTTPServer(server_address, SimpleHTTPRequestHandler)

httpd.socket = ssl.wrap_socket(httpd.socket,
                               server_side=True,
                               certfile='PATH TO YOUR PEM HERE')
httpd.serve_forever()
