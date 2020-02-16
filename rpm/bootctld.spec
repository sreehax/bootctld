Name: bootctld
%{!?qtc_make:%define qtc_make make}
Summary: bootctl slot switcher daemon
Version: 1.0.0
Release: 4
Group: System/Daemons
License: LICENSE
URL: https://github.com/sreehax/bootctld
Source0: %{name}-${version}.tar.bz2

%description
Control the next slot to boot in A/B Devices by creating a daemon, allowing regular users to control this.

%prep
%setup -q -n %{name}-%{version}

%build

%qtc_make %{?_smp_mflags}

%install
rm -rf %{buildroot}
%qmake5_install

%preun
if [ "$1" = "0" ]; then
	systemctl stop bootctld || true
	systemctl disable bootctld || true
fi

%post
systemctl daemon-reload || true
systemctl start bootctld || true
systemctl enable bootctld || true

%pre
if [ "$1" = "2" ]; then
	systemctl stop bootctld || true
	systemctl disable bootctld || true
fi

%files
%defattr(644,root,root,755)
%attr(755,root,root) %{_bindir}/%{name}
%attr(755,root,root) %{_bindir}/bootmgr
/usr/lib/systemd/system/
