project('colobot-data')

python3_exe = find_program('python3')

if not get_option('translations')
    # TODO Add info to status or log
    # message(STATUS "Translations disabled; only English files will be installed")
endif

INSTALL_DATA_DIR = get_option('install_data_dir')

if INSTALL_DATA_DIR == ''
    if host_machine.system() == 'windows'
        # TODO Default datadir under windows is probably 'share' ? Should we change it to 'data' or sth?
        INSTALL_DATA_DIR = get_option('prefix') / get_option('datadir')
    else
        INSTALL_DATA_DIR = get_option('prefix') / get_option('datadir') / 'games' / 'colobot'
    endif
endif

install_subdir('ai', install_dir: INSTALL_DATA_DIR)
install_subdir('fonts', install_dir: INSTALL_DATA_DIR)
install_subdir('icons', install_dir: INSTALL_DATA_DIR)
install_subdir('models', install_dir: INSTALL_DATA_DIR)
install_subdir('sounds', install_dir: INSTALL_DATA_DIR)
install_subdir('textures', install_dir: INSTALL_DATA_DIR)
install_subdir('mods', install_dir: INSTALL_DATA_DIR, exclude_directories: 'AltTextures/textures-src')

subdir('help')
subdir('levels')
subdir('music')
