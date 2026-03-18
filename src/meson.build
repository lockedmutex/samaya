samaya_sources = [
    'main.c',
    'samaya-application.c',
    'samaya-window.c',
    'samaya-preferences-dialog.c',
    'samaya-timer.c',
    'samaya-session.c',
    'samaya-utils.h',
]

samaya_deps = [
    dependency('gtk4'),
    dependency('libadwaita-1', version : '>= 1.7'),
]

if host_machine.system() == 'linux'
    samaya_deps += dependency('gsound')
else
    samaya_deps += dependency('miniaudio')
endif

samaya_sources += gnome.compile_resources('samaya-resources', 'samaya.gresource.xml', c_name : 'samaya')

executable(
    'samaya',
    samaya_sources,
    dependencies : samaya_deps,
    install : true,
)
