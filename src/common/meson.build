# TODO Create libcommon or sth

platform_windows = false
platform_linux   = false
platform_gnu     = false # Seems not really used that much ?
platform_macosx  = false
platform_freebsd = false
platform_other   = false

# Note: No idea what kFreeBSD matches in meson
if host_machine.system() == 'windows'
    platform_windows = true
elif host_machine.system() == 'linux'
    platform_linux = true
    platform_gnu = true
elif host_machine.system() == 'gnu'
    platform_gnu = true
elif host_machine.system() == 'darwin'
    platform_macosx = true
elif host_machine.system() == 'freebsd'
    platform_freebsd = true
else
    platform_other = true
endif


config_h = configure_file(
    input: 'config.h.cmake',
    output: 'config.h',
    format: 'cmake@',
    configuration: {
        'PLATFORM_WINDOWS' : platform_windows,
        'PLATFORM_LINUX'   : platform_linux,
        'PLATFORM_GNU'     : platform_gnu,
        'PLATFORM_MACOSX'  : platform_macosx,
        'PLATFORM_FREEBSD' : platform_freebsd,
        'PLATFORM_OTHER'   : platform_other,
        'GLEW_STATIC'      : get_option('glew_static'),
        'OPENAL_SOUND'     : get_option('openal_sound'),
        'PORTABLE_SAVES'   : get_option('portable_saves'),
        'COLOBOT_DATA_DIR' : COLOBOT_DATA_DIR, # TODO Maybe use relative paths to workdir or executable ???
        'COLOBOT_I18N_DIR' : COLOBOT_I18N_DIR # TODO Does this support DESTDIR ?
    }
)

version_h = configure_file(
    input: 'version.h.cmake',
    output: 'version.h',
    format: 'cmake@',
    configuration: {
        'COLOBOT_VERSION_FULL': COLOBOT_VERSION_FULL,
        'COLOBOT_VERSION_DISPLAY': COLOBOT_VERSION_DISPLAY,
        'BUILD_NUMBER': BUILD_NUMBER,
        'OFFICIAL_COLOBOT_BUILD': false # TODO
    }
)
