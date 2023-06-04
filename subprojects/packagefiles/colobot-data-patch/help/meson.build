# Not sure if ideal, but should do exactly the same thing as the original cmake did
# Warning!
#   File wildcards (globbing) are used in this file.
#   This is discouraged by everyone, including CMake and Meson teams!

HELP_INSTALL_DATA_DIR = INSTALL_DATA_DIR / 'help'

categories = {
    'bots': 'object',
    'cbot': 'cbot',
    'generic': '',
    'object': 'object',
    'programs': 'programs'
}

foreach category_dir, category_install_subdir : categories

    # Always install english
    c = run_command(python3_exe,
        meson.project_source_root() / 'grabber.py', category_dir / 'E' / '*',
        check: true
    )
    english_help_files = c.stdout().strip().split('\n')

    foreach file : english_help_files
        if (file != '')
            install_data(file, install_dir: HELP_INSTALL_DATA_DIR / 'E' / category_install_subdir)
        endif
    endforeach

    if get_option('translations')
        # XXX Previously, these were generated in help-po subdir, but I do not think it was necessary ?
        #     So lets generate in the default dir - 'help' dir
        output_dir = meson.current_build_dir() / category_dir

        output_subdir_arg = '--output_subdir='

        if category_install_subdir != ''
            output_subdir_arg = '--output_subdir=' + category_install_subdir
        endif

        list_translation_files_cmd = run_command(
            python3_exe,
            meson.project_source_root() / 'i18n-tools/scripts/process_translations.py',
            '--mode=print_files',
            '--type=help',
            '--input_dir=' + meson.current_source_dir() / category_dir,
            '--po_dir=' + meson.current_source_dir() / category_dir / 'po',
            '--output_dir=' + output_dir,
            output_subdir_arg,
            check: true
        )

        translation_files = list_translation_files_cmd.stdout().strip().split('\n')
        input_files = translation_files[0].split('\n')[0].split(';')
        # We do not really need it, we just generate and install
        #output_files = translation_files[1].split('\n')[0].split(';')

        # dummy file to indicate success
        signal_file_name = category_dir + '_done'
        signal_file = meson.current_build_dir() / signal_file_name
        find_po_files_cmd = run_command(python3_exe,
            meson.project_source_root() / 'grabber.py', category_dir / 'po' / '*',
            check: true
        )
        po_files = find_po_files_cmd.stdout().strip().split('\n')

        _process_translations_script = meson.project_source_root() / 'i18n-tools/scripts/process_translations.py'
        generate_translations_target = custom_target(
            'generate_translate_files_' + category_dir,
            build_by_default: true,
            command: [
                python3_exe,
                _process_translations_script,
                '--mode=generate',
                '--type=help',
                '--input_dir=' + meson.current_source_dir() / category_dir,
                '--po_dir=' + meson.current_source_dir() / category_dir / 'po',
                '--output_dir=' + output_dir,
                output_subdir_arg,
                '--signal_file=' + signal_file,
            ],
            output: signal_file_name,
            depend_files: input_files + po_files + _process_translations_script
        )

        meson.add_install_script(
            python3_exe,
            meson.project_source_root() / 'install_generated_files.py',
            output_dir,
            HELP_INSTALL_DATA_DIR
        )

    endif

endforeach
