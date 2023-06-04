MUSIC_INSTALL_DATA_DIR = INSTALL_DATA_DIR / 'music'

music_files = [
    'Intro1',
    'Intro2',
    'music002',
    'music003',
    'music004',
    'music005',
    'music006',
    'music007',
    'music008',
    'music009',
    'music010',
    'music011',
    'music012',
    'music013',
    'Constructive',
    'Humanitarian',
    'Hv2',
    'Quite',
    'Infinite',
    'Proton',
    'Prototype'
]

if not get_option('music')
    subdir_done()
endif

curl_exe = find_program('curl')

if get_option('music_flac')
    oggenc_exe = find_program('oggenc')
endif

foreach file : music_files

    extension = 'ogg'

    # TODO: We still don't have FLAC version of Intro files, they are packaged as .ogg directly
    if get_option('music_flac') and not file.contains('Intro')
        extension = 'flac'
    endif

    download_file = f'@file@.@extension@'

    download_file_tg = custom_target(
        'download_file_' + download_file.underscorify(),
        build_by_default: true,
        output: download_file,
        command: [
            curl_exe,
            '--location',
            '--fail',
            '--remote-time',
            '--time-cond', '@OUTPUT@',
            '-o', '@OUTPUT@',
            'http://colobot.info/files/music/' + download_file
        ],
        install: extension == 'ogg',
        install_dir: MUSIC_INSTALL_DATA_DIR
    )

    if get_option('music_flac') and extension == 'flac'
        convert_file_tg = custom_target(
            'convert_file_' + download_file.underscorify(),
            build_by_default: true,
            input: download_file_tg,
            output: f'@file@.ogg',
            command: [
                oggenc_exe,
                '-q', get_option('music_quality').to_string(),
                '-o', '@OUTPUT@',
                '@INPUT@'
            ],
            install: true,
            install_dir: MUSIC_INSTALL_DATA_DIR
        )
    endif

endforeach
