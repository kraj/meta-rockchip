# Copyright (C) 2017 Fuzhou Rockchip Electronics Co., Ltd
# Released under the GNU GENERAL PUBLIC LICENSE Version 2
# (see COPYING.GPLv2 for the terms)

require recipes-multimedia/gstreamer/gstreamer1.0-plugins.inc

DESCRIPTION = "GStreamer 1.0 extra plugins for Rockchip platforms"

LICENSE = "GPLv2"
LIC_FILES_CHKSUM = "file://COPYING;md5=6d1e4aa87f6192354d3de840cf774d93"
DEPENDS += "gstreamer1.0-plugins-bad"

inherit gettext autotools pkgconfig

PACKAGECONFIG ??= " \
	kms             \
	${@bb.utils.contains("TUNE_FEATURES", "aarch64", "rkv4l2", \
	   bb.utils.contains("TUNE_FEATURES", "callconvention-hard", "rkv4l2", "", d), d)} \
	${@bb.utils.contains('DISTRO_FEATURES', 'x11', 'rkximage', '', d)} \
"
PACKAGECONFIG[rkximage]	= "--enable-rkximage,--disable-rkximage,libdrm"
PACKAGECONFIG[kms]		= "--enable-kms,--disable-kms,libdrm"
PACKAGECONFIG[rkv4l2]	= "--enable-rkv4l2,--disable-rkv4l2,rockchip-aiq libv4l"

EXTRA_OECONF_remove = "--disable-gtk-doc"

do_configure[prefuncs] = " delete_pkg_m4_file"

do_configure() {
	NOCONFIGURE=true ${S}/autogen.sh
	oe_runconf
}

# Move to rockchip-aiq.bb
do_install_append() {
	[ -e ${D}/${libdir}/librk_aiq.so ] && rm ${D}/${libdir}/librk_aiq.so
	echo "Return success"
}
