project('colobot', ['c', 'cpp'], default_options: [
    'cpp_std=c++17'
])

python3_exe = find_program('python3')

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

# TODO Get rid of boost
boost_dep = dependency('boost', modules : ['system', 'filesystem', 'regex'])

# TODO Use system lib if present
gtest_proj = subproject('gtest')
gtest_dep = gtest_proj.get_variable('gtest_dep')

hippomocks_proj = subproject('hippomocks')
hippomocks_dep = hippomocks_proj.get_variable('hippomocks_dep')

localename_proj = subproject('localename')
localename_dep = localename_proj.get_variable('localename_dep')

colobot_data_proj = subproject('colobot-data', default_options: [
    f'install_data_dir=@COLOBOT_DATA_DIR@'
])

if cc.get_id() == 'msvc'
    # TODO Bigger stack size and other MSVC specific stuff
    subproject('wingetopt')

    deps += [ winegetopt_dep ]
endif

# TODO Doxygen

# TODO Maybe split into multiple libraries instead of one
subdir('src')

subdir('po')

subdir('test')
