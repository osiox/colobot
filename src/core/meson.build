_src = [
    'stringutils.cpp'
]

_deps = [
    icu_uc_dep,
]

_libcolobot_core = library(
    'colobot_core',
    sources: _src,
    dependencies: _deps,
    include_directories: 'include',
    # TODO Do not install if static ?
    install: true,
    install_dir: get_option('libdir') / get_option('colobot_lib_subdir') # TODO Other platforms ?
)

int_libcolobot_core_dep = declare_dependency(
    dependencies: _deps,
    link_with: _libcolobot_core,
    include_directories: 'include'
)
