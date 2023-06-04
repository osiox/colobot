# TODO Create separate mini-libs instead
_src = [
  '../common/logger.cpp',
  '../graphics/model/model.cpp',
  '../graphics/model/model_mesh.cpp',
  '../graphics/model/model_input.cpp',
  '../graphics/model/model_output.cpp',

  'convert_model.cpp'
]

executable(
    'convert_model',
    _src,
    include_directories: '..',
    dependencies: [ boost_dep ]
)
