_src = [
    'main.cpp',
    'app/app_test.cpp',
    'CBot/CBot_test.cpp',
    'CBot/CBotFileUtils_test.cpp',
    'CBot/CBotToken_test.cpp',
    'common/config_file_test.cpp',
    'common/timeutils_test.cpp',
    'graphics/engine/lightman_test.cpp',
    'math/func_test.cpp',
    'math/geometry_test.cpp',
    'math/matrix_test.cpp',
    'math/vector_test.cpp'
]

_test_files = [
    'common/colobot.ini'
]

_out_test_files = []

foreach test_file : _test_files
    _out_test_files += fs.copyfile(test_file)
endforeach

_extra_test_files = declare_dependency(sources: _out_test_files)

colobot_ut_test = executable(
    'colobot_ut',
    cpp_args: [ '-DGTEST_HAS_TR1_TUPLE=0', '-Wno-suggest-override'], # TODO If gcc ?
    sources: _src,
    include_directories: '.',
    dependencies: [ _extra_test_files, gtest_dep, int_libcolobotbase_dep, hippomocks_dep ]
)

test('Colobot_ut Tests', colobot_ut_test, protocol: 'gtest', workdir: meson.current_build_dir())
