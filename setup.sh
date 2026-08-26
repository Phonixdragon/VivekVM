#!/bin/bash
cd ~/Downloads/VivekVM/waste_bin_project
python3 -m venv vivek
source vivek/bin/activate
pip3 install -r Requirements.txt
python3 app.py

