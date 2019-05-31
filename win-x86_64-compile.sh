#!/bin/bash
x86_64-w64-mingw32-gcc brat.c -s -DCURL_STATICLIB -static -lcurl -lbrotlidec-static -lnghttp2 -lssh2 -lssl -lwldap32 -Wl,--start-group \
 -lbcrypt -lbrotlicommon-static -lcrypt32 -lcrypto -lws2_32 -lz -Xlinker --no-nxcompat -o bin/b.exe
