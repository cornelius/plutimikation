#
# spec file for package kwatch (Version 2.3.2)
#
# Copyright (c) 2004 SuSE Linux AG, Nuernberg, Germany.
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.
#
# Please submit bugfixes or comments via http://www.suse.de/feedback/
#

# norootforbuild
# neededforbuild  kde3-devel-packages kdegames3
# usedforbuild    aaa_base acl attr bash bind-utils bison bzip2 coreutils cpio cpp cracklib cvs cyrus-sasl db devs diffutils e2fsprogs file filesystem fillup findutils flex gawk gdbm-devel glibc glibc-devel glibc-locale gpm grep groff gzip info insserv kbd less libacl libattr libgcc libselinux libstdc++ libxcrypt m4 make man mktemp module-init-tools ncurses ncurses-devel net-tools netcfg openldap2-client openssl pam pam-modules patch permissions popt procinfo procps psmisc pwdutils rcs readline sed sendmail strace syslogd sysvinit tar tcpd texinfo timezone unzip util-linux vim zlib zlib-devel XFree86-Mesa XFree86-Mesa-devel XFree86-devel XFree86-libs arts arts-devel autoconf automake binutils expat fam fam-devel fontconfig fontconfig-devel freeglut freeglut-devel freetype2 freetype2-devel gcc gcc-c++ gdbm gettext glib2 glib2-devel gnome-filesystem kdelibs3 kdelibs3-devel libart_lgpl libart_lgpl-devel libidn libidn-devel libjpeg liblcms liblcms-devel libmng libmng-devel libpng libpng-devel libstdc++-devel libtiff libtool libxml2 libxml2-devel libxslt libxslt-devel openssl-devel pcre pcre-devel perl qt3 qt3-devel rpm update-desktop-files

Name:         plutimikation
License:      GPL
Group:        System/GUI/KDE
URL:          http://www.lst.de/~cs/plutimikation/
BuildRoot:    %{_tmppath}/%{name}-%{version}-build
Summary:      A math learning game for children
Version:      0.1
Release:      0
Source0:      %name-%{version}.tar.gz

%description
This is a math learning game for children. It asks questions, checks the
answers of the child and gives feedback and statistics about the results.



Authors:
--------
    Cornelius Schumacher <schumacher@kde.org>

%prep
%setup
. /etc/opt/kde3/common_options
update_admin

%build
. /etc/opt/kde3/common_options
./configure $configkde
  
make

%install
. /etc/opt/kde3/common_options
make DESTDIR=$RPM_BUILD_ROOT $INSTALL_TARGET

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/opt/kde3/bin/*
/opt/kde3/share/*

%changelog -n plutimikation
* Wed Jul 14 2004 - schumacher@kde.org
- initial version
