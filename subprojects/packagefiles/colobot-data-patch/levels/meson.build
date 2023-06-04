# Not sure if ideal, but should do exactly the same thing as the original cmake did
# Also - a lot of common code with help/meson.build ;)
# Warning!
#   File wildcards (globbing) are used in this file.
#   This is discouraged by everyone, including CMake and Meson teams!

LEVEL_INSTALL_DATA_DIR = INSTALL_DATA_DIR / 'levels'

level_category_dirs = [
    'missions',
    'free',
    'exercises',
    'challenges',
    'battles',
    'plus'
]

message('Configuring levels...')

# --------------------------
# ---- Exclude helpers -----
# --------------------------
exclude_chapters = []
exclude_levels = []

foreach i : range(10)
    foreach j : range(10)
        exclude_chapters += 'chapter0' + i.to_string() + j.to_string()
        exclude_levels += 'level0' + i.to_string() + j.to_string()
    endforeach
endforeach

# ------------------------------------------------------------------
# ---- Find required files once, to speed up the configuration -----
# ------------------------------------------------------------------

# Find all chapters first
c = run_command(python3_exe,
    meson.project_source_root() / 'grabber.py', '*' / 'chapter*',
    check: true
)
chapter_dirs = c.stdout().strip().split('\n')

# And find all levels
c = run_command(python3_exe,
    meson.project_source_root() / 'grabber.py', '*' / 'chapter*' / 'level*',
    check: true
)
level_dirs = c.stdout().strip().split('\n')

# Also find all english help files
c = run_command(python3_exe,
    meson.project_source_root() / 'grabber.py', '*' / 'chapter*' / 'level*' / 'help' / '*',
    check: true
)
english_help_files = c.stdout().strip().split('\n')

# And finally find all po files
c = run_command(python3_exe,
    meson.project_source_root() / 'grabber.py', '**' / 'po' / '*',
    check: true
)
all_po_files = c.stdout().strip().split('\n')

foreach category_dir : level_category_dirs

    message(f'Configuring levels/@category_dir@...')

    if not get_option('translations')
        install_subdir(category_dir, install_dir: LEVEL_INSTALL_DATA_DIR)
        continue
    endif

    # --------------------------
    # --- Add chapter titles ---
    # --------------------------
    output_dir = meson.current_build_dir() / category_dir

    c = run_command(
        python3_exe,
        meson.project_source_root() / 'i18n-tools/scripts/process_translations.py',
        '--mode=print_files',
        '--type=chaptertitles',
        '--input_dir=' + meson.current_source_dir() / category_dir,
        '--po_dir=' + meson.current_source_dir() / category_dir / 'po',
        '--output_dir=' + output_dir,
        check: true
    )

    translation_files = c.stdout().strip().split('\n')
    input_files = translation_files[0].split('\n')[0].split(';')
    # We do not really need it, we just generate and install
    #output_files = translation_files[1].split('\n')[0].split(';')

    # dummy file to indicate success
    signal_file_name = category_dir + '_done'
    signal_file = meson.current_build_dir() / signal_file_name

    po_files = []
    foreach pf : all_po_files
        if pf != '' and pf.startswith(category_dir / 'po')
            po_files += pf
        endif
    endforeach

    _process_translations_script = meson.project_source_root() / 'i18n-tools/scripts/process_translations.py'
    generate_chaptertitle_translations_target = custom_target(
        'generate_chaptertitle_translate_files_' + category_dir,
        build_by_default: true,
        command: [
            python3_exe,
            _process_translations_script,
            '--mode=generate',
            '--type=chaptertitles',
            '--input_dir=' + meson.current_source_dir() / category_dir,
            '--po_dir=' + meson.current_source_dir() / category_dir / 'po',
            '--output_dir=' + output_dir,
            '--signal_file=' + signal_file,
        ],
        output: signal_file_name,
        depend_files: input_files + po_files + _process_translations_script
    )

    meson.add_install_script(
        python3_exe,
        meson.project_source_root() / 'install_generated_files.py',
        output_dir,
        LEVEL_INSTALL_DATA_DIR / category_dir
    )

    # --------------------------
    # ------- Add levels -------
    # --------------------------

    foreach chapter_dir : chapter_dirs
        if chapter_dir == '' or not chapter_dir.startswith(category_dir)
            continue
        endif

        debug(f'Configuring levels/@category_dir@/@chapter_dir@...')

        foreach level_dir : level_dirs
            if level_dir == '' or not level_dir.startswith(chapter_dir)
                continue
            endif

            debug(f'Configuring levels/@category_dir@/@chapter_dir@/@level_dir@...')

            output_dir = meson.current_build_dir() / level_dir

            c = run_command(
                python3_exe,
                meson.project_source_root() / 'i18n-tools/scripts/process_translations.py',
                '--mode=print_files',
                '--type=level',
                '--input_dir=' + meson.current_source_dir() / level_dir,
                '--po_dir=' + meson.current_source_dir() / level_dir / 'po',
                '--output_dir=' + output_dir,
                check: true
            )

            translation_files = c.stdout().strip().split('\n')
            input_files = translation_files[0].split('\n')[0].split(';')
            # We do not really need it, we just generate and install
            #output_files = translation_files[1].split('\n')[0].split(';')

            # dummy file to indicate success
            signal_file_name = (level_dir + '_done').underscorify()
            signal_file = meson.current_build_dir() / signal_file_name

            po_files = []

            foreach pf : all_po_files
                if pf != '' and pf.startswith(level_dir)
                    po_files += pf
                endif
            endforeach

            generate_level_translations_target = custom_target(
                'generate_level_translate_files_' + level_dir.underscorify(),
                build_by_default: true,
                command: [
                    python3_exe,
                    _process_translations_script,
                    '--mode=generate',
                    '--type=level',
                    '--input_dir=' + meson.current_source_dir() / level_dir,
                    '--po_dir=' + meson.current_source_dir() / level_dir / 'po',
                    '--output_dir=' + output_dir,
                    '--signal_file=' + signal_file,
                ],
                output: signal_file_name,
                depend_files: input_files + po_files + _process_translations_script
            )

            foreach file : english_help_files
                if file != '' and file.startswith(level_dir)
                    install_data(file, install_dir: LEVEL_INSTALL_DATA_DIR / level_dir / 'help')
                endif
            endforeach

            meson.add_install_script(
                python3_exe,
                meson.project_source_root() / 'install_generated_files.py',
                output_dir,
                LEVEL_INSTALL_DATA_DIR / level_dir
            )

            install_subdir(
                level_dir,
                install_dir: LEVEL_INSTALL_DATA_DIR / chapter_dir,
                exclude_directories: ['help', 'po'],
                exclude_files: [ 'scene.txt' ]
            )

        endforeach

        install_subdir(
            chapter_dir,
            install_dir: LEVEL_INSTALL_DATA_DIR / category_dir,
            exclude_directories: exclude_levels,
            exclude_files: [ 'chaptertitle.txt' ]
        )
    endforeach

    install_subdir(
        category_dir,
        install_dir: LEVEL_INSTALL_DATA_DIR,
        exclude_directories: exclude_chapters + 'po'
    )

endforeach

install_subdir('other', install_dir: LEVEL_INSTALL_DATA_DIR)
