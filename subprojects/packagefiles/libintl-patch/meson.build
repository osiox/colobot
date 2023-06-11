project('libintl', 'c',
    version: '0.14.4',
    license: 'LGPL-2.1-or-later',
    meson_version: '>=1.1.0'
)

_source_dir = 'src/libintl/0.14.4/libintl-0.14.4-src'

_src = [
  #_source_dir / 'libintl-dllversion.c',
  #_source_dir / 'libintl-dll.rc',
  _source_dir / 'bindtextdom.c',
  _source_dir / 'dcgettext.c',
  _source_dir / 'dgettext.c',
  _source_dir / 'gettext.c',
  _source_dir / 'finddomain.c',
  _source_dir / 'loadmsgcat.c',
  _source_dir / 'localealias.c',
  _source_dir / 'textdomain.c',
  _source_dir / 'l10nflist.c',
  _source_dir / 'explodename.c',
  _source_dir / 'dcigettext.c',
  _source_dir / 'dcngettext.c',
  _source_dir / 'dngettext.c',
  _source_dir / 'ngettext.c',
  #_source_dir / 'plural.y',
  _source_dir / 'plural-exp.c',
  _source_dir / 'localcharset.c',
  _source_dir / 'relocatable.c',
  _source_dir / 'langprefs.c',
  _source_dir / 'localename.c',
  _source_dir / 'log.c',
  _source_dir / 'printf.c',
  _source_dir / 'osdep.c',
  _source_dir / 'os2compat.c',
  _source_dir / 'intl-compat.c'
]

include_dirs = include_directories(_source_dir)

# TODO Shared library ?

cc = meson.get_compiler('c')

if host_machine.system() == 'windows'
    if cc.has_header('string.h')
	    add_project_arguments('/DHAS_STRING_H', language: 'c')
	endif
	
	# TODO Test if we have uintmax_t ?
	if cc.has_header('stdint.h')
	    add_project_arguments('/DHAVE_STDINT_H_WITH_UINTMAX', language: 'c')
	endif
	
else
    error('Subproject not configured correctly for non-windows systems')
endif

libgnuintl_h = configure_file(
    input: _source_dir / 'libgnuintl.h.msvc-shared',
	output: '@BASENAME@',
	configuration: configuration_data()
)

do_install = get_option('default_library') != 'static' or not meson.is_subproject()

# TODO Compiler args ?

libintl = library(
    'intl',
    sources: _src,
    include_directories: include_dirs,
    install: do_install,
    install_dir: get_option('libdir') / get_option('colobot_lib_subdir'), # TODO Other platforms ?
)

libintl_dep = declare_dependency(
    link_with: libintl,
    include_directories: include_dirs
)
