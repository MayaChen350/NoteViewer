#!/usr/bin/python

import os
import tempfile

global tempdir
pathExist: bool = os.path.exists(os.path.join(os.curdir, ".tmp_dir_path"))

with open(".tmp_dir_path", 'r+t') as f:
    if pathExist:
        tempdir = f.readline()
    else:
        tempdir = tempfile.mkdtemp()
        f.write(tempdir)
        f.write("\n")

os.chdir(tempdir)