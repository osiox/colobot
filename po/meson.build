_potFile = 'colobot.pot'

xgettext_cmd = find_program('xgettext')
sed_cmd      = find_program('sed')
msgmerge_exe = find_program('msgmerge')
msgfmt_exe   = find_program('msgfmt')

_pot_src = [
    meson.global_source_root() + '/src/app/app.cpp',
    meson.global_source_root() + '/src/common/restext.cpp',
    meson.global_source_root() + '/src/script/script.cpp'
]

generate_pot_cmd = custom_target(
    'generate-pot',
    input: _pot_src,
    output: 'tmp.pot',
    command: [xgettext_cmd, '@INPUT@', '--output=@OUTPUT@', '--no-wrap', '--no-location', '--keyword=TR']
)

_update_pot_script = meson.current_source_dir() / 'update_pot.py'

update_pot = custom_target(
    'update_pot',
    input: generate_pot_cmd,
    output: _potFile,
    depend_files: _update_pot_script,
    command: [
        python3_exe,
        _update_pot_script,
        '@INPUT@',
        '@OUTPUT@'
    ]
)

_src = [
    'cs.po',
    'de.po',
    'fr.po',
    'pl.po',
    'pt.po',
    'ru.po'
]

msgmerge_generator = generator(
    msgmerge_exe,
    arguments: [
        '--quiet',
        '--no-wrap',
        '-s',
        '-o', '@OUTPUT@',
        '@INPUT@',
        update_pot.full_path()
    ],
    output: '@PLAINNAME@',
    depends: update_pot
)

foreach po_file : _src
    _merged_file = msgmerge_generator.process(po_file)

    _compiled_file_tg = custom_target(
        'compile-' + po_file,
        input: _merged_file,
        output: '@BASENAME@.gmo',
        command: [
            msgfmt_exe,
            '--check-format',
            '-o', '@OUTPUT@',
            '@INPUT@'
        ],
        build_by_default: true
    )

    _lang = po_file.split('.')[0]
    _install_file = _potFile.split('.')[0] + '.mo'

    meson.add_install_script(
        python3_exe,
        meson.current_source_dir() / 'install_compiled_translations.py',
        _compiled_file_tg.full_path(),
        COLOBOT_I18N_DIR / _lang / 'LC_MESSAGES' / _install_file
    )
endforeach
