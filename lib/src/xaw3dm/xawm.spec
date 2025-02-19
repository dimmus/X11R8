%define	ver	1.6
%define	RELEASE	2
%define	prefix	/usr
%define	sorev	7

Summary: Athena widgets with modern look and feel
Name: XawM
Version: %ver
Release: %RELEASE
Group: Development/Libraries
URL: http://xawm.sourceforge.net
Copyright: MIT
Packager: Ed Falk <falk@efalk.org>
Source: http://xawm.sourceforge.net/XawM-%{PACKAGE_VERSION}.src.tar.gz
Buildroot: %{_tmppath}/%{name}-root
Requires: XFree86-libs
Docdir: %prefix/doc

%description
Evolved from Xaw3d, XawM is an enhanced version of the MIT Athena widget
set for the X Window System.  XawM adds a modern three-dimension look
and feel to applications written for the old Xaw library.  XawM also
includes keyboard traversal and modern keyboard bindings.

Most applications linked to the Xaw library will run seamlessly under
XawM.  A few, such as xapm or gv require the original library.  The
README files explain how to install XawM and still run those few
applications that require Xaw.  Or, you can install the Xawm-Xaw package
which contains scripts to do this for you.

See http://xawm.sourceforge.net for screenshots.



%package devel
Summary: Header files and static libraries for development using XawM
Group: Development/Libraries
Requires: XawM

%description devel
Evolved from Xaw3d, XawM is an enhanced version of the MIT Athena widget
set for the X Window System.  XawM adds a modern three-dimension look
and feel to applications written for the old Xaw library.  XawM also
includes keyboard traversal and modern keyboard bindings.

You should install XawM-devel if you are going to develop applications
using the XawM widget set.  You'll also need to install the XawM
package.




%package Xaw3d
Summary: add symlinks so that applications linked to Xaw3d can use XawM
Group: Development/Libraries
Requires: XawM
Provides: Xaw3d

%description Xaw3d
This package creates symlinks from XawM to Xaw3d.  This allows 
applications linked against Xaw3d to use XawM instead.  You will need
to install XawM as well.


%package Xaw
Summary: add symlinks so that applications linked to Xaw can use XawM
Group: Development/Libraries
Requires: XawM

%description Xaw
This package creates symlinks from XawM to Xaw.  This allows 
applications linked against Xaw to use XawM instead.  In addition, the
original Xaw libraries are backed up so that certain legacy applications
that require them can still run.



%prep
%setup
xmkmf
make clean


%build
# these two symlinks allow xawm to build outside of an X11 build environment
ln -s . X11
ln -s . Xaw
xmkmf
make


%install
rm -rf $RPM_BUILD_ROOT
make	DESTDIR=$RPM_BUILD_ROOT install
mkdir -p $RPM_BUILD_ROOT/%prefix/doc/XawM-%{PACKAGE_VERSION} && \
	cp -p README.Linux README.XAW3D README.XawM \
		$RPM_BUILD_ROOT/%prefix/doc/XawM-%{PACKAGE_VERSION}

# xaw3d symlinks
XDIR=$RPM_BUILD_ROOT/%{prefix}/X11R6
ln -s libXawM.a $XDIR/lib/libXaw3d.a
ln -s libXawM.so $XDIR/lib/libXaw3d.so
ln -s libXawM.so.%{sorev} $XDIR/lib/libXaw3d.so.%{sorev}
ln -s libXawM.so.%{sorev}.0 $XDIR/lib/libXaw3d.so.%{sorev}.0
ln -s XawM $XDIR/include/X11/Xaw3d

# xaw files
mkdir -p $XDIR/pre-xawm/include/X11
mkdir -p $XDIR/pre-xawm/lib
mkdir -p $XDIR/pre-xawm/bin
install -m 555 legacy $XDIR/pre-xawm/lib
cp README.include-orig $XDIR/pre-xawm/include/README
cp README.lib-orig $XDIR/pre-xawm/lib/README
cp README.bin-orig $XDIR/pre-xawm/bin/README

%clean
[ -n "$RPM_BUILD_ROOT" -a "$RPM_BUILD_ROOT" != / ] && rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
%{prefix}/X11R6/lib/libXawM.so
%{prefix}/X11R6/lib/libXawM.so.%{sorev}
%{prefix}/X11R6/lib/libXawM.so.%{sorev}.0


%files devel
%defattr(-,root,root)
%{prefix}/X11R6/lib/libXawM.a
%doc README.Linux README.XAW3D README.XawM
%{prefix}/X11R6/include/X11/XawM


%files Xaw3d
%{prefix}/X11R6/lib/libXaw3d.a
%{prefix}/X11R6/lib/libXaw3d.so
%{prefix}/X11R6/lib/libXaw3d.so.%{sorev}
%{prefix}/X11R6/lib/libXaw3d.so.%{sorev}.0
%{prefix}/X11R6/include/X11/Xaw3d

%files Xaw
%{prefix}/X11R6/pre-xawm




# Here come the pre/post install/uninstall scripts.  Most of them are
# just invocations of ldconfig.  The xawm-xaw package is a little
# involved.

%post
ldconfig

%post Xaw3d
ldconfig

%postun
ldconfig

%postun Xaw3d
ldconfig


%post Xaw

# Most of the xawm-xaw package is the script that makes the backups
# and links, rather than the actual files.

# Back up the original headers and libraries
mv %{prefix}/X11R6/lib/libXaw.* %{prefix}/X11R6/pre-xawm/lib

if test -e %{prefix}/X11R6/include/X11/Xaw ; then
  mv %{prefix}/X11R6/include/X11/Xaw %{prefix}/X11R6/pre-xawm/include/X11
fi

# make symlinks to XawM
ln -s XawM %{prefix}/X11R6/include/X11/Xaw
cd %{prefix}/X11R6/lib
ln -s libXawM.so libXaw.so
ln -s libXawM.a libXaw.a
for lib in ../pre-xawm/lib/libXaw.so.*
do
    name=`basename $lib`
    rev=`expr $name : 'libXaw.so.\(.*\)'`
    if expr $rev : '.*\.' > /dev/null ; then
	ln -s libXawM.so.%{sorev}.* $name
    else
	ln -s libXawM.so.%{sorev} $name
    fi
done

# Some programs we know need to be linked against legacy libraries.

for name in xapm gv
do
  if test -e "%{prefix}/X11R6/bin/$name" ; then
    mv "%{prefix}/X11R6/bin/$name" "%{prefix}/X11R6/pre-xawm/bin"
    ln -s ../pre-xawm/lib/legacy "%{prefix}/X11R6/bin/$name"
  fi
done

ldconfig




%preun Xaw

for file in %{prefix}/X11R6/pre-xawm/bin/*
do
  name=`basename $file`
  if test -h "%{prefix}/X11R6/bin/$name"
  then
    rm -f "%{prefix}/X11R6/bin/$name"
    mv $file %{prefix}/X11R6/bin
  fi
done

for lib in %{prefix}/X11R6/pre-xawm/lib/libXaw.*
do
  name=`basename $lib`
  if test -h "%{prefix}/X11R6/lib/$name"
  then
    rm -f "%{prefix}/X11R6/lib/$name"
    mv $lib %{prefix}/X11R6/lib
  fi
done

if test -h %{prefix}/X11R6/include/X11/Xaw -a \
	-e %{prefix}/X11R6/pre-xawm/include/X11/Xaw
then
  rm -f %{prefix}/X11R6/include/X11/Xaw
  mv %{prefix}/X11R6/pre-xawm/include/X11/Xaw %{prefix}/X11R6/include/X11
fi

%postun Xaw
ldconfig
