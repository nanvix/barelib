# MIT License
#
# Copyright(c) 2011-2020 The Maintainers of Nanvix
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

#
# Default make rule.
#
.DEFAULT_GOAL := all

#===============================================================================
# Build Options
#===============================================================================

# Verbose build?
export VERBOSE ?= no

#===============================================================================
# Directories
#===============================================================================

export ROOTDIR  := $(CURDIR)
export BUILDDIR := $(ROOTDIR)/build
export DOCDIR   := $(ROOTDIR)/doc
export INCDIR   := $(ROOTDIR)/include
export LIBDIR   := $(ROOTDIR)/lib
export MAKEDIR  := $(BUILDDIR)/$(TARGET)
export SRCDIR   := $(ROOTDIR)/src
export TOOLSDIR := $(ROOTDIR)/utils

#===============================================================================
# Library
#===============================================================================

export KLIB = barelib-$(TARGET).a

#===============================================================================
# Target-Specific Make Rules
#===============================================================================

include $(MAKEDIR)/makefile

#===============================================================================
# Toolchain Configuration
#===============================================================================

export CFLAGS += -std=c99 -fno-builtin
export CFLAGS += -pedantic-errors
export CFLAGS += -Wall -Wextra -Werror -Wa,--warn
export CFLAGS += -Winit-self -Wswitch-default -Wfloat-equal
export CFLAGS += -Wundef -Wshadow -Wuninitialized -Wlogical-op
export CFLAGS += -Wvla -Wredundant-decls
export CFLAGS += -Wno-missing-profile
export CFLAGS += -fno-stack-protector
export CFLAGS += -I $(INCDIR)

# Additional C Flags
include $(BUILDDIR)/makefile.cflags

# Archiver Options
export ARFLAGS = rc

#===============================================================================

# Builds everything.
all: | make-dirs all-target

# Make directories
make-dirs:
	@mkdir -p $(LIBDIR)

# Cleans build.
clean: clean-target

# Cleans everything.
distclean: distclean-target

#===============================================================================
# Install and Uninstall Rules
#===============================================================================

include $(BUILDDIR)/makefile.install
