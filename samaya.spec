%global debug_package %{nil}
Name:           samaya
Version:        1.0.0
Release:        3%{?dist}
Summary:        Timekeeper for your tasks

License:        AGPL-3.0-or-later
URL:            https://codeberg.org/lockedmutex/samaya
Source0:        %{name}-%{version}.tar.gz

BuildRequires:  meson
BuildRequires:  gcc
BuildRequires:  gettext

# Dependencies based on your README and ldd output
BuildRequires:  pkgconfig(gtk4) >= 4.20
BuildRequires:  pkgconfig(libadwaita-1) >= 1.8
BuildRequires:  pkgconfig(gsound) >= 1.0.3
BuildRequires:  pkgconfig(libcanberra) >= 0.30
BuildRequires:  pkgconfig(gio-2.0)
BuildRequires:  pkgconfig(glib-2.0)

# Validation tools
BuildRequires:  desktop-file-utils
BuildRequires:  libappstream-glib

Requires:       hicolor-icon-theme

%description
A simple, elegant, minimalist Pomodoro timer for your desktop.
Designed to help you stay focused and productive, it offers a clean,
distraction-free interface to manage work and break intervals with ease.

%prep
%autosetup -n %{name} -p1

%build
%meson
%meson_build

%install
%meson_install
%find_lang %{name}

%check
desktop-file-validate %{buildroot}%{_datadir}/applications/*.desktop
appstream-util validate-relax --nonet %{buildroot}%{_datadir}/metainfo/*.xml

%files -f %{name}.lang
%license COPYING
%doc README.md
%{_bindir}/samaya
%{_datadir}/applications/*.desktop
%{_datadir}/icons/hicolor/scalable/apps/*.svg
%{_datadir}/icons/hicolor/symbolic/apps/*.svg
%{_datadir}/metainfo/*.xml
%{_datadir}/glib-2.0/schemas/*.gschema.xml
%{_datadir}/dbus-1/services/*.service
%{_datadir}/sounds/*.oga

%changelog
* Sun Jan 18 2026 Suyog Tandel <git@suyogtandel.in> 1.0.0-3
- fix: match Source0 filename with tito output (git@suyogtandel.in)
- packaging: add rpm spec file for fedora copr build using tito
  (git@suyogtandel.in)

* Sun Jan 18 2026 Suyog Tandel <git@suyogtandel.in> 1.0.0-2
- fix: add all files in spec file (git@suyogtandel.in)

* Sun Jan 18 2026 Suyog Tandel <git@suyogtandel.in> 1.0.0-1
- new package built with tito

* Sun Jan 18 2026 Suyog Tandel <git@suyogtandel.in>
- new package built with tito

* %{lua: print(os.date("%a %b %d %Y"))} Suyog Tandel <git@suyogtandel.in> 1.0.0-1
- New release 1.0.0
