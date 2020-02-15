Name: bootctld
%{!?qtc_make:%define qtc_make make}
Summary: bootctl slot switcher daemon
Version: 1.0.0
Release: 1
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


%prerun
if [ "$1" = "0" ]; then
	systemctl-user stop bootctld || true
	systemctl-user disable bootctld || true
fi

%post
systemctl-user daemon-reload || true
systemctl-user start bootctld || true
systemctl-user enable bootctld || true

%pre
if [ "$1" = "2" ]; then
	systemctl-user stop bootctld || true
	systemctl-user disable bootctld || true
fi

%files
%defattr(644,root,root,755)
%attr(755,root,root) %{_bindir}/%{name}
/usr/lib/systemd/user/
