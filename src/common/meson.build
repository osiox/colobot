# TODO Create libcommon or sth

config_h = configure_file(
    input: 'config.h.cmake',
    output: 'config.h',
    format: 'cmake@',
    configuration: {
        # TODO Other platforms
        'PLATFORM_LINUX'   : true,
        'PLATFORM_GNU'     : true,
        'GLEW_STATIC'      : false, # TODO Controlled by option ?
        'OPENAL_SOUND'     : true, # TODO Controlled by option
        'PORTABLE_SAVES'   : false, # TODO Controlled by option
        'COLOBOT_DATA_DIR' : COLOBOT_DATA_DIR, # TODO Maybe use relative paths to workdir or executable ???
        'COLOBOT_I18N_DIR' : COLOBOT_I18N_DIR # TODO Does this support DESTDIR ?
    }
)

version_h = configure_file(
    input: 'version.h.cmake',
    output: 'version.h',
    format: 'cmake@',
    configuration: {
        'COLOBOT_VERSION_FULL': 'TODO',
        'COLOBOT_VERSION_DISPLAY': 'TODO',
        'BUILD_NUMBER': '1234', # TODO
        'OFFICIAL_COLOBOT_BUILD': false # TODO
    }
)
