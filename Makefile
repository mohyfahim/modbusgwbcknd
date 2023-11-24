#
# Copyright (C) 2023 Mohy Fahim
#

include $(TOPDIR)/rules.mk

# Name, version and release number
# The name and version of your package are used to define the variable to point to the build directory of your package: $(PKG_BUILD_DIR)
PKG_NAME:=modbusgwbcknd
PKG_VERSION:=1.0
PKG_RELEASE:=1

# Source settings (i.e. where to find the source codes)
# This is a custom variable, used below
USE_SOURCE_DIR:=$(TOPDIR)/fahim/network/utils/modbusgwbcknd
PKG_BUILD_DIR:=$(BUILD_DIR)/$(PKG_NAME)

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk

define Package/modbusgwbcknd
  SECTION:=net
  CATEGORY:=Network
  TITLE:=Modbusgw Backend
  DEPENDS:=+jsoncpp +libulfius +libmodbus +libsqlite3
endef

define Package/modbusgwbcknd/description
  Modbus tools based on libmodbus to log data fetched by a master/client or
  received by a slave/server (writing of registers). mbcollect is able to act
  as client or server (in TCP or RTU)
endef

# define Build/Configure
# 		# mkdir -p $(PKG_BUILD_DIR)
# 		# cp $(USE_SOURCE_DIR)/* $(PKG_BUILD_DIR)
# 		$(call Build/Configure/Meson)
# endef

# Package build instructions; invoke the target-specific compiler to first compile the source file, and then to link the file into the final executable
# define Build/Compile
# 		$(TARGET_CXX) $(TARGET_CXXLAGS) -o $(PKG_BUILD_DIR)/mgbcknd  $(PKG_BUILD_DIR)/server.cpp  $(TARGET_CXXFLAGS) -ljsoncpp -lmodbus -lulfius
# endef

# Package install instructions; create a directory inside the package to hold our executable, and then copy the executable we built previously into the folder
define Package/modbusgwbcknd/install
		$(INSTALL_DIR) $(1)/usr/bin
		$(INSTALL_BIN) $(PKG_BUILD_DIR)/openwrt-build/mgbcknd $(1)/usr/bin
endef

# This command is always the last, it uses the definitions and variables we give above in order to get the job done
$(eval $(call BuildPackage,modbusgwbcknd))