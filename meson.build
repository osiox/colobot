project('colobot-gold', ['c', 'cpp'],
    version: '0.2.0',
    default_options: [
        'cpp_std=c++17'
    ]
)

python3_exe = find_program('python3')
git_exe_opt = find_program('git', required : false, disabler : true)

COLOBOT_VERSION_CODENAME = 'Gold'

OFFICIAL_RELEASE = false

PROJECT_VERSION = meson.project_version()

if OFFICIAL_RELEASE
    COLOBOT_VERSION_RELEASE_CODENAME = '-alpha'
    COLOBOT_VERSION_DISPLAY = f'@PROJECT_VERSION@@COLOBOT_VERSION_RELEASE_CODENAME@'
else
    COLOBOT_VERSION_RELEASE_CODENAME = '+alpha'

    COLOBOT_GIT_VERSION = ''

    _rev_parse_cmd = run_command(git_exe_opt, 'rev-parse', '--abbrev-ref', 'HEAD', check: false)
    if _rev_parse_cmd.returncode() == 0
        _git_branch = _rev_parse_cmd.stdout().strip()

        _rev_parse_cmd = run_command(git_exe_opt, 'rev-parse', '--short', 'HEAD', check: false)
        if _rev_parse_cmd.returncode() == 0
            _git_rev = _rev_parse_cmd.stdout().strip()
            COLOBOT_GIT_VERSION = f'@_git_branch@-r@_git_rev@'
        endif
    endif

    if COLOBOT_GIT_VERSION == ''
        COLOBOT_VERSION_DISPLAY = f'@COLOBOT_VERSION_CODENAME@-@COLOBOT_VERSION_RELEASE_CODENAME@'
    else
        COLOBOT_VERSION_DISPLAY = f'git-@COLOBOT_GIT_VERSION@'
        COLOBOT_VERSION_RELEASE_CODENAME = f'@COLOBOT_VERSION_RELEASE_CODENAME@-@COLOBOT_GIT_VERSION@'
    endif

endif

COLOBOT_VERSION_FULL = f'@PROJECT_VERSION@@COLOBOT_VERSION_RELEASE_CODENAME@'

# TODO Can't read env directly. Either get the env by calling shell or add meson option for this one
BUILD_NUMBER = 0

# TODO Windows and other platforms ??
COLOBOT_DATA_DIR = get_option('prefix') / get_option('datadir') / 'games' / 'colobot'
COLOBOT_I18N_DIR = get_option('prefix') / get_option('datadir') / 'locale'

# TODO Not sure about these... so think about it later
# TODO Other platforms
# TODO Tests - virtual if enabled, non-virtual otherwise
add_global_arguments(
    '-DNOEXCEPT=noexcept',
    '-DTEST_VIRTUAL=virtual',
    language: 'cpp'
)

cc = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')

cmake = import('cmake')
fs = import('fs')

opengl_dep = dependency('opengl', version: '>=1.4')
sdl2_dep = dependency('SDL2')
sdl2_image_dep = dependency('SDL2_image')
sdl2_ttf_dep = dependency('SDL2_ttf')
png_dep = dependency('PNG', version: '>=1.2')
physfs_dep = dependency('physfs')
# TODO Optional static ??
glew_dep = dependency('glew')
# TODO Optional ???
openal_dep = dependency('openal')
sndfile_dep = dependency('sndfile')
icu_uc_dep = dependency('icu-uc')

# TODO Switch to c++20 and use built-in span ? (currently not used)
#gsl_dep = dependency('microsoft_gsl')

# TODO Use system lib if present (or does it work like that now?)
gtest_dep = dependency('gtest')

hippomocks_dep = dependency('hippomocks')

simpleini_dep = dependency('simpleini')

localename_proj = subproject('localename')
localename_dep = localename_proj.get_variable('localename_dep')

colobot_data_proj = subproject('colobot-data', default_options: [
    f'install_data_dir=@COLOBOT_DATA_DIR@'
])

if cc.get_id() == 'msvc'
    # TODO Bigger stack size and other MSVC specific stuff
    wingetopt_dep = dependency('wingetopt')

    deps += [ winegetopt_dep ]
endif

# TODO Doxygen

# TODO Maybe split into multiple libraries instead of one
subdir('src')

subdir('po')

subdir('test')
