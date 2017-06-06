#!/usr/bin/env python

from nose.tools import raises
from nose.plugins.attrib import attr

@attr('Eigen')
def import_test():
  from ATK import Preamplifier

