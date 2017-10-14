#!/usr/bin/env python

import fileinput
import sys

def update_cmakelist(new_version):
  for line in fileinput.input(files=("CMakeLists.txt",), inplace=True):
    if line.startswith("set(ATK_VERSION"):
      sys.stdout.write("set(ATK_VERSION %s)\n" % new_version)
    else:
      sys.stdout.write(line)

def update_appveyor(new_version):
  for line in fileinput.input(files=(".appveyor.yml",), inplace=True):
    if line.startswith("version"):
      sys.stdout.write("version: '%s.{build}'\n" % new_version)
    else:
      sys.stdout.write(line)

def update_doxygen(new_version):
  for line in fileinput.input(files=("Doxyfile",), inplace=True):
    if line.startswith("PROJECT_NUMBER"):
      sys.stdout.write("PROJECT_NUMBER         = %s\n" % new_version)
    else:
      sys.stdout.write(line)

def update_changelog(new_version):
  for line in fileinput.input(files=("README.md",), inplace=True):
    sys.stdout.write(line)
    if line.startswith("## Changelog"):
      sys.stdout.write("### %s\n\n" % new_version)

def update_juce_modules(new_version):
  import glob
  for header in glob.glob("modules/JUCE/atk_*/atk_*.h"):
    for line in fileinput.input(files=(header,), inplace=True):
      if line.startswith("  version:"):
        sys.stdout.write("  version:          %s\n" % new_version)
      else:
        sys.stdout.write(line)

if __name__ == "__main__":
  update_cmakelist(sys.argv[1])
  update_appveyor(sys.argv[1])
  update_doxygen(sys.argv[1])
  update_changelog(sys.argv[1])

  update_juce_modules(sys.argv[1])
