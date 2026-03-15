{
  pkgs ? import <nixpkgs> { },
}:

let
  libraries = with pkgs; [
    # Core GTK/Gnome
    gtk4
    libadwaita
    glib
    cairo
    pango
    harfbuzz
    gdk-pixbuf
    librsvg
    graphene
    libepoxy

    # System & Graphics
    vulkan-loader
    colord
    gsound
    libcanberra
    appstream
    libxmlb

    tinysparql
    glycin-loaders
  ];

  packages = with pkgs; [
    pkg-config
    dbus
    openssl_3
    ninja
    meson
    desktop-file-utils
    libxml2
  ];

in
pkgs.mkShell {
  hardeningDisable = [ "fortify" ];
  buildInputs = packages ++ libraries;

  shellHook = ''
    export LD_LIBRARY_PATH=${pkgs.lib.makeLibraryPath libraries}:$LD_LIBRARY_PATH
    export XDG_DATA_DIRS=$GSETTINGS_SCHEMAS_PATH:$XDG_DATA_DIRS

    echo "Nix development environment loaded!"
  '';
}
