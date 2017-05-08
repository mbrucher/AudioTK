#!/usr/bin/env python

from nose.tools import raises

""" Need to find a way of testing for its existence, probably by scanning config.h """
def import_test():
  from ATK import Preamplifier

