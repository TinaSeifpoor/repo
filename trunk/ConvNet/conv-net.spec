Summary: C++ convolutional network library
Name: conv-net
Version: 0.1
Release: prealpha
License: BSD
Source:%{name}-%{version}-%{release}.tar.gz
Group: Science
BuildRoot:%{_tmppath}/%{name}-%{version}-%{release}-buildroot/
URL: http://conv-net.sourceforge.net/
Distribution: SuSE Linux 10.2
Vendor: Akhmed Umyarov
Packager: Akhmed Umyarov <akhmed.umyarov@stern.nyu.edu>
BuildRequires: cmake expat
BuildRequires: gcc-c++ libstdc++-devel

%description
ConvNet is C++ convolutional network library

%package devel
Summary: C++ convolutional network library sources
Group: Science
Requires: expat libcv.so.1 libcxcore.so.1 libhighgui.so.1

%description devel
ConvNet is C++ convolutional network library.
These are its sources.

%prep

%setup -q

%build
sh compile.sh $RPM_BUILD_ROOT

%install

%post
/sbin/ldconfig
echo ----------------------------------------------------------------------
echo You have just installed the conv-net library and its supporting files
echo Try running the following command:
echo \$ cd /usr/local/share/conv-net/data/
echo \$ /usr/local/bin/testimg mnist.xml *.png
echo ----------------------------------------------------------------------
echo Enjoy!

%postun
/sbin/ldconfig

%clean
rm -rf $RPM_BUILD_ROOT

%files
%defattr(-,root,root)
/usr/local/include/cvconvnet.h
/usr/local/lib/libcvconvnet.a
/usr/local/bin/testimg
/usr/local/bin/testmnist
/usr/local/share/conv-net/data/mnist.xml
/usr/local/share/conv-net/data/t10k-*
/usr/local/share/conv-net/data/*.png

%files devel
%defattr(-,root,root)
/usr/local/share/conv-net/src/*
/usr/local/share/conv-net/include/*
/usr/local/share/conv-net/tst/*
/usr/local/share/conv-net/data/*
/usr/local/share/conv-net/doc/*
/usr/local/share/conv-net/CMakeLists.txt
/usr/local/share/conv-net/compile.sh
/usr/local/share/conv-net/README
/usr/local/share/conv-net/conv-net.spec


%changelog
* Mon Jul  16 2007  Akhmed Umyarov
- Created a spec file
