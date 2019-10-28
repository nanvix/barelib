#
# MIT License
#
# Copyright(c) 2011-2019 The Maintainers of Nanvix
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

#===============================================================================
# Toolchain Configuration
#===============================================================================

# Toolchain Directory
export TOOLCHAIN_DIR ?= /usr/local/k1tools

# Toolchain
export CC := $(TOOLCHAIN_DIR)/bin/k1-gcc
export AR := $(TOOLCHAIN_DIR)/bin/k1-ar

# Compiler Options
export CFLAGS := -D__mppa256__
export CFLAGS += -mos=bare -march=k1b -mboard=developer
export CFLAGS += -D __HAS_HW_DIVISION

#===============================================================================

# Builds everything.
all-target: all-k1bio all-k1bdp

# Builds everything for node cluster variant.
all-k1bdp:
	@$(MAKE) -C $(SRCDIR) all             \
		CFLAGS="$(CFLAGS) -mcluster=node" \
		KLIB=barelib-k1bdp.a              \
		OBJ_SUFFIX=k1bdp

# Builds everything for ioddr cluster variant.
all-k1bio:
	@$(MAKE) -C $(SRCDIR) all              \
		CFLAGS="$(CFLAGS) -mcluster=ioddr" \
		KLIB=barelib-k1bio.a               \
		OBJ_SUFFIX=k1bio

# Cleans object files.
clean-target: clean-k1bdp clean-k1bio

# Builds everything for node cluster variant.
clean-k1bdp:
	@$(MAKE) -C $(SRCDIR) clean \
		OBJ_SUFFIX=k1bdp

# Builds everything for ioddr cluster variant.
clean-k1bio:
	@$(MAKE) -C $(SRCDIR) clean \
		OBJ_SUFFIX=k1bio

# Cleans everything.
distclean-target: distclean-k1bdp distclean-k1bio

# Cleans everything for node cluster variant.
distclean-k1bdp: clean-k1bdp
	@$(MAKE) -C $(SRCDIR) distclean \
		KLIB=barelib-k1bdp.a        \
		OBJ_SUFFIX=k1bdp

# Cleans everything for ioddr cluster variant.
distclean-k1bio: clean-k1bio
	@$(MAKE) -C $(SRCDIR) distclean \
		KLIB=barelib-k1bio.a        \
		OBJ_SUFFIX=k1bio
