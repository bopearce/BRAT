#!/bin/bash

gcc -fno-stack-protector -z execstack -lcurl -lcrypto -lssl -s -o bin/brat brat.c
